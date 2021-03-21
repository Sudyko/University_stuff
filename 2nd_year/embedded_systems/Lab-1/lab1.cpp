#include "hal.h"

void vds(GPIO_PinState vd6, GPIO_PinState vd7_1, GPIO_PinState vd7_2) {
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, vd6);
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, vd7_1);
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, vd7_2);
} // set VD6 & VD7 LEDs

unsigned char f(unsigned char step) {
    if (step < 4) return step;
    else return 6 - step;
}

int umain() {
    unsigned int leds[8] = { GPIO_PIN_3, GPIO_PIN_4, GPIO_PIN_5,
                                 GPIO_PIN_6, GPIO_PIN_8, GPIO_PIN_9,
                                 GPIO_PIN_11, GPIO_PIN_12 };
    unsigned int sw[4] = { GPIO_PIN_4, GPIO_PIN_8, GPIO_PIN_10, GPIO_PIN_12 };
    unsigned char step = 8; // animation frame, -1 == not triggered
    bool isStopped = false;
    while (1) { // main loop
        unsigned char number = 0; // num made of switches, 10 == animation
        GPIO_PinState state; // for reading pins
        for (int i = 0; i < 4; i++)
        { // read switches
            state = HAL_GPIO_ReadPin(GPIOE, sw[i]);
            if (state == GPIO_PIN_SET) {
                number += 1 << (3 - i);
            }
        }
        if (number != 2) { // display number 
            if (step != 8) {
                HAL_GPIO_WritePin(GPIOD, leds[4], GPIO_PIN_RESET);
                HAL_GPIO_WritePin(GPIOD, leds[5], GPIO_PIN_RESET);
                HAL_GPIO_WritePin(GPIOD, leds[6], GPIO_PIN_RESET);
                HAL_GPIO_WritePin(GPIOD, leds[7], GPIO_PIN_RESET);
                step = 8;
                isStopped = false;
            }
            vds(GPIO_PIN_RESET, GPIO_PIN_SET, GPIO_PIN_RESET);
            // set LEDX LEDs
            HAL_GPIO_WritePin(GPIOD, leds[0], HAL_GPIO_ReadPin(GPIOE, sw[0]));
            HAL_GPIO_WritePin(GPIOD, leds[1], HAL_GPIO_ReadPin(GPIOE, sw[1]));
            HAL_GPIO_WritePin(GPIOD, leds[2], HAL_GPIO_ReadPin(GPIOE, sw[2]));
            HAL_GPIO_WritePin(GPIOD, leds[3], HAL_GPIO_ReadPin(GPIOE, sw[3]));
        }
        else { // display animation
            if (step == 8) { // boot anim
                // set VD6 & VD7 LEDs
                vds(GPIO_PIN_SET, GPIO_PIN_RESET, GPIO_PIN_RESET);
                //clear number
                HAL_GPIO_WritePin(GPIOD, leds[1], GPIO_PIN_RESET);
                HAL_GPIO_WritePin(GPIOD, leds[2], GPIO_PIN_RESET);
                HAL_GPIO_WritePin(GPIOD, leds[3], GPIO_PIN_RESET);
                step = 0;
                // set LEDs
                HAL_GPIO_WritePin(GPIOD, leds[0], GPIO_PIN_SET);
                HAL_GPIO_WritePin(GPIOD, leds[4], GPIO_PIN_SET);
                HAL_Delay(500);
            }
            state = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_15); // read nBTN
            if (state == GPIO_PIN_RESET) { // on click
                isStopped = !isStopped;
            }
            if (isStopped) {
                vds(GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_SET);
                HAL_Delay(500);
            }
            else { // play anim
                vds(GPIO_PIN_SET, GPIO_PIN_RESET, GPIO_PIN_RESET);
                // set LEDs
                HAL_GPIO_TogglePin(GPIOD, leds[f(step)]);
                HAL_GPIO_TogglePin(GPIOD, leds[f(step + 1)]);
                HAL_GPIO_TogglePin(GPIOD, leds[f(step) + 4]);
                HAL_GPIO_TogglePin(GPIOD, leds[f(step + 1) + 4]);
                HAL_Delay(500 + (step / 5) * 500);
                step = (step + 1) % 6;
            }
        }
    }

	return 0;
}