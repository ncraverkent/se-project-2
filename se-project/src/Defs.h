#pragma once
#include <string>
#include <vector>
#include <optional>
#include <utility>

namespace WEP
{
	using String = std::string;

	template<typename T>
	using List = std::vector<T>;

	template<typename T>
	using Option = std::optional<T>;

	template<typename A, typename B>
	using Pair = std::pair<A, B>;
}