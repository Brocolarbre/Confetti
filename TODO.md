Optimizations :
- Fix HDR-based post-processing effects on high light levels
- Particle sorting for blending
- SSBO : use persistent mapping on all SSBO use cases
- Implement a frames in flight system applied to every OpenGL object that benefits from it (SSBO, UBO...)
- Mesh particle renderer : sort and store particles at the same time, no copy
- Parallelization : CPU multithreading, GPU acceleration