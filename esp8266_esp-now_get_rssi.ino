#include <ESP8266WiFi.h>
#include <espnow.h>

void OnDataRecv(uint8_t *mac, uint8_t *dat, uint8_t len) {
  int rssi = (uint8_t)*(dat - 51) - 100; // Pointer offset -51, subtract 100 for dBm
  Serial.print("RSSI: ");
  Serial.println(rssi);
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  wifi_set_channel(8);
  esp_now_init();
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
}
