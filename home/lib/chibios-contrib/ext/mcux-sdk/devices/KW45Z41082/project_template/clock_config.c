/*
 * Copyright 2021-2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/
/*
 * How to setup clock using clock driver functions:
 *
 * 1. Call CLOCK_InitXXX() to configure corresponding SCG clock source.
 *    Note: The clock could not be set when it is being used as system clock.
 *    In default out of reset, the CPU is clocked from FIRC,
 *    so before setting FIRC, change to use another avaliable clock source.
 *
 * 2. Call CLOCK_SetXtal0Freq() to set XTAL0 frequency based on board settings.
 *
 * 3. Call CLOCK_SetXxxModeSysClkConfig() to set SCG mode for Xxx run mode.
 *    Wait until the system clock source is changed to target source.
 *
 */

/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Clocks v11.0
processor: KW45Z41082xxxA
mcu_data: ksdk2_0
processor_version: 14.0.0
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

#include "fsl_ccm32k.h"
#include "fsl_spc.h"
#include "clock_config.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_CONFIG_SetScgOutSel
 * Description   : Set the SCG clock out select (CLKOUTSEL).
 * Param setting : The selected clock source.
 *
 *END**************************************************************************/
static void CLOCK_CONFIG_SetScgOutSel(clock_clkout_src_t setting)
{
     SCG0->CLKOUTCNFG = SCG_CLKOUTCNFG_CLKOUTSEL(setting);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_CONFIG_FircSafeConfig
 * Description   : This function is used to safely configure FIRC clock.
 *                 In default out of reset, the CPU is clocked from FIRC.
 *                 Before setting FIRC, change to use SIRC as system clock,
 *                 then configure FIRC. 
 * Param fircConfig  : FIRC configuration.
 *
 *END**************************************************************************/
static void CLOCK_CONFIG_FircSafeConfig(const scg_firc_config_t *fircConfig)
{
    scg_sys_clk_config_t curConfig;
    scg_sys_clk_config_t sysClkSafeConfigSource = {
         .divSlow = (uint32_t)kSCG_SysClkDivBy4, /* Slow clock divider */
         .divCore = (uint32_t)kSCG_SysClkDivBy1, /* Core clock divider */
         .src = (uint32_t)kSCG_SysClkSrcSirc,    /* System clock source */
    };
    /* Change to use SIRC as system clock source to prepare to change FIRCCFG register */
    CLOCK_SetRunModeSysClkConfig(&sysClkSafeConfigSource);
    /* Wait for clock source switch finished */
    do
    {
        CLOCK_GetCurSysClkConfig(&curConfig);
    } while (curConfig.src != sysClkSafeConfigSource.src);

    /* Init Firc */
    (void)CLOCK_InitFirc(fircConfig);
}

/*******************************************************************************
 ************************ BOARD_InitBootClocks function ************************
 ******************************************************************************/
void BOARD_InitBootClocks(void)
{
    BOARD_BootClockRUN();
}

/*******************************************************************************
 ********************** Configuration BOARD_BootClockRUN ***********************
 ******************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!Configuration
name: BOARD_BootClockRUN
called_from_default_init: true
outputs:
- {id: BUS_CLK.outFreq, value: 96 MHz}
- {id: CPU_CLK.outFreq, value: 96 MHz}
- {id: FIRC_CLK.outFreq, value: 96 MHz}
- {id: FRO16K_CLK.outFreq, value: 16 kHz}
- {id: ROSC_CLK.outFreq, value: 32.768 kHz}
- {id: SCG.FIRC_EXT_REF_TRIM_CLK.outFreq, value: 1 MHz}
- {id: SCGCLKOUT_CLK.outFreq, value: 24 MHz}
- {id: SIRC_CLK.outFreq, value: 6 MHz}
- {id: SLOW_CLK.outFreq, value: 24 MHz}
- {id: SOSC_CLK.outFreq, value: 32 MHz}
- {id: System_clock.outFreq, value: 96 MHz}
settings:
- {id: VDDCore, value: voltage_1v1}
- {id: CCM32K.CCM32K_32K_SEL.sel, value: CCM32K.OSC_32K}
- {id: CCM32K_FRO32K_CTRL_FRO_EN_CFG, value: Disabled}
- {id: CCM32K_OSC32K_CTRL_CAP_SEL_EN_CFG, value: Enabled}
- {id: CCM32K_OSC32K_CTRL_EXTAL_CAP_SEL_CFG, value: 8PF}
- {id: CCM32K_OSC32K_CTRL_OSC_EN_CFG, value: Enabled}
- {id: CCM32K_OSC32K_CTRL_XTAL_CAP_SEL_CFG, value: 8PF}
- {id: SCG.DIVCORE.scale, value: '1', locked: true}
- {id: SCG.DIVSLOW.scale, value: '4', locked: true}
- {id: SCG.FIRC_TRIMDIV.scale, value: '32', locked: true}
- {id: SCG_FIRCCSR_TRIM_CFG, value: Autotrimming}
- {id: SCG_SOSCCSR_SOSCEN_CFG, value: Enabled}
sources:
- {id: CCM32K.OSC_32K.outFreq, value: 32.768 kHz, enabled: true}
- {id: SCG.FIRC.outFreq, value: 96 MHz}
- {id: SCG.SOSC.outFreq, value: 32 MHz, enabled: true}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

/*******************************************************************************
 * Variables for BOARD_BootClockRUN configuration
 ******************************************************************************/
static const scg_firc_trim_config_t FircTrimConfig_BOARD_BootClockRUN =
{
    .trimMode = kSCG_FircTrimUpdate,              /* FIRC trim is enabled and trim value update is enabled */
    .trimSrc = kSCG_FircTrimSrcSysOsc,            /* Trim source is System OSC */
    .trimDiv = 31U,                               /* Divided by 32 */
    .trimCoar = 0U,                               /* Trim value, see Reference Manual for more information */
    .trimFine = 0U,                               /* Trim value, see Reference Manual for more information */
};
const scg_sys_clk_config_t g_sysClkConfig_BOARD_BootClockRUN =
{
    .divSlow = (uint32_t)kSCG_SysClkDivBy4,       /* Slow Clock Divider: divided by 4 */
    .divBus = (uint32_t)kSCG_SysClkDivBy1,        /* Bus Clock Divider: divided by 1 */
    .divCore = (uint32_t)kSCG_SysClkDivBy1,       /* Core Clock Divider: divided by 1 */
    .src = (uint32_t)kSCG_SysClkSrcFirc,          /* Fast IRC is selected as System Clock Source */
};
const scg_sosc_config_t g_scgSysOscConfig_BOARD_BootClockRUN =
{
    .freq = 32000000U,                            /* System Oscillator frequency: 32000000Hz */
    .monitorMode = kSCG_SysOscMonitorDisable,     /* System OSC Clock Monitor is disabled */
    .enableMode = kSCG_SoscEnable,                /* System OSC Enable */
};
const scg_sirc_config_t g_scgSircConfig_BOARD_BootClockRUN =
{
    .enableMode = kSCG_SircDisableInSleep,        /* Slow IRC is disabled in sleep modes */
};
const scg_firc_config_t g_scgFircConfig_BOARD_BootClockRUN =
{
    .enableMode = kSCG_FircEnable,                /* Fast IRC is enabled */
    .range = kSCG_FircRange96M,                   /* 96 Mhz FIRC clock selected */
    .trimConfig = &FircTrimConfig_BOARD_BootClockRUN,
};
static const ccm32k_osc_config_t g_ccm32kOscConfig_BOARD_BootClockRUN =
{
    .coarseAdjustment = kCCM32K_OscCoarseAdjustmentRange0,/* ESR_Range0 */
    .enableInternalCapBank = true,                /* Internal capacitance bank is enabled */
    .xtalCap = kCCM32K_OscXtal8pFCap,             /* 8 pF */
    .extalCap = kCCM32K_OscExtal8pFCap,           /* 8 pF */
};
/*******************************************************************************
 * Code for BOARD_BootClockRUN configuration
 ******************************************************************************/
void BOARD_BootClockRUN(void)
{
    uint32_t coreFreq;
    scg_sys_clk_config_t curConfig;
    spc_active_mode_core_ldo_option_t ldoOption;

    /* Unlock FIRC, SIRC, ROSC and SOSC control status registers */
    CLOCK_UnlockFircControlStatusReg();
    CLOCK_UnlockSircControlStatusReg();
    CLOCK_UnlockRoscControlStatusReg();
    CLOCK_UnlockSysOscControlStatusReg();

    /* Get the CPU Core frequency */
    coreFreq = CLOCK_GetSysClkFreq(kSCG_SysClkCore);

    if (coreFreq <= BOARD_BOOTCLOCKRUN_CORE_CLOCK) {
        /* Set the LDO_CORE VDD regulator level */
        ldoOption.CoreLDOVoltage = kSPC_CoreLDO_NormalVoltage;
        ldoOption.CoreLDODriveStrength = kSPC_CoreLDO_NormalDriveStrength;
        (void)SPC_SetActiveModeCoreLDORegulatorConfig(SPC0, &ldoOption);
        /* Configure Flash to support different voltage level and frequency */
        FMU0->FCTRL = (FMU0->FCTRL & ~((uint32_t)FMU_FCTRL_RWSC_MASK)) | (FMU_FCTRL_RWSC(0x2U));
        /* Specifies the operating voltage for the SRAM's read/write timing margin */
        SPC_SetSRAMOperateVoltage(SPC0, kSPC_SRAM_OperatVoltage1P1V);
    }

    /* Config 32k Crystal Oscillator */
    CCM32K_Set32kOscConfig(CCM32K, kCCM32K_Enable32kHzCrystalOsc, &g_ccm32kOscConfig_BOARD_BootClockRUN);
    /* Monitor is disabled */
    CLOCK_SetRoscMonitorMode(kSCG_RoscMonitorDisable);
    /* Wait for the 32kHz crystal oscillator to be stable */
    while ((CCM32K_GetStatusFlag(CCM32K) & CCM32K_STATUS_OSC32K_RDY_MASK) == 0UL)
    {
    }
    /* OSC32K clock output is selected as clock source */
    CCM32K_SelectClockSource(CCM32K, kCCM32K_ClockSourceSelectOsc32k);
    /* Disable the FRO32K clock */
    CCM32K_Enable32kFro(CCM32K, false);
    /* Wait for RTC Oscillator to be Valid */
    while (!CLOCK_IsRoscValid())
    {
    }

    CLOCK_SetXtal32Freq(BOARD_BOOTCLOCKRUN_ROSC_CLOCK);

    /* Init FIRC */
    CLOCK_CONFIG_FircSafeConfig(&g_scgFircConfig_BOARD_BootClockRUN);
    /* Set SCG to FIRC mode */
    CLOCK_SetRunModeSysClkConfig(&g_sysClkConfig_BOARD_BootClockRUN);
    /* Wait for clock source switch finished */
    do
    {
        CLOCK_GetCurSysClkConfig(&curConfig);
    } while (curConfig.src != g_sysClkConfig_BOARD_BootClockRUN.src);
    /* Initializes SOSC according to board configuration */
    (void)CLOCK_InitSysOsc(&g_scgSysOscConfig_BOARD_BootClockRUN);
    /* Set the XTAL0 frequency based on board settings */
    CLOCK_SetXtal0Freq(g_scgSysOscConfig_BOARD_BootClockRUN.freq);
    /* Init SIRC */
    (void)CLOCK_InitSirc(&g_scgSircConfig_BOARD_BootClockRUN);
    /* Set SystemCoreClock variable */
    SystemCoreClock = BOARD_BOOTCLOCKRUN_CORE_CLOCK;

    if (coreFreq > BOARD_BOOTCLOCKRUN_CORE_CLOCK) {
        /* Configure Flash to support different voltage level and frequency */
        FMU0->FCTRL = (FMU0->FCTRL & ~((uint32_t)FMU_FCTRL_RWSC_MASK)) | (FMU_FCTRL_RWSC(0x2U));
        /* Specifies the operating voltage for the SRAM's read/write timing margin */
        SPC_SetSRAMOperateVoltage(SPC0, kSPC_SRAM_OperatVoltage1P1V);
        /* Set the LDO_CORE VDD regulator level */
        ldoOption.CoreLDOVoltage = kSPC_CoreLDO_NormalVoltage;
        ldoOption.CoreLDODriveStrength = kSPC_CoreLDO_NormalDriveStrength;
        (void)SPC_SetActiveModeCoreLDORegulatorConfig(SPC0, &ldoOption);
    }

    /* Set SCG CLKOUT selection. */
    CLOCK_CONFIG_SetScgOutSel(kClockClkoutSelScgSlow);
}
