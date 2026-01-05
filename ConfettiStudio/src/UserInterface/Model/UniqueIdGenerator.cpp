#include "UniqueIdGenerator.hpp"

UniqueIdGenerator::UniqueIdGenerator() :
	m_id(0)
{

}

unsigned int UniqueIdGenerator::getLastId() const
{
	return m_id > 0 ? m_id - 1 : 0;
}

unsigned int UniqueIdGenerator::operator()()
{
	return m_id++;
}