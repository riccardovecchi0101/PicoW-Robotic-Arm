#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "servo.h"
#include <math.h>
#include <stdio.h>

#define PWM_FREQ 50
#define SERVO_MIN_US 500
#define SERVO_MAX_US 2400

static uint32_t wrap = 0;

/*
 * Configura un pin per generare un segnale PWM a 50 Hz.
 * Il servo richiede un periodo di 20 ms → 50 Hz.
 */
void setup_pwm(uint32_t pin) {
    gpio_set_function(pin, GPIO_FUNC_PWM);
    uint slice = pwm_gpio_to_slice_num(pin);

    float divider = 125.0f;  // 125 MHz / 125 = 1 MHz → tick = 1 µs
    wrap = (125000000 / divider) / PWM_FREQ;  // ~20000 tick

    pwm_set_clkdiv(slice, divider);
    pwm_set_wrap(slice, wrap);
    pwm_set_enabled(slice, true);
}

/*
 * Converte un angolo in durata dell'impulso e poi in duty cycle PWM.
 * Aggiorna anche servo_current_angle.
 */
void set_servo_angle(uint32_t pin, float angle, servo_motor_t* servo) {

    // limiti meccanici del servo
    if (angle < servo->servo_min_angle) angle = servo->servo_min_angle;
    if (angle > servo->servo_max_angle) angle = servo->servo_max_angle;

    // interpolazione lineare gradi → microsecondi
    float us = SERVO_MIN_US + (angle / 180.0f) * (SERVO_MAX_US - SERVO_MIN_US);

    // conversione us → duty cycle
    float duty = (us * 1e-6f) * PWM_FREQ;

    // conversione duty → valore PWM
    uint16_t level = (uint16_t)(duty * wrap);

    servo->servo_current_angle = angle;

    pwm_set_gpio_level(pin, level);
}

/*
 * Movimento interpolato NON BLOCCANTE.
 * Avanza il servo di uno step verso target_angle.
 */
void servo_update(servo_motor_t* servo) {

    float current = servo->servo_current_angle;
    float target  = servo->target_angle;
    float step    = servo->step_angle;

    // protezione da step a zero o valori assurdi
    if (fabs(step) < 0.0001f) return;

    // se il servo è molto vicino al target, setta direttamente il target
    if (fabs(target - current) <= fabs(step)) {
        set_servo_angle(servo->pin, target, servo);
        return;
    }

    // calcola prossimo step
    float next = current + (target > current ? step : -step);
    set_servo_angle(servo->pin, next, servo);
}

/*
 * Inverte il target di un singolo servo.
 */
void swap_target_angle(servo_motor_t* servo){
    if (servo->target_angle == servo->servo_min_angle)
        servo->target_angle = servo->servo_max_angle;
    else
        servo->target_angle = servo->servo_min_angle;
}

/*
 * Ritorna true se il servo ha raggiunto il target.
 */
bool servo_finished(servo_motor_t* s) {
    return fabs(s->target_angle - s->servo_current_angle) <= fabs(s->step_angle);
}
