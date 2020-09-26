_4digit: grove.TM1637 = None

def on_forever():
    global _4digit
    if input.button_is_pressed(Button.A):
        _4digit = grove.create_display(DigitalPin.C16, DigitalPin.C17)
        _4digit.bit(1, 3)
        basic.pause(1000)
        _4digit.bit(2, 3)
        basic.pause(1000)
        _4digit.bit(3, 3)
        basic.pause(1000)
        _4digit.bit(1, 2)
        basic.pause(1000)
        _4digit.bit(2, 2)
        basic.pause(1000)
        _4digit.bit(3, 2)
        basic.pause(1000)
        _4digit.clear()
basic.forever(on_forever)
