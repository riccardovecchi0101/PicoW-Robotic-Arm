/*#ifndef ROBOT_H
#define ROBOT_H

#include <stdbool.h>
#include "servo.h"

typedef enum state_t{
    START,
    GO_DOWN,
    GRAB,
    GO_UP,
    RELEASE
}state_t;

typedef struct movimento{
    state_t stato;
    float scatola_target_angle;
    float tronco_target_angle;
    float su_giu_target_angle;
    float pinza_target_angle;
}movimento_t;

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
*/
#ifndef ROBOT_H
#define ROBOT_H

#include <stdint.h>

typedef enum {
    STATO_START = 0,
    STATO_GO_DOWN,
    STATO_PREPARE_GRAB,
    STATO_GRAB,
    STATO_GO_UP,
    STATO_RELEASE
} robot_state_t;

/*
 * Target degli angoli del movimento corrente.
 */
typedef struct {
    float scatola;
    float tronco;
    float su_giu;
    float pinza;
} movimento_t;

/*
 * Struttura globale del robot.
 */
typedef struct {
    robot_state_t stato;
    movimento_t movimento_target;
} robot_t;

extern robot_t robot;

/* Funzioni */
void robot_init(void);
void robot_update_state_machine(void);

#endif
