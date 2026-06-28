Optimizations :
- SSBO : replace the current data update method with persistent mapping
- Multithread : use multiple threads whenever possible, GPU acceleration
- Simulation : DeltaTime and fixed framerate, deterministic
- Mesh particle renderer : sort and store particles at the same time, no copy
- Particle sorting for blending

Code cleanup :
- Use export macro CONFETTI_EXPORT across the entire engine API
- Consistent naming for structure attributes involved with id (emitterId / emitter)

Features :
- Trail particle
- Ribbon particle
- Spline motion behavior
- Lens flare

Application :
- Save system (JSON)

https://www.youtube.com/watch?v=ahOfNgvQ93Q