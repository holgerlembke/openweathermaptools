const String OpenweathermapAppId     = "youropenweathermapapikey";

const String OpenweathermapURI       = "http://api.openweathermap.org/data/2.5/forecast?id=2945024&units=metric&appid="+OpenweathermapAppId+"&lang=de";
const String OpenweathermapIconPath  = "http://openweathermap.org/img/w/"; // + 10d.png

// Proxy Toolkits
const String OpenweathermapProxyHost = "192.168.1.1"; 
const int    OpenweathermapProxyPort = 80;
const String OpenweathermapPfad      = "http://" + OpenweathermapProxyHost + "/openweathermap/";
const String OpenweathermapCachePfad = OpenweathermapPfad + "cache/";
const String OpenweathermapProxyURI  = OpenweathermapPfad + "owms.php";
// key must match the key in owms.php CHANGE THIS
const String OpenweathermapProxyKey  = "secret2";
byte         OpenweathermapDatafiles = 255;       // !=255 --> Daten erhalten und valide

const String cachedimageprefix       = "/.w w";     // wenn eine SSID damit beginnt, wird die gelöscht....
const String imageproxyloaderurl     = OpenweathermapPfad + "imgdecode.php?";
