/******************************************************************************
 * Copyright (c) 2018 by Cougs in Space - Washington State University         *
 * Cougs in Space website: cis.vcea.wsu.edu                                   *
 *                                                                            *
 * This file is a part of flight and/or ground software for Cougs in Space's  *
 * satellites. This file is proprietary and confidential.                     *
 * Unauthorized copying of this file, via any medium is strictly prohibited.  *
 ******************************************************************************/
/**
 * @file GPS.h
 * @author Cody Sigvartson
 * @date 22 October 2018
 * @brief Provides an interface for the on-board GPS 
 *
*/

#ifndef SRC_SYSTEMINTERFACES_GPS_H_
#define SRC_SYSTEMINTERFACES_GPS_H_

#include <mbed.h>
#include <DigitalIn.h>
#include <DigitalOut.h>


#define MSG_SIZE 120 // max size of NEMA response is 120 chars
#define GPS_ACK_TIMEOUT_MS 1000 // default wait time for how long the sender should wait for ack

#define RMC_ID "GPRMC"
#define NUM_RMC_ATTRIBUTES 9

typedef enum attributes {
	RAM_ONLY = 0x00,
	RAM_FLASH = 0x01,
	TEMP = 0x02
}Attributes_t;

typedef enum rmcfieldtype{
	TIME,
	LAT,
	LAT_DIR,
	LONG,
	LONG_DIR,
	ALTITUDE,
	SOG,
	DATE,
	NONE
}RMCField_t;

// field lookup table for decoding RMC NMEA data
RMCField_t rmcFieldTypes[NUM_RMC_ATTRIBUTES] = {TIME,NONE,LAT,LAT_DIR,LONG,LONG_DIR,SOG,NONE,DATE};

class GPS {
  public:
    GPS(Serial &serial, DigitalOut &reset, DigitalIn &pulse);
 
	// Accessors
	uint32_t getUtcTime() const;
	void getLat(int64_t *lat_upper, int64_t *lat_lower);
	void getLong(int64_t *long_upper, int64_t *long_lower);
	uint16_t getSpeedOverGround() const;
	uint16_t getDate() const;

	
	uint8_t read();
	
	// GPS configuration methods
    uint8_t setUpdateRate(uint8_t frequency, Attributes_t attribute);
    uint8_t resetReceiver(bool reboot);
    uint8_t configNMEA(uint8_t messageName, bool enable, Attributes_t attribute);
    uint8_t configNMEA(uint8_t nmeaByte, Attributes_t attribute);
    uint8_t configPowerSave(bool enable, Attributes_t attribute);
	
	// Initialize the GPS to default state
	uint8_t initialize();
  private:
	uint8_t buf[MSG_SIZE];
	// Serial interface (mbed.h)
	Serial &serial;
	
	// Digital pin interfaces (mbed.h)
	DigitalOut &reset;
	DigitalIn &pulse; // sends a 1hz pulse to adjust clock
	
	// GPS attributes
	uint8_t nmeaState; // stores current configuration of which NMEA strings are enabled
	
	// RMC attributes
    uint32_t utcTime; // UTC time in hundredths of a second
	int64_t lat_upper, lat_lower; // lat_upper degrees, lat_lower minutes (10^7 precision)
	int64_t long_upper, long_lower; // long_upper degrees, long_lower minutes (10^7 precision)
    uint16_t speed; // speed over ground in knots
    uint16_t date; // date ddmmyy

	// Utility functions
	void parse_degrees(uint8_t *field, int64_t *upper, int64_t *lower);
	uint8_t parseRMC(uint8_t *nmea);
	uint8_t parseRMCField(uint8_t *field, RMCField_t type);
    uint8_t sendCommand(uint8_t messageid, uint8_t *messagebody, uint32_t bodylen, uint32_t timemout = GPS_ACK_TIMEOUT_MS);
    uint8_t sendPacket(uint8_t *packet, uint32_t size, uint32_t timeout);
	void printPacket(uint8_t *packet, uint32_t size);
};

#endif /* !SRC_SYSTEMINTERFACES_GPS_H_ */
