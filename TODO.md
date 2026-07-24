Optimizations :
- SSBO : replace the current data update method with persistent mapping
- Parallelization : CPU multithreading, GPU acceleration
- Simulation : DeltaTime and fixed framerate, deterministic
- Mesh particle renderer : sort and store particles at the same time, no copy
- Particle sorting for blending
- Fix HDR-based post-processing effects on high light levels

Code cleanup :
- Use export macro CONFETTI_EXPORT across the entire engine API