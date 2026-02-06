/*
Мини-проект на Arduino UNO
Электронная рулетка на индикаторной шкале и УЗ датчике
Используются 9 светодиодов.
*/

#define trig 11
#define echo 12
float distance;

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
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  distance = 0.01723 * pulseIn(echo, HIGH);
  //Завершение получения показаний

  /*
  Выводим в порт в формате:
  Расстояние = S см.
  */
  Serial.print("Расстояние = ");
  Serial.print(distance);
  Serial.println("см");

  //Определяем сколько светодиодов нужно включить
  if (distance < 5) {
    Serial.println("10");
    for (int i = 2; i < 11; i++) {
      digitalWrite(i, HIGH);
    }
  } else if (distance < 10) {
    Serial.println("9");
    for (int i = 2; i < 10; i++) {
      digitalWrite(i, HIGH);
    }
    for (int i = 10; i > 9; i--) {
      digitalWrite(i, LOW);
    }
  } else if (distance < 15) {
    Serial.println("8");
    for (int i = 2; i < 9; i++) {
      digitalWrite(i, HIGH);
    }
    for (int i = 10; i > 8; i--) {
      digitalWrite(i, LOW);
    }
  } else if (distance < 20) {
    Serial.println("7");
    for (int i = 2; i < 8; i++) {
      digitalWrite(i, HIGH);
    }
    for (int i = 10; i > 7; i--) {
      digitalWrite(i, LOW);
    }
  } else if (distance < 25) {
    Serial.println("6");
    for (int i = 2; i < 7; i++) {
      digitalWrite(i, HIGH);
    }
    for (int i = 10; i > 6; i--) {
      digitalWrite(i, LOW);
    }    
  } else if (distance < 30) {
    Serial.println("5");
     for (int i = 2; i < 6; i++) {
      digitalWrite(i, HIGH);
    }
    for (int i = 10; i > 5; i--) {
      digitalWrite(i, LOW);
    }   
  } else if (distance < 35) {
    Serial.println("4");
    for (int i = 2; i < 5; i++) {
      digitalWrite(i, HIGH);
    }
    for (int i = 10; i > 4; i--) {
      digitalWrite(i, LOW);
    }    
  } else if (distance < 40) {
    Serial.println("3");
    for (int i = 2; i < 4; i++) {
      digitalWrite(i, HIGH);
    }
    for (int i = 10; i > 3; i--) {
      digitalWrite(i, LOW);
    }    
  } else if (distance < 45) {
    Serial.println("2");
    for (int i = 2; i < 3; i++) {
      digitalWrite(i, HIGH);
    }
    for (int i = 10; i > 2; i--) {
      digitalWrite(i, LOW);
    }    
  } else if (distance < 50) {
    Serial.println("1");
  } else {
    for (int i = 10; i > 1; i--) {
      digitalWrite(i, LOW);
    }  
  }
  delay(100);
}
