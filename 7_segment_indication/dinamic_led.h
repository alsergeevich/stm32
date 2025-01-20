/*
 * dinamic_led.h
 *
 *  Created on: Nov 22, 2024
 *      Author: Aleksandr Sergeevich Zaskotchenko.
 */
/*
для вывода '-' передайте '-'
для вывода градуса передайте код 129
для вывода -| передайте код 130
для вывода |- передайте код 131
*/
#ifndef INC_DINAMIC_LED_H_
#define INC_DINAMIC_LED_H_

#include "main.h"


//структура для определения индикатора
typedef struct {
	GPIO_TypeDef *port;
	uint16_t pin;
} indicator_t;
//структура для определения сегментов индикатора
typedef struct {
	GPIO_TypeDef *port_seg_A;
	uint16_t pin_seg_A;

	GPIO_TypeDef *port_seg_B;
	uint16_t pin_seg_B;

	GPIO_TypeDef *port_seg_C;
	uint16_t pin_seg_C;

	GPIO_TypeDef *port_seg_D;
	uint16_t pin_seg_D;

	GPIO_TypeDef *port_seg_E;
	uint16_t pin_seg_E;

	GPIO_TypeDef *port_seg_F;
	uint16_t pin_seg_F;

	GPIO_TypeDef *port_seg_G;
	uint16_t pin_seg_G;

	GPIO_TypeDef *port_seg_Point;
	uint16_t pin_seg_Point;

} segments_t;

enum {
    OK,
    OA,
};
 enum {
     POINT_OFF,
     POINT_ON,
 };

//Функция вывода значения на сегменты индикатора. 1-аргумент значение для отображения, 2-структура определения сегментов, 3-точка вкл(1) выкл(0)
//4-тип индикатора 0-общий катод, 1-общий анод
void write_code(uint16_t value, segments_t *seg, uint16_t point_en,
		uint16_t type);

//функция включения индикатора 1-аргумент структура определения индикатора, 2-0-управление индикатором +, 1-управление индикатором -
void enable_indicator(indicator_t *indicator, uint16_t inverse);

//функция выключения индикатора 1-аргумент структура определения индикатора, 2-0-управление индикатором +, 1-управление индикатором -
void disable_indicator(indicator_t *indicator, uint16_t inverse);


#endif /* INC_DINAMIC_LED_H_ */
