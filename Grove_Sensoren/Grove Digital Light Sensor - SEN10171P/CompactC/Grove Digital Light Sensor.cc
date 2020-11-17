/*******************************************************************************

 Project Name:      Grove Digital Light Sensor.cprj
 Required Libs's:   IntFunc_lib.cc
 Files:             Grove Digital Light Sensor.cc
 Writer:            CCPRO-TEAM
 Date:              10.05.2015
 Function:          Demonstrates the Grove Digital Light Sensor

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
 - Connect the sensor yellow wire (I2C SCL) to C-Control PD0 (MEGA128) or PC0(MEGA32)
 - Connect the sensor white wire (I2C SDA) to C-Control PD1 (MEGA128) or PC1(MEGA32)

 Start the program with F10 (or the yellow flash icon) for debug outputs!

 ------------------------------------------------------------------------------

 Note:
 -----
 Source: http://www.seeedstudio.com/depot/Grove-Digital-Light-Sensor-p-1281.html

 This module is based on the I2C light-to-digital converter TSL2561 to transform
 light intensity to a digital signal. Different from traditional analog light sensor,
 as Grove - Light Sensor, this digital module features a selectable light spectrum
 range due to its dual light sensitive diodes: infrared and full spectrum.

 You can switch between three detection modes to take your readings.
 They are infrared mode, full spectrum and human visible mode.
 When running under the human visible mode, this sensor will give you
 readings just close to your eye feelings.

 Features:
 ---------
 * Selectable detection modes
 * high resolution 16-Bit digital output at 400 kHz I2C Fast-Mode
 * Wide dynamic range: 0.1 - 40,000 LUX
 * Wide operating temperature range: -40°C to 85°C
 * Programmable interrupt function with User-Defined Upper and lower threshold settings

 Application Ideas:
 ------------------
 * Ambient light sensing
 * Backlighting control for display panel
 * Keyboard illumination control

*******************************************************************************/

#define TSL2561_ADDR_MEGA   0x29<<1         // 8bit address (MEGA Serie)
#define TSL2561_ADDR_AVR32  0x29            // 7bit address (AVR32)

#define  TSL2561_Control    0x80
#define  TSL2561_Timing     0x81
#define  TSL2561_Interrupt  0x86
#define  TSL2561_Channal0L  0x8C
#define  TSL2561_Channal0H  0x8D
#define  TSL2561_Channal1L  0x8E
#define  TSL2561_Channal1H  0x8F

#define LUX_SCALE           14              // scale by 2^14
#define RATIO_SCALE         9               // scale ratio by 2^9
#define CH_SCALE            10              // scale channel values by 2^10
#define CHSCALE_TINT0       0x7517          // 322/11 * 2^CH_SCALE
#define CHSCALE_TINT1       0x0fe7          // 322/81 * 2^CH_SCALE

#define K1T 0x0040   // 0.125 * 2^RATIO_SCALE
#define B1T 0x01f2   // 0.0304 * 2^LUX_SCALE
#define M1T 0x01be   // 0.0272 * 2^LUX_SCALE
#define K2T 0x0080   // 0.250 * 2^RATIO_SCA
#define B2T 0x0214   // 0.0325 * 2^LUX_SCALE
#define M2T 0x02d1   // 0.0440 * 2^LUX_SCALE
#define K3T 0x00c0   // 0.375 * 2^RATIO_SCALE
#define B3T 0x023f   // 0.0351 * 2^LUX_SCALE
#define M3T 0x037b   // 0.0544 * 2^LUX_SCALE
#define K4T 0x0100   // 0.50 * 2^RATIO_SCALE
#define B4T 0x0270   // 0.0381 * 2^LUX_SCALE
#define M4T 0x03fe   // 0.0624 * 2^LUX_SCALE
#define K5T 0x0138   // 0.61 * 2^RATIO_SCALE
#define B5T 0x016f   // 0.0224 * 2^LUX_SCALE
#define M5T 0x01fc   // 0.0310 * 2^LUX_SCALE
#define K6T 0x019a   // 0.80 * 2^RATIO_SCALE
#define B6T 0x00d2   // 0.0128 * 2^LUX_SCALE
#define M6T 0x00fb   // 0.0153 * 2^LUX_SCALE
#define K7T 0x029a   // 1.3 * 2^RATIO_SCALE
#define B7T 0x0018   // 0.00146 * 2^LUX_SCALE
#define M7T 0x0012   // 0.00112 * 2^LUX_SCALE
#define K8T 0x029a   // 1.3 * 2^RATIO_SCALE
#define B8T 0x0000   // 0.000 * 2^LUX_SCALE
#define M8T 0x0000   // 0.000 * 2^LUX_SCALE
#define K1C 0x0043   // 0.130 * 2^RATIO_SCALE
#define B1C 0x0204   // 0.0315 * 2^LUX_SCALE
#define M1C 0x01ad   // 0.0262 * 2^LUX_SCALE
#define K2C 0x0085   // 0.260 * 2^RATIO_SCALE
#define B2C 0x0228   // 0.0337 * 2^LUX_SCALE
#define M2C 0x02c1   // 0.0430 * 2^LUX_SCALE
#define K3C 0x00c8   // 0.390 * 2^RATIO_SCALE
#define B3C 0x0253   // 0.0363 * 2^LUX_SCALE
#define M3C 0x0363   // 0.0529 * 2^LUX_SCALE
#define K4C 0x010a   // 0.520 * 2^RATIO_SCALE
#define B4C 0x0282   // 0.0392 * 2^LUX_SCALE
#define M4C 0x03df   // 0.0605 * 2^LUX_SCALE
#define K5C 0x014d   // 0.65 * 2^RATIO_SCALE
#define B5C 0x0177   // 0.0229 * 2^LUX_SCALE
#define M5C 0x01dd   // 0.0291 * 2^LUX_SCALE
#define K6C 0x019a   // 0.80 * 2^RATIO_SCALE
#define B6C 0x0101   // 0.0157 * 2^LUX_SCALE
#define M6C 0x0127   // 0.0180 * 2^LUX_SCALE
#define K7C 0x029a   // 1.3 * 2^RATIO_SCALE
#define B7C 0x0037   // 0.00338 * 2^LUX_SCALE
#define M7C 0x002b   // 0.00260 * 2^LUX_SCALE
#define K8C 0x029a   // 1.3 * 2^RATIO_SCALE
#define B8C 0x0000   // 0.000 * 2^LUX_SCALE
#define M8C 0x0000   // 0.000 * 2^LUX_SCALE

/*------------------------------------------------------------------------------
    Gobal Variable
------------------------------------------------------------------------------*/
int CH0_LOW, CH0_HIGH, CH1_LOW, CH1_HIGH;
unsigned long ch0, ch1;
unsigned long chScale;
unsigned long channel1;
unsigned long channel0;
unsigned long  ratio1;
unsigned int b;
unsigned int m;
unsigned long temp;
unsigned long lux;
byte somedata[10], status;

/*------------------------------------------------------------------------------
    TSL2561_CalculateLux_readRegister
------------------------------------------------------------------------------*/
byte TSL2561_CalculateLux_readRegister(byte deviceAddress, byte address)
{
    byte value;

#if AVR32
    status=I2C_Read(deviceAddress, address, 1, somedata, 1);
    value=somedata[0];
#else
    I2C_Start();
    I2C_Write(deviceAddress);
    I2C_Write(address);
    I2C_Stop();
    I2C_Start();
    I2C_Write(deviceAddress+1);
    value = I2C_Read_NACK();
#endif
     return value;
}

/*------------------------------------------------------------------------------
    TSL2561_CalculateLux_writeRegister
------------------------------------------------------------------------------*/
void TSL2561_CalculateLux_writeRegister(byte deviceAddress, byte address, byte val)
{
#if AVR32
    somedata[0]=val;
    status=I2C_Write(deviceAddress, address, 1, somedata, 1);
#else
     I2C_Start();
     I2C_Write(deviceAddress);
     I2C_Write(address);
     I2C_Write(val);
     I2C_Stop();
#endif
}

/*------------------------------------------------------------------------------
    TSL2561_CalculateLux_getLux
------------------------------------------------------------------------------*/
void TSL2561_CalculateLux_getLux(void)
{
#if AVR32
    CH0_LOW=TSL2561_CalculateLux_readRegister(TSL2561_ADDR_AVR32, TSL2561_Channal0L);
    CH0_HIGH=TSL2561_CalculateLux_readRegister(TSL2561_ADDR_AVR32, TSL2561_Channal0H);
    // read two bytes from registers 0x0E and 0x0F
    CH1_LOW=TSL2561_CalculateLux_readRegister(TSL2561_ADDR_AVR32, TSL2561_Channal1L);
    CH1_HIGH=TSL2561_CalculateLux_readRegister(TSL2561_ADDR_AVR32, TSL2561_Channal1H);
    ch0 = (CH0_HIGH<<8) | CH0_LOW;
    ch1 = (CH1_HIGH<<8) | CH1_LOW;
#else
    CH0_LOW=TSL2561_CalculateLux_readRegister(TSL2561_ADDR_MEGA, TSL2561_Channal0L);
    CH0_HIGH=TSL2561_CalculateLux_readRegister(TSL2561_ADDR_MEGA, TSL2561_Channal0H);
    // read two bytes from registers 0x0E and 0x0F
    CH1_LOW=TSL2561_CalculateLux_readRegister(TSL2561_ADDR_MEGA, TSL2561_Channal1L);
    CH1_HIGH=TSL2561_CalculateLux_readRegister(TSL2561_ADDR_MEGA, TSL2561_Channal1H);
    ch0 = (CH0_HIGH<<8) | CH0_LOW;
    ch1 = (CH1_HIGH<<8) | CH1_LOW;
#endif
}

/*------------------------------------------------------------------------------
    TSL2561_CalculateLux_init
------------------------------------------------------------------------------*/
void TSL2561_CalculateLux_init(void)
{
#if AVR32
   TSL2561_CalculateLux_writeRegister(TSL2561_ADDR_AVR32, TSL2561_Control,0x03);   // POWER UP
   TSL2561_CalculateLux_writeRegister(TSL2561_ADDR_AVR32, TSL2561_Timing,0x00);    // No High Gain (1x), integration time of 13ms
   TSL2561_CalculateLux_writeRegister(TSL2561_ADDR_AVR32, TSL2561_Interrupt,0x00);
   TSL2561_CalculateLux_writeRegister(TSL2561_ADDR_AVR32, TSL2561_Control,0x00);   // POWER Down
#else
   TSL2561_CalculateLux_writeRegister(TSL2561_ADDR_MEGA, TSL2561_Control,0x03);    // POWER UP
   TSL2561_CalculateLux_writeRegister(TSL2561_ADDR_MEGA, TSL2561_Timing,0x00);     // No High Gain (1x), integration time of 13ms
   TSL2561_CalculateLux_writeRegister(TSL2561_ADDR_MEGA, TSL2561_Interrupt,0x00);
   TSL2561_CalculateLux_writeRegister(TSL2561_ADDR_MEGA, TSL2561_Control,0x00);    // POWER Down
#endif
}

/*------------------------------------------------------------------------------
    TSL2561_CalculateLux_readVisibleLux
------------------------------------------------------------------------------*/
signed long TSL2561_CalculateLux_readVisibleLux(void)
{
#if AVR32
   TSL2561_CalculateLux_writeRegister(TSL2561_ADDR_AVR32, TSL2561_Control,0x03);  // POWER UP
   AbsDelay(50);
   TSL2561_CalculateLux_getLux();
   TSL2561_CalculateLux_writeRegister(TSL2561_ADDR_AVR32, TSL2561_Control,0x00);  // POWER Down
#else
   TSL2561_CalculateLux_writeRegister(TSL2561_ADDR_MEGA, TSL2561_Control,0x03);  // POWER UP
   AbsDelay(50);
   TSL2561_CalculateLux_getLux();
   TSL2561_CalculateLux_writeRegister(TSL2561_ADDR_MEGA, TSL2561_Control,0x00);  // POWER Down
#endif
   if(ch0/ch1 < 2 && ch0 > 4900)
   {
     return -1;  // ch0 out of range, but ch1 not. the lux is not valid in this situation.
   }
   return TSL2561_CalculateLux_calculateLux(0, 0, 0);  // T package, no gain, 13ms
}

/*------------------------------------------------------------------------------
    TSL2561_CalculateLux_calculateLux
------------------------------------------------------------------------------*/
unsigned long TSL2561_CalculateLux_calculateLux(unsigned int iGain, unsigned int tInt,int iType)
{
   switch (tInt)
   {
      case 0:  // 13.7 msec
      chScale = CHSCALE_TINT0;
      break;
      case 1:  // 101 msec
      chScale = CHSCALE_TINT1;
      break;
      default: // assume no scaling
      chScale = (1 << CH_SCALE);
      break;
   }

   if(!iGain)chScale = chScale << 4; // scale 1X to 16X
   // scale the channel values
   channel0 = (ch0 * chScale) >> CH_SCALE;
   channel1 = (ch1 * chScale) >> CH_SCALE;

   ratio1 = 0;
   if(channel0!= 0) ratio1=(channel1 << (RATIO_SCALE+1))/channel0;
   // round the ratio value
   unsigned long ratio;
   ratio = (ratio1 + 1) >> 1;

   switch (iType)
   {
   case 0: // T package
     if ((ratio >= 0) && (ratio <= K1T))
      {b=B1T; m=M1T;}
     else if (ratio <= K2T)
      {b=B2T; m=M2T;}
     else if (ratio <= K3T)
      {b=B3T; m=M3T;}
     else if (ratio <= K4T)
      {b=B4T; m=M4T;}
     else if (ratio <= K5T)
      {b=B5T; m=M5T;}
     else if (ratio <= K6T)
      {b=B6T; m=M6T;}
     else if (ratio <= K7T)
      {b=B7T; m=M7T;}
     else if (ratio > K8T)
      {b=B8T; m=M8T;}
    break;
    case 1:// CS package
     if ((ratio >= 0) && (ratio <= K1C))
       {b=B1C; m=M1C;}
     else if (ratio <= K2C)
       {b=B2C; m=M2C;}
     else if (ratio <= K3C)
      {b=B3C; m=M3C;}
     else if (ratio <= K4C)
      {b=B4C; m=M4C;}
     else if (ratio <= K5C)
      {b=B5C; m=M5C;}
     else if (ratio <= K6C)
      {b=B6C; m=M6C;}
     else if (ratio <= K7C)
      {b=B7C; m=M7C;}
   }

   temp=((channel0*b)-(channel1*m));
   if(temp<0)temp=0;
   temp= temp +(1<<(LUX_SCALE-1));

   // strip off fractional portion
   lux=temp>>LUX_SCALE;
   return lux;
}

/*------------------------------------------------------------------------------
    Main Program
------------------------------------------------------------------------------*/
void main(void)
{
    TSL2561_CalculateLux_init();

    #if MEGA32||MEGA128_ARCH||MEGA128CAN
        // MEGA Serie
        I2C_Init(I2C_100kHz);                   // I2C Bit Rate: 100 kHz
    #endif

    // Endless loop
    while(1)
    {
      Msg_WriteInt(TSL2561_CalculateLux_readVisibleLux());
      Msg_WriteText(" Lux");
      Msg_WriteChar(13);
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

