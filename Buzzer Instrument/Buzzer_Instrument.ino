const int sensorPin = 0;
const int led1 = 4;
const int led2 = 5;
const int led3 = 6;
const int buzzerPin = 9;
const int buttonPin = 10;
int stateLED = HIGH;
boolean lastPress = HIGH;
boolean currentPress = HIGH;

boolean debounce(boolean last, int pin) {
  boolean current = digitalRead(pin);
  if (last != current) {
    delay(2);
    current = digitalRead(pin);
  }
  return current;
}

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {
  int sensorValue;
  int frequency;
  
  sensorValue = analogRead(0);
  frequency = map(sensorValue, 10, 1013, 262, 523);
  
  if (sensorValue > 10) {
    tone(buzzerPin, frequency);
  } else {
    noTone(buzzerPin);
  }

  currentPress = debounce(lastPress, buttonPin);
  
  if (lastPress == HIGH && currentPress == LOW) {
    if (stateLED == HIGH) {
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      stateLED = LOW;
    } else {
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, HIGH);
      stateLED = HIGH;
    }
  }
  lastPress = currentPress;
}
