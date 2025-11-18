#ifndef ROBOT_H
#define ROBOT_H

#include <stdbool.h>
#include "servo.h"

typedef struct robotic_arm {
    servo_motor_t pinza;
    servo_motor_t tronco;
    servo_motor_t su_giu;
    servo_motor_t scatola;
} robotic_arm_t;

bool all_servos_finished(robotic_arm_t* arm);
void swap_all_target_angles(robotic_arm_t* arm);
void move_robotic_arm(robotic_arm_t* arm);

#endif
