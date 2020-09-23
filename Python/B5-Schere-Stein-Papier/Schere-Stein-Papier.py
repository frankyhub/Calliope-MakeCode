Zufall = 0
def on_forever():
    global Zufall
    if input.button_is_pressed(Button.A):
        basic.clear_screen()
        Zufall = randint(1, 3)
    else:
        if Zufall == 1:
            basic.show_leds("""
                # . . . #
                . # . # .
                # . # . .
                . # . # .
                # . . . #
                """)
        elif Zufall == 2:
            basic.show_leds("""
                . . . . .
                . # # # .
                . # # # .
                . # # # .
                . . . . .
                """)
        elif Zufall == 3:
            basic.show_leds("""
                . . . . .
                . . . . .
                # # # # #
                . . . . .
                . . . . .
                """)
basic.forever(on_forever)
