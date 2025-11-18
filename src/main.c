
#include <stdio.h>
#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"

#include "servo.h"
#include "robot.h"  
// --- inizializziamo il tuo braccio robotico ---
robotic_arm_t arm = {
    .pinza = {
        .pin = 10,
        .servo_min_angle = 20,
        .servo_max_angle = 120,
        .servo_current_angle = 20,
        .target_angle = 120,      // inizializziamo come nel LogicTask
        .step_angle = 1.0f
    },

    .tronco = {
        .pin = 11,
        .servo_min_angle = 120,
        .servo_max_angle = 180,
        .servo_current_angle = 120,
        .target_angle = 120,      // iniziale = min
        .step_angle = 2.0f
    },

    .su_giu = {
        .pin = 12,
        .servo_min_angle = 120,
        .servo_max_angle = 180,
        .servo_current_angle = 120,
        .target_angle = 120,      // iniziale = min
        .step_angle = 2.5f
    },

    .scatola = {
        .pin = 13,
        .servo_min_angle = 0,
        .servo_max_angle = 180,
        .servo_current_angle = 0,
        .target_angle = 180,      // iniziale = max
        .step_angle = 1.0f
    }
};



/*****************************************************************
 *      TASK 1: ServoUpdateTask
 *  Aggiorna i servo (micro-step). NON blocca.
 *****************************************************************/
void vServoUpdateTask(void *pv) {

    const TickType_t period = pdMS_TO_TICKS(10);

    for (;;) {
        move_robotic_arm(&arm);     
        vTaskDelay(period);
    }
}


/*****************************************************************
 *      TASK 2: LogicTask
 *  Decide quando cambiare i target.
 *****************************************************************/
void vLogicTask(void *pv) {

    for (;;) {

        // Quando TUTTI i servo hanno finito...
        if (all_servos_finished(&arm)) {
            swap_all_target_angles(&arm);
        }

        vTaskDelay(pdMS_TO_TICKS(50));
    }
}


/*****************************************************************
 *                      MAIN
 *****************************************************************/
int main() {
    stdio_init_all();

    // inizializza PWM di ogni servo
    setup_pwm(arm.pinza.pin);
    setup_pwm(arm.tronco.pin);
    setup_pwm(arm.su_giu.pin);
    setup_pwm(arm.scatola.pin);

    // crea task
    xTaskCreate(vServoUpdateTask, "ServoUpdate", 256, NULL, 2, NULL);
    xTaskCreate(vLogicTask,      "LogicTask",    256, NULL, 1, NULL);

    // avvia scheduler FreeRTOS
    vTaskStartScheduler();

    while (1) {}
}
