n = 0
Temperatur = 0

def on_forever():
    global n, Temperatur
    n = pins.analog_read_pin(AnalogPin.C16)
    if n >= 270 and n <= 699:
        Temperatur = pins.map(n, 270, 699, 5, 42)
        basic.show_number(Temperatur)
        basic.pause(1000)
    else:
        basic.show_icon(IconNames.SAD)
basic.forever(on_forever)