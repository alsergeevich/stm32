/*
 * dinamic_led.c
 *
 *  Created on: Nov 22, 2024
 *      Author: funtik_alt_d
 */

#include "dinamic_led.h"

uint16_t code_numbers[10][7] = { { 1, 1, 1, 1, 1, 1, 0 },
		{ 0, 1, 1, 0, 0, 0, 0 }, { 1, 1, 0, 1,
		1, 0, 1 }, { 1, 1, 1, 1, 0, 0, 1 }, { 0, 1, 1, 0, 0, 1, 1 }, { 1, 0, 1,
		1, 0, 1, 1 }, { 1, 0, 1, 1, 1, 1, 1 }, { 1, 1, 1, 0, 0, 0, 0 }, { 1, 1,
		1, 1, 1, 1, 1 }, { 1, 1, 1, 1, 0, 1, 1 } };



void write_code(uint16_t value, segments_t *seg, uint16_t point_en,
		uint16_t type) { //0-общий катод, 1-общий анод

	if (type == 0) { //если общий катод
		HAL_GPIO_WritePin(seg->port_seg_A, seg->pin_seg_A,
				code_numbers[value][0]);
		HAL_GPIO_WritePin(seg->port_seg_B, seg->pin_seg_B,
				code_numbers[value][1]);
		HAL_GPIO_WritePin(seg->port_seg_C, seg->pin_seg_C,
				code_numbers[value][2]);
		HAL_GPIO_WritePin(seg->port_seg_D, seg->pin_seg_D,
				code_numbers[value][3]);
		HAL_GPIO_WritePin(seg->port_seg_E, seg->pin_seg_E,
				code_numbers[value][4]);
		HAL_GPIO_WritePin(seg->port_seg_F, seg->pin_seg_F,
				code_numbers[value][5]);
		HAL_GPIO_WritePin(seg->port_seg_G, seg->pin_seg_G,
				code_numbers[value][6]);

		if (point_en) {
			HAL_GPIO_WritePin(seg->port_seg_Point, seg->pin_seg_Point, 1);
		} else {
			HAL_GPIO_WritePin(seg->port_seg_Point, seg->pin_seg_Point, 0);
		}


	} else { //если общий анод
		HAL_GPIO_WritePin(seg->port_seg_A, seg->pin_seg_A,
				~(code_numbers[value][0]));
		HAL_GPIO_WritePin(seg->port_seg_B, seg->pin_seg_B,
				~(code_numbers[value][1]));
		HAL_GPIO_WritePin(seg->port_seg_C, seg->pin_seg_C,
				~(code_numbers[value][2]));
		HAL_GPIO_WritePin(seg->port_seg_D, seg->pin_seg_D,
				~(code_numbers[value][3]));
		HAL_GPIO_WritePin(seg->port_seg_E, seg->pin_seg_E,
				~(code_numbers[value][4]));
		HAL_GPIO_WritePin(seg->port_seg_F, seg->pin_seg_F,
				~(code_numbers[value][5]));
		HAL_GPIO_WritePin(seg->port_seg_G, seg->pin_seg_G,
				~(code_numbers[value][6]));

		if (point_en) {
			HAL_GPIO_WritePin(seg->port_seg_Point, seg->pin_seg_Point, 0);
		} else {
			HAL_GPIO_WritePin(seg->port_seg_Point, seg->pin_seg_Point, 1);
		}
	}

	

}

void enable_indicator(indicator_t *indicator, uint16_t inverse) { //0-управление индикатором +, 1-управление индикатором -
	if (inverse == 0) {
		HAL_GPIO_WritePin(indicator->port, indicator->pin, 1);
	} else {
		HAL_GPIO_WritePin(indicator->port, indicator->pin, 0);
	}
}

void disable_indicator(indicator_t *indicator, uint16_t inverse) { //0-управление индикатором +, 1-управление индикатором -
	if (inverse == 0) {
		HAL_GPIO_WritePin(indicator->port, indicator->pin, 0);
	} else {
		HAL_GPIO_WritePin(indicator->port, indicator->pin, 1);
	}
}
