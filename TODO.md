Optimizations :
- SSBO : replace the current data update method with persistent mapping
- Multithread : use multiple threads whenever possible, GPU acceleration
- Simulation : DeltaTime and fixed framerate, deterministic
- Mesh particle renderer : sort and store particles at the same time, no copy
- Particle sorting for blending

Code cleanup :
- Use export macro CONFETTI_EXPORT across the entire engine API
- Folder structure
- Organize ParticleSimulation.cpp (ex: TrailUpdater)

Features :
- Ribbon particle

Application :
- Save system (JSON)

https://www.youtube.com/watch?v=ahOfNgvQ93Q