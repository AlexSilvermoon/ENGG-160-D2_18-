
const int reflectivePin = 2;
const int ledPin = 13;
int reflectiveState = 0;
unsigned long reflIntervalStart;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(reflectivePin, INPUT);
  Serial.begin(9600);
  reflIntervalStart = millis();
}

void loop() {
 
  reflectiveState = digitalRead(reflectivePin);
  if (reflectiveState == HIGH && reflIntervalStart > 0) {
    
    Serial.print("Oscillation Period = ");
    float seconds = (millis() - reflIntervalStart) / 1000.0 * 2;
    Serial.println(seconds, 3);
    Serial.println();
    reflIntervalStart = 0;
    
  }
  if (reflectiveState == LOW && reflIntervalStart == 0) {
    reflIntervalStart = millis();
  }

  if (reflectiveState == HIGH) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
}