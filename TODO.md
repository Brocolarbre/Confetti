Optimizations :
- SSBO : replace the current data update method with persistent mapping
- Primitive : render circles instead of quads to reduce overdraw
- Multithread : use multiple threads whenever possible
- Simulation : DeltaTime and fixed framerate, deterministic

Code cleanup :
- Refactor camera controllers to avoid code duplication (OrbitCameraController, FirstPersonCameraController)
- Fix boundary checking for OrbitCameraController
- Remove the iostram inclusion from the Presenter.hpp file.
- Nomenclature : full variable names (ex: particleEffect instead of effect)
- Use export macro CONFETTIENGINE_EXPORT across the entire engine API

Features :
- Acceleration : distinguish between force fields that accumulate force on the velocity and force fields that reset the velocity with a new value
- ForceField : replace particlePosition with a Particle instance to allow for more complex force fields (particle fields, progress)
- Timed events : spawn emitters from particules (tick -> periodically spawn an emitter, deathEvent -> optionally emit another emitter when despawning)
- Rendering : instancing, bloom, lens flares, model rendering
- Advanced force field : crowd simulation
- Particle scrubbing : allow some particles to follow the force fields in reverse
- Constellation graph : neighbor lookup node, primitives (lines), progress (elapsedTime / despawnTime)
- Save system (JSON)
- Framebuffer clear : integrate with other graphics environments
- Grid : render a grid in the editor

https://www.youtube.com/watch?v=ahOfNgvQ93Q