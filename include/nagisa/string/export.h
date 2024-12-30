#pragma once

#include "./detail/character.h"
#include "./detail/string.h"
#include "./detail/algorithm.h"
#include "./detail/nttp.h"
#include "./environment.h"

NAGISA_BUILD_LIB_BEGIN

using details::character;
using details::character_null;

using details::ntbs;
using details::ntbs_length;

using details::character_range;
using details::string_like;

using details::string;
using details::string_character_t;

using details::c_str;

using details::basic_nttp;

NAGISA_BUILD_LIB_END