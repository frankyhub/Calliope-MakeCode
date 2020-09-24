#define _GNU_SOURCE

#include "MicroBit.h"
#include "NEPODefs.h"
#include <list>
#include <array>
#include <stdlib.h>
MicroBit _uBit;

int _initTime = _uBit.systemTime();

int main()
{
    _uBit.init();
    
    _initTime = _uBit.systemTime();
    _uBit.rgb.setColour(MicroBitColor(255, 0, 0, 255));
    while (true) {
        if ( ( _uBit.systemTime() - _initTime ) > 2000 ) {
            _uBit.rgb.setColour(MicroBitColor(51, 204, 0, 255));
            break;
        }
        if ( _uBit.buttonA.isPressed() == true ) {
            _uBit.display.print(ManagedString("A"));
            break;
        }
        _uBit.sleep(_ITERATION_SLEEP_TIMEOUT);
    }
    release_fiber();
}
