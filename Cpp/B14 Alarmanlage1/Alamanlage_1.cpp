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
    
    _uBit.accelerometer.updateSample();
    _uBit.rgb.setColour(MicroBitColor(255, 255, 0, 255));
    while ( true ) {
        if ( _uBit.accelerometer.getPitch() > 15 ) {
            _uBit.rgb.setColour(MicroBitColor(255, 0, 0, 255));
            _uBit.soundmotor.soundOn(261.626); _uBit.sleep(2000); _uBit.soundmotor.soundOff();
            _uBit.sleep(1000);
            _uBit.rgb.setColour(MicroBitColor(0, 153, 0, 255));
        }
        _uBit.sleep(_ITERATION_SLEEP_TIMEOUT);
    }
    release_fiber();
}
