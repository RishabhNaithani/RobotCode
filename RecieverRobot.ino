#include <ESP8266WiFi.h>
#include <espnow.h>
#include<Servo.h>
Servo servo1,servo2,servo3;
typedef struct struct_message {
    int x;
    int y;
    int flex;
} struct_message;

// Create a struct_message called myData
struct_message myData;

       
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Bytes received: ");
  Serial.print("Value of X: ");
  Serial.println(myData.x);
  Serial.print("Value of Y: ");
  Serial.println(myData.y);
  Serial.print("Value of POS: ");
  Serial.println(myData.flex);
}
void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  servo1.attach(12); //D6
  servo2.attach(13); //D7
  servo3.attach(4); //D4
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  servo1.write(0);
  servo2.write(0);
  servo3.write(0);

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;


  }
  
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  servo1.write(myData.x);
  servo2.write(myData.y);
  if(myData.flex<900){
    servo3.write(180);
  }
  else{
    servo3.write(0);  
  }
}
  // put your main code here, to run repeatedly:
