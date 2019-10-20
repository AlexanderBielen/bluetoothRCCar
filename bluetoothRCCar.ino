#include <Arduino_FreeRTOS.h>

#define headLightL A3
#define headLightR A2
#define rearLightL 14
#define rearLightR 16

#define steerL A1
#define steerR A0

#define driveF 5
#define driveR 6

#define bluetooth Serial1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial1.begin(9600);

  pinMode(headLightL, OUTPUT);
  pinMode(headLightR, OUTPUT);
  /*pinMode(steerL, OUTPUT);
  pinMode(steerR, OUTPUT);
  digitalWrite(steerL, LOW);
  digitalWrite(steerR, LOW);*/

  xTaskCreate(
    ledTask,
    (const portCHAR *)"Blink",
    128,  // Stack size
    NULL,
    2,  // priority
    NULL);
}

void loop() {
  vTaskDelay(1000);
  // put your main code here, to run repeatedly:
}

void ledTask(void *params) {
  while (true) {
    digitalWrite(headLightL, HIGH);   // turn the LED on (HIGH is the voltage level)
    vTaskDelay( 1000 / portTICK_PERIOD_MS ); // wait for one second
    digitalWrite(headLightL, LOW);    // turn the LED off by making the voltage LOW
    vTaskDelay( 1000 / portTICK_PERIOD_MS ); // wait for one second
  }
}

void checkData() {
  while (bluetooth.available()) {
    char c = bluetooth.read();
    if (c == '\n') {
      parseData();
      dataIn = "";
    }
  }
}

void parseData() {
  String tmp;
  while (1) {
    if (dataIn.indexOf(",") != -1)
      tmp = dataIn.substring(0, dataIn.indexOf(","));
  }
}
