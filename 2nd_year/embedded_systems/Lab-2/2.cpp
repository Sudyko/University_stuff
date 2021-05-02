#include "hal.h"

unsigned int leds[8] = { GPIO_PIN_3, GPIO_PIN_4, GPIO_PIN_5,
                                GPIO_PIN_6, GPIO_PIN_8, GPIO_PIN_9,
                                GPIO_PIN_11, GPIO_PIN_12 };
unsigned int sw[4] = { GPIO_PIN_4, GPIO_PIN_8, GPIO_PIN_10, GPIO_PIN_12 };
unsigned char step = 8;

void vds(GPIO_PinState vd6, GPIO_PinState vd7_1, GPIO_PinState vd7_2) {
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, vd6);
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, vd7_1);
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, vd7_2);
}

unsigned char f(unsigned char step) {
    if (step < 4) return step;
    else return 6 - step;
}

void TIM6_IRQ_Handler() {
    if (step == 8) {

        vds(GPIO_PIN_SET, GPIO_PIN_RESET, GPIO_PIN_RESET);

        HAL_GPIO_WritePin(GPIOD, leds[1], GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOD, leds[2], GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOD, leds[3], GPIO_PIN_RESET);
        step = 0;

        HAL_GPIO_WritePin(GPIOD, leds[0], GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOD, leds[4], GPIO_PIN_SET);
    }
}

void TIM7_IRQ_Handler() {
    unsigned char number = 0;
    GPIO_PinState state;

    for (int i = 0; i < 4; i++) {
        state = HAL_GPIO_ReadPin(GPIOE, sw[i]);
        if (state == GPIO_PIN_SET) {
            number += 1 << (3 - i);
        }
    }
    HAL_GPIO_TogglePin(GPIOD, leds[f(step)]);
    HAL_GPIO_TogglePin(GPIOD, leds[f(step + 1)]);
    HAL_GPIO_TogglePin(GPIOD, leds[f(step) + 4]);
    HAL_GPIO_TogglePin(GPIOD, leds[f(step + 1) + 4]);
    HAL_Delay((step / 5) * 500 + number * 100);
    step = (step + 1) % 6;
}

int umain() {
    registerTIM6_IRQHandler(TIM6_IRQ_Handler);
    registerTIM7_IRQHandler(TIM7_IRQ_Handler);
    __enable_irq();

    WRITE_REG(TIM6_ARR, 500);
    WRITE_REG(TIM6_DIER, TIM_DIER_UIE);
    WRITE_REG(TIM6_PSC, 0);

    WRITE_REG(TIM7_ARR, 500);
    WRITE_REG(TIM7_DIER, TIM_DIER_UIE);
    WRITE_REG(TIM7_PSC, 1);

    WRITE_REG(TIM6_CR1, TIM_CR1_CEN);
    WRITE_REG(TIM7_CR1, TIM_CR1_CEN);
    return 0;
}