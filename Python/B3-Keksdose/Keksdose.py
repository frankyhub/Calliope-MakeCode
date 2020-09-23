def on_forever():
    if input.button_is_pressed(Button.A):
        basic.show_leds("""
            . # # # .
            # . . . #
            # # # # #
            # # # # #
            # # # # #
            """)
        basic.set_led_color(0x00ff00)
    else:
        basic.show_leds("""
            . # . . .
            # . . . .
            # # # # #
            # # # # #
            # # # # #
            """)
        music.play_tone(262, music.beat(BeatFraction.WHOLE))
        basic.set_led_color(0xff0000)
basic.forever(on_forever)
