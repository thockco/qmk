/*
Copyright 2020 Thock Co

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "conundrum.h"

#include "d51_util.h"
#include "debug.h"
#include "clks.h"
#include <string.h>
#include "ec_touch.h"

uint16_t touch_signals[MATRIX_ROWS * MATRIX_COLS];
matrix_row_t mlatest[MATRIX_ROWS];

__attribute__ ((weak))
void matrix_init_kb(void) {
    matrix_init_user();
}

__attribute__ ((weak))
void matrix_scan_kb(void) {
    matrix_scan_user();
}

__attribute__ ((weak))
void matrix_init_user(void) {
}

__attribute__ ((weak))
void matrix_scan_user(void) {
}

void matrix_init(void)
{
    memset(mlatest, 0, MATRIX_ROWS * sizeof(matrix_row_t));
 
    ec_touch_init(touch_signals);

    matrix_init_quantum();

    ec_touch_start();
}

uint8_t matrix_scan(void)
{
  uint32_t row, col;

  if (!ec_touch_ready())
    return 1;

  for (row = 0; row < MATRIX_ROWS; row++) {
    for (col = 0; col < MATRIX_COLS; col++) {
      uint16_t signal = touch_signals[row * MATRIX_COLS + col];
      matrix_row_t pressed = mlatest[row] & (1u << col);
      if (pressed && signal < 75) {
        pressed = 0;
      } else {
        pressed = pressed || signal > 125;
      }

      mlatest[row] = (~(1u << col) & mlatest[row]) | (pressed << col);
    }
  }

  matrix_scan_quantum();

  return 1;
}

matrix_row_t matrix_get_row(uint8_t row)
{
    return mlatest[row];
}

void matrix_print(void)
{
    char buf[(MATRIX_COLS+8)*(MATRIX_ROWS+1)] = "R C";
    char *pbuf = buf+3;
    uint32_t cols;
    uint32_t rows;
    matrix_row_t row;

    for (cols = 1; cols <= MATRIX_COLS; cols++)
    {
        *pbuf = (cols%10)+48;
        pbuf++;
    }
    *pbuf = '\r'; pbuf++;
    *pbuf = '\n'; pbuf++;

    for (rows = 1; rows <= MATRIX_ROWS; rows++)
    {
        row = matrix_get_row(rows-1);
        if (rows < 10) { *pbuf = rows+48; pbuf++; *pbuf = ' '; pbuf++; *pbuf = ' '; pbuf++; }
        else { *pbuf = (rows/10)+48; pbuf++; *pbuf = (rows%10)+48; pbuf++; *pbuf = ' '; pbuf++; }
        for (cols = 0; cols < MATRIX_COLS; cols++)
        {
            if (row & 1 << cols) *pbuf = 'X';
            else                 *pbuf = '.';
            pbuf++;
        }
        *pbuf = '\r'; pbuf++;
        *pbuf = '\n'; pbuf++;
    }
    *pbuf = 0;
    dprint(buf);
}
