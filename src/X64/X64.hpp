#pragma once

#define assert_sizeof(__ASSET__, __SIZE__) static_assert(sizeof(__ASSET__) == __SIZE__)
#define assert_offsetof(__ASSET__, __VARIABLE__, __OFFSET__) static_assert(offsetof(__ASSET__, __VARIABLE__) == __OFFSET__)

#include "Utils/IO/filesystem.hpp"
#include "Utils/IO/assetmanager.hpp"

#include "Utils/Utils.hpp"