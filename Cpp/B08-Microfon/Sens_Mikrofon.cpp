#define _GNU_SOURCE

#include "MicroBit.h"
#include "NEPODefs.h"
#include <list>
#include <array>
#include <stdlib.h>
MicroBit _uBit;


double ___Lautstaerke;

int main()
{
    _uBit.init();
    ___Lautstaerke = 0;
    _uBit.display.setDisplayMode(DISPLAY_MODE_GREYSCALE);
    while ( true ) {
        ___Lautstaerke = _uBit.io.P21.getMicrophoneValue();
        if ( ___Lautstaerke < 20 ) {
            _uBit.display.print(MicroBitImage("0,0,0,0,0\n0,0,0,0,0\n0,0,0,0,0\n0,0,0,0,0\n255,255,255,255,255\n"));
        } else if ( ___Lautstaerke < 40 ) {
            _uBit.display.print(MicroBitImage("0,0,0,0,0\n0,0,0,0,0\n0,0,0,0,0\n255,255,255,255,255\n255,255,255,255,255\n"));
        } else if ( ___Lautstaerke < 60 ) {
            _uBit.display.print(MicroBitImage("0,0,0,0,0\n0,0,0,0,0\n255,255,255,255,255\n255,255,255,255,255\n255,255,255,255,255\n"));
        } else if ( ___Lautstaerke < 80 ) {
            _uBit.display.print(MicroBitImage("0,0,0,0,0\n255,255,255,255,255\n255,255,255,255,255\n255,255,255,255,255\n255,255,255,255,255\n"));
        } else if ( ___Lautstaerke <= 100 ) {
            _uBit.display.print(MicroBitImage("255,255,255,255,255\n255,255,255,255,255\n255,255,255,255,255\n255,255,255,255,255\n255,255,255,255,255\n"));
        }
        _uBit.sleep(_ITERATION_SLEEP_TIMEOUT);
    }
    release_fiber();
}
