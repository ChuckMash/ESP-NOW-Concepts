// Works on ESP8266 and ESP32

#ifdef ESP8266
  #include <ESP8266WiFi.h>
  #include <espnow.h>
#else // ESP32
  #include <WiFi.h>
  #include <esp_now.h>
#endif

#ifdef ESP8266
  void on_receive(uint8_t *m, uint8_t *d, uint8_t l) { process_message(m, d, l);}
#else // ESP32
  #if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 0, 0)
    void on_receive(const esp_now_recv_info_t *i, const uint8_t *d, int l){ process_message(i->src_addr, d, l); }  
  #else
    void on_receive(const uint8_t *m, const uint8_t *d, int l){ process_message(m, d, l); }
  #endif
#endif


void process_message(const uint8_t *bssid, const uint8_t *dat, int len) {
  char mac[18];
  snprintf(mac, sizeof(mac), "%02x:%02x:%02x:%02x:%02x:%02x",bssid[0], bssid[1], bssid[2],bssid[3], bssid[4], bssid[5]);

  Serial.print(mac);
  Serial.print(" ");
  Serial.println(len);
}



void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  esp_now_init();
  #ifdef ESP8266
    WiFi.setSleepMode(WIFI_NONE_SLEEP);
    esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  #else // ESP32
    WiFi.setSleep(false);
  #endif

  esp_now_register_recv_cb(on_receive);

}



void loop() {}
