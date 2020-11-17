/*******************************************************************************

 Project Name:      Camera_CJ_OV528.cprj
 Required Libs's:   IntFunc_lib.cc
 Files:             Camera_CJ_OV528.cc
 Writer:            CCPRO-TEAM
 Date:              06.05.2015
 Function:          Easy to use Camera_CJ_OV528 library   V1.0

 ------------------------------------------------------------------------------

 Note:

 http://www.seeedstudio.com/wiki/Grove_-_Serial_Camera_Kit

*******************************************************************************/

#define CAMERA_UART    1
#define BUFFER_LEN     128
#define PIC_PKT_LEN    128                  // data length of each read, dont set this too big because ram is limited
#define PIC_FMT_VGA    7
#define PIC_FMT_CIF    5
#define PIC_FMT_OCIF   3
#define CAM_ADDR       0
#define CAM_SERIAL     Serial
#define PIC_FMT        PIC_FMT_VGA

byte sz,buffer[SERIAL_BUF(BUFFER_LEN,50)], Data_Buffer[BUFFER_LEN], Buffer_Index;
byte Pic_array_write[BUFFER_LEN];

/*------------------------------------------------------------------------------
    CAMERA_INIT
------------------------------------------------------------------------------*/
void CAMERA_INIT(void)
{
    Serial_Init_IRQ(CAMERA_UART,buffer,BUFFER_LEN,50,SR_8BIT|SR_1STOP|SR_NO_PAR,SR_BD115200);
    CAMERA_SEND_COMMAND(0X0D,0X00,0X00,0X00,0X00);
    AbsDelay(100);
}

/*------------------------------------------------------------------------------
    CAMERA_SIZE_BAUD_FRAM
------------------------------------------------------------------------------*/
void CAMERA_SIZE_BAUD_FRAM(void)
{
        // ---> Camera Config <---

        // set new baudrate and image size
        CAMERA_CLEAR_UART_BUFFER();
        //CAMERA_SEND_COMMAND(0X01,0X04,0X07,0X00,0X05); // 320x240
        CAMERA_SEND_COMMAND(0X01,0X00,0X07,0X00,PIC_FMT); // VGA
        AbsDelay(100);

        // SET FRAME SIZE
        CAMERA_CLEAR_UART_BUFFER();
        CAMERA_SEND_COMMAND(0x06,0x08,PIC_PKT_LEN&0xff,(PIC_PKT_LEN>>8)&0xff,0);
        AbsDelay(100);
}

/*------------------------------------------------------------------------------
    CAMERA_SAVE_PIC
------------------------------------------------------------------------------*/
void GET_PIC(void)
{
        // GET PIC
        CAMERA_CLEAR_UART_BUFFER();
        CAMERA_SEND_COMMAND(0X05,0X00,0X0,0X00,0X00);
        AbsDelay(100);

        CAMERA_CLEAR_UART_BUFFER();
        CAMERA_SEND_COMMAND(0X04,0X01,0X0,0X00,0X00);
        AbsDelay(500);
        CAMERA_CLEAR_UART_BUFFER();
}

/*------------------------------------------------------------------------------
    CAMERA_SAVE_PIC
------------------------------------------------------------------------------*/
void CAMERA_SAVE_PIC(void)
{
    int pic_frame_cnt, offset_cnt, x_n;
    byte input_cnt, not_full_pic, highbyte, lowbyte;
    not_full_pic=0;
    pic_frame_cnt=0;

repeat_ack:

        CAMERA_CLEAR_UART_BUFFER();
        highbyte=pic_frame_cnt&0xff;
        lowbyte=(pic_frame_cnt>>8)&0xff;

        CAMERA_SEND_COMMAND(0X0E,0X00,0X00,highbyte,lowbyte);
        AbsDelay((PIC_PKT_LEN/10)*2);

        input_cnt=0;
        offset_cnt=0;
        Buffer_Index=0;

        input_cnt=Serial_IRQ_Info(CAMERA_UART,RS232_FIFO_RECV);

        while(1)
        {
            sz=Serial_ReadExt(CAMERA_UART);
            Data_Buffer[Buffer_Index]=sz;
            Buffer_Index++;
            if(Buffer_Index>input_cnt-1)break;
        }

        // normaly data frame 1 to x
        if(Buffer_Index==PIC_PKT_LEN)
        {
            // cut first 4 Bytes and last Bytes
            x_n=0;
            offset_cnt=0;
            for(x_n=4;x_n<=PIC_PKT_LEN-3;x_n++)
            {
                Pic_array_write[offset_cnt]=Data_Buffer[x_n];
                offset_cnt++;
            }
            SD_WRITE_BIN(Pic_array_write,PIC_PKT_LEN-6);
            not_full_pic=0;
        }
        else
        {
            // last frame is smaller the normaly PIC_PKT_LEN
            offset_cnt=0;
            x_n=0;
            for(x_n=4;x_n<=Buffer_Index-3;x_n++)
            {
                Pic_array_write[offset_cnt]=Data_Buffer[x_n];
                offset_cnt++;
            }
            SD_WRITE_BIN(Pic_array_write,offset_cnt-1);

            CAMERA_SEND_COMMAND(0X0E,0X00,0X0,0XF0,0XF0);
            not_full_pic=1;

            // Close open file
            SD_CLOSE_FILE();

        }

        CAMERA_CLEAR_UART_BUFFER();
        pic_frame_cnt++;
        Port_ToggleBit(PORT_LED1);

        if(not_full_pic==0)goto repeat_ack;
        Port_WriteBit(PORT_LED1,0);

        Msg_WriteInt(pic_frame_cnt);
        Msg_WriteText(" Frames write to SD-Disk\r");

}

/*------------------------------------------------------------------------------
    CAMERA_SEND_COMMAND
------------------------------------------------------------------------------*/
void CAMERA_SEND_COMMAND(byte para1, byte para2, byte para3, byte para4, byte para5)
{
    Serial_Write(CAMERA_UART,0XAA);    // default addr
    Serial_Write(CAMERA_UART,para1);
    Serial_Write(CAMERA_UART,para2);
    Serial_Write(CAMERA_UART,para3);
    Serial_Write(CAMERA_UART,para4);
    Serial_Write(CAMERA_UART,para5);
}

/*------------------------------------------------------------------------------
    CAMERA_CLEAR_UART_BUFFER
------------------------------------------------------------------------------*/
void CAMERA_CLEAR_UART_BUFFER(void)
{
    // Clear Buffer
    int i;
    for(i=0;i<BUFFER_LEN-1;i++)
    {
        Data_Buffer[i]=0;
        Pic_array_write[i]=0;
        Serial_ReadExt(CAMERA_UART);
    }
    Buffer_Index=0;
    Serial_Init_IRQ(CAMERA_UART,buffer,BUFFER_LEN,50,SR_8BIT|SR_1STOP|SR_NO_PAR,SR_BD115200);
}


