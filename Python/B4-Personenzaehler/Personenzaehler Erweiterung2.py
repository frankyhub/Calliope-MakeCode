Z�hler = 0
def on_forever():
    global Z�hler
    basic.show_number(Z�hler)
    if input.button_is_pressed(Button.A):
        Z�hler += 1
        basic.set_led_color(0xffffff)
        basic.pause(500)
        basic.set_led_color(0x00ff00)
    elif input.button_is_pressed(Button.B):
        Z�hler += -1
        basic.set_led_color(0xffffff)
        basic.pause(500)
        basic.set_led_color(0x00ff00)
    elif Z�hler < 0:
        Z�hler = 0
    else:
        pass
    basic.pause(500)
    if Z�hler > 5:
        basic.show_icon(IconNames.SAD)
        basic.pause(500)
        basic.set_led_color(0xff0000)
basic.forever(on_forever)
