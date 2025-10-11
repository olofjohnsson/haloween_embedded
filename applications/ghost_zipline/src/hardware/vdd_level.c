/**
 * @file vdd_level.c
 * @brief Implementation of function to configure the VDD output voltage level.
 */

#include <zephyr/kernel.h>
#include <hal/nrf_power.h>
#include <hal/nrf_nvmc.h>
#include <hal/nrf_uicr.h>

/**
 * @brief Set the VDD output level to 3.3V if not already configured.
 *
 * This function checks if the main regulator is active and whether the
 * UICR->REGOUT0 register is already configured for 3.3V. If not, it updates
 * the UICR value, enables NVMC write mode, waits for the operation to complete,
 * and then resets the system for the change to take effect.
 *
 * @note Writing to UICR requires enabling NVMC write mode.
 * @note The system will reset if the configuration is changed.
 *
 * @retval 0 Always returns 0 (function resets the system if change occurs).
 */
int set_vdd_level(void)
{
    if ((nrf_power_mainregstatus_get(NRF_POWER) == NRF_POWER_MAINREGSTATUS_HIGH) &&
        ((NRF_UICR->REGOUT0 & UICR_REGOUT0_VOUT_Msk) !=
         (UICR_REGOUT0_VOUT_3V3 << UICR_REGOUT0_VOUT_Pos)))
    {
        NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Wen << NVMC_CONFIG_WEN_Pos;
        while (NRF_NVMC->READY == NVMC_READY_READY_Busy) { ; }

        NRF_UICR->REGOUT0 =
            (NRF_UICR->REGOUT0 & ~((uint32_t)UICR_REGOUT0_VOUT_Msk)) |
            (UICR_REGOUT0_VOUT_3V3 << UICR_REGOUT0_VOUT_Pos);

        NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Ren << NVMC_CONFIG_WEN_Pos;
        while (NRF_NVMC->READY == NVMC_READY_READY_Busy) { ; }

        /* A reset is required for the changes to take effect */
        NVIC_SystemReset();
    }

    return 0;
}
