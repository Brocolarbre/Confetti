#include "Command.hpp"

Command::Command(bool reversible) :
    m_reversible(reversible)
{

}

bool Command::isReversible() const
{
    return m_reversible;
}