Reihe = 0
Spalte = 0

def on_button_pressed_a():
    global Reihe, Spalte
    basic.show_leds("""
        . . . . .
        . . . . .
        . . . . .
        . . . . .
        . . . . .
        """)
    Reihe = 0
    Spalte = 0
    for index in range(5):
        for index2 in range(5):
            led.toggle(Spalte, Reihe)
            basic.pause(100)
            Spalte += 1
        Reihe += 1
        Spalte = 0
    Reihe = 4
    Spalte = 4
    for index3 in range(5):
        for index4 in range(5):
            led.toggle(Spalte, Reihe)
            basic.pause(100)
            Spalte += -1
        Reihe += -1
        Spalte = 4
input.on_button_pressed(Button.A, on_button_pressed_a)