#include "servo.h"
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include <math.h>

#define PWM_FREQ     50
#define SERVO_MIN_US 500
#define SERVO_MAX_US 2400

static void setup_pwm(servo_motor_t *s) {
    gpio_set_function(s->pin, GPIO_FUNC_PWM);
    uint slice = pwm_gpio_to_slice_num(s->pin);

    float divider = 125.0f;
    s->wrap = (uint32_t)((125000000 / divider) / PWM_FREQ);

    pwm_set_clkdiv(slice, divider);
    pwm_set_wrap(slice, s->wrap);
    pwm_set_enabled(slice, true);
}

void servo_init(servo_motor_t *s, uint32_t pin, float initial_angle, float speed) {
    s->pin = pin;
    s->current_angle = initial_angle;
    s->target_angle = initial_angle;
    s->speed = speed;

    setup_pwm(s);

    float us = SERVO_MIN_US + (initial_angle / 180.0f) * (SERVO_MAX_US - SERVO_MIN_US);
    uint32_t level = (uint32_t)roundf((us / 20000.0f) * s->wrap);
    pwm_set_gpio_level(pin, level);
}

void set_servo_target(servo_motor_t *s, float angle) {
    if (angle < 0) angle = 0;
    if (angle > 180) angle = 180;
    s->target_angle = angle;
}

static void apply_pwm(servo_motor_t *s, float angle) {
    float us = SERVO_MIN_US + (angle / 180.0f) * (SERVO_MAX_US - SERVO_MIN_US);
    uint32_t level = (uint32_t)roundf((us / 20000.0f) * s->wrap);
    pwm_set_gpio_level(s->pin, level);
}

void servo_update_interpolated(servo_motor_t *s) {
    float diff = s->target_angle - s->current_angle;

    // FIX FONDAMENTALE: soglia più grande + convergenza certa
    if (fabsf(diff) <= 1.0f) {
        s->current_angle = s->target_angle;
        apply_pwm(s, s->current_angle);
        return;
    }

    // aggiornamento senza drift
    s->current_angle += diff * s->speed;

    apply_pwm(s, s->current_angle);
}

bool servo_finished(servo_motor_t *s) {
    return fabsf(s->target_angle - s->current_angle) < 1.0f;
}
