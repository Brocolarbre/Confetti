Optimizations :
- Fix HDR-based post-processing effects on high light levels
- Particle sorting for blending
- SSBO : replace the current data update method with persistent mapping
- Mesh particle renderer : sort and store particles at the same time, no copy
- Parallelization : CPU multithreading, GPU acceleration