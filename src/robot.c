
#include "robot.h"

/*
 * Ritorna true se TUTTI i servo del braccio hanno terminato il movimento.
 * Si basa sulla funzione servo_finished() definita in servo.c.
 */
bool all_servos_finished(robotic_arm_t* arm) {
    if (!arm) return false;

    return  servo_finished(&arm->pinza)   &&
            servo_finished(&arm->tronco)  &&
            servo_finished(&arm->su_giu)  &&
            servo_finished(&arm->scatola);
}

/*
 * Inverte il target di TUTTI i servo.
 * Se un servo era al minimo, va al massimo.
 * Se era al massimo, va al minimo.
 */
void swap_all_target_angles(robotic_arm_t* arm){
    if (!arm) return;

    swap_target_angle(&arm->pinza);
    swap_target_angle(&arm->tronco);
    swap_target_angle(&arm->su_giu);
    swap_target_angle(&arm->scatola);
}

/*
 * Aggiorna tutti i servo del braccio.
 * Questo NON blocca il firmware: fa un solo micro-passaggio per servo.
 * Va chiamato da un task periodico (es. ogni 10 ms).
 */
void move_robotic_arm(robotic_arm_t* arm){
    if (!arm) return;

    servo_update(&arm->pinza);
    servo_update(&arm->tronco);
    servo_update(&arm->su_giu);
    servo_update(&arm->scatola);
}
