#include <stdio.h>
#include <stdbool.h>
#include "pico/stdlib.h"

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include "servo.h"
#include "robot.h"
#include "ir.h"

/* =========================================================================
 *                          VARIABILI GLOBALI
 * ========================================================================= */

// Servo
servo_motor_t servo_scatola;
servo_motor_t servo_tronco;
servo_motor_t servo_su_giu;
servo_motor_t servo_pinza;

// IR
IR_Sensor_t ir;

// Flag protetto da mutex
static bool oggetto_rilevato = false;
static SemaphoreHandle_t xIrMutex = NULL;

/* =========================================================================
 *                     FUNZIONI THREAD-SAFE PER L'IR
 * ========================================================================= */

static void set_oggetto_rilevato(bool value) {
    if (!xIrMutex) return;
    xSemaphoreTake(xIrMutex, portMAX_DELAY);
    oggetto_rilevato = value;
    xSemaphoreGive(xIrMutex);
}

static bool get_oggetto_rilevato(void) {
    bool value = false;
    if (!xIrMutex) return false;
    xSemaphoreTake(xIrMutex, portMAX_DELAY);
    value = oggetto_rilevato;
    xSemaphoreGive(xIrMutex);
    return value;
}

/* =========================================================================
 *                           FUNZIONI SERVO
 * ========================================================================= */

bool all_servos_finished() {
    return servo_finished(&servo_tronco) &&
           servo_finished(&servo_scatola) &&
           servo_finished(&servo_su_giu) &&
           servo_finished(&servo_pinza);
}

void move_to_start() {
    set_servo_target(&servo_scatola, robot.movimento_target.scatola);
    set_servo_target(&servo_tronco,  robot.movimento_target.tronco);
    set_servo_target(&servo_su_giu,  robot.movimento_target.su_giu);
    set_servo_target(&servo_pinza,   robot.movimento_target.pinza);

    while (!all_servos_finished()) {
        servo_update_interpolated(&servo_scatola);
        servo_update_interpolated(&servo_tronco);
        servo_update_interpolated(&servo_su_giu);
        servo_update_interpolated(&servo_pinza);
    }
}

/* =========================================================================
 *                                TASK IR
 * ========================================================================= */

void IrTask(void *p) {
    (void)p;

    while (1) {
        bool detected = ir_sensor_detect(&ir);
        set_oggetto_rilevato(detected);
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

/* =========================================================================
 *                           TASK SERVO
 * ========================================================================= */

void ServoTask(void *p) {
    (void)p;

    while (1) {
        servo_update_interpolated(&servo_scatola);
        servo_update_interpolated(&servo_tronco);
        servo_update_interpolated(&servo_su_giu);
        servo_update_interpolated(&servo_pinza);

        vTaskDelay(pdMS_TO_TICKS(20));
    }
}

/* =========================================================================
 *                           TASK LOGICA ROBOT
 * ========================================================================= */

void LogicTask(void *p) {
    (void)p;

    while (1) {

        if (!get_oggetto_rilevato() && robot.stato == STATO_START) {
            vTaskDelay(pdMS_TO_TICKS(50));
            continue;
        }

        robot_update_state_machine();

        set_servo_target(&servo_scatola, robot.movimento_target.scatola);
        set_servo_target(&servo_tronco,  robot.movimento_target.tronco);
        set_servo_target(&servo_su_giu,  robot.movimento_target.su_giu);
        set_servo_target(&servo_pinza,   robot.movimento_target.pinza);

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

/* =========================================================================
 *                           TASK STEPPER (NASTRO)
 * ========================================================================= */

#define STEP 16
#define DIR  17
#define STEP_DELAY_US 1800

void StepperTask(void *p) {
    (void)p;

    gpio_init(STEP);
    gpio_set_dir(STEP, GPIO_OUT);
    gpio_put(STEP, 0);
    
    gpio_init(DIR);
    gpio_set_dir(DIR, GPIO_OUT);
    gpio_disable_pulls(DIR);
    gpio_set_drive_strength(DIR, GPIO_DRIVE_STRENGTH_12MA);
    gpio_put(DIR, 1);


    sleep_ms(50);

    while (1) {

        if (!get_oggetto_rilevato()) {

            gpio_put(STEP, 1);
            sleep_us(STEP_DELAY_US);
            gpio_put(STEP, 0);
            sleep_us(STEP_DELAY_US);

        } else {
            vTaskDelay(pdMS_TO_TICKS(10));
        }
    }
}

/* =========================================================================
 *                                 MAIN
 * ========================================================================= */

int main() {

    stdio_init_all();

    xIrMutex = xSemaphoreCreateMutex();

    robot_init();
    ir_sensor_init(&ir, 15, true);  // active-low

    servo_init(&servo_scatola, 12, 0,   0.12f);
    servo_init(&servo_tronco,  13, 120, 0.12f);
    servo_init(&servo_su_giu,  11, 80,  0.12f);
    servo_init(&servo_pinza,   9, 20,   0.12f);

    move_to_start();
    sleep_ms(1500);

    xTaskCreate(IrTask,      "IrTask",      512,  NULL, 3, NULL);
    xTaskCreate(ServoTask,   "ServoTask",   1024, NULL, 2, NULL);
    xTaskCreate(LogicTask,   "LogicTask",   1024, NULL, 1, NULL);
    xTaskCreate(StepperTask, "StepperTask", 512,  NULL, 2, NULL);

    vTaskStartScheduler();

    while (1) {}
}
