/******************************************************************************
 * Copyright (c) 2018 by Cougs in Space - Washington State University         *
 * Cougs in Space website: cis.vcea.wsu.edu                                   *
 *                                                                            *
 * This file is a part of flight and/or ground software for Cougs in Space's  *
 * satellites. This file is proprietary and confidential.                     *
 * Unauthorized copying of this file, via any medium is strictly prohibited.  *
 ******************************************************************************/
/**
 * @file main.cpp
 * @author Bradley Davis
 * @date 6 Mar 2018
 * @brief Starts the IHU software
 *
 * Initializes IHU object and starts the eventQueue
 */

#include <mbed.h>
#include <rtos.h>
#include "ADCSPins.h"
#include "tools/CISError.h"

/**
 * Program start routine
 * @return error code
 */
int main(void) {
	DigitalOut reset(GPS_DIGITAL_OUT_PIN);
	DigitalIn pulse(GPS_DIGITAL_IN_PIN);
	Serial serial(GPS_SERIAL_TX_PIN, GPS_SERIAL_RX_PIN);
	
	
	return ERROR_SUCCESS;
}
