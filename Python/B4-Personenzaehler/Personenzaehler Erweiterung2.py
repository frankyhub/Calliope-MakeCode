Zähler = 0
def on_forever():
    global Zähler
    basic.show_number(Zähler)
    if input.button_is_pressed(Button.A):
        Zähler += 1
        basic.set_led_color(0xffffff)
        basic.pause(500)
        basic.set_led_color(0x00ff00)
    elif input.button_is_pressed(Button.B):
        Zähler += -1
        basic.set_led_color(0xffffff)
        basic.pause(500)
        basic.set_led_color(0x00ff00)
    elif Zähler < 0:
        Zähler = 0
    else:
        pass
    basic.pause(500)
    if Zähler > 5:
        basic.show_icon(IconNames.SAD)
        basic.pause(500)
        basic.set_led_color(0xff0000)
basic.forever(on_forever)
