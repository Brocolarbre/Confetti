#pragma once

#include <memory>

namespace cft
{
	template <typename Derived, typename Base>
	class Cloneable : public Base
	{
	public:
		template <typename ...Args>
		Cloneable(Args&&... args);
		std::unique_ptr<Base> clone() const override;
	};

	template<typename Derived, typename Base>
	template<typename ...Args>
	inline Cloneable<Derived, Base>::Cloneable(Args&&... args) :
		Base(std::forward<Args>(args)...)
	{

	}

	template<typename Derived, typename Base>
	inline std::unique_ptr<Base> Cloneable<Derived, Base>::clone() const
	{
		return std::make_unique<Derived>(static_cast<const Derived&>(*this));
	}
}