# Openweathermap Tools collection for esp2866

## Why?

As most microcontrollers the esp8266 has limited ressources. 

This collection of tools helps to off load some memory consuming tasks to a proxy server.

https://openweathermap.org/ offers a free 5 day / 3 hour forecast. The JSON file is about 15k in size, https://arduinojson.org/ needs about 30k to interpret it.



## Solution

The OpenweathermapProxy script (owms.php) offers two solution to tackle this challenge:

- it can split the JSON into 40 small JSONS with about 1k each, arduinojson is happy with 800B.

- it can create bite-sized text files that only contain what you need ready to read with a simple read-line algorithm.

Both solution

