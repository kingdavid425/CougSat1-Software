#ifndef _LIBRARY_DRIVER_ADC_ADC_H_
#define _LIBRARY_DRIVER_ADC_ADC_H_

#include <cmath>
#include <mbed.h>

enum class ADCChannel_t : uint8_t {
  CM_00 = 0x00,
  CM_01 = 0x01,
  CM_02 = 0x02,
  CM_03 = 0x03,
  CM_04 = 0x04,
  CM_05 = 0x05,
  CM_06 = 0x06,
  CM_07 = 0x07,
  CM_08 = 0x08,
  CM_09 = 0x09,
  CM_10 = 0x0A,
  CM_11 = 0x0B,
  CM_12 = 0x0C,
  CM_13 = 0x0D,
  CM_14 = 0x0E,
  CM_15 = 0x0F,
  DM_00 = 0x80,
  DM_01 = 0x81,
  DM_02 = 0x82,
  DM_03 = 0x83,
  DM_04 = 0x84,
  DM_05 = 0x85,
  DM_06 = 0x86,
  DM_07 = 0x87,
  DM_08 = 0x88,
  DM_09 = 0x89,
  DM_10 = 0x8A,
  DM_11 = 0x8B,
  DM_12 = 0x8C,
  DM_13 = 0x8D,
  DM_14 = 0x8E,
  DM_15 = 0x8F
};

class ADC {
public:
  ADC(const ADC &) = delete;
  ADC & operator=(const ADC &) = delete;

  /**
   * @brief Construct a new ADC object
   *
   * @param refVoltage at full counts
   * @param bitDepth of the conversion
   */
  ADC(double refVoltage, uint8_t bitDepth) {
    setReferenceVoltage(refVoltage, bitDepth);
  }

  /**
   * @brief Destroy the ADC object
   *
   */
  ~ADC() {};

  /**
   * @brief Read the raw conversion result of a channel
   *
   * @param channel to read
   * @param value to return in counts
   * @param blocking will wait until data is present if true
   * @return mbed_error_status_t
   */
  virtual mbed_error_status_t readRaw(
      ADCChannel_t channel, int32_t & value, bool blocking = true) = 0;

  /**
   * @brief Set the reference voltage given the number of bits and vRef
   *
   * @param refVoltage at full counts
   * @param bitDepth of the conversion
   */
  void setReferenceVoltage(double refVoltage, uint8_t bitDepth) {
    this->refVoltage = refVoltage;
    conversionFactor = refVoltage / pow(2, bitDepth);
  }

  /**
   * @brief Get the reference voltage object
   *
   * @return double vRef in volts
   */
  double getReferenceVoltage() {
    return refVoltage;
  }

  /**
   * @brief Read the voltage of a channel
   * Reads the raw value and multiplies by the conversionFactor
   *
   * @param channel to read
   * @param value to return in volts
   * @param blocking will wait until data is present if true
   * @return mbed_error_status_t
   */
  mbed_error_status_t readVoltage(
      ADCChannel_t channel, double & value, bool blocking = true) {
    int32_t             buf    = 0;
    mbed_error_status_t result = readRaw(channel, buf, blocking);
    value                      = (double)buf * conversionFactor;
    return result;
  }

protected:
  double refVoltage       = 0.0; // Volts
  double conversionFactor = 0.0; // Volts per count
};

#endif /* _LIBRARY_DRIVER_ADC_ADC_H_ */