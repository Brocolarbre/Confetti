Optimizations :
- SSBO : replace the current data update method with persistent mapping
- Multithread : use multiple threads whenever possible, GPU acceleration
- Simulation : DeltaTime and fixed framerate, deterministic
- Mesh particle renderer : sort and store particles at the same time, no copy

Code cleanup :
- Use export macro CONFETTI_EXPORT across the entire engine API

Features :
- Timed events : spawn emitters from particules (tick -> periodically spawn an emitter, deathEvent -> optionally emit another emitter when despawning)
- Mesh particle
- Trail particle
- Ribbon particle
- Spline motion behavior
- Lens flare
- Particle sorting for blending

Application :
- Save system (JSON)

https://www.youtube.com/watch?v=ahOfNgvQ93Q