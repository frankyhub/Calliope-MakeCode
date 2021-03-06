/*******************************************************************************

 Project Name:      Grove Relay.cprj
 Required Libs's:   IntFunc_lib.cc
 Files:             Gove Relay.cc
 Writer:            CCPRO-TEAM
 Date:              29.05.2015
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

 Source: http://www.seeedstudio.com/depot/Grove-Relay-p-769.html

 The Relay is a digital normally open switch that controls a relay capable of
 switching much higher voltages and currents than your normal C-Control boards.
 When set to HIGH, the LED will light up and the relay will close allowing
 current to flow. The peak voltage capability is 250V at 10 amps.

 Please exercise great care when working with mains voltages? if in doubt
 contact a professional such as a licensed electrician for help.

 Dimension:42.00mm*24.00mm*19.50mm

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

/*------------------------------------------------------------------------------
    Main program - toggle the Relay every second
------------------------------------------------------------------------------*/
void main(void)
{
#if AVR32
    Port_Attribute(P47, PORT_ATTR_OUTPUT|PORT_ATTR_INIT_LOW);
#endif

#if MEGA32
    Port_DataDirBit(PA0, PORT_OUT);
#endif

#if MEGA128_ARCH||MEGA128CAN
    Port_DataDirBit(PD6, PORT_OUT);
#endif

    // Endless loop
    while(1)
    {
        #if AVR32
            Port_ToggleBit(P47);
        #endif

        #if MEGA32
            Port_ToggleBit(PA0);
        #endif

        #if MEGA128_ARCH||MEGA128CAN
            Port_ToggleBit(PD6);
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

