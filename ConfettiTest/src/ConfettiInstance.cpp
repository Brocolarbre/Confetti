#include "ConfettiInstance.hpp"

ConfettiInstance::ConfettiInstance(unsigned int width, unsigned int height, unsigned int samples, dove::Window& window) :
    m_renderContext(width, height),
    m_camera(width, height),
    m_particleSystem(1.0f / 60.0f, 8, width, height, samples, 5),
    m_providerRegistry(),
    m_chronometer(false),
    m_worldSpaceMousePosition()
{
    window.addEventHandler(*this);

    m_providerRegistry.registerProvider<glm::vec3>("mouseCursor", [this]() { return glm::vec3(m_worldSpaceMousePosition, 0.0f); });
}

void ConfettiInstance::onDragAndDrop(const std::vector<std::string>& paths)
{
    if (paths.empty() || !paths.front().ends_with(".json"))
        return;

    m_particleSystem.getAssetRegistry().clear();

    cft::JsonLoader::clear();
    cft::JsonLoader::initialize(m_providerRegistry);
    if (!cft::JsonLoader::load(paths.front(), m_particleSystem))
        return;

    m_particleSystem.clear();
    m_particleSystem.playEffect(0);
    m_chronometer.start();
}

void ConfettiInstance::onKeyPressed(dove::KeyEvent keyEvent)
{
    int particleEffect = -1;

    switch (keyEvent.key)
    {
    case dove::Keyboard::Key::One: particleEffect = 0; break;
    case dove::Keyboard::Key::Two: particleEffect = 1; break;
    case dove::Keyboard::Key::Three: particleEffect = 2; break;
    case dove::Keyboard::Key::Four: particleEffect = 3; break;
    case dove::Keyboard::Key::Five: particleEffect = 4; break;
    case dove::Keyboard::Key::Six: particleEffect = 5; break;
    case dove::Keyboard::Key::Seven: particleEffect = 6; break;
    case dove::Keyboard::Key::Eight: particleEffect = 7; break;
    case dove::Keyboard::Key::Nine: particleEffect = 8; break;
    }

    if (particleEffect == -1)
        return;

    m_particleSystem.clear();
    m_particleSystem.playEffect(static_cast<unsigned int>(particleEffect));
    m_chronometer.restart();
    m_worldSpaceMousePosition = glm::vec2(0.0f);
}

void ConfettiInstance::onMouseMoved(unsigned int x, unsigned int y)
{
    m_worldSpaceMousePosition = glm::vec2(m_camera.screenToWorld(x, y));
}

void ConfettiInstance::onWindowResized(unsigned int width, unsigned int height)
{
    m_camera = Camera(width, height);
    m_particleSystem.resize(width, height);
    m_renderContext.resize(width, height);
}

void ConfettiInstance::update()
{
    float deltaTime = static_cast<float>(m_chronometer.getElapsedTime().seconds);
    m_chronometer.restart();

    m_particleSystem.update(deltaTime, m_camera.getView());
}

void ConfettiInstance::render() const
{
    m_particleSystem.render(m_camera.getView(), std::nullopt);
    m_renderContext.render(m_particleSystem.getRendererOutputTextureId());
}