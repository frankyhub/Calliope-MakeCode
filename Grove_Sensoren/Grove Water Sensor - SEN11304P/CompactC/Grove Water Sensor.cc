/*******************************************************************************

 Project Name:      Grove Water Sensor.cprj
 Required Libs's:   IntFunc_lib.cc
 Files:             Grove Water Sensor.cc
 Writer:            CCPRO-TEAM
 Date:              10.05.2015
 Function:          Demonstrates the Water Sensor

 ------------------------------------------------------------------------------
 AVR32 Serie:
 ------------
 Required the C-Control PRO AVR32-Bit UNIT Conrad BN: 192573
 Applicationboard Conrad BN: 192587
 Or Mainboard Conrad BN: 192702

 MEGA Serie:
 -----------
 Required the C-Control PRO MEGA32 UNIT Conrad BN: 198206
 and Evalationboard Conrad BN: 198245
 Or Projectboard Conrad BN: 197287

 Or C-Control PRO MEGA128 UNIT Conrad BN: 198219
 Or C-Control PRO MEGA128CAN Conrad BN: 197989
 and Evaluationboard Conrad BN: 198258
 or Projectboard Conrad BN: 197313

 Input ADC0:
 ------------
 Mega32:  PA0 (PortA.0)
 Mega128: PF0 (PortF.0)
 AVR32:   P9

 Connection:
 -----------
 - Connect the Sensor red wire to +5V (MEGA) or +3,3V (AVR32)
 - Connect the Sensor black wire to GND
 - Connect the Sensor yellow wire to C-Control ADC
 - The white sensor wire is not connected

 Start the program with F10 (or the yellow flash icon) for debug outputs!

 ------------------------------------------------------------------------------

 Note:
 -----
 Source: http://www.seeedstudio.com/depot/Grove-Water-Sensor-p-748.html

 This water sensor module is part of the Twig system.
 This sensor works by having a series of exposed traces connected to ground
 and interlaced between the grounded traces are the sens traces.
 The sensor traces have a weak pull-up resistor of 1 MO.
 The resistor will pull the sensor trace value high until a drop of water
 shorts the sensor trace to the grounded trace. Believe it or not this circuit
 will work with the digital I/O pins of your Arduino or you can use it with the
 analog pins to detect the amount of water induced contact between the grounded
 and sensor traces.

 Features:
 ---------
 * Grove compatible interface
 * Low power consumption
 * High sensitivity

 Applications Ideas:
 -------------------
 * Rainfall detecting
 * Liquid leakage
 * Tank overflow detector

*******************************************************************************/

#define ALARM_SENSITY   500

/*------------------------------------------------------------------------------
name:           main
input:          -
output:         -
description:    Main program
------------------------------------------------------------------------------*/
void main(void)
{

    word ADC_Value;

    #if AVR32
        int result[8];
        ADC_Disable();
        ADC_SetInput(0, 0, ADC_GND, ADC_SHG_1);
        ADC_Enable(ADC_MODE_12BIT|ADC_MODE_FREE_RUN, 1000000, ADC_ADCREF0, 1, 0);
        ADC_Start();
    #else
        // MEGA Serie
        ADC_Set(ADC_VREF_VCC, ADC0);                // Set Vref and ADC Channel
    #endif


    // Endless loop
    while(1)
    {
      #ifdef AVR32
         ADC_GetValues(result, 1);
         ADC_Value=result[0];
      #else
        // MEGA Serie
        ADC_Value=ADC_Read();                       // Read channel values
      #endif

      /*
      Msg_WriteWord(ADC_Value);                     // Debug output of the sensor value
      Msg_WriteChar('\r');                          // Debug new line
      AbsDelay(100);                                // Shows the output slower
      */

      // If the sensor value < ALARM_SENSITY send a alarm Message to the IDE output window
      if(ADC_Value<ALARM_SENSITY)
      {
        Msg_WriteText("WATER ALARM!!\r");
        AbsDelay(1000);
      }

    }
}

/*******************************************************************************
 * Info
 *******************************************************************************
 * Changelog:
 * -
 *
 *******************************************************************************
 * Bugs, feedback, questions and modifications can be posted on the
 * C-Control Forum on http://www.c-control.de
 * Of course you can also write us an e-mail to: webmaster@c-control.de
 * We publish updates from time to time on www.c-control.de!
/******************************************************************************/

// EOF

