#include <ESP8266WiFi.h>
#include <espnow.h>

struct RxControl {
  signed   rssi         : 8;
  unsigned rate         : 4;
  unsigned is_group     : 1;
  unsigned              : 1;
  unsigned sig_mode     : 2;
  unsigned legacy_length: 12;
  unsigned damatch0     : 1;
  unsigned damatch1     : 1;
  unsigned bssidmatch0  : 1;
  unsigned bssidmatch1  : 1;
  unsigned MCS          : 7;
  unsigned CWB          : 1;
  unsigned HT_length    : 16;
  unsigned Smoothing    : 1;
  unsigned Not_Sounding : 1;
  unsigned              : 1;
  unsigned Aggregation  : 1;
  unsigned STBC         : 2;
  unsigned FEC_CODING   : 1;
  unsigned SGI          : 1;
  unsigned rxend_state  : 8;
  unsigned ampdu_cnt    : 8;
  unsigned channel      : 4;
  unsigned              : 12;
};  // 12 bytes total

void OnDataRecv(uint8_t *mac, uint8_t *dat, uint8_t len) {
  struct RxControl *rx = (struct RxControl *)(dat - 51); // offset always -51?
  int rssi = rx->rssi - 100;  // subtract 100 for dBm

  Serial.print("RSSI: ");
  Serial.print(rssi);
  Serial.println(" dBm");
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
