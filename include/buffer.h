#pragma once

#include <array>

#include "protocols.h"

using buf_t = std::array<uint8_t, MAX_DATA_SIZE>;
using buf_iterator = buf_t::iterator;
