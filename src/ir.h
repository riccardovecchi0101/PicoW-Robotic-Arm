#ifndef IR_H
#define IR_H

#include "pico/stdlib.h"
#include <stdbool.h>

typedef struct IR_Sensor{
    uint gpio_pin;
    bool active_low;  // true se il sensore dà 0 quando rileva
} IR_Sensor_t;

/**
 * @brief Inizializza il sensore IR
 */
void ir_sensor_init(IR_Sensor_t *sensor, uint gpio_pin, bool active_low);

/**
 * @brief Ritorna true se viene rilevato un oggetto
 */
bool ir_sensor_detect(IR_Sensor_t *sensor);

#endif
