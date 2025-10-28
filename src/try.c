#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "FreeRTOS.h"
#include "task.h"

// LED blink delay (in ms)
#define BLINK_DELAY_MS 500

// Task: blink the onboard LED
void blink_task(void *pvParameters) {
    if (cyw43_arch_init()) {
        printf("Wi-Fi init failed\n");
        vTaskDelete(NULL);
    }

    while (true) {
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        printf("LED ON\n");
        vTaskDelay(pdMS_TO_TICKS(BLINK_DELAY_MS));

        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        printf("LED OFF\n");
        vTaskDelay(pdMS_TO_TICKS(BLINK_DELAY_MS));
    }
}

// Main: start scheduler
int main(void) {
    stdio_init_all();

    xTaskCreate(
        blink_task,
        "BlinkTask",
        256,
        NULL,
        1,
        NULL
    );

    vTaskStartScheduler();

    while (true) {
        // Never should reach here
    }
}
