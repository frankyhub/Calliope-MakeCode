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
    _uBit.accelerometer.updateSample();
    while ( true ) {
        while (true) {
            if ( (_uBit.accelerometer.getGesture() == MICROBIT_ACCELEROMETER_EVT_TILT_UP) == true ) {
                _uBit.display.print(MicroBitImage("0,0,255,0,0\n0,255,255,255,0\n255,0,255,0,255\n0,0,255,0,0\n0,0,255,0,0\n"));
                break;
            }
            if ( (_uBit.accelerometer.getGesture() == MICROBIT_ACCELEROMETER_EVT_TILT_DOWN) == true ) {
                _uBit.display.print(MicroBitImage("0,0,255,0,0\n0,0,255,0,0\n255,0,255,0,255\n0,255,255,255,0\n0,0,255,0,0\n"));
                break;
            }
            if ( (_uBit.accelerometer.getGesture() == MICROBIT_ACCELEROMETER_EVT_FACE_DOWN) == true ) {
                _uBit.display.print(MicroBitImage("0,0,0,0,0\n0,0,255,0,0\n0,255,255,255,0\n0,0,255,0,0\n0,0,0,0,0\n"));
                break;
            }
            if ( (_uBit.accelerometer.getGesture() == MICROBIT_ACCELEROMETER_EVT_FACE_UP) == true ) {
                _uBit.display.print(MicroBitImage("0,0,255,0,0\n0,255,0,255,0\n255,0,0,0,255\n0,255,0,255,0\n0,0,255,0,0\n"));
                break;
            }
            if ( (_uBit.accelerometer.getGesture() == MICROBIT_ACCELEROMETER_EVT_SHAKE) == true ) {
                _uBit.display.print(MicroBitImage("255,0,255,0,255\n0,0,0,0,0\n255,0,255,0,255\n0,0,0,0,0\n255,0,255,0,255\n"));
                break;
            }
            if ( (_uBit.accelerometer.getGesture() == MICROBIT_ACCELEROMETER_EVT_FREEFALL) == true ) {
                _uBit.display.print(MicroBitImage("0,0,0,0,0\n0,255,0,255,0\n255,0,255,0,255\n0,255,0,255,0\n0,0,255,0,0\n"));
                break;
            }
            _uBit.sleep(_ITERATION_SLEEP_TIMEOUT);
        }
        _uBit.sleep(_ITERATION_SLEEP_TIMEOUT);
    }
    release_fiber();
}
