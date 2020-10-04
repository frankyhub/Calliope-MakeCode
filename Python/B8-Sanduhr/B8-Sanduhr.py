ef on_button_pressed_a():
    global Reihe, Spalte
    basic.show_leds("""
        # # # # #
        # # # # #
        # # # # #
        # # # # #
        # # # # #
        """)
    Reihe = 0
    for index in range(5):
        for index2 in range(5):
            led.toggle(Spalte, Reihe)
            basic.pause(500)
            Spalte += 1
        Reihe += 1
        Spalte = 0
input.on_button_pressed(Button.A, on_button_pressed_a)

Spalte = 0
Reihe = 0
Startzeit = 25000
durch25 = Startzeit / 25
basic.show_leds("""
    # # # # #
    # # # # #
    # # # # #
    # # # # #
    # # # # #
    """)
