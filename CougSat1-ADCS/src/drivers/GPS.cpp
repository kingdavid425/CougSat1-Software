/******************************************************************************
 * Copyright (c) 2018 by Cougs in Space - Washington State University         *
 * Cougs in Space website: cis.vcea.wsu.edu                                   *
 *                                                                            *
 * This file is a part of flight and/or ground software for Cougs in Space's  *
 * satellites. This file is proprietary and confidential.                     *
 * Unauthorized copying of this file, via any medium is strictly prohibited.  *
 ******************************************************************************/
/**
 * @file GPS.cpp
 * @author Cody Sigvartson
 * @date 13 November 2018
 * @brief Provides an interface to the on-board GPS 
 *
*/

#include "GPS.h"
#include <cstring>
#include "tools/CISConsole.h"
#include "tools/CISError.h"

/**
 * @brief Constructs the GPS object
 *
 * @param serial object
 * @param reset pin (active LOW) leave HIGH, pulse LOW will reset
 * @param pulse pin precision 1Hz heartbeat from GPS clock
 */
GPS::GPS(Serial &serial, DigitalOut &reset, DigitalIn &pulse) : serial(serial), reset(reset), pulse(pulse){
	this->nmeaState = 0x0; // disable all nmea messages
	this->reset = reset;
	this->pulse = pulse;
}

/**
 * @brief Accessor for most recent UTC reported by GPS
 *
 * @return UTC time as hhmmss
 */
uint32_t GPS::getUtcTime() const{
	return this->utcTime;
}

/**
 * @brief Accessor for most recent latitude reported by GPS
 *
 * @param lat_upper degrees
 * @param lat_lower minutes (10^7 precision)
 */
void GPS::getLat(int64_t *lat_upper, int64_t *lat_lower){
	*lat_upper = this->lat_upper;
	*lat_lower = this->lat_lower;
}

/**
 * @brief Accessor for most recent longitude reported by GPS
 *
 * @param long_upper degrees
 * @param long_lower minutes (10^7 precision)
 */
void GPS::getLong(int64_t *long_upper, int64_t *long_lower){
	*long_upper = this->long_upper;
	*long_lower = this-> long_lower;
}

/**
 * @brief Accessor for most recent SOG reported by GPS
 *
 * @return speed over ground in knots
 */
uint16_t GPS::getSpeedOverGround() const{
	return this->speed;
}

/**
 * @brief Accessor for date reported by GPS
 *
 * @return date ddmmyy
 */
uint16_t GPS::getDate() const{
	return this->date;
}

/**
 * @brief Reads one byte of data
 *
 * @return error code
 */
uint8_t GPS::read(){
	memset(buf,0,MSG_SIZE);
	for(uint8_t i = 0; i < MSG_SIZE; i++){
		if(serial.readable()){
			buf[i] = serial.getc();
		}
		else break;
	}
	
	uint8_t result = parseRMC(buf);
	if(result != ERROR_SUCCESS){
		DEBUG("ADCS", "Error parsing serial data.\n");
	}
	
	return result;
}

/**
 * @brief set the update rate of the GPS receiver
 *
 * @param frequency in Hz
 * @param attribute:
 * RAM_ONLY = only update RAM
 * RAM_FLASH = update RAM and flash
 *
 * @return error code
 */
uint8_t GPS::setUpdateRate(uint8_t frequency, Attributes_t attribute)
{
    DEBUG("GPS","Setting update rate\n");
    uint8_t messageBody[2];
    memset(messageBody, 0, 2);
    messageBody[0] = frequency;
    messageBody[1] = attribute;
    return sendCommand(0x0E, messageBody, 2);
}

/**
 * @brief reset the GPS receiver to factory default settings
 *
 * @param reboot after reset 
 *
 * @return error code
 */
uint8_t GPS::resetReceiver(bool reboot)
{
    DEBUG("GPS","Resetting receiver\n");
    uint8_t messageBody[1];
    memset(messageBody, 0, 1);
    messageBody[0] = reboot ? 1 : 0;
    uint8_t code = sendCommand(0x04, messageBody, 1, 10000);
    if (code != ERROR_SUCCESS)
    {
		DEBUG("GPS", "Unable to reset receiver\n");
    }

    return code;
}

/**
 * @brief configure the NMEA messages sent from the GPS receiver
 *
 * @param messageName of NMEA message
 * @param enable or disable
 * @param attribute:
 * RAM_ONLY = only update RAM
 * RAM_FLASH = update RAM and flash
 *
 * @return error code
 */
uint8_t GPS::configNMEA(uint8_t messageName, bool enable, Attributes_t attribute)
{
    DEBUG("GPS","Configuring a NMEA string\n");
    if (enable){
        nmeaState |= 1 << messageName;
	}
    else{
        nmeaState &= ~(1 << messageName);
	}
    return configNMEA(nmeaState, attribute);
}

/**
 * @brief configure the NMEA messages sent from the GPS receiver
 *
 * @param nmeaByte new state of NMEA message configuration
 * @param attribute:
 * RAM_ONLY = only update RAM
 * RAM_FLASH = update RAM and flash
 *
 * @return error code
 */
uint8_t GPS::configNMEA(uint8_t nmeaByte, Attributes_t attribute)
{
    DEBUG("GPS","Configuring all NMEA strings\n");
    nmeaState = nmeaByte;
    uint8_t messageBody[8];
    memset(messageBody, 0, 8);
	// determine which nmea sentences are enabled/disabled
	messageBody[0] = (nmeaState >> 0) & 1; // GGA
    messageBody[1] = (nmeaState >> 1) & 1; // GSA
    messageBody[2] = (nmeaState >> 2) & 1; // GSV
    messageBody[3] = (nmeaState >> 3) & 1; // GLL
    messageBody[4] = (nmeaState >> 4) & 1; // RMC
    messageBody[5] = (nmeaState >> 5) & 1; // VTG
    messageBody[6] = (nmeaState >> 6) & 1; // ZDA
    messageBody[7] = attribute;
    return sendCommand(0x08, messageBody, 8);
}

/**
 * @brief configure the GPS power mode
 *
 * @param enable or disable power save mode
 * @param attribute:
 * RAM_ONLY = only update RAM
 * RAM_FLASH = update RAM and flash
 *
 * @return error code
 */
uint8_t GPS::configPowerSave(bool enable, Attributes_t attribute)
{
    DEBUG("GPS","Configuring Power Save mode\n");
    uint8_t messageBody[2];
    memset(messageBody, 0, 2);
    messageBody[0] = enable ? 1 : 0;
    messageBody[1] = attribute;
    return sendCommand(0x0C, messageBody, 2);
}

/**
 * @brief initialize the GPS to default state
 *
 * @return error code
 */
uint8_t GPS::initialize(){
	uint8_t result = configNMEA(0x10, true, RAM_FLASH);
	if(result != ERROR_SUCCESS){
		DEBUG("ADCS","Error initializing the GPS receiver.\n");
		return result;
	}
	
	return result;
}

/////////////////////////// Private Utility Functions ////////////////////////////

/**
 * @brief parse lat/long degrees from NMEA message into dd.mmmmmmm format (10^7 precision)
 *
 * @param field containing lat/long to be parsed
 * @param upper degrees
 * @param lower minutes (10^7 precision)
 *
 */
void GPS::parse_degrees(uint8_t *field, int64_t *upper, int64_t *lower){
	int64_t deg = 0L;
    while ((*(field + 2) != '.') && (*field >= '0' && *field <= '9')){
        deg = deg * 10L + *field++ - '0';
	}
    *upper = deg;

    int64_t min = (*field++ - '0') * 10;
    min += *field++ - '0';
    field++;
    while ((*field >= '0' && *field <= '9')){
        min = min * 10L + *field++ - '0';
	}

    min *= 100L;

    *lower = min / 6;
}

/**
 * @brief parse an NMEA RMC message
 *	Time, date, position, course and speed data provided by a GNSS navigation receiver.
 *	Structure:
 *	$GPRMC,hhmmss.sss,A,dddmm.mmmm,a,dddmm.mmmm,a,x.x,x.x,ddmmyy,,,a*hh<CR><LF>
 *	Example:
 *	$GPRMC,111636.932,A,2447.0949,N,12100.5223,E,000.0,000.0,030407,,,A*61<CR><LF>
 *
 * @param nmea RMC message
 *
 * @return error code
 */
uint8_t GPS::parseRMC(uint8_t *nmea){
	char *field = strtok((char*)nmea,",");
	if(field[0] == '$'){
		field++;
		if(strncmp(RMC_ID,field,strlen(RMC_ID)==0)){
			DEBUG("ADCS","Parsing NMEA RMC data\n");
		} 
		else{
			DEBUG("ADCS","NMEA unidentified or not supported\n");
			return ERROR_UNKNOWN_COMMAND;
		}
	}
	
	uint8_t counter = 0;
	while(counter < NUM_RMC_ATTRIBUTES){
		field = strtok(NULL,",");
		parseRMCField((uint8_t *)field,rmcFieldTypes[counter]);
		counter++;
	}
	DEBUG("ADCS","Parsing NMEA data complete\n");
	return ERROR_SUCCESS;
}

/**
 * @brief parse a specific RMC field from the RMC message
 *	Time, date, position, course and speed data provided by a GNSS navigation receiver.
 *	Structure:
 *	$GPRMC,hhmmss.sss,A,dddmm.mmmm,a,dddmm.mmmm,a,x.x,x.x,ddmmyy,,,a*hh<CR><LF>
 *	Example:
 *	$GPRMC,111636.932,A,2447.0949,N,12100.5223,E,000.0,000.0,030407,,,A*61<CR><LF>
 *
 * @param field to be parsed
 * @param type of field being parsed
 *
 * @return error code
 */
uint8_t GPS::parseRMCField(uint8_t *field, RMCField_t type){
	switch(type){
		case TIME:
			this->utcTime = atoi((char*)field);
			break;	
		case LAT:
			parse_degrees(field, &(this->lat_upper), &(this->lat_lower));
			break;
		case LAT_DIR:
			this->lat_upper = *field == 'S' ? (this->lat_upper)*-1 : this->lat_upper;
			break;
		case LONG:
			parse_degrees(field, &(this->long_upper), &(this->long_lower));
			break;
		case LONG_DIR:
			this->long_upper = *field == 'W' ? (this->long_upper)*-1 : this->long_upper;
			break;
		case SOG:
			this->speed = atoi((char*)field);
			break;
		case DATE:
			this->date = atoi((char*)field);
			 break;
		default:
			return ERROR_UNKNOWN_COMMAND;
	}
	return ERROR_SUCCESS;
}

/**
 * @brief send command to GPS receiver
 *
 * @param messageId of command
 * @param messageBody of command
 * @param bodyLen of command
 * @param timeout
 *
 * @return error code
 */
uint8_t GPS::sendCommand(uint8_t messageId, uint8_t *messageBody, uint32_t bodyLen, uint32_t timeout)
{
    DEBUG("GPS","sending command\n");
    // Assemble Packet
    uint32_t packetLength = 8 + bodyLen;
    uint8_t packet[packetLength];
    memset(packet, 0, packetLength);

    packet[0] = 0xA0; // start sequence
    packet[1] = 0xA1;

    packet[2] = (uint8_t) ((bodyLen + 1) >> 8); // payload length includes message id
    packet[3] = (uint8_t) bodyLen + 1;

    packet[4] = messageId;

    // calculate checksum
	// We should implement a general CougSat error detection class
	// to perform checksums, CRCs, etc
    uint8_t checksum = messageId;
    for (int i = 5; i < packetLength - 3; i++)
    {
        packet[i] = messageBody[i - 5];
        checksum ^= packet[i];
    }
    packet[packetLength - 3] = checksum;

    packet[packetLength - 2] = 0x0D; // terminate command with crlf
    packet[packetLength - 1] = 0x0A;

    // Send Packet
    printPacket(packet, packetLength);

    uint8_t code = sendPacket(packet, packetLength, timeout / 2);

    if (code != ERROR_SUCCESS)
    {
        DEBUG("GPS","failed, trying again\n");
        code = sendPacket(packet, packetLength, timeout / 2);
    }
    return code;
}

/**
 * @brief send command to GPS receiver
 *
 * @param messageId of command
 * @param messageBody of command
 * @param bodyLen of command
 * @param timeout
 *
 * @return error code
 */
uint8_t GPS::sendPacket(uint8_t *packet, uint32_t size, uint32_t timeout)
{
    uint8_t c = 0;
    uint8_t last = 0;
    bool response = false;
	for(uint32_t i = 0; i < size; i++)
		serial.putc(packet[i]);
    // TODO: wait for ACK, need to use different API to get current
	// time in ms
	Timer t;
	t.start();
    for(uint32_t start = t.read_ms(); t.read_ms() - start < timeout;)
    {
        while (serial.readable())
        {
            c = serial.getc();
            if (last == 0xA0 && c == 0xA1 && response == false)
                response = true;
            if (response && last == 0x83)
            {
                if (c == packet[4]) // packet[4] = messageid
                    return ERROR_SUCCESS;
                else
                    return ERROR_UNKNOWN_COMMAND;
            }
            else if (response && last == 0x84)
            {
                if (c == packet[4]) // packet[4] = messageid
                    return ERROR_NACK;
                else
                    return ERROR_UNKNOWN_COMMAND;
            }
            last = c;
        }
    }
    return ERROR_WAIT_TIMEOUT;
}

/**
 * @brief print out a packet
 *
 * @param packet to be printed
 * @param size of packet to be printed
 *
 */
void GPS::printPacket(uint8_t *packet, uint32_t size)
{
    DEBUG("GPS","assembled Packet: {");
    for (uint32_t i = 0; i < size; i++)
    {
        char hexval[4];
        sprintf(hexval, "0x%02X", packet[i]);
        if (i < size - 1) {
			DEBUG("GPS",", ");
		}
    }
    DEBUG("GPS","}");
}
// END GPS_CPP IMPLEMENTATION