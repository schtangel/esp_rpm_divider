#include <Arduino.h>

int pulsesInCycle = 9;
int syncEveryCycles = 100;
bool state = false;
int32_t pulsesCount = 0;
uint32_t cyclesCount = 0;

void IRAM_ATTR CountPulses() // in interrupt just determine output state
{
  pulsesCount++;
  state = pulsesCount == 1 ? HIGH : LOW;
  pulsesCount = pulsesCount > (pulsesInCycle-1) ? 0 : pulsesCount;
}

void IRAM_ATTR SyncronizePulses() // in interrupt just determine number of cycle and syncronize cycles zero
{
  cyclesCount++;
  pulsesCount = 1;
  detachInterrupt(34);
  attachInterrupt(35, CountPulses, RISING);
  // if (cyclesCount > syncEveryCycles){
  //   pulsesCount = 0;
  //   cyclesCount = 0;
  // }
}

void setup() {
  pinMode(15, OUTPUT);
  pinMode(35, INPUT_PULLUP);
  pinMode(34, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  attachInterrupt(34, SyncronizePulses, RISING);
}
  void loop() {
  digitalWrite(15, state); // in loop just set the output
}