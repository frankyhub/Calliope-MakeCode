/*******************************************************************************

 Project Name:      Grove Piezo Vibration Sensor.cprj
 Required Libs's:   IntFunc_lib.cc
 Files:             Grove Piezo Vibration Sensor.cc
 Writer:            CCPRO-TEAM
 Date:              10.05.2015
 Function:          Demonstrates the Piezo Vibration Sensor

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
 Source: http://www.seeedstudio.com/wiki/Grove-_Piezo_Vibration_Sensor

 Grove- Piezo Vibration Sensor is suitable for measurements of flexibility,
 vibration, impact and touch. The module is based on PZT film sensor LDT0-028.
 When the sensor moves back and forth, a certain voltage will be created by the
 voltage comparator inside of it. A wide dynamic range (0.001Hz~1000MHz)
 guarantees an excellent measuring performance. And, you can adjust its
 sensitivity by adjusting the on-board potentiometer with a screw.

 Applications:
 -------------
 * Vibration Sensing in Washing Machine
 * Low Power Wakeup Switch
 * Low Cost Vibration Sensing
 * Car Alarms
 * Body Movement
 * Security Systems

*******************************************************************************/

#define ALARM_SENSITY   1000


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

      // If the sensor value > 1000 send a alarm Message to the IDE output window
      if(ADC_Value>ALARM_SENSITY)
      {
        Msg_WriteText("ALARM\r");
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

