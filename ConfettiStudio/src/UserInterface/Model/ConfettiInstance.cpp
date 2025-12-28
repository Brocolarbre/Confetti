#include "ConfettiInstance.hpp"

ConfettiInstance::ConfettiInstance() :
    m_renderer()
{

}

cft::Renderer& ConfettiInstance::getRenderer()
{
    return m_renderer;
}