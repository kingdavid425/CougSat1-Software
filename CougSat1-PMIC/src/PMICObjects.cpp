#include "PMICObjects.h"

/*************************** Interfaces and Drivers ***************************/
// I2C i2cLocal(PIN_I2C_BUS_SDA, PIN_I2C_BUS_SCL);
// I2C i2cBus(PIN_I2C_LOCAL_SDA, PIN_I2C_LOCAL_SCL);

// CDH cdh(i2cBus);

// LTC2499 adcEPS0(i2cBus, I2C_ADDR_ADC_EPS0, ADC_AVREF, ADC_GAIN_NONE);
// LTC2499 adcEPS1(i2cBus, I2C_ADDR_ADC_EPS1, ADC_AVREF, ADC_GAIN_NONE);
// LTC2499 adcEPS2(i2cBus, I2C_ADDR_ADC_EPS2, ADC_AVREF, ADC_GAIN_NONE);
// LTC2499 adcEPS3(i2cBus, I2C_ADDR_ADC_EPS3, ADC_AVREF, ADC_GAIN_NONE);
// LTC2499 adcEPS4(i2cBus, I2C_ADDR_ADC_EPS4, ADC_AVREF, ADC_GAIN_NONE);
// LTC2499 adcEPS5(i2cBus, I2C_ADDR_ADC_EPS5);
// LTC2499 adcPV0(i2cBus, I2C_ADDR_ADC_PV0);
// LTC2499 adcPV1(i2cBus, I2C_ADDR_ADC_PV1);
// LTC2499 adcPV2(i2cBus, I2C_ADDR_ADC_PV2);
// LTC2499 adcPV3(i2cBus, I2C_ADDR_ADC_PV3);

// TCA9535 gpioEPS0(i2cBus, I2C_ADDR_GPIO_EPS0);
// TCA9535 gpioEPS1(i2cBus, I2C_ADDR_GPIO_EPS1);

// DigitalOut statusLED(PIN_LED);
// DigitalOut umbilicalSwitchA(PIN_UMB_SW_A);
// DigitalOut umbilicalSwitchB(PIN_UMB_SW_B);

// InterruptIn interruptCtrlSync(PIN_CTRL_SYNC);
// InterruptIn interruptBusI2CIRQ(PIN_I2C_BUS_IRQ);

// /******************************** Power Nodes
// *********************************/ PowerNode   nodePVIn_0A(adcPV0,
// PIN_ADC_PVIN_I_A, SHUNT_PVIN_0A); PowerNode   nodePVIn_0B(adcPV0,
// PIN_ADC_PVIN_I_B, SHUNT_PVIN_0B); PowerNode   nodePVIn_1A(adcPV1,
// PIN_ADC_PVIN_I_A, SHUNT_PVIN_1A); PowerNode   nodePVIn_1B(adcPV1,
// PIN_ADC_PVIN_I_B, SHUNT_PVIN_1B); PowerNode   nodePVIn_2A(adcPV2,
// PIN_ADC_PVIN_I_A, SHUNT_PVIN_2A); PowerNode   nodePVIn_2B(adcPV2,
// PIN_ADC_PVIN_I_B, SHUNT_PVIN_2B); PowerNode   nodePVIn_3A(adcPV3,
// PIN_ADC_PVIN_I_A, SHUNT_PVIN_3A); PowerNode   nodePVIn_3B(adcPV3,
// PIN_ADC_PVIN_I_B, SHUNT_PVIN_3B); PowerNode * nodesPVIn[COUNT_PV] =
// {&nodePVIn_0A, &nodePVIn_0B, &nodePVIn_1A,
//     &nodePVIn_1B, &nodePVIn_2A, &nodePVIn_2B, &nodePVIn_3A, &nodePVIn_3B};

// PowerNodeTCA9535 nodePVOut_0A(adcPV0, PIN_ADC_PVOUT_I_A, SHUNT_PVOUT_0A,
//     gpioEPS0, PIN_PV_SW_0A, PIN_PV_SW_0B);
// PowerNodeTCA9535 nodePVOut_0B(adcPV0, PIN_ADC_PVOUT_I_A, SHUNT_PVOUT_0B,
//     gpioEPS0, PIN_PV_SW_1A, PIN_PV_SW_1B);
// PowerNodeTCA9535 nodePVOut_1A(adcPV0, PIN_ADC_PVOUT_I_A, SHUNT_PVOUT_1A,
//     gpioEPS0, PIN_PV_SW_2A, PIN_PV_SW_2B);
// PowerNodeTCA9535 nodePVOut_1B(adcPV0, PIN_ADC_PVOUT_I_A, SHUNT_PVOUT_1B,
//     gpioEPS0, PIN_PV_SW_3A, PIN_PV_SW_3B);
// PowerNodeTCA9535 nodePVOut_2A(adcPV0, PIN_ADC_PVOUT_I_A, SHUNT_PVOUT_2A,
//     gpioEPS1, PIN_PV_SW_4A, PIN_PV_SW_4B);
// PowerNodeTCA9535 nodePVOut_2B(adcPV0, PIN_ADC_PVOUT_I_A, SHUNT_PVOUT_2B,
//     gpioEPS1, PIN_PV_SW_5A, PIN_PV_SW_5B);
// PowerNodeTCA9535 nodePVOut_3A(adcPV0, PIN_ADC_PVOUT_I_A, SHUNT_PVOUT_3A,
//     gpioEPS1, PIN_PV_SW_6A, PIN_PV_SW_6B);
// PowerNodeTCA9535 nodePVOut_3B(adcPV0, PIN_ADC_PVOUT_I_A, SHUNT_PVOUT_3B,
//     gpioEPS1, PIN_PV_SW_7A, PIN_PV_SW_7B);

// PowerNode * nodesPVOut[COUNT_PV] = {&nodePVOut_0A, &nodePVOut_0B,
// &nodePVOut_1A,
//     &nodePVOut_1B, &nodePVOut_2A, &nodePVOut_2B, &nodePVOut_3A,
//     &nodePVOut_3B};

// PowerNodeTCA9535 nodePR3V3_0(adcEPS0, PIN_ADC_PR_3V3_0, SHUNT_PR_3V3_0,
//     gpioEPS1, PIN_PC_3V3_0A, PIN_PC_3V3_0B);
// PowerNodeTCA9535 nodePR3V3_1(adcEPS0, PIN_ADC_PR_3V3_1, SHUNT_PR_3V3_1,
//     gpioEPS1, PIN_PC_3V3_1A, PIN_PC_3V3_1B);
// PowerNodeDirect  nodePR3V3_2(
//     adcEPS0, PIN_ADC_PR_3V3_2, SHUNT_PR_3V3_2, PIN_PC_3V3_2A, PIN_PC_3V3_2B);
// PowerNodeDirect nodePR3V3_3(
//     adcEPS0, PIN_ADC_PR_3V3_3, SHUNT_PR_3V3_3, PIN_PC_3V3_3A, PIN_PC_3V3_3B);
// PowerNodeDirect nodePR3V3_4(
//     adcEPS0, PIN_ADC_PR_3V3_4, SHUNT_PR_3V3_4, PIN_PC_3V3_4A, PIN_PC_3V3_4B);
// PowerNodeDirect nodePR3V3_5(
//     adcEPS0, PIN_ADC_PR_3V3_5, SHUNT_PR_3V3_5, PIN_PC_3V3_5A, PIN_PC_3V3_5B);
// PowerNodeDirect nodePR3V3_6(
//     adcEPS0, PIN_ADC_PR_3V3_6, SHUNT_PR_3V3_6, PIN_PC_3V3_6A, PIN_PC_3V3_6B);
// PowerNodeDirect nodePR3V3_7(
//     adcEPS0, PIN_ADC_PR_3V3_7, SHUNT_PR_3V3_7, PIN_PC_3V3_7A, PIN_PC_3V3_7B);
// PowerNodeDirect nodePR3V3_8(
//     adcEPS2, PIN_ADC_PR_3V3_8, SHUNT_PR_3V3_8, PIN_PC_3V3_8A, PIN_PC_3V3_8B);
// PowerNodeDirect nodePR3V3_9(
//     adcEPS2, PIN_ADC_PR_3V3_9, SHUNT_PR_3V3_9, PIN_PC_3V3_9A, PIN_PC_3V3_9B);
// PowerNodeDirect nodePR3V3_10(adcEPS2, PIN_ADC_PR_3V3_10, SHUNT_PR_3V3_10,
//     PIN_PC_3V3_10A, PIN_PC_3V3_10B);
// PowerNodeDirect nodePR3V3_11(adcEPS2, PIN_ADC_PR_3V3_11, SHUNT_PR_3V3_11,
//     PIN_PC_3V3_11A, PIN_PC_3V3_11B);
// PowerNodeDirect nodePR3V3_12(adcEPS1, PIN_ADC_PR_3V3_12, SHUNT_PR_3V3_12,
//     PIN_PC_3V3_12A, PIN_PC_3V3_12B);

// PowerNode * nodesPR3V3[COUNT_PR_3V3] = {&nodePR3V3_0, &nodePR3V3_1,
//     &nodePR3V3_2, &nodePR3V3_3, &nodePR3V3_4, &nodePR3V3_5, &nodePR3V3_6,
//     &nodePR3V3_7, &nodePR3V3_8, &nodePR3V3_9, &nodePR3V3_10, &nodePR3V3_11,
//     &nodePR3V3_12};

// PowerNodeDirect nodePRBatt_0(adcEPS1, PIN_ADC_PR_BATT_0, SHUNT_PR_BATT_0,
//     PIN_PC_BATT_0A, PIN_PC_BATT_0B);
// PowerNodeDirect nodePRBatt_1(adcEPS1, PIN_ADC_PR_BATT_1, SHUNT_PR_BATT_1,
//     PIN_PC_BATT_1A, PIN_PC_BATT_1B);
// PowerNodeDirect nodePRBatt_2(adcEPS1, PIN_ADC_PR_BATT_2, SHUNT_PR_BATT_2,
//     PIN_PC_BATT_2A, PIN_PC_BATT_2B);
// PowerNodeDirect nodePRBatt_3(adcEPS1, PIN_ADC_PR_BATT_3, SHUNT_PR_BATT_3,
//     PIN_PC_BATT_3A, PIN_PC_BATT_3B);
// PowerNodeDirect nodePRBatt_4(adcEPS1, PIN_ADC_PR_BATT_4, SHUNT_PR_BATT_4,
//     PIN_PC_BATT_4A, PIN_PC_BATT_4B);
// PowerNodeDirect nodePRBatt_5(adcEPS1, PIN_ADC_PR_BATT_5, SHUNT_PR_BATT_5,
//     PIN_PC_BATT_5A, PIN_PC_BATT_5B);
// PowerNodeDirect nodePRBatt_6(adcEPS1, PIN_ADC_PR_BATT_6, SHUNT_PR_BATT_6,
//     PIN_PC_BATT_6A, PIN_PC_BATT_6B);

// PowerNode * nodesPRBatt[COUNT_PR_BATT] = {&nodePRBatt_0, &nodePRBatt_1,
//     &nodePRBatt_2, &nodePRBatt_3, &nodePRBatt_4, &nodePRBatt_5,
//     &nodePRBatt_6};

// PowerNodeTCA9535 nodePV3V3_0(adcEPS4, PIN_ADC_PV_3V3_0, SHUNT_PV_3V3_0,
//     gpioEPS0, PIN_PVC_3V3_0A, PIN_PVC_3V3_0B);
// PowerNodeTCA9535 nodePV3V3_1(adcEPS4, PIN_ADC_PV_3V3_1, SHUNT_PV_3V3_1,
//     gpioEPS0, PIN_PVC_3V3_1A, PIN_PVC_3V3_1B);
// PowerNodeTCA9535 nodePV3V3_2(adcEPS2, PIN_ADC_PV_3V3_2, SHUNT_PV_3V3_2,
//     gpioEPS1, PIN_PVC_3V3_2A, PIN_PVC_3V3_2B);
// PowerNodeTCA9535 nodePV3V3_3(adcEPS2, PIN_ADC_PV_3V3_3, SHUNT_PV_3V3_3,
//     gpioEPS1, PIN_PVC_3V3_3A, PIN_PVC_3V3_3B);

// PowerNode * nodesPV3V3[COUNT_PV_3V3] = {
//     &nodePV3V3_0, &nodePV3V3_1, &nodePV3V3_2, &nodePV3V3_3};

// PowerNodeTCA9535 nodeBH_0(
//     adcEPS4, PIN_ADC_PR_BH_0, SHUNT_BH_0, gpioEPS0, PIN_PC_BH_0A,
//     PIN_PC_BH_0B);
// PowerNodeTCA9535 nodeBH_1(
//     adcEPS3, PIN_ADC_PR_BH_1, SHUNT_BH_1, gpioEPS0, PIN_PC_BH_1A,
//     PIN_PC_BH_1B);

// PowerNode * nodesBatteryHeaters[COUNT_BH] = {&nodeBH_0, &nodeBH_1};

// PowerNodeDirect nodeDeployables(adcEPS3, PIN_ADC_PR_DEPLOY,
// SHUNT_DEPLOYABLES,
//     PIN_PC_DEPLOY_A, PIN_PC_DEPLOY_B);

// PowerNode nodeVBattA(adcEPS4, PIN_ADC_VBATT_I_A, SHUNT_VBATT_A);
// PowerNode nodeVBattB(adcEPS3, PIN_ADC_VBATT_I_B, SHUNT_VBATT_B);
// PowerNode nodeBattA(adcEPS4, PIN_ADC_BATT_A, SHUNT_BATT_A);
// PowerNode nodeBattB(adcEPS4, PIN_ADC_BATT_B, SHUNT_BATT_B);
// PowerNode node3V3InA(adcEPS4, PIN_ADC_3V3_IN_A, SHUNT_3V3_IN_A);
// PowerNode node3V3InB(adcEPS3, PIN_ADC_3V3_IN_B, SHUNT_3V3_IN_B);
// PowerNode node3V3OutA(adcEPS4, PIN_ADC_3V3_OUT_A, SHUNT_3V3_OUT_A);
// PowerNode node3V3OutB(adcEPS3, PIN_ADC_3V3_OUT_B, SHUNT_3V3_OUT_B);

// /******************************** Thermistors
// *********************************/ Thermistor thermistorBattA(
//     adcEPS5, PIN_ADC_TEMP_BATT_A, THERM_CAL_BATT_A_270K,
//     THERM_CAL_BATT_A_350K);
// Thermistor thermistorBattB(
//     adcEPS5, PIN_ADC_TEMP_BATT_B, THERM_CAL_BATT_B_270K,
//     THERM_CAL_BATT_B_350K);
// Thermistor thermistorPMIC(
//     adcEPS5, PIN_ADC_TEMP_PMIC, THERM_CAL_PMIC_270K, THERM_CAL_PMIC_350K);
// Thermistor thermistorRegA(
//     adcEPS5, PIN_ADC_TEMP_REG_A, THERM_CAL_REG_A_270K, THERM_CAL_REG_A_350K);
// Thermistor thermistorRegB(
//     adcEPS5, PIN_ADC_TEMP_REG_B, THERM_CAL_REG_B_270K, THERM_CAL_REG_B_350K);
// Thermistor thermistorpXpY(
//     adcEPS5, PIN_ADC_TEMP_pXpY, THERM_CAL_pXpY_270K, THERM_CAL_pXpY_350K);
// Thermistor thermistornXpY(
//     adcEPS5, PIN_ADC_TEMP_nXpY, THERM_CAL_nXpY_270K, THERM_CAL_nXpY_350K);
// Thermistor thermistorpXnY(
//     adcEPS5, PIN_ADC_TEMP_pXnY, THERM_CAL_pXnY_270K, THERM_CAL_pXnY_350K);
// Thermistor thermistornXnY(
//     adcEPS5, PIN_ADC_TEMP_nXnY, THERM_CAL_nXnY_270K, THERM_CAL_nXnY_350K);

// Thermistor thermistorsMPPT[8] = {
//     Thermistor(adcPV0, PIN_ADC_TEMP_MPPT_A, THERM_CAL_PV0_MPPT_A_270K,
//         THERM_CAL_PV0_MPPT_A_350K),
//     Thermistor(adcPV0, PIN_ADC_TEMP_MPPT_B, THERM_CAL_PV0_MPPT_B_270K,
//         THERM_CAL_PV0_MPPT_B_350K),
//     Thermistor(adcPV1, PIN_ADC_TEMP_MPPT_A, THERM_CAL_PV1_MPPT_A_270K,
//         THERM_CAL_PV1_MPPT_A_350K),
//     Thermistor(adcPV1, PIN_ADC_TEMP_MPPT_B, THERM_CAL_PV1_MPPT_B_270K,
//         THERM_CAL_PV1_MPPT_B_350K),
//     Thermistor(adcPV2, PIN_ADC_TEMP_MPPT_A, THERM_CAL_PV2_MPPT_A_270K,
//         THERM_CAL_PV2_MPPT_A_350K),
//     Thermistor(adcPV2, PIN_ADC_TEMP_MPPT_B, THERM_CAL_PV2_MPPT_B_270K,
//         THERM_CAL_PV2_MPPT_B_350K),
//     Thermistor(adcPV3, PIN_ADC_TEMP_MPPT_A, THERM_CAL_PV3_MPPT_A_270K,
//         THERM_CAL_PV3_MPPT_A_350K),
//     Thermistor(adcPV3, PIN_ADC_TEMP_MPPT_B, THERM_CAL_PV3_MPPT_B_270K,
//         THERM_CAL_PV3_MPPT_B_350K)};

// Thermistor thermistorsPVBoard[12] = {
//     Thermistor(adcPV0, PIN_ADC_TEMP_BACK, THERM_CAL_PV0_BACK_270K,
//         THERM_CAL_PV0_BACK_350K),
//     Thermistor(adcPV0, PIN_ADC_TEMP_FRONT_TOP, THERM_CAL_PV0_FRONT_TOP_270K,
//         THERM_CAL_PV0_FRONT_TOP_350K),
//     Thermistor(adcPV0, PIN_ADC_TEMP_FRONT_BOTTOM,
//         THERM_CAL_PV0_FRONT_BOTTOM_270K, THERM_CAL_PV0_FRONT_BOTTOM_350K),
//     Thermistor(adcPV1, PIN_ADC_TEMP_BACK, THERM_CAL_PV1_BACK_270K,
//         THERM_CAL_PV1_BACK_350K),
//     Thermistor(adcPV1, PIN_ADC_TEMP_FRONT_TOP, THERM_CAL_PV1_FRONT_TOP_270K,
//         THERM_CAL_PV1_FRONT_TOP_350K),
//     Thermistor(adcPV1, PIN_ADC_TEMP_FRONT_BOTTOM,
//         THERM_CAL_PV1_FRONT_BOTTOM_270K, THERM_CAL_PV1_FRONT_BOTTOM_350K),
//     Thermistor(adcPV2, PIN_ADC_TEMP_BACK, THERM_CAL_PV1_BACK_270K,
//         THERM_CAL_PV2_BACK_350K),
//     Thermistor(adcPV2, PIN_ADC_TEMP_FRONT_TOP, THERM_CAL_PV2_FRONT_TOP_270K,
//         THERM_CAL_PV2_FRONT_TOP_350K),
//     Thermistor(adcPV2, PIN_ADC_TEMP_FRONT_BOTTOM,
//         THERM_CAL_PV2_FRONT_BOTTOM_270K, THERM_CAL_PV2_FRONT_BOTTOM_350K),
//     Thermistor(adcPV3, PIN_ADC_TEMP_BACK, THERM_CAL_PV3_BACK_270K,
//         THERM_CAL_PV3_BACK_350K),
//     Thermistor(adcPV3, PIN_ADC_TEMP_FRONT_TOP, THERM_CAL_PV3_FRONT_TOP_270K,
//         THERM_CAL_PV3_FRONT_TOP_350K),
//     Thermistor(adcPV3, PIN_ADC_TEMP_FRONT_BOTTOM,
//         THERM_CAL_PV3_FRONT_BOTTOM_270K, THERM_CAL_PV3_FRONT_BOTTOM_350K)};