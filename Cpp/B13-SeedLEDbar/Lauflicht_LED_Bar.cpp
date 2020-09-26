/*Grove_LED_Bar v2.0
Lauflicht
ROBOTERKONFIGURATION "LED Leiste L1 pin A1"
https://lab.open-roberta.org/
*/

PROGRAMM NEPOprog
ROBOTERKONFIGURATION 
    
#define _GNU_SOURCE

#include "MicroBit.h"
#include "NEPODefs.h"
#include "Grove_LED_Bar.h"
#include <list>
#include <array>
#include <stdlib.h>
MicroBit _uBit;
Grove_LED_Bar _ledBar(MICROBIT_PIN_P8, MICROBIT_PIN_P2);



int main()
{
    _uBit.init();
    
    for (int ___k0 = 0; ___k0 < 10; ___k0 += 1) {
        _ledBar.setLed(0, 6);
        _uBit.sleep(500);
        _ledBar.setLed(0, 0);
        _ledBar.setLed(1, 5);
        _uBit.sleep(500);
        _ledBar.setLed(1, 0);
        _ledBar.setLed(2, 5);
        _uBit.sleep(500);
        _ledBar.setLed(2, 0);
        _ledBar.setLed(3, 5);
        _uBit.sleep(500);
        _ledBar.setLed(3, 0);
        _ledBar.setLed(4, 5);
        _uBit.sleep(500);
        _ledBar.setLed(4, 0);
        _ledBar.setLed(5, 5);
        _uBit.sleep(500);
        _ledBar.setLed(5, 0);
        _ledBar.setLed(6, 5);
        _uBit.sleep(500);
        _ledBar.setLed(6, 0);
        _ledBar.setLed(7, 5);
        _uBit.sleep(500);
        _ledBar.setLed(7, 0);
        _ledBar.setLed(8, 5);
        _uBit.sleep(500);
        _ledBar.setLed(8, 0);
        _ledBar.setLed(9, 5);
        _uBit.sleep(500);
        _ledBar.setLed(9, 0);
        _ledBar.setLed(10, 5);
        _uBit.sleep(500);
        _ledBar.setLed(10, 0);
        _uBit.sleep(_ITERATION_SLEEP_TIMEOUT);
    }
    release_fiber();
}

#define _GNU_SOURCE

#include "MicroBit.h"
#include "NEPODefs.h"
#include "Grove_LED_Bar.h"
#include <list>
#include <array>
#include <stdlib.h>
MicroBit _uBit;
Grove_LED_Bar _ledBar(MICROBIT_PIN_P8, MICROBIT_PIN_P2);



int main()
{
    _uBit.init();
    
    for (int ___k0 = 0; ___k0 < 10; ___k0 += 1) {
        _ledBar.setLed(0, 6);
        _uBit.sleep(500);
        _ledBar.setLed(0, 0);
        _ledBar.setLed(1, 5);
        _uBit.sleep(500);
        _ledBar.setLed(1, 0);
        _ledBar.setLed(2, 5);
        _uBit.sleep(500);
        _ledBar.setLed(2, 0);
        _ledBar.setLed(3, 5);
        _uBit.sleep(500);
        _ledBar.setLed(3, 0);
        _ledBar.setLed(4, 5);
        _uBit.sleep(500);
        _ledBar.setLed(4, 0);
        _ledBar.setLed(5, 5);
        _uBit.sleep(500);
        _ledBar.setLed(5, 0);
        _ledBar.setLed(6, 5);
        _uBit.sleep(500);
        _ledBar.setLed(6, 0);
        _ledBar.setLed(7, 5);
        _uBit.sleep(500);
        _ledBar.setLed(7, 0);
        _ledBar.setLed(8, 5);
        _uBit.sleep(500);
        _ledBar.setLed(8, 0);
        _ledBar.setLed(9, 5);
        _uBit.sleep(500);
        _ledBar.setLed(9, 0);
        _ledBar.setLed(10, 5);
        _uBit.sleep(500);
        _ledBar.setLed(10, 0);
        _uBit.sleep(_ITERATION_SLEEP_TIMEOUT);
    }
    release_fiber();
}
1.
2.
3.
4.
5.
6.
7.
8.
9.
10.
11.
12.
13.
14.
15.
16.
17.
18.
19.
20.
21.
22.
23.
24.
25.
26.
27.
28.
29.
30.
31.
32.
33.
34.
35.
36.
37.
38.
39.
40.
41.
42.
43.
44.
45.
46.
47.
48.
49.
50.
51.
52.
53.
54.
55.
56.