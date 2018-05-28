# Openweathermap Tools collection for esp2866

## Why?

As most microcontrollers the esp8266 has limited ressources. 

https://openweathermap.org/ offers a free 5 day / 3 hour forecast. The JSON file is about 15k in size, https://arduinojson.org/ needs about 30k to interpret it (plus the additional code size).

https://openweathermap.org/ offers nice weather icons. They are PNG files, to display them it would need a PNG interpreter and some memory.

OpenweathermapProxy and ImageDecoder can 

- off load memory consuming tasks to a proxy server,
- allow local caching of files and
- create simple data structures.

## Solution I

The OpenweathermapProxy script (owms.php) offers two solution to tackle this challenge:

- it can split the JSON into 40 small JSONS with about 1k size each, arduinojson is happy with 800 bytes now.

- alternatively it can create bite-sized text files that only contain what you need ready to read with a simple read-line algorithm that counsume even less memory.

## Solution II

ImageDecoder (imgdecode.php) converts a .png, .gif or .jpeg grafic into an uncompressed rgb-file.

## Solution III

The codessnippets folder has some code snippets I use with both solution. 





