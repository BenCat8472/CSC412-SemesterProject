#pragma once
#include <stdint.h>

typedef uint8_t byte;


constexpr byte S1[2][8] = {
    { 0b101, 0b010, 0b001, 0b110, 0b011, 0b100, 0b111, 0b000 },
    { 0b001, 0b100, 0b110, 0b010, 0b000, 0b111, 0b101, 0b011 }
};
constexpr byte S2[2][8] = {
    { 0b100, 0b000, 0b110, 0b101, 0b111, 0b001, 0b011, 0b010 },
    { 0b101, 0b011, 0b000, 0b111, 0b110, 0b010, 0b001, 0b100 }
};


uint16_t simpleDES(uint16_t msg, uint16_t key, unsigned rounds);
byte simple_expand(byte x);
byte simple_f(byte r, byte k);
