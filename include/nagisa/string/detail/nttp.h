#pragma once

#include "./environment.h"

NAGISA_BUILD_LIB_DETAIL_BEGIN

template<class Char, ::std::size_t N>
struct basic_nttp : ::std::ranges::view_interface<basic_nttp<Char, N>>
{
	using char_type = Char;
	constexpr static auto size = N;

	consteval explicit(false) basic_nttp(Char const(&data)[N]) noexcept
	{
		for (::std::size_t i = 0; i < N; ++i)
		{
			_data[i] = data[i];
		}
	}

	constexpr auto begin() const noexcept { return &_data[0]; }
	constexpr auto end() const noexcept { return &_data[N - 1]; }
	constexpr auto data() const noexcept { return &_data[0]; }
	constexpr auto c_str() const noexcept { return data(); }

	char_type _data[size];
};


NAGISA_BUILD_LIB_DETAIL_END