/*******************************************************************************

 Project Name:      Grove Mini Fan.cprj
 Required Libs's:   IntFunc_lib.cc
 Files:             Grove Mini Fan.cc
 Writer:            CCPRO-TEAM
 Date:              07.06.2015
 Function:          Demonstrates the Grove Mini Fan

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

 PWM Output:
 ------------
 AVR32: Output PWMH_1 255 is slow (P38) or PWML_1 (P39) 255 is fast
 Mega32: Output PB3 (PortB.3)
 Mega128: Output PB4 (PortB.4)

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
 Source: http://www.seeedstudio.com/wiki/Grove_-_Mini_Fan

 Grove - Mini Fan is a DC motor driver base on AVR microcontroller Atmega168,
 you can change code by breakout , this module also reserve servo connector,
 it can driver servo by change code ,Grove - Mini Fan is design for kids,
 which is use soft fan-leafed in order to avoid unnecessary damage.

 Specification:
 --------------
 * Grove connector
 * Soft fan-leafed
 * User-friendly

 Package Include:
 ----------------
 * Grove - Mini Fan
 * Fan
 * DC Motor
 * Grove Cable-20cm

*******************************************************************************/


/*------------------------------------------------------------------------------
    Main program
------------------------------------------------------------------------------*/
void main(void)
{
    byte speed, flag;
    flag=0;
    speed=1;

    #if AVR32
        PWM_Init(1, PWM_16, PWM_ENAB_HIGH|PWM_ENAB_LOW);
    #endif

    // Endless loop
    while(1)
    {
        #if AVR32
            // Set new PWM output value
            PWM_Update(1, 255L, speed, 0, 0);
        #endif

        #if MEGA32||MEGA128_ARCH||MEGA128CAN
            Timer_T0PWM(speed,PS0_8);
        #endif

        // up-/down counter
        if((flag==0))
        {
            speed++;
            if(speed>254)flag=1;
        }
        else if((flag==1))
        {
            speed--;
            if(speed<=1)flag=0;
        }

        // PWM speed info
        Msg_WriteText("Speed: ");
        Msg_WriteWord(speed);
        Msg_WriteText("\r");
        AbsDelay(20);
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

