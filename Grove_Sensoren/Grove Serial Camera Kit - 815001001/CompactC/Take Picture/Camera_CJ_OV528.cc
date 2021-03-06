/*******************************************************************************

 Project Name:      Grove Camera_CJ_OV528.cprj
 Required Libs's:   IntFunc_lib.cc
 Files:             Camera_CJ_OV528.cc
 Writer:            CCPRO-TEAM
 Date:              10.05.2015
 Function:          Demonstrates the Grove Camera_CJ_OV528

 ------------------------------------------------------------------------------
 AVR32 Serie:
 ------------
 Required the C-Control PRO AVR32-Bit UNIT Conrad BN: 192573
 Applicationboard Conrad BN: 192587
 Or Mainboard Conrad BN: 192702

 Connection:
 -----------
 - Connect the sensor red wire to +5V (AVR32) the Camers dosn't work with 3,3V!
 - Connect the sensor black wire to GND
 - Connect the sensor yellow wire (UART-RxD) P37
 - Connect the sensor white wire (UART-TxD) P36

 Start the program with F10 (or the yellow flash icon) for debug outputs!

 ------------------------------------------------------------------------------

 Note:
 -----
 Source: http://www.seeedstudio.com/depot/Grove-Serial-Camera-Kit-p-1608.html

 Grove - Serial Camera Kit includes one control board and two interchangeble lenses,
 one is standard lens and the other is wide-angle lens.
 To make it more fun and playable, lenses of two specs are shipped in this kit.
 The standard one is for common photo shots and the wide-angle one is specially
 suitable for monitoring projects.

 Specifications:
 ---------------
 * Input Voltage: 5V
 * Pixel: 300,000
 * Resolution: 640*480, 320*240, 160*120
 * Uart Baud Rate: 9600~115200
 * Communication: RS485 and RS232
 * Photo JPEG compression, high, medium and low grades Optional
 * AGC
 * Auto Exposure Event Control
 * Automatic White Balance Control
 * Focus adjustable

*******************************************************************************/

// Only for the C-Control PRO AVR32
#ifdef AVR32

/*------------------------------------------------------------------------------
name:           main
description:    Mainprogram
------------------------------------------------------------------------------*/
void main(void)
{
    char picName[9];
    int picNameNum;
    picNameNum=0;

    // SD WRITE LED
    Port_Attribute(PORT_LED1,PORT_ATTR_OUTPUT|PORT_ATTR_DRIVE_MIN);
    Port_WriteBit(PORT_LED1,0);

    // Input without pull-up or pull-down resistor
    // C-Control PRO Applicationboard have a pull-up resistor on the tactical switches!
    // Normal state read a 1, is the button presses read a 0
    // Use Tactical switch T2 to snap and save a picture on SD-Card
    Port_Attribute(PORT_T2, PORT_ATTR_INPUT);

    // Init
    Msg_WriteText("Camera initialize...\r");
    SD_INIT();
    CAMERA_INIT();
    CAMERA_SIZE_BAUD_FRAM();

    Msg_WriteText("Press T2 to take a picture\r");
    while(1)
    {
        if(!Port_ReadBit(PORT_T2))
        {
            AbsDelay(20);
            if(!Port_ReadBit(PORT_T2))
            {
                // new picture name
                picName ="pic00.jpg";
                picName[3] = picNameNum/10 + '0';
                picName[4] = picNameNum%10 + '0';
                picNameNum++;

                // CREAT NEW FILE
                SD_OPEN_FILE(picName);
                Msg_WriteText("Please wait while save picture ");
                Msg_WriteText(picName);
                Msg_WriteChar(13);
                if(res_sd_info!=0)break;

                GET_PIC();
                CAMERA_SAVE_PIC();
                Msg_WriteText("Picture saved!\r");
            }
        }
    }

    // Error - Exit program
    Msg_WriteText("Error: Program exit!\r\n");

}

#else
#error "Only C-Control PRO AVR32-Bit"
#endif

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









