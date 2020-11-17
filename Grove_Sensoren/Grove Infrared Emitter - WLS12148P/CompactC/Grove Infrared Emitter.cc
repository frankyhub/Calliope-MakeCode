/*******************************************************************************

 Project Name:      Grove Infrared Emitter.cprj
 Required Libs's:   IntFunc_lib.cc
 Files:             Grove Infrared Emitter.cc
 Writer:            CCPRO-TEAM
 Date:              10.05.2015
 Function:          Demonstrates the Grove Infrared Emitter

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

 Start the program with F10 (or the yellow flash icon) for debug outputs!

 ------------------------------------------------------------------------------

 Note:
 -----
 Source: http://www.seeedstudio.com/depot/Grove-Infrared-Emitter-p-993.html

 The Infrared Emitter is used to transmit infrared signals through an infrared LED,
 while there is an Infrared receiver to get the signals on the other side .
 An infrared LED is like any other LED, with its color centered around 940nm.
 We can use the emitter not only to transmit data or commands, but also to emulate
 remotes to control your home appliance using an Arduino. The Infrared Emitter can
 transmit signals reliable up to 10 meters. Beyond 10 meters,
 the receiver may not get the signals.

*******************************************************************************/


/*------------------------------------------------------------------------------
    Main program
------------------------------------------------------------------------------*/
void main(void)
{
    // Pin config
    #if AVR32
        // Connect on the AVR32 the yellow wire to pin P46 or other free pin...
        RC5_Init(P46);
    #else
        // Mega32 or Mega128 (PD.0) connect the yellow wire to pin 24 or other free pin...
        RC5_Init(24);
    #endif

    // Send every 2 sec. the RC5 Code...
    while(1)
    {
        //RC5_Write(0b11000000000001);
        RC5_Write(12345);
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