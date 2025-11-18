#ifndef SERVO_H
#define SERVO_H

#include <stdint.h>   

typedef struct servo_motor {
    uint32_t pin;           
    float servo_min_angle;
    float servo_max_angle;
    float servo_current_angle;
    float target_angle;
    float step_angle;
} servo_motor_t;

void setup_pwm(uint32_t pin);
void set_servo_angle(uint32_t pin, float angle, servo_motor_t* servo);
void servo_update(servo_motor_t* servo);
void swap_target_angle(servo_motor_t* servo);
bool servo_finished(servo_motor_t* s);

#endif
