﻿#pragma once

#if (__cpp_lib_freestanding_utility < 202306L) && !__has_include(<utility>)
#	error "This library requires the <utility> header to be standard compliant."
#endif

#include <utility>
#include <concepts>
#include <type_traits>
#include <ranges>

#include <nagisa/concept/concept.h>
#include <nagisa/stl_freestanding/utility/utility.h>

//
#define NAGISA_BUILD_LIB_NAME NAGISA_NS::strings
#define NAGISA_BUILD_LIB_CONFIG_VERSION (0,0,0)
#include <nagisa/build_lib/construct.h>