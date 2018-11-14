/******************************************************************************
 * Copyright (c) 2018 by Cougs in Space - Washington State University         *
 * Cougs in Space website: cis.vcea.wsu.edu                                   *
 *                                                                            *
 * This file is a part of flight and/or ground software for Cougs in Space's  *
 * satellites. This file is proprietary and confidential.                     *
 * Unauthorized copying of this file, via any medium is strictly prohibited.  *
 ******************************************************************************/
/**
 * @file ADCSPins.h
 * @author Cody Sigvartson
 * @date 13 Apr 2018
 * @brief Contains all hardware pins as constants
 */

#ifndef SRC_ADCSPINS_H_
#define SRC_ADCSPINS_H_

#define GPS_SERIAL_TX_PIN PA_9
#define GPS_SERIAL_RX_PIN PA_10

#define GPS_DIGITAL_IN_PIN PA_11
#define GPS_DIGITAL_OUT_PIN PA_8

#define SWO_UART0_TX 0x00
#define SWO_UART0_RX 0x00

#endif /* SRC_ADCSPINS_H_ */
