# Openweathermap Tools collection for esp2866

## Preface

As most microcontrollers the esp8266 has limited ressources. My little i2c-weather-test toy displays variouse in door sensor data and uses multiple communication methods to store and distribute the data. Currently it has the following hardware

- bme280 Bosch Temperature Humidity Pressure Sensor
- bmp180 Bosch Temperature Pressure Sensor
- ccs811 AMS "Air Quality Sensor" with VOC and eCO2
- hih9130 Honeywell Humidity Sensor
- htu21d Measurement Specialties Humidity Sensor 
- bh1750fvi ROHM Ambient Light Sensor 
- TSL2561 AMS luminosity sensor 
- MH-Z19 winsen-sensor CO2 sensor, connectd with a arduino nano i2c slave
- ds3231 maxim integrated real time clock
- ILI9341 display 320x240 (SPI)
- lcd 2004 with pcf8574
- FM24C256 Cypress Semiconductor F-RAM cell (2x)

The software side uses a web server creating a dynamic web site with SVG and ajax, mqtt, sddp, OTA, SPIFFS and all the other bells and whistles. It is one of my testbeds for Arduino IoT training classes...

For weather forecast display I use https://openweathermap.org/. It is stable, reliable and free.

## Problem

https://openweathermap.org/ offers a free 5 day / 3 hour forecast. The JSON file is about 15k in size, https://arduinojson.org/ needs about 30k to interpret it (plus the additional code size).

https://openweathermap.org/ offers nice weather icons. They are PNG files, to display them it would need a PNG interpreter and some memory. 

For some other grafics I use jped and gif, so it needs a jpeg and gif interpreter, too.

## Solution

OpenweathermapProxy and ImageDecoder can 

- off load memory consuming tasks to a proxy server,
- allow local caching of files and
- create simple data structures.

### Solution I

The OpenweathermapProxy script (owms.php) offers two solution to tackle this challenge:

- it can split the JSON into 40 small JSONS with about 1k size each, arduinojson is happy with 800 bytes now.

- alternatively it can create bite-sized text files that only contain what you need ready to read with a simple read-line algorithm that counsume even less memory.

### Solution II

ImageDecoder (imgdecode.php) converts a .png, .gif or .jpeg grafic into an uncompressed rgb-file.

### Solution III

The codessnippets folder has some code snippets I use with both solution. 





