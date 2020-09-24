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
    
    _uBit.soundmotor.soundOn(261.626); _uBit.sleep(500); _uBit.soundmotor.soundOff();
    _uBit.soundmotor.soundOn(293.665); _uBit.sleep(500); _uBit.soundmotor.soundOff();
    _uBit.soundmotor.soundOn(329.628); _uBit.sleep(500); _uBit.soundmotor.soundOff();
    _uBit.soundmotor.soundOn(349.228); _uBit.sleep(500); _uBit.soundmotor.soundOff();
    _uBit.soundmotor.soundOn(391.995); _uBit.sleep(1000); _uBit.soundmotor.soundOff();
    _uBit.soundmotor.soundOn(391.995); _uBit.sleep(1000); _uBit.soundmotor.soundOff();
    for (int ___k0 = 0; ___k0 < 2; ___k0 += 1) {
        _uBit.soundmotor.soundOn(440); _uBit.sleep(500); _uBit.soundmotor.soundOff();
        _uBit.soundmotor.soundOn(440); _uBit.sleep(500); _uBit.soundmotor.soundOff();
        _uBit.soundmotor.soundOn(440); _uBit.sleep(500); _uBit.soundmotor.soundOff();
        _uBit.soundmotor.soundOn(440); _uBit.sleep(500); _uBit.soundmotor.soundOff();
        _uBit.soundmotor.soundOn(391.995); _uBit.sleep(1000); _uBit.soundmotor.soundOff();
        _uBit.sleep(_ITERATION_SLEEP_TIMEOUT);
    }
    _uBit.soundmotor.soundOn(349.228); _uBit.sleep(500); _uBit.soundmotor.soundOff();
    _uBit.soundmotor.soundOn(349.228); _uBit.sleep(500); _uBit.soundmotor.soundOff();
    _uBit.soundmotor.soundOn(349.228); _uBit.sleep(500); _uBit.soundmotor.soundOff();
    _uBit.soundmotor.soundOn(349.228); _uBit.sleep(500); _uBit.soundmotor.soundOff();
    _uBit.soundmotor.soundOn(329.628); _uBit.sleep(1000); _uBit.soundmotor.soundOff();
    _uBit.soundmotor.soundOn(329.628); _uBit.sleep(1000); _uBit.soundmotor.soundOff();
    _uBit.soundmotor.soundOn(293.665); _uBit.sleep(500); _uBit.soundmotor.soundOff();
    _uBit.soundmotor.soundOn(293.665); _uBit.sleep(500); _uBit.soundmotor.soundOff();
    _uBit.soundmotor.soundOn(293.665); _uBit.sleep(500); _uBit.soundmotor.soundOff();
    _uBit.soundmotor.soundOn(293.665); _uBit.sleep(500); _uBit.soundmotor.soundOff();
    _uBit.soundmotor.soundOn(261.626); _uBit.sleep(2000); _uBit.soundmotor.soundOff();
    release_fiber();
}
