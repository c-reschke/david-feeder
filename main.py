import machine, time
from machine import Pin

p01 = Pin(1, Pin.IN)

p02 = machine.Pin(2)
pwm = machine.PWM(p02)
pwm.freq(50)
pwm.duty(0)



def callback(p):
    print('pin change', p)

# Creates a function for mapping the 0 to 180 degrees
# to 20 to 120 pwm duty values
def map(x, in_min, in_max, out_min, out_max):
    return int((x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min)

# Creates another function for turning 
# the servo according to input angle
def servo(pin, angle):
    pin.duty(map(angle, 0, 180, 20, 120))

def feed(qtd):
    for i in range(qtd):      
        servo(pwm, 0)
        time.sleep(0.6)
        servo(pwm, 120)
        time.sleep(0.6)



p01.irq(trigger=Pin.IRQ_FALLING, handler=callback)

p01.irq(lambda p:print(p))


feed(2)


