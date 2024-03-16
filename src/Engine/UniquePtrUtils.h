#pragma once
#include <type_traits>
#include <memory>

namespace util {
	// std::unique_ptr<Derived> ==> std::unique_ptr<Base>
	template <typename Base, typename Derived>
	std::unique_ptr<Base> upcast(std::unique_ptr<Derived> e)
	{
		static_assert(
			std::is_base_of_v<Base, Derived>,
			"Invalid Base, Derived parameters!"
		);
		Base* upcasted{ static_cast<Base*>(e.release()) };
		return std::unique_ptr<Base>(upcasted);
	}
}