from machine import I2C
import bh1750
from sensor_pack.bus_service import I2cAdapter
import time


if __name__ == '__main__':
    i2c =  I2C(scl=Pin(22), sda=Pin(21), freq=9600)
    
    sted
    adaptor = I2cAdapter(i2c)
    sol = bh1750.Bh1750(adaptor, 0x23, True)

    sol.power(True)
    sol.set_mode(True, True)
    old_lux = curr_max = 1
    
    for lux in sol:
        if lux != old_lux:
            curr_max = max(lux, curr_max)
            lt = time.localtime()
            print(f"{lt[3:6]}\tIllumination [lux]: {lux}\tmax: {curr_max}\tNormalized [%]: {100*lux/curr_max}")
        old_lux = lux        
        time.sleep_ms(150)
