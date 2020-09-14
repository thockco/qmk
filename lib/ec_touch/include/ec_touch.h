#pragma once

#include <stdint.h>
#include <stdbool.h>

#define MATRIX_ROWS 4
#define MATRIX_COLS 12

uint8_t ec_touch_ready(void);
void ec_touch_init(uint16_t* signals);
void ec_touch_start(void);
