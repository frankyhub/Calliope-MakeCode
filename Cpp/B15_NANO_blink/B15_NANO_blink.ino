/*  NANO blink
 *  Board: NANO
 *  Programm von OpenRoberta in Arduino IDE kopiert
 */


int _led_L = LED_BUILTIN; //int _led_L = 13;
void setup()
{
    pinMode(_led_L, OUTPUT);
}

void loop()
{
    digitalWrite(_led_L, HIGH);
    delay(500);
    digitalWrite(_led_L, LOW);
    delay(500);
}
