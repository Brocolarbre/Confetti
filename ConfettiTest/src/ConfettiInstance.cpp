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

    if (keyEvent.key == dove::Keyboard::Key::Q)
        particleEffect = 9;
    else if (keyEvent.key == dove::Keyboard::Key::One || keyEvent.key == dove::Keyboard::Key::Numpad1)
        particleEffect = 0;
    else if (keyEvent.key == dove::Keyboard::Key::Two || keyEvent.key == dove::Keyboard::Key::Numpad2)
        particleEffect = 1;
    else if (keyEvent.key == dove::Keyboard::Key::Three || keyEvent.key == dove::Keyboard::Key::Numpad3)
        particleEffect = 2;
    else if (keyEvent.key == dove::Keyboard::Key::Four || keyEvent.key == dove::Keyboard::Key::Numpad4)
        particleEffect = 3;
    else if (keyEvent.key == dove::Keyboard::Key::Five || keyEvent.key == dove::Keyboard::Key::Numpad5)
        particleEffect = 4;
    else if (keyEvent.key == dove::Keyboard::Key::Six || keyEvent.key == dove::Keyboard::Key::Numpad6)
        particleEffect = 5;
    else if (keyEvent.key == dove::Keyboard::Key::Seven || keyEvent.key == dove::Keyboard::Key::Numpad7)
        particleEffect = 6;
    else if (keyEvent.key == dove::Keyboard::Key::Eight || keyEvent.key == dove::Keyboard::Key::Numpad8)
        particleEffect = 7;
    else if (keyEvent.key == dove::Keyboard::Key::Nine || keyEvent.key == dove::Keyboard::Key::Numpad9)
        particleEffect = 8;

    if (particleEffect == -1)
        return;
    
    m_particleSystem.clear();
    if (particleEffect == 9)
    {
        for (unsigned int i = 0; m_particleSystem.getAssetRegistry().hasParticleEffectDescriptor(i); ++i)
            m_particleSystem.playEffect(i);
    }
    else
    {
        if (m_particleSystem.getAssetRegistry().hasParticleEffectDescriptor(static_cast<unsigned int>(particleEffect)))
            m_particleSystem.playEffect(static_cast<unsigned int>(particleEffect));
    }
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