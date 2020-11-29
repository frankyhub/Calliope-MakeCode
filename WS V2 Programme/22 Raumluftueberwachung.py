n = 0

def on_forever():
    global n
    n = pins.analog_read_pin(AnalogPin.C16)
    if n >= 0 and n <= 333:
        basic.show_icon(IconNames.HAPPY)
        basic.pause(100)
    elif n >= 334 and n <= 666:
        basic.show_icon(IconNames.ASLEEP)
        basic.pause(100)
    else:
        basic.show_icon(IconNames.SAD)
        basic.pause(100)
basic.forever(on_forever)