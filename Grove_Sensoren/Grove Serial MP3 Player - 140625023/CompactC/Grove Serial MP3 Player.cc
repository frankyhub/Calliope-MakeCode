/*******************************************************************************

 Project Name:      Grove Serial MP3 Player.cprj
 Required Libs's:   IntFunc_lib.cc
 Files:             Grove Serial MP3 Player.cc
 Writer:            CCPRO-TEAM
 Date:              10.05.2015
 Function:          Demonstrates the Grove Serial MP3 Player

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

 Attention!
 ----------
 MEGA32 use the same UART to upload the program, please disconnect the MP3 Player bevor uploading !!!

 Start the program with F10 (or the yellow flash icon) for debug outputs!

 ------------------------------------------------------------------------------

 Note:
 -----
 Source: http://www.seeedstudio.com/depot/Grove-Serial-MP3-Player-p-1542.html

 Grove-Serial MP3 Player is a kind of simple MP3 player device whose design
 is based on a high-quality MP3 audio chip---WT5001. It can support 8KHZ~44.1KHZ
 sampling frequency MP3 and WAV file formats. This product has several peripheral
 ports: a standard UART Grove interface, a dual track headphone jack,
 an external interface and also a  micro SD card interface.
 You can control the MP3 playback state by sending commands to module via serial
 port tools, such as switch songs, change the volume and play mode and so on.
 It seems a simple module, but it owns such strong function. Want to know how
 the sound quality? Please come to experience it!

 Features:
 ---------
 * Standard Grove interface
 * Asynchronous serial port control play mode
 * Busy Indicator
 * Reset Button
 * Standard micro SD card Interface
 * Support FAT16 and FAT32 file system

*******************************************************************************/

byte PORT;

/*------------------------------------------------------------------------------
    SetMusicPlay
    Set the music index to play, the index is decided by the input sequence
    of the music.
    hbyte: the high byte of the index
    lbyte: the low byte of the index
------------------------------------------------------------------------------*/
byte SetMusicPlay(byte hbyte, byte lbyte)
{
    Serial_Write(PORT, 0x7E);
    Serial_Write(PORT, 0x04);
    Serial_Write(PORT, 0xA0);
    Serial_Write(PORT, hbyte);
    Serial_Write(PORT, lbyte);
    Serial_Write(PORT, 0x7E);
    AbsDelay(100);

    #if AVR32
        if(0xA0==Serial_ReadExt(PORT))
    #else
        if(0xA0==Serial_Read(PORT))
    #endif
            return 1;
        else
            return 0;
}

/*------------------------------------------------------------------------------
    PauseOnOffCurrentMusic - Pause on/off  the current music
------------------------------------------------------------------------------*/
byte PauseOnOffCurrentMusic(void)
{
    Serial_Write(PORT, 0x7E);
    Serial_Write(PORT, 0x02);
    Serial_Write(PORT, 0xA3);
    Serial_Write(PORT, 0x7E);
    AbsDelay(100);

    #if AVR32
        if(0xA3==Serial_ReadExt(PORT))
    #else
        if(0xA3==Serial_Read(PORT))
    #endif
            return 1;
        else
            return 0;
}

/*------------------------------------------------------------------------------
    SetVolume - Set the volume, the range is 0x00 to 0x1F
------------------------------------------------------------------------------*/
byte SetVolume(byte volume)
{
    Serial_Write(PORT, 0x7E);
    Serial_Write(PORT, 0x03);
    Serial_Write(PORT, 0xA7);
    Serial_Write(PORT, volume);
    Serial_Write(PORT, 0x7E);
    AbsDelay(100);

    #if AVR32
        if(0xA7==Serial_ReadExt(PORT))
    #else
        if(0xA7==Serial_Read(PORT))
    #endif
            return 1;
        else
            return 0;
}

/*------------------------------------------------------------------------------
    SetPlayMode
------------------------------------------------------------------------------*/
byte SetPlayMode(byte playmode)
{
    if(((playmode==0x00)|(playmode==0x01)|(playmode==0x02)|(playmode==0x03))==false)
    {
        Msg_WriteText("PlayMode Parameter Error!\r");
        return 0;
    }

    Serial_Write(PORT, 0x7E);
    Serial_Write(PORT, 0x03);
    Serial_Write(PORT, 0xA9);
    Serial_Write(PORT, playmode);
    Serial_Write(PORT, 0x7E);
    AbsDelay(100);

    #if AVR32
        if(0xA9==Serial_ReadExt(PORT))
    #else
        if(0xA9==Serial_Read(PORT))
    #endif
            return 1;
        else
            return 0;
}

/*------------------------------------------------------------------------------
    Main program
------------------------------------------------------------------------------*/
void main(void)
{
    // UART Init
    #if AVR32
        PORT=0;  // P38 = RxD / P39 = TxD UART0
    #else
        PORT=1;  // MEGA128 use PORT 1 (RxD=PD2, TxD=PD3)
                 // MEGA32 use PORT 0 (RxD=PD0, TxD=PD1)
    #endif

    Serial_Init(PORT,SR_8BIT|SR_1STOP|SR_NO_PAR,SR_BD9600);

    // Play a Song (use max. 2GB SD-Card)
    if(true==SetPlayMode(0x01))
        Msg_WriteText("Set The Play Mode to 0x01, Single Loop Mode.\r");
    else
        Msg_WriteText("Playmode Set Error\r");

    PauseOnOffCurrentMusic();
    SetPlayMode(0x01);          // show WT5001 datasheet
    AbsDelay(1000);
    SetMusicPlay(00,01);        // Song number (highbyte, lowbyte)
    AbsDelay(1000);
    SetVolume(0x1F);            // Volume 0x00 to 0x1F (Dec. 32)

    while(1);                   // endless...
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