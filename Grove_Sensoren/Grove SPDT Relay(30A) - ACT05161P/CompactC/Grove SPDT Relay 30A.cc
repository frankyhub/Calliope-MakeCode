/*******************************************************************************

 Project Name:      Grove SPDT 30A.cprj
 Required Libs's:   IntFunc_lib.cc
 Files:             Gove SPDT Relay.cc
 Writer:            CCPRO-TEAM
 Date:              10.05.2015
 Function:          Demonstrates switch the Gove Relay

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
 ------------------------------------------------------------------------------

 Note:
 -----
 - Connect the Grove-Relay red wire to +5V
 - Connect the Grove-Relay black wire to GND
 - Connect the Grove-Relay yellow wire to C-Control Port
 - The Grove-Relay white wire is not connected

 Input:
 ------
 Mega32:  PA0 (PortA.0)
 Mega128: PD6 (PortD.6)
 AVR32:   P47

 Start the program with F10 (or the yellow flash icon) for debug outputs!

*******************************************************************************/

#define AVR32_RELAY_PIN     27
#define MEGA_RELAY_PIN      0      // Pin PA.0


/*------------------------------------------------------------------------------
    Main program - toggle the Relay every second
------------------------------------------------------------------------------*/
void main(void)
{
#if AVR32
    Port_Attribute(AVR32_RELAY_PIN, PORT_ATTR_OUTPUT|PORT_ATTR_INIT_LOW);
#else
    Port_DataDirBit(MEGA_RELAY_PIN, PORT_OUT);
#endif

    // Endless loop
    while(1)
    {
        #if AVR32
            Port_ToggleBit(AVR32_RELAY_PIN);
        #else
            Port_ToggleBit(MEGA_RELAY_PIN);
        #endif

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

