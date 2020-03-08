import spidev, time

spi = spidev.SpiDev ()
spi.open (2,0 )
spi.max_speed_hz = 500000
spi.bits_per_word = 8
spi.mode = 0b01
data = [0x55,0x55,0x55,0x55]
re=spi.xfer2(data)
print(re)
spi.close