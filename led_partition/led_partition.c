/*
 * Copyright (c) 2026, CATIE
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdint.h>

#include "psa/service.h"
#include "psa_manifest/tfm_led_partition.h"
#include "stm32u5xx.h"

#define LED_PORT GPIOH
#define LED_PIN 7U

static void led_gpio_init(void)
{
    /** reference: RM0456, STM32U5 series Arm®-based 32-bit MCUs
     * Link: https://www.st.com/resource/en/reference_manual/rm0456-stm32u5-series-armbased-32bit-mcus-stmicroelectronics.pdf
     */

    RCC->AHB2ENR1 |= RCC_AHB2ENR1_GPIOHEN;
    (void)RCC->AHB2ENR1;

    LED_PORT->MODER &= ~(3U << (LED_PIN * 2U));
    LED_PORT->MODER |= (1U << (LED_PIN * 2U));
    LED_PORT->OTYPER &= ~(1U << LED_PIN);
    LED_PORT->PUPDR &= ~(3U << (LED_PIN * 2U));

    LED_PORT->BSRR = (1U << LED_PIN);
}

static psa_status_t led_toggle(void)
{
    LED_PORT->ODR ^= (1U << LED_PIN);
    return PSA_SUCCESS;
}

psa_status_t tfm_lp_req_mngr_init(void)
{
    psa_msg_t msg;
    led_gpio_init();

    while (1)
    {
        psa_signal_t signals = psa_wait(PSA_WAIT_ANY, PSA_BLOCK);

        if (signals & TFM_LP_LED_TOGGLE_SIGNAL)
        {
            psa_get(TFM_LP_LED_TOGGLE_SIGNAL, &msg);
            switch (msg.type)
            {
            case PSA_IPC_CONNECT:
            case PSA_IPC_DISCONNECT:
                psa_reply(msg.handle, PSA_SUCCESS);
                break;
            case PSA_IPC_CALL:
                psa_reply(msg.handle, led_toggle());
                break;
            default:
                psa_panic();
            }
        }
        else
        {
            psa_panic();
        }
    }

    return PSA_ERROR_SERVICE_FAILURE;
}