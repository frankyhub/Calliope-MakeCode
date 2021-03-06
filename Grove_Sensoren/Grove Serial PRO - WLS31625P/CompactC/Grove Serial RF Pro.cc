/*******************************************************************************

 Project Name:      Grove Serial RF Pro.cprj
 Required Libs's:   IntFunc_lib.cc
 Files:             Grove Serial RF PRO.cc
 Writer:            CCPRO-TEAM
 Date:              10.05.2015
 Function:          Demonstrates the Grove Serial RF Pro

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

 Connection:
 -----------
 - Connect the sensor red wire to +5V (MEGA) or +3,3V (AVR32)
 - Connect the sensor black wire to GND
 - Connect the sensor yellow wire (UART-RxD)
 - Connect the sensor white wire (UART-TxD)

 Start the program with F10 (or the yellow flash icon) for debug outputs!

 ------------------------------------------------------------------------------

 Note:
 -----
 Source: http://www.seeedstudio.com/depot/Grove-Serial-RF-Pro-p-794.html
         http://www.seeedstudio.com/wiki/Grove_-_Serial_RF_Pro

 Serial RF Pro Twig is a low cost, high performance transparent FSK transceiver
 with operating at 433/470/868/915 MHz. It features small size, high output power,
 high sensitivity, long transmission distance and high communication data rate
 with auto set up for communication change and data receiving and transmission control. There is UART interface, it is easy to realize the wireless data transmission with only providing the UART data. It is flexible for the users to set the UART baud rate, frequency, output power, data rate, frequency deviation, receiving bandwidth etc parameters. It is your ideal choice for designing wireless data transmission products which can be widely used on wireless data transmission field.

 To get the best performance, please use it at 433MHZ (Default).

 Features:
 ---------
 * Grove compatible
 * Low cost, high performance , high reliability
 * FSK modulation, 2-way half ?duplex communication, strong anti-interfere
 * 433/470/868/915MHz ISM band,globally license free
 * Maximal output power100mW(20dBm),output power adjustable between 1-20dBm
 * Sensitivity -117dBm
 * Supply current for Tx 100mA@20dBm, 40mA@14dBm
 * Supply current for Rx 25mA
 * Low current sleep mode 1uA
 * Operation frequency can be configured, acceptable for several modules working in different frequency with no disturbance on each other
 * Optional for frequency deviation and receiving ISM bandwidth, users can be modulated by software
 * Communication speed 1.2kbps -115.2kbps,can be modulated through software
 * Longer transmission distance,about 600m in open air
 * RSSI function
 * Accord FCC,ETSI standard

 Application Ideas:
 ------------------
 * Remote control, remote measurement system
 * Wireless meter
 * Access control
 * Identification system
 * Data collection
 * IT household appliance
 * Intelligence household appliance
 * Baby monitoring system


*******************************************************************************/

#define UART_PORT           0   // MEGA32 and AVR32 use PORT 0 and MEGA128 use PORT 1
#define MODE                0   // 0 = RX / 1 = TX

// 80 bytes receive + 80 bytes send buffer internal FIFO management
// Caution: Make the buffer never too small!
byte buffer[SERIAL_BUF(80,80)], Buffer_Index, sz, count;         // Array declaration
char str[100];

/*------------------------------------------------------------------------------
    Main program
------------------------------------------------------------------------------*/
void main(void)
{

    // Initialize UART: 9600 bps, 8 Bit, 1 Stop, NP
    // 80 bytes receive buffer - 80 bytes send buffer
    Serial_Init_IRQ(UART_PORT,buffer,80,80,SR_8BIT|SR_1STOP|SR_NO_PAR,SR_BD9600);

    // Receiver function (RX)
    if(MODE==0)
    {
        // Main receive loop
        while(1)
        {

            sz=0;
            Buffer_Index=0;

            // wait for incoming data...
            AbsDelay(1000);

            count=Serial_IRQ_Info(UART_PORT,RS232_FIFO_RECV);    // Investigates, how many characters have been received
            Str_Printf(str,"%02d Characters received by IRQ\r\n", count);
            Msg_WriteText(str);                                  // The number of characters is displayed as message

            // Data are available
            if(Serial_IRQ_Info(UART_PORT,RS232_FIFO_RECV)!=0)
            {
                // Read data
                while(1)
                {
                    Buffer_Index++;
                    sz=Serial_ReadExt(UART_PORT);
                    if(sz==0x100) break;
                    if(Buffer_Index>79)break;
                    Msg_WriteChar(sz);
                }
            }
        }
    }
    // Transceiver function (TX)
    else if(MODE==1)
    {
        while(1)
        {
            Serial_WriteText(UART_PORT, "C-Control with Seeed RF\r\n");
            AbsDelay(1000);
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