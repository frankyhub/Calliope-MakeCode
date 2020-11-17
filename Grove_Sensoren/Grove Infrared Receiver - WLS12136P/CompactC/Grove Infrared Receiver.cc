/*******************************************************************************

 Project Name:      Grove Infrared Emitter.cprj
 Required Libs's:   IntFunc_lib.cc
 Files:             Grove Infrared Receiver.cc
 Writer:            CCPRO-TEAM
 Date:              10.05.2015
 Function:          Demonstrates the Grove Infrared Receiver

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
 Source: http://www.seeedstudio.com/depot/Grove-Infrared-Receiver-p-994.html

 The Infrared Receiver is used to receive infrared signals and also used for
 remote control detection. There is a IR detector on the Infrared Receiver
 which is used to get the infrared light emitted by the Infrared Emitter.
 The IR detector have a demodulator inside that looks for modulated IR at 38 KHz.
 The Infrared Receiver can receive signals well within 10 meters.
 If more than 10 meters , the receiver may not get the signals.
 We often use the two Twigs-the Infrared Receiver and the Infrared Emitter
 to work together.

*******************************************************************************/


/*------------------------------------------------------------------------------
    Main program
------------------------------------------------------------------------------*/
void main(void)
{
    word rc5_data;

    // Pin config
    #ifdef AVR32
        // Connect on the AVR32 the yellow wire to pin P38 or other free pin...
        RC5_Init(P38);
    #else
        // Mega32 or Mega128 (PD.0) connect the yellow wire to pin 24 or other free pin...
        RC5_Init(24);
    #endif

    while(1)
    {
        // Read data (max. 113ms)
        rc5_data = RC5_Read();

        // Show word
        if(rc5_data)
        {
            Msg_WriteInt(rc5_data);
            Msg_WriteChar(13);
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