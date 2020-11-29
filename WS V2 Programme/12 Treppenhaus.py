def on_forever():
    basic.turn_rgb_led_off()
    if input.button_is_pressed(Button.A):
        basic.set_led_color(0xff0000)
        basic.pause(2000)
basic.forever(on_forever)