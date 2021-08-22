from sensorlib import HCSR04

sensor = HCSR04(trigger_pin="P3", echo_pin="P4")

distance = sensor.distance_cm()

print('Distance:', distance, 'cm')
