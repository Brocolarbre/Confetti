#pragma once

class UniqueIdGenerator
{
private:
	unsigned int m_id;

public:
	UniqueIdGenerator();

	unsigned int operator()();
};