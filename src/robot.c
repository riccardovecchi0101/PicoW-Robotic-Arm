
/*#include "robot.h"


Ritorna true se TUTTI i servo del braccio hanno terminato il movimento.
Si basa sulla funzione servo_finished() definita in servo.c.

bool all_servos_finished(robotic_arm_t* arm) {
    if (!arm) return false;

    return  servo_finished(&arm->pinza)   &&
            servo_finished(&arm->tronco)  &&
            servo_finished(&arm->su_giu)  &&
            servo_finished(&arm->scatola);
}


Inverte il target di TUTTI i servo.
Se un servo era al minimo, va al massimo.
Se era al massimo, va al minimo.

void swap_all_target_angles(robotic_arm_t* arm){
    if (!arm) return;

    swap_target_angle(&arm->pinza);
    swap_target_angle(&arm->tronco);
    swap_target_angle(&arm->su_giu);
    swap_target_angle(&arm->scatola);
}


Aggiorna tutti i servo del braccio.
Questo NON blocca il firmware: fa un solo micro-passaggio per servo.
Va chiamato da un task periodico (es. ogni 10 ms).

void move_robotic_arm(robotic_arm_t* arm){
    if (!arm) return;

    servo_update(&arm->pinza);
    servo_update(&arm->tronco);
    servo_update(&arm->su_giu);
    servo_update(&arm->scatola);
}


*/

#include "robot.h"
#include <stdio.h>

/*
 * Struttura globale
 */
robot_t robot;

/*
 * Tabella stati → target angles
 */
static const movimento_t TAB_STATI[] = {
    [STATO_START]   = { .scatola = 0,   .tronco = 120, .su_giu = 80, .pinza = 20 },
    [STATO_GO_DOWN] = { .scatola = 180, .tronco = 120, .su_giu = 35, .pinza = 120 },
    [STATO_PREPARE_GRAB] = { .scatola = 180, .tronco = 170, .su_giu = 35, .pinza = 120 },
    [STATO_GRAB]    = { .scatola = 180, .tronco = 170, .su_giu = 35, .pinza = 20 },
    [STATO_GO_UP]   = { .scatola = 0,   .tronco = 120, .su_giu = 80, .pinza = 20 },
    [STATO_RELEASE] = { .scatola = 0,   .tronco = 120, .su_giu = 80, .pinza = 120 }
};


/*
 * Inizializzazione dello stato
 */
void robot_init(void) {
    robot.stato = STATO_START;
    robot.movimento_target = TAB_STATI[robot.stato];
}


/*
 * Passaggio allo stato successivo (sequenza fissa)
 */
static robot_state_t next_state(robot_state_t s) {
    switch (s) {
        case STATO_START:   return STATO_GO_DOWN;
        case STATO_GO_DOWN: return STATO_PREPARE_GRAB;
        case STATO_PREPARE_GRAB:    return STATO_GRAB;
        case STATO_GRAB:    return STATO_GO_UP;
        case STATO_GO_UP:   return STATO_RELEASE;
        case STATO_RELEASE: return STATO_START;
        default:            return STATO_START;
    }
}


/*
 * Macchina a stati: aggiorna movimento_target in base allo stato
 */
void robot_update_state_machine(void) {
    robot.movimento_target = TAB_STATI[robot.stato];
    robot.stato = next_state(robot.stato);
}
