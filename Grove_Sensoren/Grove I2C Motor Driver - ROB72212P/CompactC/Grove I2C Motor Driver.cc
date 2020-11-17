/*******************************************************************************

 Project Name:      Grove I2C Motor Driver.cprj
 Required Libs's:   IntFunc_lib.cc
 Files:             Grove I2C Motor Driver.cc
 Writer:            CCPRO-TEAM
 Date:              10.05.2015
 Function:          Demonstrates the Grove I2C Motor Driver 1.3

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
 - Connect the sensor red wire to +5V (MEGA) or AVR32 open, do not connect to AVR32!
 - Connect the sensor black wire to GND
 - Connect the sensor yellow wire (I2C SCL) to C-Control PD0 (MEGA128) or PC0(MEGA32)
 - Connect the sensor white wire (I2C SDA) to C-Control PD1 (MEGA128) or PC1(MEGA32)

 Start the program with F10 (or the yellow flash icon) for debug outputs!

 ------------------------------------------------------------------------------

 Note:
 -----
 Source: http://www.seeedstudio.com/depot/Grove-I2C-Motor-Driver-p-907.html

 Its heart is a dual channel H-bridge driver chip that can handle current
 up to 2A per channel, controlled by an Atmel ATmega8L which handles the
 I2C communication. Both motors can be driven simultaneously while
 set to a different speed and direction.
 It can power two brushed DC motors or one 4-wire two-phase stepper motor.
 It requires a 6V to 15V power supply to power the motor and has an onboard
 5V voltage regulator which can power the I2C bus (selectable by jumper).
 All driver lines are diode protected from back EMF.

 The easy software interface is not the only easy-to-use feature because the
 I2C motor driver is designed to get you up and running in notime.
 It features a LED for power and four LED's to indicate if and to which
 direction each motor is running. Screw terminals facilitate motor and
 power connections, and the GROVE system plug and I2C interface enables
 you to daisy-chain the driver with many other devices.

*******************************************************************************/

#define MotorSpeedSet             0x82
#define PWMFrequenceSet           0x84
#define DirectionSet              0xAA
#define MotorSetA                 0xA1
#define MotorSetB                 0xA5
#define Nothing                   0x01
#define EnableStepper             0x1A
#define UnenableStepper           0x1B
#define Stepernu                  0x1C
#define I2CMotorDriverAdd_MEGA    0x0F<<1       // 8bit I2C address (MEGA)
#define I2CMotorDriverAdd_AVR32   0x0F          // 7bit I2C adresse (AVR32)

// AVR32 I2C
byte somedata[10], status;

/*------------------------------------------------------------------------------
    SteperStepset
    set the steps you want, if 255, the stepper will rotate continuely
------------------------------------------------------------------------------*/
void SteperStepset(byte stepnu)
{
#if AVR32
    somedata[0]=Stepernu;
    somedata[1]=stepnu;
    somedata[2]=Nothing;
    status=I2C_Write(I2CMotorDriverAdd_AVR32, 0, 0, somedata, 3);
#else
    I2C_Start();
    I2C_Write(I2CMotorDriverAdd_MEGA);
    I2C_Write(Stepernu);
    I2C_Write(stepnu);
    I2C_Write(Nothing);
    I2C_Stop();
#endif
}

/*------------------------------------------------------------------------------
    StepperMotorEnable
    Enanble the i2c motor driver to drive a 4-wire stepper. the i2c motor driver will
    driver a 4-wire with 8 polarity  .
    Direction: stepper direction ; 1/0
    motor speed: defines the time interval the i2C motor driver change it output to drive the stepper
    the actul interval time is : motorspeed * 4ms. that is , when motor speed is 10, the interval time
    would be 40 ms
------------------------------------------------------------------------------*/
void StepperMotorEnable(byte Direction, byte motorspeed)
{
#if AVR32
    somedata[0]=EnableStepper;
    somedata[1]=Direction;
    somedata[2]=motorspeed;
    status=I2C_Write(I2CMotorDriverAdd_AVR32, 0, 0, somedata, 3);
#else
    I2C_Start();
    I2C_Write(I2CMotorDriverAdd_MEGA);
    I2C_Write(EnableStepper);
    I2C_Write(Direction);
    I2C_Write(motorspeed);
    I2C_Stop();
#endif
}

/*------------------------------------------------------------------------------
    StepperMotorUnenable
    function to uneanble i2C motor drive to drive the stepper
------------------------------------------------------------------------------*/
void StepperMotorUnenable(void)
{
#if AVR32
    somedata[0]=UnenableStepper;
    somedata[1]=Nothing;
    somedata[2]=Nothing;
    status=I2C_Write(I2CMotorDriverAdd_AVR32, 0, 0, somedata, 3);
#else
    I2C_Start();
    I2C_Write(I2CMotorDriverAdd_MEGA);
    I2C_Write(UnenableStepper);
    I2C_Write(Nothing);
    I2C_Write(Nothing);
    I2C_Stop();
#endif
}

/*------------------------------------------------------------------------------
    MotorSpeedSetAB
    Function to set the 2 DC motor speed
    motorSpeedA : the DC motor A speed; should be 0~255;
    motorSpeedB: the DC motor B speed; should be 0~255
------------------------------------------------------------------------------*/
void MotorSpeedSetAB(byte MotorSpeedA , byte MotorSpeedB)
{
#if AVR32
    somedata[0]=MotorSpeedSet;
    somedata[1]=MotorSpeedA;
    somedata[2]=MotorSpeedB;
    status=I2C_Write(I2CMotorDriverAdd_AVR32, 0, 0, somedata, 3);
#else
    I2C_Start();
    I2C_Write(I2CMotorDriverAdd_MEGA);
    I2C_Write(MotorSpeedSet);
    I2C_Write(MotorSpeedA);
    I2C_Write(MotorSpeedB);
    I2C_Stop();
#endif
}

/*------------------------------------------------------------------------------
    MotorPWMFrequenceSet
    set the prescale frequency of PWM, 0x03 default
------------------------------------------------------------------------------*/
void MotorPWMFrequenceSet(byte Frequence)
{
#if AVR32
    somedata[0]=PWMFrequenceSet;
    somedata[1]=Frequence;
    somedata[2]=Nothing;
    status=I2C_Write(I2CMotorDriverAdd_AVR32, 0, 0, somedata, 3);
#else
    I2C_Start();
    I2C_Write(I2CMotorDriverAdd_MEGA);
    I2C_Write(PWMFrequenceSet);
    I2C_Write(Frequence);
    I2C_Write(Nothing);
    I2C_Stop();
#endif
}

/*------------------------------------------------------------------------------
    MotorDirectionSet
    set the direction of DC motor
------------------------------------------------------------------------------*/
void MotorDirectionSet(byte Direction)
{
    //  Adjust the direction of the motors 0b0000 I4 I3 I2 I1
#if AVR32
    somedata[0]=DirectionSet;
    somedata[1]=Direction;
    somedata[2]=Nothing;
    status=I2C_Write(I2CMotorDriverAdd_AVR32, 0, 0, somedata, 3);
#else
    I2C_Start();
    I2C_Write(I2CMotorDriverAdd_MEGA);
    I2C_Write(DirectionSet);
    I2C_Write(Direction);
    I2C_Write(Nothing);
    I2C_Stop();
#endif
}

/*------------------------------------------------------------------------------
    MotorDriectionAndSpeedSet
------------------------------------------------------------------------------*/
void MotorDriectionAndSpeedSet(byte Direction, byte MotorSpeedA, byte MotorSpeedB)
{
    // you can adjust the driection and speed together
    MotorDirectionSet(Direction);
    MotorSpeedSetAB(MotorSpeedA, MotorSpeedB);
}

/*------------------------------------------------------------------------------
    Stepper_Run_Demo1
------------------------------------------------------------------------------*/
void Stepper_Run_Demo1(void)
{
    Msg_WriteText("sent command to + direction, very fast\r");
    SteperStepset(255);
    StepperMotorEnable(1, 1);   // ennable the i2c motor driver a stepper.
    AbsDelay(5000);

    Msg_WriteText("sent command to - direction, slow\r");
    SteperStepset(255);
    StepperMotorEnable(0, 20);
    AbsDelay(5000);

    Msg_WriteText("sent command to - direction, fast\r");
    StepperMotorEnable(0, 2);   // ennable the i2c motor driver a stepper.
    AbsDelay(5000);

    Msg_WriteText("sent command to + direction,100 steps, fast\r");
    SteperStepset(100);
    StepperMotorEnable(1, 5);
    AbsDelay(3000);

    Msg_WriteText("sent command to shut down the stepper\r");
    StepperMotorUnenable();
    AbsDelay(1000);

    Msg_WriteText("sent command to - direction, slow, and 10 steps then stop\r");
    SteperStepset(10);
    StepperMotorEnable(0, 40);
    AbsDelay(5000);

    Msg_WriteText("sent command to shut down the stepper\r");
    StepperMotorUnenable();
    AbsDelay(5000);
}

/*------------------------------------------------------------------------------
    Stepper_Run_Demo2
------------------------------------------------------------------------------*/
void Stepper_Run_Demo2(void)
{
    MotorSpeedSetAB(255,255);   // when driving a stepper, the speed should be set to 255;
    AbsDelay(10);
    MotorDirectionSet(0b0001);
    AbsDelay(4);
    MotorDirectionSet(0b0011);
    AbsDelay(4);
    MotorDirectionSet(0b0010);
    AbsDelay(4);
    MotorDirectionSet(0b0110);
    AbsDelay(4);
    MotorDirectionSet(0b0100);
    AbsDelay(4);
    MotorDirectionSet(0b1100);
    AbsDelay(4);
    MotorDirectionSet(0b1000);
    AbsDelay(4);
    MotorDirectionSet(0b1001);
    AbsDelay(4);
}

/*------------------------------------------------------------------------------
    DC_Motor_Demo
------------------------------------------------------------------------------*/
void DC_Motor_Demo(void)
{
    Msg_WriteText("sent DC speed 100\r");
    MotorSpeedSetAB(150,150);       // defines the speed of motor 1 and motor 2 (o to 255);
    AbsDelay(10);                   // this delay needed
    MotorDirectionSet(0b1010);      // "0b1010" defines the output polarity, "10" means the M+ is "positive" while the M- is "negtive"
                                    // make sure M+ and M- is different polatity when driving DC motors.
    AbsDelay(5000);
    MotorDirectionSet(0b0101);      // 0b0101  Rotating in the opposite direction
    AbsDelay(5000);
}

/*------------------------------------------------------------------------------
    Main program
------------------------------------------------------------------------------*/
void main(void)
{

    #if AVR32
        I2C_SetSpeed(I2C_100kHz);
    #else
        I2C_Init(I2C_100kHz);                   // I2C Bit Rate: 100 kHz
    #endif


    // Endless loop
    while(1)
    {
        //Stepper_Run_Demo2();
        DC_Motor_Demo();
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

