#include <esp_now.h>
#include <esp_wifi_internal.h>
#include <WiFi.h>

#define TRY_ESP_ACTION(action, name) if(action == ESP_OK) {Serial.println(String(name));} else {Serial.println("----------Error while " + String(name) + " !---------------");}

#define CHANNEL 1
#define DATARATE WIFI_PHY_RATE_24M

uint8_t broadcast_mac[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

typedef struct struct_touch_message {
    int touches[9];
} struct_touch_message;

struct_touch_message outputData;
esp_now_peer_info_t peerInfo;

void setup() {
  Serial.begin(115200);

  WiFi.disconnect();
  WiFi.mode(WIFI_STA);

  TRY_ESP_ACTION( esp_wifi_stop(), "stop WIFI");
  TRY_ESP_ACTION( esp_wifi_deinit(), "De init");
  wifi_init_config_t my_config = WIFI_INIT_CONFIG_DEFAULT();
  my_config.ampdu_tx_enable = 0;
  TRY_ESP_ACTION( esp_wifi_init(&my_config), "Disable AMPDU");
  TRY_ESP_ACTION( esp_wifi_start(), "Restart WiFi");
  TRY_ESP_ACTION( esp_wifi_set_promiscuous(true), "Set promiscuous");
  TRY_ESP_ACTION( esp_wifi_set_channel(CHANNEL, WIFI_SECOND_CHAN_NONE), "Set channel");
  TRY_ESP_ACTION( esp_wifi_internal_set_fix_rate(ESP_IF_WIFI_STA, true, DATARATE), "Fixed rate set up");
  TRY_ESP_ACTION( esp_now_init(), "ESPNow Init");
  
  esp_now_register_send_cb(OnDataSent);

  // Register peer
  memcpy(peerInfo.peer_addr, broadcast_mac, 6);
  peerInfo.channel = CHANNEL;  
  peerInfo.encrypt = false;

  // Add peer
  TRY_ESP_ACTION( esp_now_add_peer(&peerInfo), "Add peer");

}

void loop() {
  outputData.touches[0] = touchRead(4);
  outputData.touches[1] = touchRead(2);
  outputData.touches[2] = touchRead(15);
  outputData.touches[3] = touchRead(13);
  outputData.touches[4] = touchRead(12);
  outputData.touches[5] = touchRead(14);
  outputData.touches[6] = touchRead(27);
  outputData.touches[7] = touchRead(32);
  outputData.touches[8] = touchRead(33);

  esp_now_send(broadcast_mac, (uint8_t *) &outputData, sizeof(outputData));
  delay(10); // Send at 100Hz
}

// Callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  //Serial.print("Send Status:\t");
  //Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
