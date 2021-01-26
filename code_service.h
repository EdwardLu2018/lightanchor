/**
 * Copyright (c) 2015 - 2018, Nordic Semiconductor ASA
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 *
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 *
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 *
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
#ifndef CODE_SERVICE_H__
#define CODE_SERVICE_H__

#include "ble.h"
#include "ble_srv_common.h"
#include "nrf_sdh_ble.h"
#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**@brief   Macro for defining a ble_lbs instance.
 *
 * @param   _name   Name of the instance.
 * @hideinitializer
 */
#define CODE_SERVICE_DEF(_name)         \
    static code_service_t _name;        \
    NRF_SDH_BLE_OBSERVER(_name##_obs,   \
    BLE_LBS_BLE_OBSERVER_PRIO,          \
    code_service_on_ble_evt, &_name)

// d6a4de56-d451-4c76-85dd-360a038983df
#define CODE_UUID_BASE     {0xDF, 0x83, 0x89, 0x03, 0x0A, 0x36, 0xDD, 0x85, \
                            0x76, 0x4C, 0x51, 0xD4, 0x56, 0xDE, 0xA4, 0xD6}


#define CODE_UUID_SERVICE   0x1800
#define CODE_UUID_CHAR      0x1801

// Forward declaration of the code_service_t type.
typedef struct code_s code_service_t;

typedef void (*code_service_write_handler_t)(uint16_t conn_handle, code_service_t *p_lbs, uint8_t new_state);

/** @brief Code Button Service init structure. This structure contains all options and data needed for
 *        initialization of the service.*/
typedef struct
{
  code_service_write_handler_t code_write_handler;  /**< Event handler to be called when the Code Characteristic is written. */
} code_service_init_t;

/**@brief Code Button Service structure. This structure contains various status information for the service. */
struct code_s {
  uint16_t service_handle;                          /**< Handle of Code Button Service (as provided by the BLE stack). */
  ble_gatts_char_handles_t code_char_handles;       /**< Handles related to the Code Characteristic. */
  ble_gatts_char_handles_t button_char_handles;     /**< Handles related to the Button Characteristic. */
  uint8_t uuid_type;                                /**< UUID type for the Code Button Service. */
  code_service_write_handler_t code_write_handler;  /**< Event handler to be called when the Code Characteristic is written. */
};

/**@brief Function for initializing the Code Button Service.
 *
 * @param[out] p_lbs      Code Button Service structure. This structure must be supplied by
 *                        the application. It is initialized by this function and will later
 *                        be used to identify this particular service instance.
 * @param[in] p_lbs_init  Information needed to initialize the service.
 *
 * @retval NRF_SUCCESS If the service was initialized successfully. Otherwise, an error code is returned.
 */
uint32_t code_service_init(code_service_t *p_lbs, const code_service_init_t *p_lbs_init);

/**@brief Function for handling the application's BLE stack events.
 *
 * @details This function handles all events from the BLE stack that are of interest to the Code Button Service.
 *
 * @param[in] p_ble_evt  Event received from the BLE stack.
 * @param[in] p_context  Code Button Service structure.
 */
void code_service_on_ble_evt(ble_evt_t const *p_ble_evt, void *p_context);

#ifdef __cplusplus
}
#endif

#endif // CODE_SERVICE_H__

/** @} */
