# Confetti

Confetti is a high-performance data-driven deterministic C++ particle engine.

The rendering system is written with **OpenGL**. The simulation uses **CPU multithreading** for performance.
The engine takes the form of a **C++ library** and can be integrated in existing OpenGL applications.

## Design

The engine is :

**data-driven** : anything the engine is able to do do can be described in a configuration file.
Confetti translates this into a JSON file format. The user can either create the assets in the code, or load a JSON file with an equivalent description.

**deterministic** : running the same simulation multiple times produces the same result. The determinism is global : changing any random-based asset of the simulation does not affect the other assets, regardless of order. This is also the case on different machines.

**optimized for performance** : the simulation stores particle data as a structure of arrays (SoA idiom).
Particles, trails and ribbons update is performed with CPU parallelization through multithreading.

**user-friendly** : the data-driven representation allows for a very expressive system that does not require any code, other than creating the assets or loading the JSON file. The assets are created using a declarative system, effectively separating artistic authoring from the engine's complexity.

**expressive** : assets are made of many tools and parameters, some being optional. This gives a lot of customization options and a very high amount of effects for the user to compose.

## Terminology

**Asset** : a resource used by the engine (particle effect, force field, image...)\
**Particle** : a primitive that is simulated and rendered\
**Particle emitter** : an object that spawns particles\
**Particle effect** : an object that describes which emitters to spawn and when\
**Trail** : a primitive attached to a particle\
**Ribbon** : a primitive connecting two particles\
**Descriptor** : a data structure filled once and used to instantiate the object it describes\
**Instance** : a runtime object managed by the simulation instantiated from a descriptor

## Usage

The usage workflow is as follows :
- Create a `ParticleSystem` instance.
- Fill the particle system's asset registry
- Load renderer's resources from the asset registry
- Play particle effects when desired

To use Confetti in your project, you need to include the `Confetti/Confetti.hpp` header file. The entire library resides inside the `cft` namespace.

The main class is `ParticleSystem`, it holds the simulation, renderer and assets.\
The simulation is updated and rendered with the `ParticleSystem::update` and `ParticleSystem::render` methods.\
These methods take a `cft::View`, containing camera information **filled by the user**. The camera implementation itself is up to the user.

The update method takes a delta time parameter.\
The **fixed framerate** managment is handled by Confetti and the delta time itself is **provided by the user**. This means the user can pass a variable delta time and the engine makes sure the simulation remains stable with an internal fixed framerate.

Here is an example :
```c++
#include <Confetti/Confetti.hpp>

cft::ParticleSystem particleSystem;

void update()
{
    float deltaTime = /* time since last frame */;
    cft::View view = /* camera information */;

    particleSystem.update(deltaTime, view);
    particleSystem.render(view);
}
```

To integrate the engine's result in your own application, the `ParticleSystem::getRendererOutputTextureId` method returns a **handle** to the OpenGL output texture id.

Filling the asset registry and loading the renderer assets can be done with a JSON file or with code.
The assets use an **id system**. Assets that depend on other assets specify the corresponding asset id. The id must be **unique per asset type** (two force fields cannot have the same id but a force field and a motion behavior can have the same id).

### JSON loading

To load a JSON file, do `JsonLoader::initialize`, then `JsonLoader::load`.\
The `initialize` method takes a provider registry. The reason is that some assets have **dynamic parameters** provided by the user in the form of a `std::function` that is called by the assets at evaluation.\
This allows assets to use changing values that originate from the user's application (such as following a target or varying intensity depending on a specific variable).\
As this cannot be represented in a JSON file, the file instead stores a **provider name**.
This provider name is used as a key by the engine to query the provider registry. The user has to fill the provider registry with all the provider methods used by the assets **before** loading the json file.

```c++
cft::ProviderRegistry providerRegistry;
providerRegistry.registerProvider<glm::vec3>("mouseCursor", [this]() { return glm::vec3(worldSpaceMousePosition, 0.0f); }); // example provider

cft::JsonLoader::initialize(providerRegistry);
cft::JsonLoader::load("file.json", particleSystem);
```

Here is the structure of a minimal JSON file with no assets :
```json
{
    "seed": 0,
    "billboardRendererImages": null,
    "pathRendererImages": null,
    "meshRendererImageIds": [],
    "meshRendererModelIds": [],
    "assets": {
        "forceFields": [],
        "motionBehaviors": [],
        "visualBehaviors": [],
        "particleSpawners": [],
        "emissionPatterns": [],
        "particleLinkers": [],
        "ribbonGenerators": [],
        "images": [],
        "models": [],
        "spriteSheetDescriptors": [],
        "particleEffectDescriptors": [],
        "particleEmitterDescriptors": []
    }
}
```

You can find example JSON files in the `ConfettiTest/res/systems/` folder.
Note that if you want to load files multiple times, you should call `JsonLoader::clear` each time.\
Any asset attribute with the "(optional)" mention means it can be specified as "null" is the JSON file.\
The enumeration values are represented as string literals.

### Code

To load the simulation, use the asset registry stored in the `ParticleSystem` instance.
Then, call the loading methods by giving the ids of the resources to load.

```c++
#include <Confetti/Behavior/Force/DirectionalForceField.hpp>

cft::AssetRegistry& assetRegistry = particleSystem.getAssetRegistry();

assetRegistry.addForceField(0, std::make_unique<cft::DirectionalForceField>(glm::vec3(0.0f, -1.0f, 0.0f), 9.81f));
assetRegistry.addMotionBehavior(0, std::make_unique<cft::CircleMotionBehavior>(glm::vec3(0.0f, 0.0f, 1.0f), 2.0f, 1.0f));
assetRegistry.addVisualBehavior(0, std::make_unique<cft::FadeInVisualBehavior>(cft::ParticleTime::absolute(0.25f)));
assetRegistry.addParticleSpawner(0, std::make_unique<cft::ParticleSpawner>(/* ... */));
assetRegistry.addEmissionPattern(0, std::make_unique<cft::PeriodicBurstEmissionPattern>(150, 0.5f));
assetRegistry.addImage(0, /* ... */);
assetRegistry.addModel(0, /* ... */);
assetRegistry.addParticleLinker(0, std::make_unique<cft::ChainParticleLinker>(/* ... */));
assetRegistry.addRibbonGenerator(0, std::make_unique<cft::SegmentRibbonGenerator>());
assetRegistry.addSpriteSheetDescriptor(0, /* ... */);
assetRegistry.addParticleEffectDescriptor(0, /* ... */);
assetRegistry.addParticleEmitterDescriptor(0, /* ... */);

particleSystem.getParticleRenderer().loadBillboardRendererTextures(assetRegistry, { 0, 1 }, 100, 100);
particleSystem.getParticleRenderer().loadMeshRendererMeshes(assetRegistry, { 0 });
particleSystem.getParticleRenderer().loadMeshRendererTextures(assetRegistry, { 2 });
particleSystem.getParticleRenderer().loadPathRendererTextures(assetRegistry, { 3, 4 }, 120, 120);
```

Use the corresponding add method for the asset you need.\
Note that the path renderer refers to both trains and ribbons.

#### Clearing

`ParticleSystem::clear` resets simulation data. It **does not** reset asset registry data.\
To reset asset registry data, `ParticleSystem::getAssetRegistry` and `AssetRegistry::clear` can be used.

## Assets

The engine uses different asset types, each with a distinct purpose and representation. Below is a description of each asset type, along with its JSON representation.

### Force fields

Force fields allow to modify particle emitters and particles **motion state** by applying a linear and angular velocity **acceleration**.
The nature of the acceleration depends on the active force fields and their parameters.
Some force fields use a `SpatialInfluence` to support additional parameters such as an effect radius and a strength falloff.
Here are the available force fields :
- **Attraction** : moves the object toward the origin of the spatial influence
- **Directional** : moves the object in a constant direction
- **FollowTarget** : moves the object toward a dynamic target using the mass–spring–damper equation
- **LinearDrag** : slows the object down linearly
- **Orbit** : orbits the object around the origin of the spatial influence given an axis
- **QuadraticDrag** : slows the object down quadratically
- **Repulsion** : moves the object away from the origin of the spatial influence
- **ShockWave** : moves the object away from the origin of the spatial influence given an axis when it is close to a cylindrical wavefront
- **Turbulence** : randomly moves the object around
- **Vortex** : moves the object spin around an axis while pulling it toward the axis
- **Wind** : slows down or fastens up the object depending on its velocity relative to the wind direction and strength

The force fields can be found in the `Confetti/Behavior/Force/` folder.
The user can implement additional force fields by implementing the `ForceField` interface.

### Motion behaviors

Motion behaviors allow to modify particle emitters and particles **position** by applying a position **offset**.
Just like force fields, multiple motion behaviors can be applied at once.
Note that while the position resulting from the offset affects rendering and trail spawning, the offset itself **does not override** force fields contribution.
The motion behavior can be seen as an additional **absolute offset** applied to the object on top of force fields.
Here are the available motion behaviors :
- **Circle** : moves the object in a circular fashion
- **FigureEight** : moves the object in the shape of an eight
- **Jitter** : randomly moves the object around
- **Orbit** : orbits the object around an origin given an axis
- **Oscillation** : repeatedly moves the object from a source to a destination
- **Path** : moves the object along a path
- **Segment** : moves the object from a source to a destination
- **SnapTarget** : snaps the object's position on a dynamic target
- **Spiral** : moves the object in a spiral fashion

The motion behaviors can be found in the `Confetti/Behavior/Motion/` folder.
The user can implement additional motion behaviors by implementing the `MotionBehavior` interface.

### Visual behaviors

Visual behaviors allow to modify particles **appearance** by modifying their **color and scale**.
Multiple visual behaviors can be applied at once.
Visual behaviors can drastically improve the appearance of particles.
Here are the available visual behaviors :
- **ColorShift** : sets the particle's color over time according to a color palette
- **DimOut** : lowers the particle's color brightness until it reaches zero given a duration
- **FadeIn** : increases the particle's opacity until it reaches its initial value given a duration
- **FadeOut** : lowers the particle's opacity until it reaches zero given a duration
- **Flicker** : lowers and increases the particle's color brightness repeatedly given a minimum and maximum strength
- **GrowIn** : increases the particle's scale until it reaches its initial value given a duration
- **Pulse** : interpolates the particle's color over time between two colors
- **ShrinkOut** : lowers the particle's scale until it reaches zero given a duration
- **SmoothColorShift** : sets the particle's color over time according to a color palette with smooth interpolation
- **SquashStretch** : lowers and increases the particle's scale repeatedly according to the squash and stretch animation principle

The visual behaviors can be found in the `Confetti/Behavior/Visual/` folder.
The user can implement additional visual behaviors by implementing the `VisualBehavior` interface.

### Particle spawners and attribute generators

Particle emitters use a particle spawner to describe the **initial attributes** of the spawned particles.
Particle spawners use **attribute generators** to spawn particles.

Here are the particle attributes generated by particle spawners :
- **color** (vec4) : rgba color channels
- **position** (vec3)
- **rotation** (quaternion)
- **scale** (vec3)
- **linear velocity** (vec3)
- **angular velocity** (vec3)
- **phase** (float) : an arbitrary value used by the assets to introduce variation between particles (offset, range, strength factor...)
- **lifetime** (float) : in seconds

The above representation applies to both billboard and mesh particles. The only difference with billboards is that the rotation only accounts for roll (z component in Euler angles representation), and the scale only accounts for the first two components (xy).

#### Generic generators

Confetti's attribute generator system is flexible : the same generic attribute generators can be used to generate **any attribute type**.
For instance, this means that the position and velocity attribute can be generated by the same generator.

Here are the available generic attribute generators :
- **Constant** : generates the same value for all the particles
- **InterpolatedRandomSet** : picks a random value in the set for each particle with smooth interpolation
- **Linear** : generates values ranging linearly from a source to a destination value
- **Random** : generates random values between a minimum and a maximum value
- **RandomSet** : picks a random value in the set for each particle
- **Time** : generates values ranging linearly from a source to a destination value according to specific time points
- **WeightedRandomSet** : picks a random value in the set for each particle with weighted probabilities

The generic attribute generators can be found in the `Confetti/Emission/AttributeGenerator/Generic/` folder.
The user can implement additional generic attribute generators by implementing the `AttributeGenerator` interface.

#### Specialized generators

While generic generators provide a way to cover most generation cases, **more specific** attribute generation logic can be needed.
Specialized generators serve that purpose. The cannot be used for attributes of different types.
Here are the available specialized attribute generators :
- **BrightnessColor** : generates color and strength with user-specified generators and multiplies the color's rgb components with the strength
- **NormalBurstLinearVelocity** : generates linear velocity according to the normal and a random offset (requires a spawn shape)
- **NormalLinearVelocity** : generates linear velocity according to the normal (requires a spawn shape)
- **RandomNormalOffsetPosition** : generates position along the normal with a random offset (requires a spawn shape)
- **ValueStrength** : generates three-component values and strength values with user-specified generators and multiplies the three-component value with the strength

The specialized attribute generators can be found in the `Confetti/Emission/AttributeGenerator/Specialized/` folder.
The user can implement additional specialized attribute generators by implementing the `AttributeGenerator` interface.

#### Spawn shapes

The `ParticleSpawner` class constructor has an overload that replaces the position attribute generator with a `SpawnShape`.
A spawn shape generates positions **according to a shape**. It differs from a position attribute generator because it also provides a normal alongside the position through the `SpawnContext` structure.
Some of the specialized attribute generators use the spawn context to generate the values. It is up to the user to ensure that an appropriate spawn shape is used when using any specialized attribute generators that needs a spawn context. Otherwise, a default-generated spawn context is used.
Here are the available spawn shapes :
- **Circle** : generates spawn contexts in the shape of a circle
- **Cone** : generates spawn contexts in the shape of a cone surface
- **ConeVolume** : generates spawn contexts in the shape of a circle volume
- **Cylinder** : generates spawn contexts in the shape of a cylinder surface
- **CylinderVolume** : generates spawn contexts in the shape of a cylinder volume
- **Disk** : generates spawn contexts in the shape of a circle surface
- **Sphere** : generates spawn contexts in the shape of a sphere surface
- **SphereVolume** : generates spawn contexts in the shape of a sphere volume

### Emission patterns

To describe **how many** and **how often** particles are spawned, particle emitters use an emission pattern.
Emission patterns have a significant impact on an emitter's overall appearance.
Here are the available emission patterns :
- **ConstantRate** : spawns particles at a constant rate where rate is the number of particles per second
- **FixedBurst** : spawns a fixed number of particles a fixed number of times at a fixed interval
- **LinearBurst** : spawns a fixed number of particles at a varying interval
- **LinearRate** : spawns particles at a varying rate
- **PeriodicBurst** : spawns a fixed number of particles at a fixed interval
- **RandomRate** : spawns particles at a random rate
- **SingleBurst** : spawns a fixed number of particles once

The emission patterns can be found in the `Confetti/Emission/EmissionPattern/` folder.
The user can implement additional emission patterns by implementing the `EmissionPattern` interface.

### Link rules

Link rules are here to determine whether a connection between two particles is possible in the context of ribbon generation.
The user provides the particle linkers with link rules, which are given the appropriate parameters to ensure the desired connections are created and removed during simulation.
Here are the available link rules :
- **AgeSimilarity** : allow connection for particles that have a similar age according to a threshold
- **ColorSimilarity** : allow connection for particles that have a similar color according to a threshold
- **Connection** : prevents connection for particles that already have a certain amount of connections
- **Distance** : allow connection for particles that are within a specific distance range of each other
- **PhaseSimilarity** : allow connection for particles that have a similar phase according to a threshold
- **VelocitySimilarity** : allow connection for particles that have a similar velocity according to a threshold

The link rules can be found in the `Confetti/Simulation/Link/LinkRule/` folder.
The user can implement additional link rules by implementing the `LinkRule` interface.

### Particle linkers

Particle linkers connect particles together in order to create ribbons.
They use a selection algorithm and decice which particles should be connected while respecting the link rules.
Here are the available particle linkers :
- **Chain** : particles are sorted by spawn time and connected in a chain
- **KNearestNeighbor** : each particle is connected to its k nearest neighbors
- **NearestNeighbor** : each particle is connected to all its neighbors sorted by distance
- **Origin** : particles are connected to the closest particle to an origin
- **Random** : particles are randomly connected
- **Target** : particles are connected to the particle with a specific id

The particle linkers can be found in the `Confetti/Simulation/Link/ParticleLinker/` folder.
The user can implement additional particle linkers by implementing the `ParticleLinker` interface.

### Ribbon generators

Ribbon generators define the appearance of a connection between two particles.
They generate a list of points that are later used to generate ribbon geometry.
Here are the available ribbon generators :
- **Path** : the connection takes the shape of a path by interpolating control points
- **Segment** : the connection takes the shape of a straight line
- **Spiral** : the connection takes the shape of a spiral
- **Wave** : the connection takes the shape of a wave

The ribbon generators can be found in the `Confetti/Simulation/Link/RibbonGenerator/` folder.
The user can implement additional ribbon generators by implementing the `RibbonGenerator` interface.

Note that any user-defined asset is not supported in the JSON loader.

### Images

Images load and store the content of an image from a file or from memory with the `Image::loadFromFile` and `Image::loadFromMemory` methods.
They are used by the renderer to create textures for rendering.
The library uses `STB` to load images so the supported formats are the ones supported by this library.

Here is the JSON representation :
```json
{
    "id": 0,
    "path": "image.png"
}
```

### Models

Models load and store the content of a model from a file or from memory with the `Model::loadFromFile` and `Model::loadFromMemory` methods.
They are used by the renderer to create meshes for rendering.
The library uses `tinyobjloader` to load models so the supported formats is **.obj**.

Here is the JSON representation :
```json
{
    "id": 0,
    "path": "model.obj"
}
```

### Particle emitter descriptors

A particle emitter descriptor defines how a particle emitter instance behaves.
It is defined as :
- **poolId** : the particle pool in which the spawned particles are stored
- **particleSpawnerId** : the id of the particle spawner used by the particle emitter instance
- **emissionPatternId** : the id of the emission pattern used by the particle emitter instance
- **motionStateInheritance** : information on which motion state attributes are inherited by spawn particles and how
- **trailConfiguration** : trail behavior settings (optional)
- **ribbonConfiguration** : ribbon behavior settings (optional)
- **spawnTriggerDescriptor** : settings for particles that can spawn particle emitter instances (optional)
- **renderConfiguration** : how particles are rendered
- **forceFieldIds** : force fields applied to the spawned particles
- **motionBehaviorIds** : motion behaviors applied to the spawned particles
- **visualBehaviorIds** : visual behaviors applied to the spawned particles

Here is the JSON representation :
```json
{
    "id": 0,
    "poolId": 0,
    "particleSpawnerId": 0,
    "emissionPatternId": 0,
    "motionStateInheritance": {
        "position": true,
        "linearVelocityFactor": 1.0,
        "rotation": true,
        "angularVelocityFactor": 1.0
    },
    "trailConfiguration": null,
    "ribbonConfiguration": null,
    "spawnTriggerDescriptor": null,
    "renderConfiguration": {
        "renderType": "Mesh",
        "configurationData": {
            "modelId": 0,
            "imageId": 1
        }
    },
    "forceFieldIds": [ 1 ],
    "motionBehaviorIds": [ 0, 1 ],
    "visualBehaviorIds": [ 0, 3, 4 ]
}
```

#### Motion state inheritance

Motion state inheritance describes which particle emitter instance's motion state attributes the particles inherit from at spawn.
It is defined as :
- **position** : boolean, do particles spawn relative to their parent emitter's position, true most of the time
- **linearVelocityFactor** : float, to what extent do particle spawn with a linear velocity relative to their parent emitter's position
- **rotation** : boolean, do particles spawn relative to their parent emitter's position
- **angularVelocityFactor** : float, to what extent do particle spawn with an angular relative to their parent emitter's position

Here is the JSON representation :
```json
{
    "position": true,
    "linearVelocityFactor": 1.0,
    "rotation": true,
    "angularVelocityFactor": 1.0
}
```

#### Trail configuration

A trail configuration describes the appearance and behavior of particle trails.
It is defined as :
- **presistenceLifetime** (float) : how long the trail stays alive after its owner particle died
- **minimumSpawnDistance** (float) : the minimum distance the owner particle must have moved before adding a new point to the trail
- **maximumSpawnTime** (float, optional) : the maximum time the trail can wait before adding a new point (this is a safeguard that overrides the minimum spawn distance attribute)
- **maximumSegmentCount** (unsigned int, optional) : the maximum number of segments in the trail (oldest ones are truncated)
- **pathConfiguration** : the appearance and behavior of the path itself

Here is the JSON representation :
```json
{
    "persistenceLifetime": 0.0,
    "minimumSpawnDistance": 0.05,
    "maximumSpawnTime": null,
    "maximumSegmentCount": null,
    "pathConfiguration": {
        "startThickness": 0.05,
        "endThickness": 0.05,
        "lifetime": 0.1,
        "lifetimeFade": null,
        "appendParticleColor": false,
        "colorGradient": [ { "r": 1.0, "g": 1.0, "b": 1.0, "a": 1.0 } ],
        "colorStart": null,
        "colorInterpolation": "Constant",
        "thicknessDistribution": "Linear",
        "thicknessEvolution": null,
        "image": null
    }
}
```

#### Ribbon configuration

A ribbon configuration describes the appearance and behavior of particle ribbons.
It is defined as :
- **pathConfiguration** : the appearance and behavior of the path itself
- **particleLinkerId** (unsigned int) : the id of the particle linker
- **ribbonGeneratorId** (unsigned int) : the id of the ribbon generator
- **ribbonPointCount** (unsigned int) : the number of points to create in each ribbon

Here is the JSON representation :
```json
{
    "pathConfiguration": {
        "startThickness": 0.05,
        "endThickness": 0.05,
        "lifetime": 0.1,
        "lifetimeFade": null,
        "appendParticleColor": false,
        "colorGradient": [ { "r": 1.0, "g": 1.0, "b": 1.0, "a": 1.0 } ],
        "colorStart": null,
        "colorInterpolation": "Constant",
        "thicknessDistribution": "Linear",
        "thicknessEvolution": null,
        "image": null
    },
    "": 0,
    "": 0,
    "": 35
}
```

#### Path configuration

A path configuration describes a path's appearance and behavior.
It is defined as :
- **startThickness** (float) : the thickness at the start of the path
- **endThickness** (float) : the thickness at the end of the path
- **lifetime** (float, optional) : the lifetime of the points
- **lifetimeFade** : the fading behavior of the points
- **appendParticleColor** (bool) : whether the particle's color should be appended to the color gradient (visual behaviors are taken into account)
- **colorGradient** : the color gradient used to color the trail
- **colorStart** (optional) : a list of distances at which each color start to be used
- **colorInterpolation** : how color should be interpolated between points
- **thicknessDistribution** : how thickness should be distributed along the path
- **thicknessEvolution** (optional) : how thickness should evolve over time
- **image** (optional) : the image that should be displayed on the path

#### Lifetime fade

Lifetime fade represents how a path should fade over its lifetime.
It is defined as :
- **start** (float) : the age at which the points' opacity starts to fade out
- **end** (float) : the age at which points's opacity reaches zero

Here is the JSON representation :
```json
{
    "start": 2.0,
    "end": 3.0
}
```

#### Color interpolation

`ColorInterpolation` is an enumeration representing how color is interpolated along a path. It can take the following values : **Constant**, **Linear**.

#### Thickness distribution

`ThicknessDistribution` is an enumeration representing how thickness is distributed along a path. It can take the following values : **Linear**, **Quadratic**.

#### Thickness evolution

Thickness evolution represents how a path's thickness evolves over time.
It is defined as :
- **distribution** : how the thickness distribution evolves over time
- **speed** : how fast the thickness evolves

Here is the JSON representation :
```json
{
    "distribution": "Constant",
    "speed": 1.5
}
```

#### Thickness evolution distribution

`ThicknessEvolutionDistribution` is an enumeration representing how thickness evolution is distributed along a path. It can take the following values : **Constant**, **Linear**, **Quadratic**.

#### Path image

Path image represents an image displayed on a path.
It is defined as :
- **imageId** : (unsigned int), the id of the image to display
- **repeatStretch** : (float, optional), the stretch factor at which the image is repeated

Here is the JSON representation :
```json
{
    "imageId": "0",
    "repeatStretch": 3.0
}
```

#### Spawn trigger descriptor

A spawn trigger descriptor defines how particles can instantiate particle emitter descriptors during simulation.
It is defined as :
- **maximumRecursionDepth** : the maximum number of recursive emitter spawns from the same particle emitter instance
- **spawnEmitterSpawnContext** : a particle emitter spawn context triggered when the particle spawns
- **deathEmitterSpawnContext** : a particle emitter spawn context triggered when the particle dies
- **periodicEmitterSpawnContext** : a particle emitter spawn context triggered periodically during the particle's lifetime

Here is the JSON representation :
```json
{
    "maximumRecursionDepth": 3,
    "spawnEmitterSpawnContext": null,
    "deathEmitterSpawnContext": {
        "emitterDescriptorId": 2,
        "timeRange": {
            "spawnTime": 0.0,
            "duration": 1.0
        },
        "initialMotionState": {
            "position": { "x": 0.0, "y": 0.0, "z": 0.0 },
            "linearVelocity": { "x": 0.0, "y": 0.0, "z": 0.0 },
            "rotation": { "x": 0.0, "y": 0.0, "z": 0.0 },
            "angularVelocity": { "x": 0.0, "y": 0.0, "z": 0.0 }
        },
        "forceFieldIds": [],
        "motionBehaviorIds": []
    },
    "periodicEmitterSpawnContext": null
}
```

#### Periodic spawn trigger context

A periodic spawn trigger context associates a particle emitter spawn context with a time interval.
It is defined as :
- **emitterSpawnContext** : the emitter spawn context to instantiate periodically
- **interval** : the time interval between each spawn trigger

Here is the JSON representation :
```json
{
    "emitterSpawnContext": {
        "emitterDescriptorId": 1,
        "timeRange": {
            "spawnTime": 0.0,
            "duration": 1.0
        },
        "initialMotionState": {
            "position": { "x": 0.0, "y": 0.0, "z": 0.0 },
            "linearVelocity": { "x": 0.0, "y": 0.0, "z": 0.0 },
            "rotation": { "x": 0.0, "y": 0.0, "z": 0.0 },
            "angularVelocity": { "x": 0.0, "y": 0.0, "z": 0.0 }
        },
        "forceFieldIds": [],
        "motionBehaviorIds": []
    },
    "interval": 0.1
}
```

#### Render configuration

A render configuration describes how particles are rendered.
It is defined as :
- **renderType** : the type of render primitive
- **configurationData** : the render primitive configuration data (different for each primitive type)

Here are the JSON representations :
```json
{
    "renderType": "Billboard",
    "configurationData": {
        "spriteSheetId": 0
    }
}
```

```json
{
    "renderType": "Mesh",
    "configurationData": {
        "modelId": 0,
        "imageId": 1
    }
}
```

#### Render type

`RenderType` is an enumeration representing the type of a render primitive. It can take the following values : **Billboard**, **Mesh**.
The render type value must match the provided configuration data type.

### Particle effect descriptors

A particle effect descriptor defines which particle emitter to spawn and when.
It is defined as :
- **emitterSpawnContexts** : a list of particle emitter spawn contexts

Here is the JSON representation :
```json
{
    "id": 0,
    "emitterSpawnContexts": []
}
```

#### Emitter spawn context

A particle emitter spawn context associates a particle emitter descriptor id with spawn information.
It is defined as :
- **emitterDescriptorId** : id of the particle emitter descriptor to use when spawning the particle emitter instance
- **timeRange** : spawn time and lifetime of the particle emitter instance
- **initialMotionState** : initial motion state of the particle emitter instance
- **forceFieldIds** : force fields applied to the particle emitter instance
- **motionBehaviorIds** : motion behaviors applied to the particle emitter instance

Here is the JSON representation :
```json
{
    "emitterDescriptorId": 0,
    "timeRange": {
        "spawnTime": 0.0,
        "duration": 1.0
    },
    "initialMotionState": {
        "position": { "x": 0.0, "y": 0.0, "z": 0.0 },
        "linearVelocity": { "x": 0.0, "y": 0.0, "z": 0.0 },
        "rotation": { "x": 0.0, "y": 0.0, "z": 0.0 },
        "angularVelocity": { "x": 0.0, "y": 0.0, "z": 0.0 }
    },
    "forceFieldIds": [ 0, 1 ],
    "motionBehaviorIds": [ 0 ]
}
```

#### Time range

A time range represents the spawn time and lifetime of an object.
It is defined as :
- **spawnTime** : time in seconds at which the object spawns
- **duration** : time in seconds the object remains alive

Here is the JSON representation :
```json
{
    "spawnTime": 0.0,
    "duration": 1.0
}
```

#### MotionState

A motion state represents the simulation state of a physical object.
It is defined as :
- **position** : vec3 position
- **linearVelocity** : vec3 linear velocity
- **rotation** : quaternion rotation
- **angularVelocity** : vec3 angular velocity

Here is the JSON representation :
```json
{
    "position": { "x": 0.0, "y": 0.0, "z": 0.0 },
    "linearVelocity": { "x": 0.0, "y": 0.0, "z": 0.0 },
    "rotation": { "x": 0.0, "y": 0.0, "z": 0.0 },
    "angularVelocity": { "x": 0.0, "y": 0.0, "z": 0.0 }
}
```

### Sprite sheet descriptors

A sprite sheet descriptor defines which image the sprite sheet uses and how it displays it.
It is defined as :
- **imageId** : id of the image to display
- **frameCount** : number of frames that make the sprite sheet animation (use 1 if the sprite is not animated)
- **rowFrameCount** : number of images per row (this allows frames to be organized into a grid, use 1 if the sprite is not animated)
- **frameWidth** : width of one frame in pixels (use the image total width if the sprite is not animated)
- **frameHeight** : height of one frame in pixels (use the image total height if the sprite is not animated)
- **animationSpeed** : speed at which the sprite sheet displays the next frame (use 0.0 if the sprite is not animated)

Here is the JSON representation :
```json
{
    "id": 0,
    "imageId": 0,
    "frameCount": 1,
    "rowFrameCount": 1,
    "frameWidth": 100,
    "frameHeight": 100,
    "animationSpeed": 0.0
}
```

### Renderer models and textures

The renderer needs to convert image and model data into texture and mesh data for rendering.\
The loading can be done by accessing the particle renderer with `ParticleSystem::getParticleRenderer` and using the appropriate methods :
- `ParticleRenderer::loadBillboardRendererTextures` : loads billboard renderer textures from the images (note that all the images given to this method need to have the same size, this allows to render every billboard particle in a single draw call by using texture arrays, which require all textures to have the same size)
- `ParticleRenderer::loadMeshRendererMeshes` : loads mesh renderer meshes from the models
- `ParticleRenderer::loadMeshRendererTextures` : loads mesh renderer textures from the images
- `ParticleRenderer::loadPathRendererTextures` : loads path (trails and ribbons) renderer textures from the images (the same size constraint also applies here but the size can be different than the billboard renderer texture size)

Here is the JSON representation, the `billboardRendererImages`, `pathRendererImages`, `meshRendererImageIds`  and `meshRendererModelIds` attributes resides in the root object of the JSON file :
```json
"billboardRendererImages": {
    "width": 100,
    "height": 100,
    "imageIds": [ 0 ]
},
"pathRendererImages": {
    "width": 120,
    "height": 120,
    "imageIds": [ 1, 2 ]
},
"meshRendererImageIds": [ 3 ],
"meshRendererModelIds": [ 4 ]
```

The `billboardRendererImages` and `pathRendererImages` attributes can be null.
The `meshRendererImageIds` and `meshRendererModelIds` attributes ban be empty.

### Seeds

The `ParticleSimulation` class stores a seed that is **global to the simulation** : changing this seed changes **every** random-asset result. More fine-grained seed control is possible everytime a **local seed attribute** is exposed. This allows to limit the random behavior change to a select few assets if needed.
The seed can be set by accessing the particle simulation with `ParticleSystem::getParticleSimulation` and using `ParticleSimulation::setSeed`.

Here is the JSON representation, this `seed` attribute resides in the root object of the JSON file :
```json
"seed": 0
```

## Future improvements

### GPU acceleration

The data-driven design and CPU optimization were the core principles during development.
Particle engines benefit a lot from GPU acceleration. Confetti aims to support GPU parallelism in the future.
This would allow to greatly improve performance as the heavy simulation work would be hardware accelerated.
Once simulation data is updated, it could be directly converted to render data by the GPU to avoid a CPU sendback.
The GPU acceleration would be performed with OpenGL compute shaders.

### Vulkan

The rendering system uses modern OpenGL features, yet it could benefit from a Vulkan rewrite.
Concepts like triple buffering, pre-compiled shaders and frames in flight would improve performance. The vulkan rewrite would be done after OpenGL GPU acceleration is proven efficient.

### Additional features

GPU acceleration would make space partitionning viable, which in turn would open the door to boid simulation and particle collision.
Space partitionning would also allow to improve performance for neighbor-based algorithms such as `KNearestNeighborParticleLinker`.

## Test application

**LineWeaverTest** is a test application that can be used to try the library with ease. It implements a window with an OpenGL context, as well as drag and drop for JSON files.

## Setup

The project follows the [Nest](https://github.com/Brocolarbre/Nest/) structure.
To build the project:
- Open a terminal in the **root folder** of the project
- Run the following command:
  - Windows : `.\scripts\windows\set_environment.bat` and `.\scripts\windows\set_workspace.bat`
  - Linux : `.\scripts\linux\set_environment.bat` and `./scripts/linux/set_workspace.sh`
- Windove is available [here](https://github.com/Brocolarbre/Windove/). Download the repository and follow the build setup instructions. Then copy the header and library files to the appropriate `Confetti/external/` subfolders.
- Open the project workspace
- Build the project

### Static and dynamic linkage

Any project that uses the the static version of the library shoud define the `CONFETTI_STATIC` macro.
To manually export the library as a shared library, the project should define the `CONFETTI_BUILD` macro.
Using the library as a static library requires to link the external dependencies of the library (as only a dynamic library or an executable can store static dependencies).
The dependencies are listed below, the library is guaranteed to work with the specified library versions. Replacing a library with another version may or may not work.

### External dependencies

The minimum required C++ version is **C++17**.

**Confetti** has the following external dependencies :
- GLAD
- GLM
- STB
- tinyobjloader
- nlohmann-json

**ConfettiTest** has the following external dependencies :
- [Windove](https://github.com/Brocolarbre/Windove/) (Windove uses GLFW so linking a static version of Windove requires linking GLFW)