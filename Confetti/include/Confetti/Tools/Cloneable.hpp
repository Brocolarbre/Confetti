#pragma once

#include <memory>

namespace cft
{
	template <typename Derived, typename Base>
	class Cloneable : public Base
	{
	public:
		std::unique_ptr<Base> clone() const override;
	};

	template<typename Derived, typename Base>
	inline std::unique_ptr<Base> Cloneable<Derived, Base>::clone() const
	{
		return std::make_unique<Derived>(static_cast<const Derived&>(*this));
	}
}