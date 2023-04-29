# David Feeder

### Install Anaconda prompt

https://anaconda.org/conda-forge/prompt

### Install python and create virtual dir
```
conda create -n micropython python=3.8
conda activate micropython
pip install esptool
```

## ESP32
#### Erase flash
```
esptool --chip esp32 erase_flash
```
### Flash
```
esptool --chip esp32 --port <serial_port> write_flash --flash_size=detect 0 -z 0x1000 <esp32-X.bin>
```
## ESP8266

#### Erase flash
```
esptool --chip esp8266 erase_flash
```
### Flash

```
esptool --chip esp8266 --port <serial_port> write_flash --flash_mode dio --flash_size detect 0x0 <esp8266-X.bin>
```
