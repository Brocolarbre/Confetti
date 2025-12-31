Optimizations :
- SSBO : replace the current data update method with persistent mapping
- Primitive : render circles instead of quads to reduce overdraw

Code cleanup :
- Refactor camera controllers to avoid code duplication (OrbitCameraController, FirstPersonCameraController)
- Fix boundary checking for OrbitCameraController
- Remove the iostram inclusion from the Presenter.hpp file.
- Nomenclature : full variable names (ex: particleEffect instead of effect)

Exporting :
- Use export macro CONFETTIENGINE_EXPORT across the entire engine API