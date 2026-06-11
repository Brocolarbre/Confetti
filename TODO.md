Optimizations :
- SSBO : replace the current data update method with persistent mapping
- Multithread : use multiple threads whenever possible, GPU acceleration
- Simulation : DeltaTime and fixed framerate, deterministic

Code cleanup :
- Use export macro CONFETTI_EXPORT across the entire engine API

Features :
- Timed events : spawn emitters from particules (tick -> periodically spawn an emitter, deathEvent -> optionally emit another emitter when despawning)
- Texture, sprite, animated sprite
- Mesh particle
- Spline motion behavior
- Lens flare

Application :
- Save system (JSON)

https://www.youtube.com/watch?v=ahOfNgvQ93Q