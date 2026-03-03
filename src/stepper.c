#include "pico/stdlib.h"

#define STEP 16
#define DIR  17
#define STEP_DELAY_US 1800

int main() {

    gpio_init(STEP);
    gpio_set_dir(STEP, GPIO_OUT);
    gpio_put(STEP, 0);

    gpio_init(DIR);
    gpio_set_dir(DIR, GPIO_OUT);
    gpio_put(DIR, 1);

    sleep_ms(50);

    while (true) {
        gpio_put(STEP, 1);
        sleep_us(STEP_DELAY_US);                // impulso breve
        gpio_put(STEP, 0);
        sleep_us(STEP_DELAY_US);     // pausa vera
    }
}
