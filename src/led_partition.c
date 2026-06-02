/*
 * Copyright (c) 2026, CATIE
 * SPDX-License-Identifier: Apache-2.0
 */

#include <tfm_ns_interface.h>

#include "led_partition.h"

#include "psa/client.h"
#include "psa_manifest/sid.h"

psa_status_t lp_led_toggle(void)
{
    psa_status_t status;
    psa_handle_t handle;

    handle = psa_connect(TFM_LP_LED_TOGGLE_SID,
                         TFM_LP_LED_TOGGLE_VERSION);
    if (!PSA_HANDLE_IS_VALID(handle))
    {
        return PSA_ERROR_GENERIC_ERROR;
    }

    /* No payload: the toggle takes no input and returns no output. */
    status = psa_call(handle, PSA_IPC_CALL, NULL, 0, NULL, 0);

    psa_close(handle);

    return status;
}
