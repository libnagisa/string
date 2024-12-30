#pragma once

#include "./environment.h"

NAGISA_BUILD_LIB_DETAIL_BEGIN

template<class T>
concept character =
	::std::same_as<::std::remove_cv_t<T>, char>
	|| ::std::same_as<::std::remove_cv_t<T>, char8_t>
	|| ::std::same_as<::std::remove_cv_t<T>, char16_t>
	|| ::std::same_as<::std::remove_cv_t<T>, char32_t>
	|| ::std::same_as<::std::remove_cv_t<T>, wchar_t>
;

template<character T>
constexpr bool character_equal(T a, T b) noexcept
{
	return a == b;
}

template<character T>
inline constexpr character auto character_null = T{};

NAGISA_BUILD_LIB_DETAIL_END