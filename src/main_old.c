
/*#include <stdio.h>
#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"
#include "hardware/pwm.h"

#include "servo.h"
#include "robot.h"  
// --- inizializziamo il tuo braccio robotico ---

bool paused = false;
robotic_arm_t arm = {
    .pinza = {
        .pin = 10,
        .servo_min_angle = 20,
        .servo_max_angle = 120,
        .servo_current_angle = 20,
        //.target_angle = 120,      // inizializziamo come nel LogicTask
        .step_angle = 2.0f
    },

    .tronco = {
        .pin = 13,
        .servo_min_angle = 120,
        .servo_max_angle = 170,
        .servo_current_angle = 120,
        //.target_angle = 170,      // iniziale = min
        .step_angle = 1.0f
    },

    .su_giu = {
        .pin = 11,
        .servo_min_angle = 35,
        .servo_max_angle = 80,
        .servo_current_angle = 80,
        //.target_angle = 35,      // iniziale = min
        .step_angle = 1.0f
    },

    .scatola = {
        .pin = 12,
        .servo_min_angle = 0,
        .servo_max_angle = 180,
        .servo_current_angle = 0,
        //.target_angle = 180,      // iniziale = max
        .step_angle = 1.0f
    }
};




 
void vServoUpdateTask(void *pv) {

    const TickType_t period = pdMS_TO_TICKS(10);

    for (;;) {
        move_robotic_arm(&arm);
       // printf("Su/Giu angle: %.2f\t target angle: %.2f\n", arm.scatola.servo_current_angle, arm.scatola.target_angle);
        //sleep_ms(1000);
             
        vTaskDelay(period);
    }
}







 
void vLogicTask(void *pv) {

    for (;;) {

        // Quando TUTTI i servo hanno finito...
        if (all_servos_finished(&arm)) {
            swap_all_target_angles(&arm);
            //paused = true;
            //vTaskDelay(pdMS_TO_TICKS(1000));
            //paused = false;
        }

        vTaskDelay(pdMS_TO_TICKS(20));

    }
}








int main() {
    stdio_init_all();

    // inizializza PWM di ogni servo
   // setup_pwm(arm.pinza.pin);
    setup_pwm(arm.scatola.pin);
    setup_pwm(arm.tronco.pin);
    setup_pwm(arm.su_giu.pin);
    setup_pwm(arm.pinza.pin);
    //setup_pwm(arm.su_giu.pin);
    //setup_pwm(arm.scatola.pin);

    //arm.tronco.target_angle = arm.tronco.servo_current_angle; 
    // crea task

    set_servo_angle(arm.scatola.pin, arm.scatola.servo_current_angle, &arm.scatola);
    set_servo_angle(arm.tronco.pin, arm.tronco.servo_current_angle, &arm.tronco);
    set_servo_angle(arm.su_giu.pin, arm.su_giu.servo_current_angle, &arm.su_giu);
    set_servo_angle(arm.pinza.pin, arm.pinza.servo_current_angle, &arm.pinza);
    sleep_ms(3000);




    //pwm_set_enabled(pwm_gpio_to_slice_num(arm.su_giu.pin), false);
    xTaskCreate(vServoUpdateTask, "ServoUpdate", 256, NULL, 2, NULL);
    xTaskCreate(vLogicTask,      "LogicTask",    256, NULL, 1, NULL);

    // avvia scheduler FreeRTOS
    vTaskStartScheduler();

    while (1) {}
}

*/

#include <stdio.h>
#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"
#include "servo.h"
#include "robot.h"
#include "ir.h"
#include <stdbool.h>

/*
 * Servomotori
 */
servo_motor_t servo_scatola;
servo_motor_t servo_tronco;
servo_motor_t servo_su_giu;
servo_motor_t servo_pinza;
IR_Sensor_t ir;

/*
 * TASK: aggiornamento interpolato servo
 */


bool all_servos_finished(){
    return servo_finished(&servo_tronco) &&
           servo_finished(&servo_scatola)&&
           servo_finished(&servo_su_giu)&&
           servo_finished(&servo_pinza);

}

void move_to_start(){
    set_servo_target(&servo_scatola, robot.movimento_target.scatola);
    set_servo_target(&servo_tronco,  robot.movimento_target.tronco);
    set_servo_target(&servo_su_giu,  robot.movimento_target.su_giu);
    set_servo_target(&servo_pinza,   robot.movimento_target.pinza);

    while(!all_servos_finished()){
        servo_update_interpolated(&servo_scatola);
        servo_update_interpolated(&servo_tronco);
        servo_update_interpolated(&servo_su_giu);
        servo_update_interpolated(&servo_pinza);
    }


}
void ServoTask(void *p) {
    while (1) {
        servo_update_interpolated(&servo_scatola);
        servo_update_interpolated(&servo_tronco);
        servo_update_interpolated(&servo_su_giu);
        servo_update_interpolated(&servo_pinza);
        vTaskDelay(pdMS_TO_TICKS(20));
    }
}

/*
 * TASK: logica/movimento
 */
 void LogicTask(void *p) {
    robot_state_t stato_precedente = robot.stato;

    while (1) {

        // Salva lo stato precedente
        stato_precedente = robot.stato;

        // Aggiorna la macchina a stati
        robot_update_state_machine();

        // --- DELAY SPECIALE: GRAB → GO_UP ---
        if (stato_precedente == STATO_GRAB && robot.stato == STATO_GO_UP) {
            // aspetta che la pinza si chiuda
            //vTaskDelay(pdMS_TO_TICKS(5000));
        }

        // Aggiorna i target
        set_servo_target(&servo_scatola, robot.movimento_target.scatola);
        set_servo_target(&servo_tronco,  robot.movimento_target.tronco);
        set_servo_target(&servo_su_giu,  robot.movimento_target.su_giu);
        set_servo_target(&servo_pinza,   robot.movimento_target.pinza);

        // Delay regolare
        vTaskDelay(pdMS_TO_TICKS(1000)); 
    }
}
 


int main() {
    stdio_init_all();

    robot_init();
    ir_sensor_init(&ir, 15, true);

    // INIZIALIZZAZIONE SERVI – con angolo iniziale e velocità
    servo_init(&servo_scatola, 12, 0,   0.12f);
    servo_init(&servo_tronco,  13, 120, 0.12f);
    servo_init(&servo_su_giu,  11, 80,  0.12f);
    servo_init(&servo_pinza,   10, 20,  0.12f);

    move_to_start();

    sleep_ms(2000);


    // quando FSM parte, i target verranno aggiornati
    xTaskCreate(ServoTask, "ServoTask", 1024, NULL, 2, NULL);
    xTaskCreate(LogicTask, "LogicTask", 1024, NULL, 1, NULL);

    vTaskStartScheduler();
    while (1) {}
}
