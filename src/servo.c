#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include <stdio.h>

#define SERVO_PIN 11
#define PWM_FREQ 50
#define SERVO_MIN_US 500
#define SERVO_MAX_US 2400

/***
PINZA: close = 20, open = 120
TRONCO: close = 120, close = 180
SU-GIU: close = 120, open= = 180
SCATOLA: close = 0, open = 180

*/

// === LIMITI CORRETTI (ORIGINALI, NON INVERTITI) ===
#define SAFE_CLOSE_ANGLE  0// pinza chiusa
#define SAFE_OPEN_ANGLE 180// pinza aperta (più ampio)
#define MICRO_STEP 120        // movimento più evidente

uint32_t setup_pwm(uint pin) {
    gpio_set_function(pin, GPIO_FUNC_PWM);
    uint slice = pwm_gpio_to_slice_num(pin);

    float divider = 125.0f;
    uint32_t wrap = (125000000 / divider) / PWM_FREQ;

    pwm_set_clkdiv(slice, divider);
    pwm_set_wrap(slice, wrap);
    pwm_set_enabled(slice, true);

    return wrap;
}

void set_servo_angle(uint pin, float angle, uint wrap) {
    if (angle < SAFE_CLOSE_ANGLE) angle = SAFE_CLOSE_ANGLE;
    if (angle > SAFE_OPEN_ANGLE)  angle = SAFE_OPEN_ANGLE;

    float us = SERVO_MIN_US + (angle / 180.0f) * (SERVO_MAX_US - SERVO_MIN_US);
    float duty = (us * 1e-6f) * PWM_FREQ;
    uint16_t level = (uint16_t)(duty * wrap);

    pwm_set_gpio_level(pin, level);
}

void micro_open(float *a, uint wrap) {
    *a += MICRO_STEP;
    if (*a > SAFE_OPEN_ANGLE) *a = SAFE_OPEN_ANGLE;
    set_servo_angle(SERVO_PIN, *a, wrap);
}

void micro_close(float *a, uint wrap) {
    *a -= MICRO_STEP;
    if (*a < SAFE_CLOSE_ANGLE) *a = SAFE_CLOSE_ANGLE;
    set_servo_angle(SERVO_PIN, *a, wrap);
}

int main() {
    stdio_init_all();

    uint wrap = setup_pwm(SERVO_PIN);

    float angle = SAFE_CLOSE_ANGLE;   // parte chiusa (logica originale)
    set_servo_angle(SERVO_PIN, angle, wrap);

    while (true) {
        set_servo_angle(SERVO_PIN, SAFE_OPEN_ANGLE, wrap);
        sleep_ms(2000);
        set_servo_angle(SERVO_PIN, SAFE_CLOSE_ANGLE, wrap);
        sleep_ms(2000);
    }
}
