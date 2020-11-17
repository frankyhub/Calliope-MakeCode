/*******************************************************************************

 Project Name:      File_Access.cprj
 Required Libs's:   IntFunc_lib.cc
 Files:             SD_Lib.cc
 Writer:            CCPRO-TEAM
 Date:              02.05.2015
 Function:          Easy to use C-Control PRO SD-Card library   V1.2

 ------------------------------------------------------------------------------

 Note:
 MEGA128 and MEGA128CAN -> C-Control Pro SD-Card holder required!
 C-Control SD-Card Interface Conrad BN: 197220

 V1.1: - SD_WRITE_BIN

*******************************************************************************/

// must be global declared
byte _fat[SDC_FAT_BUF];
byte _fil[SDC_FILE_BUF];
dword _free_kb[1];
dword _attrib[4], _attr;

// variable for external use
char error_str[30];
char SD_READ_BUF[SDC_FAT_BUF];
byte res_sd_info;

/*------------------------------------------------------------------------------
name:           SD_RESET (only MEGA128 and MEGA128CAN)
input:          none
output:         none
description:    Reset the SD-Card holder (Reset Pins EN1 & EN2)
------------------------------------------------------------------------------*/
void SD_RESET(void)
{
#ifndef AVR32
    // disable EN1 for 50ms - on PB.5
    Port_DataDirBit(13,1);

    // enable EN2 - on PB.6
    Port_DataDirBit(14,1);

    // EN1 High
    Port_WriteBit(13,1);

    // EN2 Low
    Port_WriteBit(14,0);

    AbsDelay(50);

    // EN1 Low
    Port_WriteBit(13,0);

    // EN2 Hight
    Port_WriteBit(14,1);
#endif
}

/*------------------------------------------------------------------------------
name:           SD_POWER_ON (only MEGA128 and MEGA128CAN)
input:          none
output:         none
description:    SD-Card holder power on (if available)
------------------------------------------------------------------------------*/
void SD_POWER_ON(void)
{
#ifndef AVR32
    // enable EN2 - on PB.6
    Port_DataDirBit(14,1);
    Port_WriteBit(14,1);
    AbsDelay(50);
#endif
}

/*------------------------------------------------------------------------------
name:           SD_POWER_OFF (only MEGA128 and MEGA128CAN)
input:          none
output:         none
description:    SD-Card holder power off (if available)
------------------------------------------------------------------------------*/
void SD_POWER_OFF(void)
{
#ifndef AVR32
    // disable EN2 - on PB.6
    Port_DataDirBit(14,1);
    Port_WriteBit(14,0);
    AbsDelay(50);
#endif
}

/*------------------------------------------------------------------------------
name:           SD_ACCESS_LED_ON (only MEGA128 and MEGA128CAN)
input:          none
output:         none
description:    SD-Card holder access LED on (if available)
------------------------------------------------------------------------------*/
void SD_ACCESS_LED_ON(void)
{
#ifndef AVR32
    // access led on PB.7
    Port_DataDirBit(15,1);
    Port_WriteBit(15,1);
#endif
}

/*------------------------------------------------------------------------------
name:           SD_ACCESS_LED_OFF (only MEGA128 and MEGA128CAN)
input:          none
output:         none
description:    SD-Card holder access LED off (if available)
------------------------------------------------------------------------------*/
void SD_ACCESS_LED_OFF(void)
{
#ifndef AVR32
    // access led on PB.7
    Port_DataDirBit(15,1);
    Port_WriteBit(15,0);
#endif
}

/*------------------------------------------------------------------------------
name:           error_code_translate
input:          Error byte
output:         global error string
description:    Returns the Error code as string
------------------------------------------------------------------------------*/
void error_code_translate(byte res)
{

    if(res==0)error_str="FR_OK\r";
    else if(res==1)error_str="FR_DISK_ERR\r";
    else if(res==2)error_str="FR_INT_ERR\r";
    else if(res==3)error_str="FR_NOT_READY\r";
    else if(res==4)error_str="FR_NO_FILE\r";
    else if(res==5)error_str="FR_NO_PATH\r";
    else if(res==6)error_str="FR_INVALID_NAME\r";
    else if(res==7)error_str="FR_DENIED\r";
    else if(res==8)error_str="FR_EXIST\r";
    else if(res==9)error_str="FR_INVALID_OBJECT\r";
    else if(res==10)error_str="FR_WRITE_PROTECTED\r";
    else if(res==11)error_str="FR_INVALID_DRIVE\r";
    else if(res==12)error_str="FR_NOT_ENABLED\r";
    else if(res==13)error_str="FR_NO_FILESYSTEM\r";
    else if(res==14)error_str="FR_MKFS_ABORTED\r";
    else if(res==15)error_str="FR_TIMEOUT\r";

}

/*------------------------------------------------------------------------------
name:           isolate_bits
input:          value, from, to (help function)
output:         isolatet bits
description:    Bit isolated function for Date & Time
------------------------------------------------------------------------------*/
word isolate_bits(word val, byte from, byte to)
{
    return((val>>from) & ((1<<(to-from+1))-1));
}

/*------------------------------------------------------------------------------
name:           SD_INIT
input:          none
output:         change error code
description:    Init the SD-Card (call this first)
------------------------------------------------------------------------------*/
void SD_INIT(void)
{

    char SD_READ_BUF[SDC_FAT_BUF];

    byte res;
    word i;

    // clear arrays
    for(i=0;i<SDC_FAT_BUF;i++)
    {
        _fat[i]=0;
        SD_READ_BUF[i]=0;
    }

    for(i=0;i<SDC_FILE_BUF;i++)
    {
        _fil[i]=0;
    }

    res=SDC_Init(_fat);
    error_code_translate(res);
    res_sd_info=res;
}

/*------------------------------------------------------------------------------
name:           SD_FREE
input:          none
output:         size of free SD-Card memory (kB)
description:    read available SD-Card memory
------------------------------------------------------------------------------*/
dword SD_FREE(void)
{
    dword free_kb[1];
    byte res;

    res= SDC_GetFree("0:/", free_kb);
    error_code_translate(res);
    res_sd_info=res;
    return free_kb[0];
}

/*------------------------------------------------------------------------------
name:           SD_NEW_DIR
input:          directory name as string
output:         none
description:    create a new directory folder
------------------------------------------------------------------------------*/
void SD_NEW_DIR(char dir_name[])
{
    byte res;
    char str[20];
    Str_Printf(str,"0:/%s",dir_name);
    res=SDC_MkDir(str);
    res_sd_info=res;
    error_code_translate(res);
}

/*------------------------------------------------------------------------------
name:           SD_NEW_DIRS
input:          directory names as string
output:         none
description:    create a new directory folder with sub folder
------------------------------------------------------------------------------*/
void SD_NEW_DIRS(char dir_name1[], char dir_name2[])
{
    byte res;
    char str[20];
    Str_Printf(str,"0:/%s",dir_name1);
    res=SDC_MkDir(str);
    Str_Printf(str,"0:/%s/%s",dir_name1, dir_name2);
    res=SDC_MkDir(str);
    res_sd_info=res;
    error_code_translate(res);
}

/*------------------------------------------------------------------------------
name:           SD_OPEN_FILE
input:          file name as string
output:         none
description:    open file to write
------------------------------------------------------------------------------*/
void SD_OPEN_FILE(char file_name[])
{
    byte res;
    char str[40];
    Str_Printf(str,"0:/%s",file_name);
    res=SDC_FOpen(_fil, str, FA_WRITE|FA_CREATE_ALWAYS);
    res_sd_info=res;
    error_code_translate(res);
}

/*------------------------------------------------------------------------------
name:           SD_REOPEN_FILE
input:          file name as string
output:         none
description:    open existing file
------------------------------------------------------------------------------*/
void SD_REOPEN_FILE(char file_name[])
{
    byte res;
    char str[20];
    Str_Printf(str,"0:/%s",file_name);
    res=SDC_FOpen(_fil, str, FA_READ|FA_WRITE|FA_OPEN_EXISTING);
    res_sd_info=res;
    error_code_translate(res);
}

/*------------------------------------------------------------------------------
name:           SD_CLOSE_FILE
input:          none
output:         none
description:    close the open file
------------------------------------------------------------------------------*/
void SD_CLOSE_FILE(void)
{
    byte res;
    res=SDC_FClose(_fil);
    res_sd_info=res;
    error_code_translate(res);
}

/*------------------------------------------------------------------------------
name:           SD_WRITE_FILE
input:          string to write
output:         bytes written
description:    write file
------------------------------------------------------------------------------*/
word SD_WRITE_FILE(char txt[])
{
     byte res;
     word bytes_written[1];
     res=SDC_FWrite(_fil, txt, Str_Len(txt), bytes_written);
     error_code_translate(res);
     res=SDC_FSync(_fil);
     res_sd_info=res;
     error_code_translate(res);
     return bytes_written[0];
}

/*------------------------------------------------------------------------------
name:           SD_WRITE_BIN
input:          bytes to write
output:         bytes written
description:    write file
------------------------------------------------------------------------------*/
word SD_WRITE_BIN(byte data_bin[], byte len)
{
     byte res;
     word bytes_written[1];
     res=SDC_FWrite(_fil, data_bin, len, bytes_written);
     error_code_translate(res);
     res=SDC_FSync(_fil);
     res_sd_info=res;
     error_code_translate(res);
     return bytes_written[0];
}

/*------------------------------------------------------------------------------
name:           SD_SEEK
input:          set cursor to position
output:         none
description:    "hello" cursor after hello is 6 (position is 6)
------------------------------------------------------------------------------*/
void SD_SEEK(long position)
{
     byte res;
     res=SDC_FSeek(_fil, position);
     res_sd_info=res;
     error_code_translate(res);
}

/*------------------------------------------------------------------------------
name:           SD_READ_STRING
input:          position
output:         bytes read
description:    read string from file at pos char 9
------------------------------------------------------------------------------*/
word SD_READ_STRING(long lenght)
{
    byte res;
    char buf[SDC_FAT_BUF];
    char str[SDC_FAT_BUF];
    word bytes_read[1];
    res=SDC_FRead(_fil, buf, lenght, bytes_read);
    res_sd_info=res;
    buf[lenght]=0;
    error_code_translate(res);
    Str_Printf(SD_READ_BUF, "%s", buf);
    return bytes_read[0];
}

/*------------------------------------------------------------------------------
name:           SD_TRUNCATE
input:          position
output:         none
description:    truncate file at this position
------------------------------------------------------------------------------*/
void SD_TRUNCATE(char fil[])
{
    byte res;
    res=SDC_FTruncate(fil);
    res_sd_info=res;
    error_code_translate(res);
}

/*------------------------------------------------------------------------------
name:           SD_RENAME_FILE
input:          name old, name new as string
output:         none
description:    rename file
------------------------------------------------------------------------------*/
void SD_RENAME_FILE(char file_name_old[], char file_name_new[])
{
    byte res;
    char str1[20];
    char str2[20];
    Str_Printf(str1,"0:/%s",file_name_old);
    Str_Printf(str2,"/%s",file_name_new);
    res=SDC_Rename(str1, str2);
    res_sd_info=res;
    error_code_translate(res);
}

/*------------------------------------------------------------------------------
name:           SD_CLEANUP
input:          file or folder name as string
output:         none
description:    clear file or folder
------------------------------------------------------------------------------*/
void SD_CLEANUP(char name_file_or_folder[])
{
    byte res;
    char str[20];
    Str_Printf(str,"0:/%s",name_file_or_folder);
    res=SDC_Unlink(str);
    res_sd_info=res;
    error_code_translate(res);
}

/*------------------------------------------------------------------------------
name:           SD_SET_TIME_DATE
input:          file name, day, month, year, hour, minute, second
output:         none
description:    write date and time info
------------------------------------------------------------------------------*/
void SD_SET_DATE_TIME(char file_name[],byte day, byte month, word year, byte minute, byte hour, byte second)
{
    byte res;
    char str[40];
    Str_Printf(str,"0:/%s",file_name);
    res=SDC_FSetDateTime(str, day, month, year, hour, minute, second);
    res_sd_info=res;
    error_code_translate(res);
}

/*------------------------------------------------------------------------------
name:           SD_READ_FILE_STATUS
input:          file name
output:         none
description:    show file infos
------------------------------------------------------------------------------*/
void SD_READ_FILE_STATUS(char file_name[])
{
    byte res;
    char str[40];
    dword attrib[4], attr;
    Str_Printf(str,"0:/%s",file_name);

    res=SDC_FStat(str, attrib);
    error_code_translate(res);
    res_sd_info=res;
    Msg_WriteText(error_str);

    // output size
    Str_Printf(str, "Filesize:%ld\r", attrib[0]);
    Msg_WriteText(str);

    // output date
    Str_Printf(str, "date: %02d.%02d.%d\r",  isolate_bits(attrib[1],0,4),
    isolate_bits(attrib[1],5,8), isolate_bits(attrib[1],9,15)+1980);
    Msg_WriteText(str);

    // output time
    Str_Printf(str, "time: %02d:%02d:%02d\r",  isolate_bits(attrib[2],11,15),
    isolate_bits(attrib[2],5,10), isolate_bits(attrib[2],0,4)*2);
    Msg_WriteText(str);

    Str_Printf(str, "attr0:%ld attr1:%ld attr2:%ld attr3:%ld\r", attrib[0], attrib[1], attrib[2], attrib[3]);
    Msg_WriteText(str);

    attr= attrib[0];
    if(attr & AM_RDO) Msg_WriteText("Attrib Read Only\r");
    if(attr & AM_HID) Msg_WriteText("Attrib Hidden\r");
    if(attr & AM_SYS) Msg_WriteText("Attrib System\r");
    if(attr & AM_DIR) Msg_WriteText("Attrib Directory\r");
    if(attr & AM_ARC) Msg_WriteText("Attrib Archive\r");
    if(attr & AM_VOL) Msg_WriteText("Attrib Volume\r");
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
 *******************************************************************************
 * - LICENSE -
 * GNU GPL v2 (http://www.gnu.org/licenses/gpl.txt)
 * This program is free software. You can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as published
 * by the Free Software Foundation.
/******************************************************************************/
