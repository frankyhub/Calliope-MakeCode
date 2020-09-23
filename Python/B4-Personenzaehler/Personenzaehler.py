Zähler = 0

def on_forever():
    global Zähler
    basic.show_number(Zähler)
    if input.button_is_pressed(Button.A):
        Zähler += 1
        basic.set_led_color(0xff0000)
        basic.pause(1000)
        basic.set_led_color(0x00ff00)
    else:
        if input.button_is_pressed(Button.B):
            Zähler += -1
            basic.pause(1000)
            basic.set_led_color(0xff0000)
            basic.pause(1000)
        else:
            basic.set_led_color(0x00ff00)
basic.forever(on_forever)
