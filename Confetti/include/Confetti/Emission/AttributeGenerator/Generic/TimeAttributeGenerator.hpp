#pragma once

#include "Confetti/Emission/AttributeGenerator/AttributeGenerator.hpp"

namespace cft
{
	template <typename T>
	class TimeAttributeGenerator : public Cloneable<TimeAttributeGenerator<T>, AttributeGenerator<T>>
	{
	private:
		T m_from;
		T m_to;

		float m_fromTime;
		float m_toTime;

		float m_duration;

		T generateValue(unsigned int count, unsigned int index, const SpawnContext& context, float elapsedTime) override;

	public:
		TimeAttributeGenerator(const T& from, const T& to, float fromTime, float toTime);
	};

	template <typename T>
	inline T TimeAttributeGenerator<T>::generateValue(unsigned int count, unsigned int index, const SpawnContext& context, float elapsedTime)
	{
		float t = m_duration != 0.0f ? (elapsedTime - m_fromTime) / m_duration : 1.0f;
		t = glm::clamp(t, 0.0f, 1.0f);

		return glm::mix(m_from, m_to, t);
	}

	template <typename T>
	inline TimeAttributeGenerator<T>::TimeAttributeGenerator(const T& from, const T& to, float fromTime, float toTime) :
		m_from(from),
		m_to(to),
		m_fromTime(fromTime),
		m_toTime(toTime),
		m_duration(toTime - fromTime)
	{

	}
}