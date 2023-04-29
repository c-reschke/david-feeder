# David Feeder

### Install Anaconda prompt

https://anaconda.org/conda-forge/prompt

### Install python and create virtual dir
```
conda create -n micropython python=3.8
conda activate micropython
pip install esptool
```
#### Erase flash
```
esptool --port COM7 erase_flash
```
### Flash
```
esptool --port COM7 --baud 115200 write_flash --flash_size=detect 0 esp32-20230426-v1.20.0.bin
```

