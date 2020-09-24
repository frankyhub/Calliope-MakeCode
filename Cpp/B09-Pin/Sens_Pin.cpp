#define _GNU_SOURCE

#include "MicroBit.h"
#include "NEPODefs.h"
#include <list>
#include <array>
#include <stdlib.h>
MicroBit _uBit;



int main()
{
    _uBit.init();
    _uBit.display.setDisplayMode(DISPLAY_MODE_GREYSCALE);
    while ( true ) {
        while (true) {
            if ( _uBit.io.P12.isTouched() == true ) {
                _uBit.display.print(MicroBitImage("0,0,0,0,0\n141,0,0,0,0\n255,141,0,0,0\n141,0,0,0,0\n0,0,0,0,0\n"));
                break;
            }
            if ( _uBit.io.P0.isTouched() == true ) {
                _uBit.display.print(MicroBitImage("0,0,0,0,0\n0,0,0,0,0\n0,0,0,0,0\n141,0,0,0,0\n255,141,0,0,0\n"));
                break;
            }
            if ( _uBit.io.P1.isTouched() == true ) {
                _uBit.display.print(MicroBitImage("0,0,0,0,0\n0,0,0,0,0\n0,0,0,0,0\n0,0,0,0,141\n0,0,0,141,255\n"));
                break;
            }
            if ( _uBit.io.P16.isTouched() == true ) {
                _uBit.display.print(MicroBitImage("0,0,0,0,0\n0,0,0,0,141\n0,0,0,141,255\n0,0,0,0,141\n0,0,0,0,0\n"));
                break;
            }
            _uBit.sleep(_ITERATION_SLEEP_TIMEOUT);
        }
        _uBit.sleep(_ITERATION_SLEEP_TIMEOUT);
    }
    release_fiber();
}
