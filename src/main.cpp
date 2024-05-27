#include <Arduino.h>

bool state = false;
uint8_t count = 0;

void IRAM_ATTR countPulses()
{
  count++;
  state = count == 1 ? HIGH : LOW;
  count = count > 8 ? 0 : count;
}

void setup() {
  pinMode(15, OUTPUT);
  pinMode(35, INPUT_PULLUP);
  attachInterrupt(35, countPulses, RISING);
  pinMode(LED_BUILTIN, OUTPUT);
}
  void loop() {
  digitalWrite(15, state);
}