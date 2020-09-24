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
        _uBit.display.print(MicroBitImage("255,255,255,255,255\n255,141,141,141,255\n255,141,28,141,255\n255,141,141,141,255\n255,255,255,255,255\n"));
        _uBit.sleep(1000);
        _uBit.display.print(MicroBitImage("0,255,0,255,0\n255,255,255,255,255\n255,255,255,255,255\n0,255,255,255,0\n0,0,255,0,0\n"));
        _uBit.sleep(1000);
        _uBit.sleep(_ITERATION_SLEEP_TIMEOUT);
    }
    release_fiber();
}
