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
    
    while ( true ) {
        _uBit.rgb.setColour(MicroBitColor(51, 204, 0, 255));
        _uBit.sleep(1000);
        _uBit.rgb.setColour(MicroBitColor(255, 0, 0, 255));
        _uBit.sleep(1000);
        _uBit.rgb.off();
        _uBit.sleep(1000);
        _uBit.sleep(_ITERATION_SLEEP_TIMEOUT);
    }
    release_fiber();
}
