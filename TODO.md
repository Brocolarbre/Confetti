Optimizations :
- SSBO : replace the current data update method with persistent mapping

Code cleanup :
- Refactor camera controllers to avoid code duplication (OrbitCameraController, FirstPersonCameraController)
- Fix boundary checking for OrbitCameraController
- Remove the iostram inclusion from the Presenter.hpp file

Exporting :
- Use export macro CONFETTIENGINE_EXPORT across the entire engine API