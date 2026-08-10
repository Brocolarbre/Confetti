# Confetti

Confetti is a high-performance data-driven deterministic C++ particle engine.
The rendering system is written with OpenGL. The simulation uses CPU multithreading for performance.

## Design

The engine is **data-driven**. This means that anything the engine is able to do do can be described in a configuration file.
Confetti translates this in a JSON file format. The user can either create the assets in the code, or load a JSON file that describes them.

The engine is **deterministic**. Running the same simulation multiple times produces the same result. The determinism is global : changing any random-based effect of the simulation does not affect the other effects, regardless of order. This is also the case on different machines.

The engine is **optimized for performance**. The simulation stores particle data as a structure of arrays (SoA idiom).
Particles, trails and ribbons update is performed with CPU parallelization through multithreading.

The engine is **user-friendly**. The data-driven representation allows for a very expressive system that does not require any code, other than creating the assets or loading the JSON file.

The engine is **expressive**. Many tools and parameters can be specified, some are optional. This gives a very high amount of effects for the user to compose.

## Usage

The usage workflow is as follow :
- Create a `ParticleSystem` instance.
- Fill the particle system's asset registry
- Load renderers' resources from the asset registry
- Play particle effects when desired

To use Confetti in your project, you need to include the `Confetti/Confetti.hpp` header file. The entire library resides in the `cft` namespace.

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
    cft::View view{};
    particleSystem.update(deltaTime, view);
    particleSystem.render(view);
}
```

To integrate the engine's result in your own application, the `ParticleSystem::getRendererOutputTextureId` method returns a handle to the OpenGL output texture id.

Filling the asset registry and loading the renderer assets can be done with a JSON file or with code.
The assets use an id system. Assets that depend on other assets specify the corresponding asset id. The id must be unique per asset type (two force fields can not have the same id but a force field and a motion behavior can have the same id).

### JSON loading

To load a JSON file, do `JsonLoader::initialize`, then `JsonLoader::load`.
The initialize method takes a provide registry. Some effects have dynamic parameters provided by the user in the form of a `std::function`. As this can not be represented in a JSON file, the file instead stores a provider name.
This provider name is used by the engine to query the provider registry. This is why the user has to fill the provider registry with all the provider methods used by the effects.

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
- Open the project workspace
- Build the project

### Static and dynamic linkage

Any project that uses the the static version of the library shoud define the `CONFETTI_STATIC` macro.
To manually export the library as a shared library, the project should define the `CONFETTI_BUILD` macro.
Using the library as a static library requires to link the external dependencies of the library (as only a dynamic library or an executable can store static dependencies).
The dependencies are listed below, the library is guaranteed to work with the specified library versions. Replacing a library with another version may or may not work.

### External dependencies

The minimum required C++ version is C++17.