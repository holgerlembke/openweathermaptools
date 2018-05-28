//==================================================================================================
//==================================================================================================
String urlencode(String str)
{
  String encodedString = "";
  char c;
  char code0;
  char code1;
  char code2;
  for (int i = 0; i < str.length(); i++) {
    c = str.charAt(i);
    if (c == ' ') {
      encodedString += '+';
    } else if (isalnum(c)) {
      encodedString += c;
    } else {
      code1 = (c & 0xf) + '0';
      if ((c & 0xf) > 9) {
        code1 = (c & 0xf) - 10 + 'A';
      }
      c = (c >> 4) & 0xf;
      code0 = c + '0';
      if (c > 9) {
        code0 = c - 10 + 'A';
      }
      code2 = '\0';
      encodedString += '%';
      encodedString += code0;
      encodedString += code1;
      //encodedString+=code2;
    }
    yield();
  }
  return encodedString;
}


//==================================================================================================
//==================================================================================================
void OpenWeathermapForecastRequester(void) {
  String data = "url=" + urlencode(OpenweathermapURI) +
                "&key=" + urlencode(OpenweathermapProxyKey);

  HTTPClient http;

  http.begin(OpenweathermapProxyURI);
  http.addHeader(F("Host"), OpenweathermapProxyHost);
  http.addHeader(F("Content-Type"), F("application/x-www-form-urlencoded; charset=UTF-8"));

  int result = http.POST(data);

  if (http.connected()) {
    if (result == 200) {
      String answer = http.getString();
      OpenweathermapDatafiles = answer.toInt();
      // toInt failed?
      if (OpenweathermapDatafiles == 0) {
        OpenweathermapDatafiles = 255;
      }
    } else {
      OpenweathermapDatafiles = 255;
    }
  } else {
    SerialUDP.println("not connected");
    OpenweathermapDatafiles = 255;
  }

  http.end();
}
