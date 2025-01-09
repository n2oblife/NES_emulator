#pragma once

#include <cstdint>

// Define redefine types
using byte = uint8_t;
using h_word = uint16_t;
using word = uint32_t;

// Define bus widths
const unsigned int DATA_WIDTH = 8;
const unsigned int ADDRESS_WIDTH = 16;

// Define bus regions
const unsigned int BUS_RANGE = 0xFFFF; // 64KB
