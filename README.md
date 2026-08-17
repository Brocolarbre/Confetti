# Confetti

Confetti is a high-performance data-driven deterministic C++ particle engine.

The rendering system is written with **OpenGL**. The simulation uses **CPU multithreading** for performance.
The engine takes the form of a **C++ library** and can be integrated in existing OpenGL applications.

## Design

The engine is :

**data-driven** : anything the engine is able to do do can be described in a configuration file.
Confetti translates this into a JSON file format. The user can either create the assets in the code, or load a JSON file with an equivalent description.

**deterministic** : running the same simulation multiple times produces the same result. The determinism is global : changing any random-based effect of the simulation does not affect the other effects, regardless of order. This is also the case on different machines.

**optimized for performance** : the simulation stores particle data as a structure of arrays (SoA idiom).
Particles, trails and ribbons update is performed with CPU parallelization through multithreading.

**user-friendly** : the data-driven representation allows for a very expressive system that does not require any code, other than creating the assets or loading the JSON file. The effects are created using a declarative system, effectively separating artistic authoring from the engine's complexity.

**expressive** : effects are made of many tools and parameters, some being optional. This gives a lot of customization options and a very high amount of effects for the user to compose.

## Terminology

**Particle** : a primitive that is simulated and rendered\
**Particle emitter** : an object that spawns particles\
**Particle effect** : an object that describes which emitters to spawn and when\
**Trail** : a primitive attached to a particle\
**Ribbon** : a primitive connecting two particles

## Usage

The usage workflow is as follows :
- Create a `ParticleSystem` instance.
- Fill the particle system's asset registry
- Load renderers' resources from the asset registry
- Play particle effects when desired

To use Confetti in your project, you need to include the `Confetti/Confetti.hpp` header file. The entire library resides inside the `cft` namespace.

The main class is `ParticleSystem`, it holds the simulation, renderers and assets.
The simulation is updated and rendered with the `ParticleSystem::update` and `ParticleSystem::render` methods.
These methods take a `cft::View`, containing camera information filled by the user. The camera implementation itself is up to the user.

The update method takes a delta time parameter. The fixed framerate managment is handled by Confetti and the delta time itself is provided by the user.

Here is an example :
```c++
#include <Confetti/Confetti.hpp>

cft::ParticleSystem particleSystem;

void update()
{
    float deltaTime = /* ... */;
    cft::View view = /* ... */;

    particleSystem.update(deltaTime, view);
    particleSystem.render(view);
}
```

To integrate the engine's result in your own application, the `ParticleSystem::getRendererOutputTextureId` method returns a handle to the OpenGL output texture id.

Filling the asset registry and loading the renderer assets can be done with a JSON file or with code.
The assets use an id system. Assets that depend on other assets specify the corresponding asset id. The id must be unique per asset type (two force fields can not have the same id but a force field and a motion behavior can have the same id).

### JSON loading

To load a JSON file, do `JsonLoader::initialize`, then `JsonLoader::load`.\
The `initialize` method takes a provider registry. The reason is that some effects have dynamic parameters provided by the user in the form of a `std::function` that is called by the effects at evaluation.\
This allows effects to use changing values that originate from the user's application (such as following a target or varying intensity depending on a specific variable).\
As this can not be represented in a JSON file, the file instead stores a provider name.
This provider name is used as a key by the engine to query the provider registry. The user has to fill the provider registry with all the provider methods used by the effects before loading the json file.

```c++
cft::ProviderRegistry providerRegistry;
providerRegistry.registerProvider<glm::vec3>("mouseCursor", [this]() { return glm::vec3(m_worldSpaceMousePosition, 0.0f); }); // example provider

cft::JsonLoader::initialize(providerRegistry);
cft::JsonLoader::load("file.json", m_particleSystem);
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

particleSystem.loadBillboardRendererTextures({ "image.png" }, 100, 100);
```

Use the corresponding add method for the asset you need.

### Force fields

Force fields allow to modify particle emitters and particles motion state by applying a linear and angular velocity acceleration.
The nature of the acceleration depends on the active force fields and their parameters.
Some force fields use a `SpatialInfluence` to support additional parameters such as an effect radius and a strength falloff.
Here are the available force fields :
- Attraction
- Directional
- FollowTarget
- LinearDrag
- Orbit
- QuadraticDrag
- Repulsion
- ShockWave
- Turbulence
- Vortex
- Wind

The force fields can be found in the `Confetti/Behavior/Force/` folder.
The user can implement additional force fields by implementing the `ForceField` interface.

### Motion behaviors

Motion behaviors allow to modify particle emitters and particles position by applying a position offset.
Just like force fields, multiple motion behaviors can be applied at once.
Note that while the position resulting from the offset affects rendering and trail spawning, the offset itself does not override force fields contribution.
The motion behavior can be seen as an additional absolute offset applied to the object on top of force fields.
Here are the available motion behaviors :
- Circle
- FigureEight
- Jitter
- Orbit
- Oscillation
- Path
- Segment
- SnapTarget
- Spiral

The motion behaviors can be found in the `Confetti/Behavior/Motion/` folder.
The user can implement additional motion behaviors by implementing the `MotionBehavior` interface.

### Visual behaviors

Visual behaviors allow to modify particles appearance by modifying their color and scale.
Multiple visual behaviors can be applied at once.
Visual behaviors can drastically improve the appearance of particle effects.
Here are the available visual behaviors :
- ColorShift
- DimOut
- FadeIn
- FadeOut
- Flicker
- GrowIn
- Pulse
- ShrinkOut
- SmoothColorShift
- SquashStretch

The visual behaviors can be found in the `Confetti/Behavior/Visual/` folder.
The user can implement additional visual behaviors by implementing the `VisualBehavior` interface.

### Particle spawners and attribute generators

Particle emitters use a particle spawner to describe the initial attributes of the spawned particles.
Particle spawners use attribute generators to spawn particles.

#### Generic generators

Confetti's attribute generator system is flexible : the same generic attribute generators can be used to generate any attribute type.
For instance, this means that the position and velocity attribute can be generated by the same generator.

Here are the available generic attribute generators :
- Constant
- InterpolatedRandomSet
- Linear
- Random
- RandomSet
- Time
- WeightedRandomSet

The generic attribute generators can be found in the `Confetti/Emission/AttributeGenerator/Generic/` folder.
The user can implement additional generic attribute generators by implementing the `AttributeGenerator` interface.

#### Specialized generators

While generic generators provide a way to cover most generation cases, more specific attribute generation logic can be needed.
Specialized generators serve that purpose. The cannot be used for attributes of different types.
Here are the available specialized attribute generators :
- BrightnessColor
- NormalBurstLinearVelocity
- NormalLinearVelocity
- RandomNormalOffsetPosition
- ValueStrength

The specialized attribute generators can be found in the `Confetti/Emission/AttributeGenerator/Specialized/` folder.
The user can implement additional specialized attribute generators by implementing the `AttributeGenerator` interface.

#### Spawn shapes

The `ParticleSpawner` class constructor has a variant that replaces the position attribute generator with a `SpawnShape`.
A spawn shape generates positions according to a shape. It differs from a position attribute generator because it also provides a normal alongside the position through the `SpawnContext` structure.
Some of the specialized attribute generators use the spawn context to generate the values. It is up to the user to ensure that an appropriate spawn shape is used when using any specialized attribute generators that needs a spawn context. Otherwise, a default-generated spawn context is used.
Here are the available spawn shapes :
- Circle
- Cone
- ConeVolume
- Cylinder
- CylinderVolume
- Disk
- Sphere
- SphereVolume

### Emission patterns

To describe how many and how often particles are spawned, particle emitters use an emission pattern.
Emission patterns have a significant impact on an emitter contribution to the particle effect.
Here are the available emission patterns :
- ConstantRate
- FixedBurst
- LinearBurst
- LinearRate
- PeriodicBurst
- RandomRate
- SingleBurst

The emission patterns can be found in the `Confetti/Emission/EmissionPattern/` folder.
The user can implement additional emission patterns by implementing the `EmissionPattern` interface.

## Future improvements

### GPU acceleration

The data-driven design and CPU optimization were the core principles during developpement.
Particle engines benefit a lot from GPU acceleration. Confetti aims to support GPU parallelism in the future.
This would allow to greatly improve performance as the heavy simulation work would be hardware accelerated.
Once simulation data is updated, it could be directly converted to render data by the GPU to avoid a CPU sendback.
The GPU acceleration would be performed with OpenGL compute shaders.

### Vulkan

The rendering system uses modern OpenGL features, yet could benefit from a Vulkan rewrite.
Concepts like triple buffering, pre-compiled shaders and frames in flight would improve performance.

## Test application

**LineWeaverTest** is a test application that you can use to try the library with ease. It implements a window with an OpenGL context, as well as drag and drop for JSON files.

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