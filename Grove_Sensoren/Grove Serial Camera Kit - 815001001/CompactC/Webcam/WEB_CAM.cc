/*******************************************************************************

 Project Name:      WEB_CAM.cprj
 Required Libs's:   IntFunc_lib.cc
 Files:             CAMERA_CJ_OV528.cc, SD.Lib.cc
 Writer:            CCPRO-TEAM
 Date:              10.05.2015
 Function:          Demonstrates the Grove Camera_CJ_OV528 with Webserver

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

 HTTP-Webserver:
 ---------------
 http://localhost
 Copy the "Webroot" files to the microSD-Card (main directory)

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

// Webserver user variables
#define WEB_VAR_CNT     1

// Webserver
byte webmem[WEB_BUF(WEB_VAR_CNT)];
byte ip_info[6];
int cmd;

// Str_Printf
char text[80];

/*------------------------------------------------------------------------------
    Main loop
------------------------------------------------------------------------------*/
void main(void)
{

    // Webserver request variable
    byte req_id;
    int counter;
    counter=0;
    cmd=0;

    // Live LED init
    Port_Attribute(PORT_LED2, PORT_ATTR_OUTPUT | PORT_ATTR_INIT_LOW);

    // SD WRITE LED
    Port_Attribute(PORT_LED1,PORT_ATTR_OUTPUT|PORT_ATTR_DRIVE_MIN);
    Port_WriteBit(PORT_LED1,0);

    // SD and Camera initialize
    Msg_WriteText("Camera initialize...\r");
    SD_INIT();
    CAMERA_INIT();
    CAMERA_SIZE_BAUD_FRAM();

    // HTTP Webserver debug output
    ETH_GetIPInfo(EI_IP_ADDR, ip_info);
    Str_Printf(text, "IP-Adresse: %d.%d.%d.%d\r", ip_info[0],ip_info[1],ip_info[2],ip_info[3]);
    Msg_WriteText(text);

    ETH_GetIPInfo(EI_NETMASK, ip_info);
    Str_Printf(text, "IP-Netmask: %d.%d.%d.%d\r", ip_info[0],ip_info[1],ip_info[2],ip_info[3]);
    Msg_WriteText(text);

    ETH_GetIPInfo(EI_GATEWAY, ip_info);
    Str_Printf(text, "IP-Gateway: %d.%d.%d.%d\r", ip_info[0],ip_info[1],ip_info[2],ip_info[3]);
    Msg_WriteText(text);

    // Start the HTTP Websever as port 80
    WEB_StartServer(80, webmem, WEB_VAR_CNT, 0);

    // Set the HTTP Webserver variables
    WEB_SetDynVar(0, cmd, DYN_INT,  DYN_CGIVAR, 0);

    // Here start the endless loop
    while(1)
    {

        // Received the request variable
        req_id=WEB_GetRequest();

        if(req_id!=0)
        {
            Str_Printf(text, "req_id:%d hash:%x cmd:%d\r", req_id, WEB_GetFileHash(req_id), cmd);
            Msg_WriteText(text);

            if(cmd==1)
            {
                // Save the Camera Picture
                SNAP();
            }
            // Clear the request variable and send infomation to Website
            cmd=0;
            WEB_ReleaseRequest(req_id);
        }

        // Toggle "Live LED"
        if(counter==1000)
        {
            Port_ToggleBit(PORT_LED2);
            counter=0;
        }

        counter++;

    }

}

/*------------------------------------------------------------------------------
    SNAP PIC
------------------------------------------------------------------------------*/
void SNAP(void)
{
    // Save the Camera Picture
    SD_OPEN_FILE("bild.jpg");
    GET_PIC();
    CAMERA_SAVE_PIC();
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