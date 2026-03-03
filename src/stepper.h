#ifndef STEPPER_H
#define STEPPER_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint32_t step_pin;
    uint32_t dir_pin;
    uint32_t enable_pin;

    bool running;
    bool direction;
} stepper_t;

void stepper_init(stepper_t *m,
                  uint32_t step_pin,
                  uint32_t dir_pin,
                  uint32_t enable_pin);

void stepper_start(stepper_t *m, bool direction);
void stepper_stop(stepper_t *m);
void stepper_generate_step(stepper_t *m);

#endif