/*******************************************************************************

 Project Name:      Grove Moisture Sensor.cprj
 Required Libs's:   IntFunc_lib.cc
 Files:             Grove Moisture Sensor.cc
 Writer:            CCPRO-TEAM
 Date:              03.06.2015
 Function:          Demonstrates the Grove Moisture Sensor

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
 Source: http://www.seeedstudio.com/depot/Grove-Moisture-Sensor-p-955.html

 This Moisture Sensor can be used to detect the moisture of soil or judge
 if there is water around the sensor, let the plants in your garden reach
 out for human help. They can be very to use, just insert it into the soil
 and then read it. With help of this sensor, it will be realizable to make
 the plant remind you : Hey, I am thirsty now, please give me some water.

 Features:
 ---------
 * Easy to Use
 * 2.0cmX6.0cm grove module

 Application Ideas:
 ------------------
 * Botanical gardening
 * Water sensor

*******************************************************************************/

#define DRY_ALARM_SENSITY   60


/*------------------------------------------------------------------------------
    Main program
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
      #if AVR32
         ADC_GetValues(result, 1);
         ADC_Value=result[0];
      #else
        // MEGA Serie
        ADC_Value=ADC_Read();                        // Read channel values
      #endif

      // If the sensor value > 1000 send a alarm Message to the IDE output window
      if(ADC_Value<DRY_ALARM_SENSITY)
      {
        Msg_WriteText("The Plant is to dry!!!\r");
        AbsDelay(1000);
      }
      else
      {
        Msg_WriteWord(ADC_Value);                     // Debug output of the sensor value
        Msg_WriteChar('\r');                          // Debug new line
        AbsDelay(100);                                // Shows the output slower
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

