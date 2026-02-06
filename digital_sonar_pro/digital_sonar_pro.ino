/*
ProVersion
Мини-проект на Arduino UNO ()
Электронная рулетка на индикаторной шкале и УЗ датчике
Используются 9 светодиодов.
Используется map вместо условий + функция обработк датчика
*/

#define trig 11
#define echo 12
float distance;
short type = 0;

void setup() {
  Serial.begin(9600);
  //Устанавливаем режим пинов для светодиодов
  for (int i = 2; i < 11; i++) {
    pinMode(i, OUTPUT);
  }
  //Режим пина для излучателя и приёмника УЗ
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
}

void loop() {
  //Блок получения показаний с датчика
  distance = uz_tick(trig, echo);
  /*
  Выводим в порт в формате:
  Расстояние = S см.
  */
  Serial.print("Расстояние = ");
  Serial.print(distance);
  Serial.println("см");
  distance = constrain(distance, 2, 51);
  type = map(distance, 2, 51, 9, 0);
  for (int i = 2; i < 2 + type; i++) {
    digitalWrite(i, HIGH);
  }
  for (int i = 10; i > 10 - (9 - type); i--) {
    digitalWrite(i, LOW);
  }

  //Задержка для стабильности
  delay(100);
}

float uz_tick (int trig_pin, int echo_pin) {
    //Блок получения показаний с датчика
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);
  return (0.01723 * pulseIn(echo_pin, HIGH));
}