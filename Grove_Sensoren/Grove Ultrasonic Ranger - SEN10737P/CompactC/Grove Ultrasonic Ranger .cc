/*******************************************************************************

 Project Name:      Grove Ultrasonic Ranger.cprj
 Required Libs's:   IntFunc_lib.cc
 Files:             Grove Ultrasonic Ranger.cc
 Writer:            CCPRO-TEAM
 Date:              07.06.2015
 Function:          Demonstrates the Grove Ultrasonic Ranger

 ------------------------------------------------------------------------------
 MEGA Serie:
 -----------
 Required the C-Control PRO MEGA32 UNIT Conrad BN: 198206
 and Evalationboard Conrad BN: 198245
 Or Projectboard Conrad BN: 197287

 Or C-Control PRO MEGA128 UNIT Conrad BN: 198219
 Or C-Control PRO MEGA128CAN Conrad BN: 197989
 and Evaluationboard Conrad BN: 198258
 or Projectboard Conrad BN: 197313

 Pulse in- output:
 -----------------
 Mega32:  Counter input (input capture) PD6 (PortD.6)
 Mega128: Timer1 counter input (input capture) PD4 (PortD.4)

 Connection:
 -----------
 - Connect the Sensor red wire to +5V (MEGA) or +3,3V (AVR32)
 - Connect the Sensor black wire to GND
 - Connect the Sensor yellow wire to C-Control ICP Pin
 - The Sensor white wire is open

 Start the program with F10 (or the yellow flash icon) for debug outputs!

 ------------------------------------------------------------------------------

 Note:
 -----
 Source: http://www.seeedstudio.com/depot/Grove-Ultrasonic-Ranger-p-960.html

 This Grove-ultrasonic sensor is a non-contact distance measurement module
 which is compatible with the Grove system. It’s designed for easy modular
 project usage with industrial performance. There is also the electronic
 version of this module here

 Features:
 ---------
 * Detecting range: 3cm-4m,best in 30 degree angle.
 * Grove interface
 * 5V DC power supply
 * Arduino library ready

*******************************************************************************/

word PM_Value;

/*------------------------------------------------------------------------------
    Measurement
------------------------------------------------------------------------------*/
void Timer1_ISR(void)
{
    PM_Value=Timer_T1GetPM();                   // read value
    Irq_GetCount(INT_TIM1CAPT);                 // reset Interrupt
}

/*------------------------------------------------------------------------------
    Main program
------------------------------------------------------------------------------*/
void main(void)
{
    float distance_cm;
    float distance_inch;
    word timeout;
    timeout=0;

    // endless loop
    while(1)
    {
        // pulse - start measurement
        #if MEGA32
            Port_DataDirBit(PD6,1);
            Port_WriteBit(PD6,0);
            Port_WriteBit(PD6,1);
            Port_WriteBit(PD6,0);
            Port_DataDirBit(PD6,0);
        #endif

        #if MEGA128_ARCH||MEGA128CAN
            Port_DataDirBit(PD4,1);
            Port_WriteBit(PD4,0);
            Port_WriteBit(PD4,1);
            Port_WriteBit(PD4,0);
            Port_DataDirBit(PD4,0);
        #endif

        Irq_SetVect(INT_TIM1CAPT,Timer1_ISR);       // define Interrupt Service Routine

        PM_Value=0;
        Timer_T1PM(0,PS_64);                        // initialize and start pulswith measurement

        timeout=0;                                  // timeout reset
        while(PM_Value==0)                          // wait for new value
        {
            if(timeout>200)break;
            timeout++;
            AbsDelay(1);
        }


        #if MEGA32||MEGA128_ARCH
            // cm
            distance_cm=(PM_Value*4.34)/29/2;

            // inch
            distance_inch=(PM_Value*4.34)/74/2;
        #endif

        #if MEGA128CAN
            // cm
            distance_cm=(PM_Value*4)/29/2;

            // inch
            distance_inch=(PM_Value*4)/74/2;
        #endif

        Msg_WriteFloat(distance_cm);
        Msg_WriteText(" cm\r");
        Msg_WriteFloat(distance_inch);
        Msg_WriteText(" inch\n\r");
        AbsDelay(500);                          // delay 500ms
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

