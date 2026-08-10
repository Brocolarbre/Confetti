#include "ConfettiInstance.hpp"

//
#include <iostream>

ConfettiInstance::ConfettiInstance(unsigned int width, unsigned int height, unsigned int samples, dove::Window& window) :
    m_renderContext(width, height),
    m_camera(width, height),
    m_particleSystem(1.0f / 60.0f, 8, width, height, samples),
    m_providerRegistry(),
    m_chronometer(false),
    m_worldSpaceMousePosition()
{
    window.addEventHandler(*this);

    m_providerRegistry.registerProvider<glm::vec3>("mouseCursor", [this]() { return glm::vec3(m_worldSpaceMousePosition, 0.0f); });
    onDragAndDrop({ "res/systems/follow.json" });
}

void ConfettiInstance::onDragAndDrop(const std::vector<std::string>& paths)
{
    if (paths.empty() || !paths.front().ends_with(".json"))
        return;

    cft::JsonLoader::clear();
    cft::JsonLoader::initialize(m_providerRegistry);
    cft::JsonLoader::load(paths.front(), m_particleSystem);

    m_particleSystem.clear();
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
    //
    static krono::Chronometer c;
    if (c.getElapsedTime().seconds > 0.5)
    {
        std::cout << 1.0 / deltaTime << '\n';
        c.restart();
    }
    //
    m_chronometer.restart();

    m_particleSystem.update(deltaTime, m_camera.getView());
}

void ConfettiInstance::render() const
{
    m_particleSystem.render(m_camera.getView());
    m_renderContext.render(m_particleSystem.getRendererOutputTextureId());
}