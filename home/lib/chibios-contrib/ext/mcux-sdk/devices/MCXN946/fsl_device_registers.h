/*
 * Copyright 2014-2016 Freescale Semiconductor, Inc.
 * Copyright 2016-2023 NXP
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef __FSL_DEVICE_REGISTERS_H__
#define __FSL_DEVICE_REGISTERS_H__

/*
 * Include the cpu specific register header files.
 *
 * The CPU macro should be declared in the project or makefile.
 */
#if (defined(CPU_MCXN946VDF_cm33_core0) || defined(CPU_MCXN946VNL_cm33_core0))

#define MCXN946_cm33_core0_SERIES

/* CMSIS-style register definitions */
#include "MCXN946_cm33_core0.h"
/* CPU specific feature definitions */
#include "MCXN946_cm33_core0_features.h"

#elif (defined(CPU_MCXN946VDF_cm33_core1) || defined(CPU_MCXN946VNL_cm33_core1))

#define MCXN946_cm33_core1_SERIES

/* CMSIS-style register definitions */
#include "MCXN946_cm33_core1.h"
/* CPU specific feature definitions */
#include "MCXN946_cm33_core1_features.h"

#else
#error "No valid CPU defined!"
#endif

#endif /* __FSL_DEVICE_REGISTERS_H__ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
