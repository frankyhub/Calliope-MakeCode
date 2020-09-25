LED = 0

def on_forever():
    global LED
    if input.sound_level() > 20:
        if LED == 1:
            LED = 0
            if LED == 0:
                basic.turn_rgb_led_off()
        elif LED == 0:
            LED = 1
            if LED == 1:
                basic.set_led_color(0xff0000)
        basic.pause(500)
basic.forever(on_forever)