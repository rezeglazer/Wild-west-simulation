#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

#include <esp_now.h>
#include <WiFi.h>

const uint8_t  kButtonPin = 23;   // Button
const uint8_t  kDiodePin  = 19;   // Blue LED

const unsigned long kBlinkMs = 200;
unsigned long blinkStart = 0;

decode_results results;

bool wasPressed = false;
bool blinking = false;

void setup() {
  Serial.begin(115200);
  delay(500);

  pinMode(kButtonPin, INPUT_PULLUP);
  pinMode(kDiodePin, OUTPUT);
}

void loop() {
  bool pressed = (digitalRead(kButtonPin) == LOW);
  if (pressed && !wasPressed) {
    Serial.println("Button clicked");
    digitalWrite(kDiodePin, HIGH);

    blinkStart = millis();
    blinking = true;
  }

  wasPressed = pressed;

  // Turn LED off after 200 ms
  if (blinking && millis() - blinkStart >= kBlinkMs) {
    digitalWrite(kDiodePin, LOW);
    blinking = false;
  }

  delay(10);
}
