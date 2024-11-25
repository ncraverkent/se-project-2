#pragma once
#include <string>
#include <vector>
#include <optional>
#include <utility>
#include <memory>

namespace WEP
{
	using String = std::string;

	template<typename T>
	using List = std::vector<T>;

	template<typename T>
	using Option = std::optional<T>;

	template<typename A, typename B>
	using Pair = std::pair<A, B>;

	template<typename T>
	using Arc = std::shared_ptr<T>;

	template<typename T>
	using Box = std::unique_ptr<T>;
}