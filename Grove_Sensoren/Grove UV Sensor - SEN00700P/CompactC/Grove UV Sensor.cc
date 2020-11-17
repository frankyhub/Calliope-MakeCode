/*******************************************************************************

 Project Name:      Grove UV Sensor.cprj
 Required Libs's:   IntFunc_lib.cc
 Files:             Grove UV Sensor.cc
 Writer:            CCPRO-TEAM
 Date:              06.06.2015
 Function:          Demonstrates the Grove UV Sensor

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
 Source: http://www.seeedstudio.com/depot/Grove-UV-Sensor-p-1540.html

 The Grove – UV Sensor is used for detecting the intensity of incident
 ultraviolet(UV) radiation. This form of electromagnetic radiation has
 shorter wavelengths than visible radiation. It is based on the sensor GUVA-S12D.
 It has a wide spectral range of 200nm-400nm. The module will output electrical
 signal which is varied with the change of the UV intensity. UV sensors are used
 for determining exposure to ultraviolet radiation in laboratory or
 environmental settings.

 Features:
 ---------
 * High stability
 * Good Sensitivity
 * Low power consumption
 * Schottky type photodiode sensor
 * Wide response range
 * Grove Interface

*******************************************************************************/


/*------------------------------------------------------------------------------
    Main program
------------------------------------------------------------------------------*/
void main(void)
{
    word sensorValue;
    int i;
    unsigned long sum;
    float UV_Value;

    sum=0L;
    i=0;

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
      sum=0L;

      for(i=0;i<64;i++)
      {
          #if AVR32
             ADC_GetValues(result, 1);
             sensorValue=result[0];
          #else
            // MEGA Serie
            sensorValue=ADC_Read();                  // Read channel values
          #endif

          sum=sum+sensorValue;
          AbsDelay(2);
      }

      sum = sum / 64;
      UV_Value=sum*4980.0/1023.0;

      Msg_WriteText("The voltage value: ");
      Msg_WriteFloat(UV_Value);
      Msg_WriteText("mV\n\r");
      AbsDelay(1000);

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

