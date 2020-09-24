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
        while (true) {
            if ( round(_uBit.display.readLightLevel() * _GET_LIGHTLEVEL_MULTIPLIER) > 50 ) {
                break;
            }
            _uBit.sleep(_ITERATION_SLEEP_TIMEOUT);
        }
        _uBit.soundmotor.soundOn(261.626); _uBit.sleep(500); _uBit.soundmotor.soundOff();
        _uBit.sleep(100);
        _uBit.sleep(_ITERATION_SLEEP_TIMEOUT);
    }
    release_fiber();
}
