/* Тестовая программа для проверки работоспособности основных элемеентов
В основном цикле (loop) расскоментируйте строку 
для проверки нужно элемента.

servo_test() - Поворачивает сервопривод от 0 до 180 градусов и обратно
led_test() - Моргает светодиодами 1) индикатора карты 2)светодиодом фотоэлемента 3) индикатором 1
button_tes() - Выводит в порт состояние 3-х кнопок
photo_test() - Выводит в порт показания фотоэлемента

Перед использованием укажите порты подключения оборудования в диррективах #define
*/

#include <Servo.h>

#define pos_1 2     //порт кнопки 1
#define pos_2 3     //порт кнопки 2
#define pos_3 4     //порт кнопки 3
#define led_1 6     //порт индикатора 1
#define led_card 5  //индикатора карты
#define led_photo 7 //порт светодиода фотоэлемента
#define pinServo 9  //порт сервопривода
#define photo A1    //порт фото

Servo servo;

void setup() {
  Serial.begin(9600);
  servo.attach(pinServo);
  //при использования режима INPUT_PULLUP - показания кнопок инвертированы
  pinMode(pos_1, INPUT_PULLUP);
  pinMode(pos_2, INPUT_PULLUP);
  pinMode(pos_3, INPUT_PULLUP);
  pinMode(led_1, OUTPUT);
  pinMode(led_card, OUTPUT);
  pinMode(led_photo, OUTPUT);
}

void loop() {
  //servo_test();
  //led_test();
  //button_test();
  //photo_test();
}

void servo_test() {
  for (int i = 0; i <= 180; i++){
    servo.write(i);
    delay(10);
  }
  for(int i = 180; i > 0; i--) {
    servo.write(i);
    delay(10);
  }
}

void led_test() {
  digitalWrite(led_1, HIGH);
  digitalWrite(led_card, HIGH);
  digitalWrite(led_photo, HIGH);
  delay(500);
  digitalWrite(led_1, LOW);
  digitalWrite(led_card, LOW);
  digitalWrite(led_photo, LOW);
  delay(500);  
}

void button_test () {
  uint8_t but1, but2, but3;
  but1 = digitalRead(pos_1);
  but2 = digitalRead(pos_2);
  but3 = digitalRead(pos_3);
  Serial.print("Status button_1 = ");
  Serial.println(but1);
  Serial.print("Status button_2 = ");
  Serial.println(but2);
  Serial.print("Status button_3 = ");
  Serial.println(but3);
}

void photo_test() {
  uint16_t photoread = analogRead(photo);
  Serial.print("Status photo = ");
  Serial.println(photoread);  
}
