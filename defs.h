#pragma once

#if defined(ARDUINO_PORTENTA_H7_M4) || defined(ARDUINO_PORTENTA_H7_M7)
#define MOTOR_Z_FG PJ_10
#define MOTOR_Z_SPEED PA_8
#define MOTOR_Z_DIR PC_6

#define MOTOR_Y_FG PI_7
#define MOTOR_Y_SPEED PC_7
#define MOTOR_Y_DIR PJ_7

#define MOTOR_X_FG PJ_11
#define MOTOR_X_SPEED PH_6
#define MOTOR_X_DIR PK_1
#else

#define MOTOR_Z_FG 3
#define MOTOR_Z_SPEED 13
#define MOTOR_Z_DIR 14

#define MOTOR_Y_FG 3
#define MOTOR_Y_SPEED 13
#define MOTOR_Y_DIR 14

#define MOTOR_X_FG 3
#define MOTOR_X_SPEED 13
#define MOTOR_X_DIR 14

#endif


#define IMUADDRESS1  0x4B    //==75
#define TEMP_OBC 0x4A

#define EPS_ADDRESS 0x18
#define IRARRAY_ADDRESS_X1  0x33    //NEVER EVER USER 34 ON TBEAM!!!!@#!@#!@#!@
#define IRARRAY_ADDRESS_X2  0x32
#define IRARRAY_ADDRESS_Y1  0x33
#define IRARRAY_ADDRESS_Y2  0x32
#define IRARRAY_ADDRESS_Z1  0x33
#define IRARRAY_ADDRESS_Z2  0x32
#define TEMP_X1 0x48
#define TEMP_X2 0x49
#define TEMP_Y1 0x48
#define TEMP_Y2 0x49
#define TEMP_Z1 0x48
#define TEMP_Z2 0x49

//#define TEMP_ADCS 0x4B

#define MAG_ADDRESS_X  0x60
#define MAG_ADDRESS_Y  0x61
#define MAG_ADDRESS_Z  0x63

#define WATCHDOG_LOOP_COUNT 1000
