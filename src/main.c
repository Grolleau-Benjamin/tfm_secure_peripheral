/*
 * Copyright (c) 2026, CATIE
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr / kernel.h>
#include <tfm_ns_interface.h>

#include "led_partition.h"

int main(void)
{
    printk("NSPE: toggling secure LED (LD7/PH7) via TF-M partition\n");

    while (1)
    {
        psa_status_t status = lp_led_toggle();

        if (status != PSA_SUCCESS)
        {
            printk("lp_led_toggle failed: %d\n", status);
        }

        k_sleep(K_MSEC(500));
    }

    return 0;
}
