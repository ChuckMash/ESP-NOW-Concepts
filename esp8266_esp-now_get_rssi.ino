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


/*
dat-51  [1]  rssi                   (uint8_t, subtract 100 for dBm)
dat-50  [1]  rate+is_group+sig_mode (bitfield byte 1 of RxControl)
dat-49  [1]  legacy_length low      (bitfield byte 2 of RxControl)
dat-48  [1]  legacy_length hi       (bitfield byte 3 of RxControl)
dat-47  [1]  MCS+damatch            (bitfield byte 4 of RxControl)
dat-46  [1]  CWB+flags              (bitfield byte 5 of RxControl)
dat-45  [1]  HT_length low          (bitfield byte 6 of RxControl)
dat-44  [1]  HT_length hi           (bitfield byte 7 of RxControl)
dat-43  [1]  flags                  (bitfield byte 8 of RxControl)
dat-42  [1]  ampdu_cnt              (bitfield byte 9 of RxControl)
dat-41  [1]  channel                (bitfield byte 10 of RxControl) = 8
dat-40  [1]  reserved               (bitfield byte 11 of RxControl)
dat-39  [2]  frame_ctrl             (uint16_t, 802.11 MAC header)
dat-37  [2]  duration               (uint16_t, 802.11 MAC header)
dat-35  [6]  addr1/dst MAC          (uint8_t[6]) = FF:FF:FF:FF:FF:FF
dat-29  [6]  addr2/src MAC          (uint8_t[6]) = sender MAC
dat-23  [6]  addr3/bssid            (uint8_t[6]) = FF:FF:FF:FF:FF:FF
dat-17  [2]  sequence_ctrl          (uint16_t)
dat-15  [1]  category_code          (uint8_t) = 0x7f
dat-14  [3]  organization_id        (uint8_t[3]) = 0x18fe34
dat-11  [4]  random_values          (uint8_t[4]) — random values
dat-7   [1]  element_id             (uint8_t) = 0xdd
dat-6   [1]  length                 (uint8_t) = 18
dat-5   [3]  organization_id2       (uint8_t[3]) = 0x18fe34
dat-2   [1]  type                   (uint8_t) = 0x04
dat-1   [1]  version                (uint8_t) = 0x01
dat-0   [?]  esp-now message start  (dat)
*/
