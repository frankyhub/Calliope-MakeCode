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
            if ( _uBit.buttonA.isPressed() == true ) {
                _uBit.display.print(ManagedString("A"));
                break;
            }
            if ( _uBit.buttonB.isPressed() == true ) {
                _uBit.display.print(ManagedString("B"));
                break;
            }
            _uBit.sleep(_ITERATION_SLEEP_TIMEOUT);
        }
        _uBit.sleep(_ITERATION_SLEEP_TIMEOUT);
    }
    release_fiber();
}
