/* Система безопасности с вводом пароля и ключ картой */
#include <Servo.h>

#define pos_1 2    //порт кнопки 1
#define pos_2 3    //порт кнопки 2
#define pos_3 4    //порт кнопки 3
#define led_1 6    //порт индикатора 1
#define led_card 5 //индикатора карты
#define pinServo 9 //порт сервопривода
#define photo A1   //порт фото

uint8_t bt1, lastbt1, bt2, lastbt2, bt3, lastbt3; //переменные кнопок 
const uint8_t longpass = 3; //установка длины пароля
int password[longpass];     //массив хранения пароля
uint16_t brith, porog_b;    //хранение освещенности
uint8_t queue = 0;          //номер вводимой цифры пароля

Servo servo;

void setup() {
  Serial.begin(9600);
  servo.attach(pinServo);
  pinMode(pos_1, INPUT_PULLUP);
  pinMode(pos_2, INPUT_PULLUP);
  pinMode(pos_3, INPUT_PULLUP);
  pinMode(led_1, OUTPUT);
  pinMode(led_card, OUTPUT);
  //Установка уровня освещенности (наличие карты)
  Serial.println("Set Brightness, Put card on slot");
  delay(3000);
  porog_b = analogRead(photo);
  Serial.print("Set Brightness as = ");
  Serial.println(porog_b);
  //Установка пароля
  Serial.println("Set Password");
  set_password(longpass); //функция вызова настройки пароля
  Serial.println("Enter Password");
  delay(500);
}

void loop() {
  brith = analogRead(photo);
  //проверяем наличие карты в слоте
  if (brith < (porog_b + 50)) {
    digitalWrite(led_card, HIGH);
    //проверка пароля
    bt1= !digitalRead(pos_1);
    bt2 = !digitalRead(pos_2);
    bt3 = !digitalRead(pos_3);
    if (bt1 || bt2 || bt3) {
        digitalWrite(led_1, HIGH); //включаем индикатор нажатия на кнопку
        int cur, flag = 0; //cur - номер нажатой кнопки. флаг - нажатия
        if (bt1 && !lastbt1) {
            flag =1;
            cur = 1;  
        }
        if (bt2 && !lastbt2) {
            flag =1;
            cur = 2;
        }
        if (bt3 && !lastbt3) {
            flag = 1;
            cur = 3;
        }
        //проверяем было ли нажатие
        if(flag) {
          //проверка совпадения
        if (password[queue] == cur) {
            queue++; //увеличиваем счетчик правильных нажатий
            Serial.println(cur);
        }
        //неверная кнопка
        else {
          digitalWrite(led_1, HIGH);
          Serial.println("Wrong");
          queue = 0;
          Serial.println("Start again");
          delay(3000);
          digitalWrite(led_1, LOW);
        }
        flag =false; //сброс флага, ждем некст нажатия
        }
    }
    else {
      // выключаем индикатор если кнопка ненажата
      digitalWrite(led_1, LOW);
    }
    //если ввели все цифры правильно
    if (queue == 3) {
      Serial.println("Correct");
      queue = 0;
      //открыли механизм на 5 сек
      servo.write(90);
      delay(5000);
      servo.write(0);
    }
    //меняем состояние
    lastbt1 = bt1;
    lastbt2 = bt2;
    lastbt3 = bt3;   
  }
  //все выключаем если карты нет в слоте
  else {
    Serial.println("OFF");
    queue = 0; //сбрасываем счетчик
    digitalWrite(led_1, LOW);
    digitalWrite(led_card, LOW);
  }

}

//функция ввода пароля
void set_password (uint8_t num) {
  //передаем в функцию num - число цифр в пароле
  uint8_t kn1, last_kn1, kn2, last_kn2, kn3, last_kn3, flag;
   
  for (int i = 0; i < num; i++) {
    flag = true;
    while (flag) {
      kn1 = !digitalRead(pos_1);
      kn2 = !digitalRead(pos_2);
      kn3 = !digitalRead(pos_3);
      if (kn1 && !last_kn1) {
        password[i] = 1;
        flag = false;
      }
      if (kn2 && !last_kn2) {
        password[i] = 2;
        flag = false;
      }
      if (kn3 && !last_kn3) {
        password[i] = 3;
        flag = false;
      }
      last_kn1 = kn1;
      last_kn2 = kn2;
      last_kn3 = kn3;
    }
    Serial.print("Set");
    Serial.print(i);
    Serial.print("as = ");
    Serial.println(password[i]);
  }
  Serial.print("Password was set as =");
  for (int i = 0; i < num; i++) {
    Serial.print(password[i]);
    Serial.print(",");
  }
}
