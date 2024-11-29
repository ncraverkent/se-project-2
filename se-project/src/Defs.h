#pragma once
#include <string>
#include <vector>
#include <optional>
#include <utility>
#include <memory>
#include <map>

namespace WEP
{
	/**
	* @breif Type alias for std::string
	*/
	using String = std::string;

	/**
	* @breif Type alias for std::vector
	*/
	template<typename T>
	using List = std::vector<T>;

	/**
	* @breif Type alias for std::optional
	*/
	template<typename T>
	using Option = std::optional<T>;

	/**
	* @breif Type alias for std::pair
	*/
	template<typename A, typename B>
	using Pair = std::pair<A, B>;

	/**
	* @breif Type alias for std::shared_ptr
	*/
	template<typename T>
	using Arc = std::shared_ptr<T>;
	
	/**
	* @breif Type alias for std::unique_ptr
	*/
	template<typename T>
	using Box = std::unique_ptr<T>;

	/**
	* @breif Type alias for std::map
	*/
	template<typename TKey, typename TVal>
	using Map = std::map<TKey, TVal>;

	using u32 = std::uint32_t;
}