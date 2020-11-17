/*******************************************************************************

 Project Name:      Grove PIR Motion Sensor.cprj
 Required Libs's:   IntFunc_lib.cc
 Files:             Grove PIR Motion Sensor.cc
 Writer:            CCPRO-TEAM
 Date:              10.05.2015
 Function:          Demonstrates the PIR Motion Sensor

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

 Input:
 ------
 Mega32:  PA0 (PortA.0)
 Mega128: PD6 (PortD.6)
 AVR32:   P47

 Connection:
 -----------
 - Connect the Sensor red wire to +5V (MEGA) or +3,3V (AVR32)
 - Connect the Sensor black wire to GND
 - Connect the Sensor yellow wire to C-Control digital input pin
 - The white sensor wire is not connected

 Start the program with F10 (or the yellow flash icon) for debug outputs!

 ------------------------------------------------------------------------------

 Note:
 -----
 Source: http://www.seeedstudio.com/depot/Grove-PIR-Motion-Sensor-p-802.html

 This is a simple to use PIR motion sensor with Grove compatible interface.
 Simply connect it to Stem shield and program it, when anyone moves in its
 detecting range, the sensor outputs HIGH on its SIG pin.

 The detecting range and response speed can be adjusted by 2 potentiometers
 soldered on its circuit board, The response speed is from 0.3s - 25s,
 and max 6 meters of detecting range.
 Note: Potentiometers are not included!

 Specifications:
 ---------------
 * Grove compatible interface
 * Voltage range: 3V–5V
 * Detecting angle: 120 degree
 * Detecting distance: max 6m  (3m by default)
 * Adjustable detecting distance and holding time

 Application Ideas:
 ------------------
 * Motion sensor
 * Thief-guarding System
 * Switch
 * Industrial automation

*******************************************************************************/

#define AVR32_DETECT_PIN        P47
#define MEGA32_DETECT_PIN       0
#define MEGA128_DETECT_PIN      30
#define ALARM_MSG               "ALARM INTRUDER!"

/*------------------------------------------------------------------------------
    Main program
------------------------------------------------------------------------------*/
void main(void)
{

    byte people_detect;

    #if AVR32
        // Output
        Port_Attribute(PORT_LED1, PORT_ATTR_OUTPUT|PORT_ATTR_INIT_LOW);     // LED1

        // Input
        Port_Attribute(AVR32_DETECT_PIN, PORT_ATTR_INPUT);                  // PIR Sensor

        // LCD INIT (only Applicationboard)
        LCD_Init();
        LCD_CursorOff();
        LCD_ClearLCD();
    #else
        // Input
        Port_DataDirBit(MEGA128_DETECT_PIN, PORT_IN);                       // PIR Sensor
    #endif


    // Endless loop
    while(1)
    {
      #ifdef AVR32
        // Read the PIR Sensor
        if(Port_ReadBit(AVR32_DETECT_PIN))
        {
            people_detect=1;
            Port_WriteBit(PORT_LED1, 1);    // On
        }
        else
        {
            people_detect=0;
            Port_WriteBit(PORT_LED1, 0);    // Off
        }
      #else
        // MEGA Serie

        // read the PIR Sensor
        if(Port_ReadBit(MEGA128_DETECT_PIN))
        {
            people_detect=1;
        }
        else
        {
            people_detect=0;
        }
      #endif

      // If a people detect, send a alarm Message to the IDE output window
      if(people_detect)
      {
        Msg_WriteText(ALARM_MSG);
        Msg_WriteChar('\r');

        #ifdef AVR32
            LCD_Locate(0,0);
            LCD_WriteText(ALARM_MSG);
        #endif

        AbsDelay(5000);

        #ifdef AVR32
            LCD_ClearLCD();
        #endif

      }

      AbsDelay(100);

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

