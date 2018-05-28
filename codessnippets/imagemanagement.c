//==================================================================================================
//==================================================================================================
void CachedGraphicsDeleteAll(void) {
  Dir dir = SPIFFS.openDir("/");
  while (dir.next()) {
    if (dir.fileName().indexOf(cachedimageprefix) == 0) {
      SerialUDP.print("Delete ");
      SerialUDP.print(dir.fileName());
      SerialUDP.println();
      SPIFFS.remove(dir.fileName());
    }
  }
}

//==================================================================================================
//==================================================================================================
String CachedGraphicsURL2filename(String url) {
  int idx;
  do {
    idx = url.indexOf("/");
    if (idx != -1) {
      url.remove(0, idx + 1);
    }
  } while (idx != -1);

  return cachedimageprefix + url;
}

//==================================================================================================
//==================================================================================================
void CachedGraphicsFetchUnCached(const String url) {
  String filename = CachedGraphicsURL2filename(url);

  if (! SPIFFS.exists(filename) ) {
    SerialUDP.println("Download: " + url);

    HTTPClient http;
    http.begin(imageproxyloaderurl + url);
    int httpCode = http.GET();
    if (httpCode > 0) {
      if (httpCode == HTTP_CODE_OK) {
        // get lenght of document (is -1 when Server sends no Content-Length header)
        int len = http.getSize();
        // create buffer for read
        uint8_t buff[128] = { 0 };

        File file = SPIFFS.open(filename, "w");

        // get tcp stream
        WiFiClient * stream = http.getStreamPtr();

        int cc = 0;

        // read all data from server
        while (http.connected() && (len > 0 || len == -1)) {
          // get available data size
          size_t size = stream->available();

          if (size) {
            // read up to 128 byte
            int c = stream->readBytes(buff, ((size > sizeof(buff)) ? sizeof(buff) : size));

            cc = cc + c;

            // write it to Serial
            file.write(buff, c);

            if (len > 0) {
              len -= c;
            }
          }
          delay(1);
        }
        file.close();
      }
    }
    http.end();
  }
}


const int maxforecasts = 4;
struct forecasttype {
.....
  String iconfilename; // list.weather.icon 
.....
};
struct forecasttype forecast[maxforecasts];


//==================================================================================================
//==================================================================================================
String OpenWeathermapIconURL(int index) {
  return OpenweathermapIconPath + forecast[index].iconfilename + ".png";
}

//==================================================================================================
//==================================================================================================
byte Findforecasts(void) {
.....

    CachedGraphicsFetchUnCached(OpenWeathermapIconURL(i));
	
.....

  return 0;
}


//==================================================================================================
//==================================================================================================
void ImageDraw(int index, int xofs, int yofs) {
  String filename = CachedGraphicsURL2filename(OpenWeathermapIconURL(index));

  // scheitert furios, wenn die Datei zu kurz oder irgendwas nicht passt....
  if (SPIFFS.exists(filename) ) {
    File file = SPIFFS.open(filename, "r");

    byte buffer[3];
    file.read(buffer, 2);
    forecast[index].width = (buffer[0] << 8) + buffer[1];
    file.read(buffer, 2);
    forecast[index].height = (buffer[0] << 8) + buffer[1];

    forecast[index].dx = xofs;
    forecast[index].dy = yofs;

    for (int y = 0; y < forecast[index].height; y++) {
      for (int x = 0; x < forecast[index].width; x++) {
        file.read(buffer, 3);
        if ( (buffer[0] != 0xff) || (buffer[1] != 0xff) || (buffer[2] != 0xff) ) {
          tft.drawPixel(x + xofs, y + yofs, tft.color565(buffer[0], buffer[1], buffer[2]));
        }
      }
      yield();
    }

    file.close();
  }
}
