#ifndef SERVO_H
#define SERVO_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint32_t pin;
    float current_angle;
    float target_angle;
    float speed;      // fattore per interpolazione
    uint32_t wrap;    // wrap per-SERVO
} servo_motor_t;

void servo_init(servo_motor_t *s, uint32_t pin, float initial_angle, float speed);

void set_servo_target(servo_motor_t *s, float angle);

void servo_update_interpolated(servo_motor_t *s);

bool servo_finished(servo_motor_t *s);

#endif
