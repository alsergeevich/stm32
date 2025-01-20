/*
 * dinamic_led.c
 *
 *  Created on: Nov 22, 2024
 *      Author: Aleksandr Sergeevich Zaskotchenko.
 */

#include "dinamic_led.h"

uint16_t code_chars[16][7] = {{1,1,1,0,1,1,1}, {0,0,1,1,1,1,1}, {1,0,0,1,1,1,0}, {0,1,1,1,1,0,1},
                        {1,0,0,1,1,1,1}, {1,0,0,0,1,1,1}, {1,0,1,1,1,1,0}, {0,1,1,0,1,1,1},
                        {0,0,1,0,0,0,0}, {0,1,1,1,1,0,0}, {0,0,0,1,1,1,0}, {1,1,0,0,1,1,1},
                        {1,1,1,0,0,1,1}, {0,0,0,1,1,1,1}, {0,1,1,1,1,1,0}, {0,0,1,1,1,0,1}};


uint16_t code_numbers[10][7] = { { 1, 1, 1, 1, 1, 1, 0 },
		{ 0, 1, 1, 0, 0, 0, 0 }, { 1, 1, 0, 1,
		1, 0, 1 }, { 1, 1, 1, 1, 0, 0, 1 }, { 0, 1, 1, 0, 0, 1, 1 }, { 1, 0, 1,
		1, 0, 1, 1 }, { 1, 0, 1, 1, 1, 1, 1 }, { 1, 1, 1, 0, 0, 0, 0 }, { 1, 1,
		1, 1, 1, 1, 1 }, { 1, 1, 1, 1, 0, 1, 1 } };

uint16_t code_znaki[4][7] = { {0,0,0,0,0,0,1}, {1,1,0,0,0,1,1}, {0,1,1,0,0,0,1}, {0,0,0,0,1,1,1} }; //массив знаков 0-(-), 1-(градус), 2-(-|), 3-(|-)


uint16_t to_lowercase(uint16_t c) {
    if (c >= 'A' && c <= 'Z') {
        return c + ('a' - 'A');
    }
    return c;
}
int is_alpha(uint16_t c) {
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
        return 1;
    }
    return 0;
}

uint16_t get_index_symbol(uint16_t c) {
    if (c == 'a') return 0;
    if (c == 'b') return 1;
    if (c == 'c') return 2;
    if (c == 'd') return 3;
    if (c == 'e') return 4;
    if (c == 'f') return 5;
    if (c == 'g') return 6;
    if (c == 'h') return 7;
    if (c == 'i') return 8;
    if (c == 'j') return 9;
    if (c == 'l') return 10;
    if (c == 'p') return 11;
    if (c == 'q') return 12;
    if (c == 't') return 13;
    if (c == 'u') return 14;
    if (c == 'o') return 15;
    return 0;
}


void write_code(uint16_t value, segments_t *seg, uint16_t point_en,
		uint16_t type) { //0-общий катод, 1-общий анод
  	if(value == '-') {value = 128;}
    uint16_t (*array_value)[7]; //объявляем указатель на массив [][7]
    uint16_t out_value = 0;
    if(value > 9 && value <= 122) {
        if(is_alpha(value)) {
            array_value = code_chars;
            out_value = get_index_symbol(to_lowercase(value));
        }

    } else if(value <= 9){
        array_value = code_numbers;
        out_value = value;
    } else if(value >= 128 && value <= 131) {
      	array_value = code_znaki;

        out_value = value - 128;
    }
	if (type == 0) { //если общий катод
		HAL_GPIO_WritePin(seg->port_seg_A, seg->pin_seg_A,
                          array_value[out_value][0]);
		HAL_GPIO_WritePin(seg->port_seg_B, seg->pin_seg_B,
                          array_value[out_value][1]);
		HAL_GPIO_WritePin(seg->port_seg_C, seg->pin_seg_C,
                          array_value[out_value][2]);
		HAL_GPIO_WritePin(seg->port_seg_D, seg->pin_seg_D,
                          array_value[out_value][3]);
		HAL_GPIO_WritePin(seg->port_seg_E, seg->pin_seg_E,
                          array_value[out_value][4]);
		HAL_GPIO_WritePin(seg->port_seg_F, seg->pin_seg_F,
                          array_value[out_value][5]);
		HAL_GPIO_WritePin(seg->port_seg_G, seg->pin_seg_G,
                          array_value[out_value][6]);

		if (point_en) {
			HAL_GPIO_WritePin(seg->port_seg_Point, seg->pin_seg_Point, 1);
		} else {
			HAL_GPIO_WritePin(seg->port_seg_Point, seg->pin_seg_Point, 0);
		}


	} else { //если общий анод
		HAL_GPIO_WritePin(seg->port_seg_A, seg->pin_seg_A,
				~(array_value[out_value][0]));
		HAL_GPIO_WritePin(seg->port_seg_B, seg->pin_seg_B,
				~(array_value[out_value][1]));
		HAL_GPIO_WritePin(seg->port_seg_C, seg->pin_seg_C,
				~(array_value[out_value][2]));
		HAL_GPIO_WritePin(seg->port_seg_D, seg->pin_seg_D,
				~(array_value[out_value][3]));
		HAL_GPIO_WritePin(seg->port_seg_E, seg->pin_seg_E,
				~(array_value[out_value][4]));
		HAL_GPIO_WritePin(seg->port_seg_F, seg->pin_seg_F,
				~(array_value[out_value][5]));
		HAL_GPIO_WritePin(seg->port_seg_G, seg->pin_seg_G,
				~(array_value[out_value][6]));

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
