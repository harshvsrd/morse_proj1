#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define LDR_PIN A0
#define THRESHOLD 100
#define UNIT 25   // unit time in (ms)

unsigned long lightStart = 0;
unsigned long darkStart = 0;

bool lightNow = false;
bool lightPrev = false;

String morse = "";
String message = "";

//A–Z
const char* morseTable[] = {
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....",
  "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.",
  "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-",
  "-.--", "--.."
};

char decodeMorse(String code) {
  for (int i = 0; i < 26; i++) {
    if (code == morseTable[i]) {
      return char('A' + i);
    }
  }
  return '?';
}

void updateDisplay() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, 0);
  display.print("Morse: ");
  display.print(morse);

  display.setCursor(0, 16);
  display.setTextSize(1);
  display.print(message);

  display.display();
}

void setup() {
  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (true);
  }

  display.clearDisplay();
  display.display();
}

void loop() {
  int ldr = analogRead(LDR_PIN);
  lightNow = (ldr > THRESHOLD);
  unsigned long now = millis();

  // Light on edge
  if (lightNow && !lightPrev) {
    lightStart = now;
  }

  // Light off edge to dot or dash
  if (!lightNow && lightPrev) {
    unsigned long onTime = now - lightStart;

    if (onTime < UNIT * 2) {
      morse += ".";
    } else {
      morse += "-";
    }

    darkStart = now;
    updateDisplay();
  }

  // dark period
  if (!lightNow && !lightPrev) {
    unsigned long offTime = now - darkStart;

    // letter gap (3 units)
    if (offTime > UNIT * 3 && morse.length() > 0) {
      message += decodeMorse(morse);
      morse = "";
      updateDisplay();
    }

    // WORD GAP  (7 units)
    if (offTime > UNIT * 7 && offTime < UNIT * 14) {
      if (message.length() > 0 && message.charAt(message.length() - 1) != ' ') {
        message += " ";
        updateDisplay();
      }
    }

    // NEW LINE (14 units)
    if (offTime > UNIT * 14) {
      if (message.length() > 0 && message.charAt(message.length() - 1) != '\n') {
        message += "\n";
        updateDisplay();
      }
    }
  }

  lightPrev = lightNow;
}
