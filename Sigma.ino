#include <WiFiNINA.h>
#include <ArduinoHttpClient.h>

char ssid[] = "DigitalTeknik24";
char pass[] = "DigiTek24";

char serverAddress[] = "192.168.50.206";
int port = 80;

WiFiClient wifi;
HttpClient client = HttpClient(wifi, serverAddress, port);

int lightNumber = 17;     // skift til din pære
int delayTime = 2000;     // 2000 ms = 2 sekunder

void setup() {
  Serial.begin(9600);
  while (!Serial);

  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected!");
}

void loop() {
  // Tænd lyset
  setLight(true);
  delay(delayTime);

  // Sluk lyset
  setLight(false);
  delay(delayTime);
}

void setLight(bool on) {
  String path = "/api/41oxODjOX9EsuUQo5KgwbglIOZQxXIItIOAmJdV7/lights/" + String(lightNumber) + "/state";
  String body = "{\"on\":" + String(on ? "true" : "false") + "}";

  client.beginRequest();
  client.put(path);
  client.sendHeader("Content-Type", "application/json");
  client.sendHeader("Content-Length", body.length());
  client.beginBody();
  client.print(body);
  client.endRequest();

  // Optional: print status
  int statusCode = client.responseStatusCode();
  Serial.print("Status: ");
  Serial.println(statusCode);
}
