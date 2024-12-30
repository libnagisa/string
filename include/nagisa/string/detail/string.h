#pragma once

#include "./character.h"
#include "./environment.h"

NAGISA_BUILD_LIB_DETAIL_BEGIN

template<class T>
struct string_character { using type = typename ::std::remove_cv_t<T>::character_type; };
template<class T> requires requires{ requires character<typename string_character<T>::type>; }
using string_character_t = typename string_character<T>::type;

// null-terminated byte string(c string)
template<class T>
concept ntbs = concepts::pointer<T> && character<::std::remove_pointer_t<T>>;
template<ntbs T>
struct string_character<T> { using type = ::std::remove_pointer_t<T>; };

template<class T>
concept character_range = ::std::ranges::input_range<T> && character<::std::ranges::range_value_t<T>>;
template<character_range T>
struct string_character<T> { using type = ::std::ranges::range_value_t<T>; };

template<class T>
concept string_like = character_range<T> && ::std::ranges::contiguous_range<T>;

template<class T>
concept string = character_range<T> || ntbs<T>;


NAGISA_BUILD_LIB_DETAIL_END