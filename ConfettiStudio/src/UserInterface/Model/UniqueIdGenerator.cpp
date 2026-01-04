#include "UniqueIdGenerator.hpp"

UniqueIdGenerator::UniqueIdGenerator() :
	m_id(0)
{

}

unsigned int UniqueIdGenerator::operator()()
{
	return m_id++;
}