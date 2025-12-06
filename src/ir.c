#include "ir.h"

void ir_sensor_init(IR_Sensor_t* sensor, uint gpio_pin, bool active_low) {
    sensor->gpio_pin = gpio_pin;
    sensor->active_low = active_low;

    gpio_init(gpio_pin);
    gpio_set_dir(gpio_pin, GPIO_IN);
    gpio_pull_up(gpio_pin);   // quasi tutti i moduli funzionano meglio con pull-up
}

bool ir_sensor_detect(IR_Sensor_t *sensor) {
    bool raw_value = gpio_get(sensor->gpio_pin);

    // Se il sensore è active-low → 0 significa rilevato
    if (sensor->active_low) {
        return !raw_value;
    }

    return raw_value;
}
