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

**Asset** : a resource used by the engine (particle effect, force field, image...)
**Particle** : a primitive that is simulated and rendered\
**Particle emitter** : an object that spawns particles\
**Particle effect** : an object that describes which emitters to spawn and when\
**Trail** : a primitive attached to a particle\
**Ribbon** : a primitive connecting two particles

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
Note that if you want to load files multiple times, you should call `JsonLoader::clear` each time.

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
- **color** : vec4 (rgba color channels)
- **position** : vec3
- **rotation** : quaternion
- **scale** : vec3
- **linear** velocity : vec3
- **angular** velocity : vec3
- **phase** : an arbitrary float value used by the assets to introduce variation between particles (offset, range, strength factor...)
- **lifetime** : float (in seconds)

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

Note that any user-defined asset is not supported in the JSON loader.

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