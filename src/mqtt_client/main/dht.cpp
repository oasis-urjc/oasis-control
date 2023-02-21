/**
 * @file dht.cpp
 * @methods for a DHT11 sensor
 * @date 30/01/2022
 */
 
#include "Arduino.h"
#include "dht.h"

void DHT::update_value()
{
  // BUFFER TO RECEIVE
  uint8_t bits[5];
  uint8_t cnt = 7;
  uint8_t idx = 0;

  // EMPTY BUFFER
  for (int i=0; i< 5; i++) bits[i] = 0;

  // REQUEST SAMPLE
  pinMode(pin_in, OUTPUT);
  digitalWrite(pin_in, LOW);
  delay(18);
  digitalWrite(pin_in, HIGH);
  delayMicroseconds(40);
  pinMode(pin_in, INPUT);

  // ACKNOWLEDGE or TIMEOUT
  unsigned int loopCnt = 10000;
  while(digitalRead(pin_in) == LOW)
    delayMicroseconds(1);

  loopCnt = 10000;
  while(digitalRead(pin_in) == HIGH)
    delayMicroseconds(1);

  // READ OUTPUT - 40 BITS => 5 BYTES or TIMEOUT
  for (int i=0; i<40; i++)
  {
    loopCnt = 10000;
    while(digitalRead(pin_in) == LOW)
      delayMicroseconds(1);

    unsigned long t = micros();

    loopCnt = 10000;
    while(digitalRead(pin_in) == HIGH)
      delayMicroseconds(1);

    if ((micros() - t) > 40) bits[idx] |= (1 << cnt);
    if (cnt == 0)   // next byte?
    {
      cnt = 7;    // restart at MSB
      idx++;      // next byte!
    }
    else cnt--;
  }

  // WRITE TO RIGHT VARS
  // as bits[1] and bits[3] are allways zero they are omitted in formulas.
  temp = (float)bits[2];
  hum = (float)bits[0];  

  uint8_t sum = bits[0] + bits[2];  

  // if (bits[4] != sum) return DHT_BAD_CHECKSUM;
}
