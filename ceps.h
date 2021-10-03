/**
 * @file eps.h
 * @author IRQdesign d.o.o. 
 * @date August 2021 
 * @brief File containing API for the EPS module.
 *
 */

/*! \mainpage  
 *
 * \section intro_sec Introduction
 *
 * This document will give more info about the API implementation for the EPS module.
 *
 * \section install_sec How to use
 *  To use this library, user needs to implement I2C wrapper fuctions for reading and sending data. User needs to initalize I2C peripheral.
 *  Example of wrapper functions can be found in file porting.cpp
 *
 */
#ifndef __CEPS_H
#define __CEPS_H 

#include <stdint.h>

#include <msg.h>
#include <funcs.h>
#include <systemobject.h>

uint8_t readI2C(uint8_t i2cs_addr, uint8_t reg, uint8_t * data, uint16_t nbyte);
uint8_t writeI2C(uint8_t i2cs_addr, uint8_t reg, uint8_t * data, uint16_t nbyte);

#define BATTERY_VOLTAGE_CC        0.0023394775
#define BATTERY_CURRENT_CC        0.0030517578
#define BCR_VOLTAGE_CC          0.0023394775
#define BCR_CURRENT_CC          0.0015258789
#define X_VOLTAGE_CC          0.0024414063
#define X_CURRENT_CC          0.0006103516
#define Y_VOLTAGE_CC          0.0024414063
#define Y_CURRENT_CC          0.0006103516
#define Z_VOLTAGE_CC          0.0024414063
#define Z_CURRENT_CC          0.0006103516
#define P3V3_CURRENT_CC         0.0020345052
#define P5V_CURRENT_CC          0.0020345052
#define MCU_TEMPERATURE_CC        0.0006103516
#define BATTERY_TEMPERATURE_CC      0.00390625
#define MAX_TEMPERATURE_CC        0.00390625
#define MIN_TEMPERATURE_CC        0.00390625
#define EXT_TEMPERATURE_CC        0x00390625

/// Valid states for the EPS output
enum EPS_OUTPUT_STATE
{
  EPS_OUTPUT_STATE_AUTO_OFF = 0x00,   /*!< Auto Off state */
  EPS_OUTPUT_STATE_AUTO_ON,       /*!< Auto On state */
  EPS_OUTPUT_STATE_FORCED_OFF,      /*!< Forced Off state */  
  EPS_OUTPUT_STATE_FORCED_ON        /*!< Forced On state */
};

/// Valid values for enabeling/disabling different parts of EPS module
enum EPS_CONFIG_STATE
{
  EPS_CONFIG_STATE_OFF = 0x00,      /*!< Off state */
  EPS_CONFIG_STATE_ON = 0x01        /*!< On state */
};

/// Valid charging modes of the EPS module
enum EPS_CONFIG_CHARGE
{
  EPS_CONFIG_CHARGE_FAST = 0x00,      /*!< Fast charging mode */
  EPS_CONFIG_CHARGE_SLOW          /*!< Slow charging mode */
};

/*!< Valid read commands for the EPS module */
enum EPS_RCMD
{
  EPS_RCMD_BATTERY_VOLTAGE = 0x01,      /*!< Read battery voltage */
  EPS_RCMD_BATTERY_CURRENT,         /*!< Read battery current */
  EPS_RCMD_BCR_VOLTAGE,           /*!< Read BCR voltage */
  EPS_RCMD_BCR_CURRENT,           /*!< Read BCR current */
  EPS_RCMD_X_VOLTAGE,             /*!< Read X Axis solar panel voltage */
  EPS_RCMD_XM_CURRENT,            /*!< Read X Axis solar panel current- */
  EPS_RCMD_XP_CURRENT,            /*!< Read X Axis solar panel current+ */
  EPS_RCMD_Y_VOLTAGE,             /*!< Read Y Axis solar panel voltage */
  EPS_RCMD_YM_CURRENT,            /*!< Read Y Axis solar panel current+ */
  EPS_RCMD_YP_CURRENT,            /*!< Read Y Axis solar panel current+ */
  EPS_RCMD_Z_VOLTAGE,             /*!< Read Z Axis solar panel voltage */
  EPS_RCMD_ZM_CURRENT,            /*!< Read Z Axis solar panel current+ */
  EPS_RCMD_ZP_CURRENT,            /*!< Read Z Axis solar panel current+ */
  EPS_RCMD_3V3_CURRENT,           /*!< Read 3V3 Bus current */
  EPS_RCMD_5V_CURRENT,            /*!< Read 5V Bus current */
  EPS_RCMD_LUP_3V3,             /*!< Read LUP 3V3 */
  EPS_RCMD_LUP_5V,              /*!< Read LUP 5V */
  EPS_RCMD_MCU_TEMP,              /*!< Read MCU temperature */
  EPS_RCMD_BAT_TEMP_SENS1,          /*!< Read temperature from battery sensor1 */
  EPS_RCMD_BAT_TEMP_SENS2,          /*!< Read temperature from battery sensor2 */
  EPS_RCMD_BAT_TEMP_SENS3,          /*!< Read temperature from battery sensor3 */
  EPS_RCMD_BAT_TEMP_SENS4,          /*!< Read temperature from battery sensor4 */
  EPS_RCMD_INPUT_CONDITION,         /*!< Read input condition */
  EPS_RCMD_OUTPUTS_CONDITIONS,        /*!< Read output condition */
  EPS_RCMD_OUTPUTS_CONDITIONS2,       /*!< Read output condition */
  EPS_RCMD_PWR_ON_CYCLE,            /*!< Read number of powe on cycles */
  EPS_RCMD_V_UNDER_VOLTAGE,         /*!< Read number of under-voltage situations */
  EPS_RCMD_V_SHORT_CIRCUIT,         /*!< Read number of shor-circuit situations */
  EPS_RCMD_V_OVER_TEMPERATURE,        /*!< Read number of over-temperature situations */
  EPS_RCMD_MAX_TEMP1,             /*!< Read MAX temperature 1 */
  EPS_RCMD_MAX_TEMP2,             /*!< Read MAX temperature 2 */
  EPS_RCMD_MAX_TEMP3,             /*!< Read MAX temperature 3 */
  EPS_RCMD_MAX_TEMP4,             /*!< Read MAX temperature 4 */
  EPS_RCMD_MIN_TEMP1,             /*!< Read MIN temperature 1 */
  EPS_RCMD_MIN_TEMP2,             /*!< Read MIN temperature 2 */
  EPS_RCMD_MIN_TEMP3,             /*!< Read MIN temperature 3 */
  EPS_RCMD_MIN_TEMP4,             /*!< Read MIN tempearutre 4 */
  EPS_RCMD_TEMP_SENSOR_5,           /*!< Read External temperature 5 */
  EPS_RCMD_TEMP_SENSOR_6,           /*!< Read External tempreature 6 */
  EPS_RCMD_TEMP_SENSOR_7,           /*!< Read External temperature 7 */
  EPS_RCMD_TEMP_SENSOR_8,           /*!< Read External temperature 8 */
  EPS_RCMD_SOFTWARE_VERSION,          /*!< Read Software version */
  EPS_RCMD_DEFAULTS1,             /*!< Read Defaults 1 */
  EPS_RCMD_DEFAULTS2,             /*!< Read Defaults 2 */
  EPS_RCMD_RES1,                /*!< Reserved 1 */
  EPS_RCMD_RES2,                /*!< Reserved 2 */
  EPS_RCMD_RES3,                /*!< Reserved 3 */
  EPS_RCMD_RES4,                /*!< Reserved 4 */
  EPS_RCMD_CHARGE_CYCLES            /*!< Read number of charge cycles */
};

/*!< Valid write commands for the EPS module */
typedef enum
{
  EPS_WCMD_SW_SELFLOCK = 0x00,        /*!< Write SW Selfloc */
  EPS_WCMD_VBATEN,              /*!< Write VBAT enable */
  EPS_WCMD_BCROUTEN,              /*!< Write BCR enable */
  EPS_WCMD_SHD3V3,              /*!< Write 3V3 enable */
  EPS_WCMD_SHD5V,               /*!< Write 5V enable */
  EPS_WCMD_LUP3V3,              /*!< Write LUP 3V3 enable */
  EPS_WCMD_LUP5V,               /*!< Write LUP 5V enable */
  EPS_WCMD_SHDCHRG,             /*!< Write Shutdown charger */
  EPS_WCMD_CHRG_I1,             /*!< Write charger 1 configuration */
  EPS_WCMD_CHRG_I2,             /*!< Write charger 2 configuration */
  EPS_WCMD_OUT1,                /*!< Write OUT1 control */
  EPS_WCMD_OUT2,                /*!< Write OUT2 control */
  EPS_WCMD_OUT3,                /*!< Write OUT3 control */
  EPS_WCMD_OUT4,                /*!< Write OUT4 control */  
  EPS_WCMD_OUT5,                /*!< Write OUT5 control */
  EPS_WCMD_OUT6,                /*!< Write OUT6 control */
  EPS_WCMD_HEATER1,             /*!< Write HEATER1 control */
  EPS_WCMD_HEATER2,             /*!< Write HEATER2 control */
  EPS_WCMD_HEATER3              /*!< Write HEATER3 control */
}EPS_WCMD;

class AXIS_INFO
{
  private:
    float voltage;              /*!< Solar panel voltage for the given axis */
    float current_m;            /*!< Solar panel current- for the given axis */
    float current_p;            /*!< Solar panel current+ for the given axis */
  public:
    void setVoltage(float voltage_);
    void setCurrentM(float currentm_);
    void setCurrentP(float currentp_);
    float readVoltage(void);
    float readCurrentM(void);
    float readCurrentP(void);
};

class TEMPERATURE_INFO
{
  private:
    float temp1;              /*!< Temperature value 1 */
    float temp2;              /*!< Temperature value 2 */
    float temp3;              /*!< Temperature value 3 */
    float temp4;              /*!< Temperature value 4 */
  public:
    void setTemp1(float temp1_);
    void setTemp2(float temp2_);
    void setTemp3(float temp3_);
    void setTemp4(float temp4_);
    float readTemp1(void);
    float readTemp2(void);
    float readTemp3(void);
    float readTemp4(void);
};

class CEPS:public CSystemObject
{
  private:
    uint8_t addr=0x18;              /*!< EPS module I2C address */    
  //  uint8_t (*readI2C)(uint8_t i2cs_addr, uint8_t reg, uint8_t * data, uint16_t nbyte);     /*!< Low level I2C read function */
  //  uint8_t (*writeI2C)(uint8_t i2cs_addr, uint8_t reg, uint8_t * data, uint16_t nbyte);      /*!< Low level I2C write function */

  uint8_t readI2C(uint8_t i2cs_addr, uint8_t reg, uint8_t * data, uint16_t nbyte);    
  uint8_t writeI2C(uint8_t i2cs_addr, uint8_t reg, uint8_t * data, uint16_t nbyte); 
  

  public:
    CEPS(){};
    void setup();
    void init();
    void loop();
  //  void begin( uint8_t addr_ , uint8_t (*readI2C_)(uint8_t i2cs_addr, uint8_t reg, uint8_t * data, uint16_t nbyte),  uint8_t (*writeI2C_)(uint8_t i2cs_addr, uint8_t reg, uint8_t * data, uint16_t nbyte));

    float readBatteryVoltage(void);
    float readBatteryCurrent(void);
    float readBCRVoltage(void);
    float readBCRCurrent(void);
    
    float read3V3Current(void);
    float read5VCurrent(void);
    uint16_t readLUP3V3(void);
    uint16_t readLUP5V(void);
    float readMCUTemp(void);
    
    uint16_t readInputConditions(void);
    uint16_t readOutputCOnditions(void);
    uint16_t readOutputCOnditions2(void);
    uint16_t readPowerONCycles(void);
    uint16_t readVUnderVoltage(void);
    uint16_t readVShortCircuit(void);
    uint16_t readVOverTemperature(void);
    uint16_t readSoftwareVersion(void);
    uint16_t readDefaults1(void);
    uint16_t readDefaults12(void);
    uint16_t readChargeCycles(void);


    AXIS_INFO readXAxisInfo(void);
    AXIS_INFO readYAxisInfo(void);
    AXIS_INFO readZAxisInfo(void);
    TEMPERATURE_INFO readBatteryTemperature(void);
    TEMPERATURE_INFO readMaxTemperature(void);
    TEMPERATURE_INFO readMinTemperature(void);
    TEMPERATURE_INFO readTemperatureSensor(void);
    

    void writeSWSelflock(uint8_t state);
    void writeVBATEN(uint8_t state);
    void writeBCROutEN(uint8_t state);
    void writeSHD3V3(uint8_t state);
    void write5V(uint8_t state);
    void writeLUP3V3(uint8_t state);
    void writeLUP5V(uint8_t state);
    void writeSHDChrg(uint8_t state);
    void writeChrgI1(uint8_t state);
    void writeChrgI2(uint8_t state);
    void writeOut1(uint8_t state);
    void writeOut2(uint8_t state);
    void writeOut3(uint8_t state);
    void writeOut4(uint8_t state);
    void writeOut5(uint8_t state);
    void writeOut6(uint8_t state);
    void writeHeater1(uint8_t state);
    void writeHeater2(uint8_t state);
    void writeHeater3(uint8_t state);

    
  
};

#endif 
