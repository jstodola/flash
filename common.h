#ifndef COMMON_H
#define COMMON_H

#include <Arduino.h>

const uint8_t IDLE  = 0;
const uint8_t UP    = 1;
const uint8_t DOWN  = 2;
const uint8_t LEFT  = 3;
const uint8_t RIGHT = 4;
const uint8_t OK    = 5;
const uint8_t RC1   = 6;
const uint8_t RC2   = 7;

const uint8_t DETECTS_SOUND = 1;
const uint8_t DETECTS_LIGHT = 2;

double log2(double x);
double shutter_index_to_seconds(int8_t speed_index, const uint16_t *shutter_speeds);

#endif
