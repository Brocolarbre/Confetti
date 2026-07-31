#include "ConfettiInstance.hpp"

#include <Confetti/Serialization/JsonLoader.hpp>

ConfettiInstance::ConfettiInstance(unsigned int width, unsigned int height, unsigned int samples, dove::Window& window) :
    m_renderContext(width, height),
    m_camera(width, height),
    m_particleSystem(1.0f / 60.0f, width, height, samples),
    m_chronometer(false),
    m_worldSpaceMousePosition()
{
    window.addEventHandler(*this);

    cft::JsonLoader::getProviderRegistry().registerProvider<glm::vec3>("mouseCursor", [this]() { return glm::vec3(m_worldSpaceMousePosition, 0.0f); });
    cft::JsonLoader::initialize();
    cft::JsonLoader::load("res/systems/follow.json", m_particleSystem);

    m_particleSystem.playEffect(0);
    m_chronometer.start();
}

void ConfettiInstance::onKeyPressed(dove::KeyEvent keyEvent)
{
    if (keyEvent.key == dove::Keyboard::Key::R)
    {
        m_particleSystem.clear();
        m_particleSystem.playEffect(0);
        m_chronometer.restart();
        m_worldSpaceMousePosition = glm::vec2(0.0f);
    }
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
    m_particleSystem.render(m_camera.getView());
    m_renderContext.render(m_particleSystem.getRendererOutputTextureId());
}