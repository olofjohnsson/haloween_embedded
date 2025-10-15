/**
 * @file vdd_level.h
 * @brief Function declaration for configuring VDD output voltage level.
 *
 * This module provides a function to configure the VDD output level
 * of the nRF52 device via the UICR register. The function checks the
 * current main regulator status and adjusts the REGOUT0 setting if
 * necessary.
 */

#ifndef VDD_LEVEL_H
#define VDD_LEVEL_H

/**
 * @brief Set the VDD output level to 3.3V if not already configured.
 *
 * This function checks the current main regulator status and, if the
 * REGOUT0 value in UICR is not set to 3.3V, reconfigures it to 3.3V.
 * The change requires enabling write access to non-volatile memory (NVMC),
 * modifying the UICR register, and performing a system reset for the
 * new setting to take effect.
 *
 * @note The function triggers a system reset if the configuration is updated.
 * @note Must be executed early in system initialization.
 *
 * @return 0 on success (the function never returns if a reset is triggered).
 */
int set_vdd_level(void);

#endif /* VDD_LEVEL_H */
