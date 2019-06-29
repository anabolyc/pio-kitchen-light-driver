#ifdef __AVR_ATmega328P__
#define PIN_A 2
#define PIN_B 3
#define PIN_C 4
#define PIN_D 5

#define PIN_SNH A0
#define SENS_TRESHOLD 512
#define USE_LED_BUILTIN
#endif 

#ifdef __AVR_ATtiny85__
#define PIN_A 0
#define PIN_B 1
#define PIN_C 2
#define PIN_D 4

#define PIN_SNH 3
#define SENS_TRESHOLD 128
#endif 


#define ON  HIGH
#define OFF LOW

uint8_t pins[] = {
    PIN_A,
    PIN_B,
    PIN_C,
    PIN_D
};

uint8_t pins_len = 4;

uint8_t states[] = {
    0b1100,
    0b0100,
    0b1000,
};

uint8_t states_len = 3;

enum state {
    BEFORE_ON,
    POWER_ON,
    POWER_GONE
};