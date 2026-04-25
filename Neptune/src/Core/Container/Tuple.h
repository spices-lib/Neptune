/**
* @file Tuple.h.
* @brief The Tuple Helper Functions Definitions and Implementation.
* @author VisualGMQ.
*/

#pragma once
#include <tuple>

namespace Neptune::Container {

	namespace detail {

		/**
		* @brief Iter a tuple.
		* 
		* @tparam Idx Size of tuple.
		* @tparam Tuple tuple.
		* @tparam Function Iter Function.
		*/
		template<size_t... Idx, typename Tuple, typename Function>
		void IterTuple(Tuple& tuple, Function&& fn, std::index_sequence<Idx...>)
		{
			(std::invoke(fn, std::get<Idx>(tuple)), ...);
		}

	}

	/**
	* @brief Iter a tuple.
	* 
	* @tparam Tuple tuple.
	* @tparam Function Iter Function.
	*/
	template<typename Tuple, typename Function>
	void IterTuple(Tuple& tuple, Function&& fn)
	{
		detail::IterTuple(tuple, fn, std::make_index_sequence<std::tuple_size_v<Tuple>>());
	}
}