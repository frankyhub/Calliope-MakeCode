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
    
    _uBit.display.scroll(ManagedString("Hallo"));
    _uBit.display.print(ManagedString("Hallo"));
    release_fiber();
}
