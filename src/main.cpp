#include <Arduino.h>
#include <LowPower.h>
#include "main.h"
//#define DEBUG

uint8_t outs_state_index = 0;
uint8_t power_led_state = 0;
state current_state = BEFORE_ON;

void setOutsState(uint8_t mask)
{
  for (uint8_t i = 0; i < pins_len; i++)
    digitalWrite(pins[i], (mask >> i) & 1);
}

void setState(state new_state)
{
#ifdef DEBUG
  Serial.print(current_state);
  Serial.print(" > ");
#endif
  current_state = new_state;
#ifdef DEBUG
  Serial.print(current_state);
  Serial.println();
#endif
}

void check_power_off()
{
  uint16_t sens = analogRead(PIN_SNH);
  if (sens < SENS_TRESHOLD)
  {
    outs_state_index++;
    setOutsState(0b0000);
    setState(POWER_GONE);
  }
}

void check_power_on()
{
  uint16_t sens = analogRead(PIN_SNH);
  if (sens >= SENS_TRESHOLD)
  {
    setOutsState(states[outs_state_index % states_len]);
    setState(POWER_ON);
  }
}

void setup()
{
#ifdef DEBUG
  Serial.begin(9600);
  Serial.println("Hello!");
#endif

  pinMode(PIN_A, OUTPUT);
  pinMode(PIN_B, OUTPUT);
  pinMode(PIN_C, OUTPUT);
  pinMode(PIN_D, OUTPUT);

  pinMode(PIN_SNH, INPUT);
}

void loop()
{ 
  switch (current_state)
  {
  case BEFORE_ON:
    setOutsState(states[outs_state_index]);
    setState(POWER_ON);
    break;

  case POWER_ON:
    check_power_off();
    break;

  case POWER_GONE:
    #ifdef USE_LED_BUILTIN
    digitalWrite(LED_BUILTIN, power_led_state);
    LowPower.powerDown(power_led_state ? SLEEP_15MS : SLEEP_500MS, ADC_OFF, BOD_OFF);
    power_led_state = !power_led_state;
    #else
    LowPower.powerDown(SLEEP_500MS, ADC_OFF, BOD_OFF);
    #endif
    check_power_on();
    break;
  }
  /*
  setOutsState(states[outs_state_index++ % states_len]);
  LowPower.powerDown(SLEEP_500MS, ADC_OFF, BOD_OFF);
  */
}