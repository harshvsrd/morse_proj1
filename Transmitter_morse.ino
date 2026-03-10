#define LED_PIN 9
#define BUTTON_PIN 2

#define UNIT 25 

String message = "vijji  bhoomi  pranav  battery";   // EDIT MESSAGE HERE

// Morse table A–Z
const char* morseTable[] = {
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....",
  "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.",
  "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-",
  "-.--", "--.."
};

void sendDot() {
  digitalWrite(LED_PIN, HIGH);
  delay(UNIT);        
  digitalWrite(LED_PIN, LOW);
  delay(UNIT);   
}

void sendDash() {
  digitalWrite(LED_PIN, HIGH);
  delay(UNIT * 3);      // 60ms ON
  digitalWrite(LED_PIN, LOW);
  delay(UNIT);          // 20ms gap
}

void sendLetter(char c) {

  if (c == ' ') {
    delay(UNIT * 7);    // Word gap
    return;
  }

  if (c >= 'a' && c <= 'z') {
    c = c - 'a' + 'A';
  }

  if (c < 'A' || c > 'Z') return;

  const char* code = morseTable[c - 'A'];

  for (int i = 0; code[i] != '\0'; i++) {
    if (code[i] == '.') sendDot();
    else sendDash();
  }

  delay(UNIT * 4);   // Letter gap (>60ms for receiver)
}

void sendMessage() {
  for (int i = 0; i < message.length(); i++) {
    sendLetter(message[i]);
  }
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {

  if (digitalRead(BUTTON_PIN) == LOW) {   // Button pressed
    delay(50);  // Debounce

    if (digitalRead(BUTTON_PIN) == LOW) {
      sendMessage();

      // Wait until button released
      while (digitalRead(BUTTON_PIN) == LOW);
      delay(50);
    }
  }
}