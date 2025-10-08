// bool sost;
short s4et = 0;
bool cur = 0;
bool last = 0;
bool cur2 = 0;
bool LEDSOST = 0;

void setup() {
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(13, OUTPUT);
  Serial.begin (9600);
}

void loop() {
 cur = digitalRead(3);
 if (cur and !last){
  delay(10);
  cur = digitalRead(3);
  if (cur){
    s4et++;
    LEDSOST = !LEDSOST;
    digitalWrite(13,LEDSOST);
  }
 }
last = cur;
cur2 = digitalRead(2);
 if (cur2) {
  s4et = 0;
 }
Serial.print("knob=");
Serial.println(s4et);
delay(10);
}
