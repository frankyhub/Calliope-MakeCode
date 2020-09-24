// Kompass 
// Open Roberta
//1. Programm in Calliope laden
//2. Calliope bewegen und den Bildschirm ganz ausfüllen
//3. Kompass verwenden :-)

#define _GNU_SOURCE

#include "MicroBit.h"
#include "NEPODefs.h"
#include <list>
#include <array>
#include <stdlib.h>
MicroBit _uBit;


double ___Winkel;

int main()
{
    _uBit.init();
    ___Winkel = 0;
    _uBit.display.setDisplayMode(DISPLAY_MODE_GREYSCALE);
    _uBit.accelerometer.updateSample();
    while ( true ) {
        ___Winkel = _uBit.compass.heading();
        if ( ___Winkel < 20 ) {
            _uBit.display.print(MicroBitImage("0,0,255,0,0\n0,0,255,0,0\n0,0,255,0,0\n0,0,0,0,0\n0,0,0,0,0\n"));
        } else if ( ___Winkel < 70 ) {
            _uBit.display.print(MicroBitImage("255,0,0,0,0\n0,255,0,0,0\n0,0,255,0,0\n0,0,0,0,0\n0,0,0,0,0\n"));
        } else if ( ___Winkel < 110 ) {
            _uBit.display.print(MicroBitImage("0,0,0,0,0\n0,0,0,0,0\n255,255,255,0,0\n0,0,0,0,0\n0,0,0,0,0\n"));
        } else if ( ___Winkel < 160 ) {
            _uBit.display.print(MicroBitImage("0,0,0,0,0\n0,0,0,0,0\n0,0,255,0,0\n0,255,0,0,0\n255,0,0,0,0\n"));
        } else if ( ___Winkel < 200 ) {
            _uBit.display.print(MicroBitImage("0,0,0,0,0\n0,0,0,0,0\n0,0,255,0,0\n0,0,255,0,0\n0,0,255,0,0\n"));
        } else if ( ___Winkel < 250 ) {
            _uBit.display.print(MicroBitImage("0,0,0,0,0\n0,0,0,0,0\n0,0,255,0,0\n0,0,0,255,0\n0,0,0,0,255\n"));
        } else if ( ___Winkel < 290 ) {
            _uBit.display.print(MicroBitImage("0,0,0,0,0\n0,0,0,0,0\n0,0,255,255,255\n0,0,0,0,0\n0,0,0,0,0\n"));
        } else if ( ___Winkel < 340 ) {
            _uBit.display.print(MicroBitImage("0,0,0,0,255\n0,0,0,255,0\n0,0,255,0,0\n0,0,0,0,0\n0,0,0,0,0\n"));
        } else if ( ___Winkel <= 360 ) {
            _uBit.display.print(MicroBitImage("0,0,255,0,0\n0,0,255,0,0\n0,0,255,0,0\n0,0,0,0,0\n0,0,0,0,0\n"));
        }
        _uBit.sleep(_ITERATION_SLEEP_TIMEOUT);
    }
    release_fiber();
}

