#include "esp_sleep.h"

RTC_DATA_ATTR int counter = 0;

void setup() {
  Serial.begin(115200);
  delay(1000); //delay to set up serial monitor

  //increment boot counter RTC variable every wake-up and print
  counter++;
  Serial.println(counter);

  //initialize RTC GPIO25 as OUTPUT and set to LOW
  pinMode(GPIO_NUM_25, OUTPUT);
  delay(200);
  digitalWrite(GPIO_NUM_25, LOW);
  delay(200);

  //configure wake-up when RTC GPIO4 set to HIGH(1)
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_4,1);

  Serial.println("Going to sleep now");
  delay(1000);

  //enable hold on GPIO25 and enable hold in deep sleep
  //GPIO25 will be held LOW (last state) in deep sleep
  gpio_hold_en(GPIO_NUM_25);
  gpio_deep_sleep_hold_en();

  //go to sleep
  esp_deep_sleep_start();

}

void loop() {
  //This will not be printed
  Serial.println("Not sleeping.");

}
