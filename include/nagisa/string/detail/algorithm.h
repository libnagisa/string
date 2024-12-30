#pragma once

#include "./cpo.h"
#include "./string.h"
#include "./environment.h"

NAGISA_BUILD_LIB_DETAIL_BEGIN

// include null character
// "foo" -> 4
template<class CharTrait = void>
constexpr ::std::unsigned_integral auto ntbs_length(ntbs auto s) noexcept
{
	if constexpr(::std::same_as<CharTrait, void>)
	{
		::std::size_t result = 0;
		while (true)
		{
			if (details::character_equal(*s, character_null<string_character_t<decltype(s)>>))
			{
				result++;
				break;
			}
			result++;
			s = ::std::ranges::next(s);
		}
		return result;
	}
	else
	{
		return CharTrait::length(s) + 1;
	}
}

#if defined(__cpp_static_call_operator)
#	define NAGISA_STRING_CALL_STATIC static
#	define NAGISA_STRING_CALL_CONST
#else
#	define NAGISA_STRING_CALL_STATIC
#	define NAGISA_STRING_CALL_CONST const
#endif

namespace cpo_details
{
	template<class String>
	consteval result choose_c_str() noexcept
	{
		if constexpr (requires(String s) { NAGISA_STL_FREESTANDING_UTILITY_FORWARD(s).c_str(); })
		{
			return { choose::member, noexcept(::std::declval<String>().c_str()) };
		}
		else if constexpr (requires(String s) { c_str(NAGISA_STL_FREESTANDING_UTILITY_FORWARD(s)); })
		{
			return { choose::adl, noexcept(c_str(::std::declval<String>())) };
		}
		else
		{
			return { choose::none, true };
		}
	}
}
inline constexpr struct
{
	constexpr NAGISA_STRING_CALL_STATIC ntbs decltype(auto) operator()(character_range auto&& s) NAGISA_STRING_CALL_CONST
		noexcept(cpo_details::choose_c_str<decltype(s)>().except)
		requires (cpo_details::choose_c_str<decltype(s)>().value != cpo_details::choose::none)
	{
		if constexpr (
			constexpr auto result = cpo_details::choose_c_str<decltype(s)>();
			result.value == cpo_details::choose::member)
		{
			return NAGISA_STL_FREESTANDING_UTILITY_FORWARD(s).c_str();
		}
		else if constexpr (result.value == cpo_details::choose::adl)
		{
			return c_str(NAGISA_STL_FREESTANDING_UTILITY_FORWARD(s));
		}
	}
	constexpr NAGISA_STRING_CALL_STATIC ntbs decltype(auto) operator()(ntbs auto s) NAGISA_STRING_CALL_CONST noexcept
	{
		return s;
	}
}c_str{};

inline constexpr struct
{
	constexpr NAGISA_STRING_CALL_STATIC decltype(auto) operator()(character_range auto const& s, auto result) NAGISA_STRING_CALL_CONST noexcept
		requires ::std::output_iterator<decltype(result), string_character_t<decltype(s)>> && ::std::contiguous_iterator<decltype(result)>
	{
		
	}
}copy_as_ntbs{};

#undef NAGISA_STRING_CALL_STATIC
#undef NAGISA_STRING_CALL_CONST

NAGISA_BUILD_LIB_DETAIL_END