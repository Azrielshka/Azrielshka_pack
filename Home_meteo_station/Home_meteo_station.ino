/*
-========= Мини-проект домашняя метеостанция =======-
Подключение для Arduino UNO:
I. DHT11 - пин 9
II. Аналоговый датчик влажность почвы - пин А0
III. Кнопка - пин 7
IV. LCD экран (11, 12, 5, 4, 3, 2)

1. Программа выводит на LCD экран показания датчиков:
 * температуры
 * влажности воздуха
 * влажности почвы

2. Клик кнопки переключает экраны вывода. 
0 экран - Температура+влажность
1 экран - Влажность почвы

3.Отображается адекватность окружающей среды ОК - BED
Для температуры воздуха: 20-24 градуса
Для влажности воздуха: 33-55 %
Для влажности почвы: 300-600 условных единиц с АЦП
Все остальные значения считаются недопустимыми и выводится "BED".
*/

#include <LiquidCrystal.h> //Библиотека для работы с LCD экраном
#include <TroykaDHT.h>     //Библиотека для работы с DHT11
#define dht_pin 9          // Пин подключения датчика
#define bt_pin  7          // Пин подключения кнопки
#define soil_pin A0        // Пин подключения влажности повы

DHT vlg(dht_pin, DHT11);   // Создание объекта датчика
LiquidCrystal lcd(11, 12, 5, 4, 3, 2); // Создание объекта для LCD 

//Блок переменных
float h = 0.0, t = 0.0;   // Хранение показаний с DHT11
int soil = 0;             // Хранение почвы 
String mod_h = "ERR";     // Состояние влажности
String mod_t = "ERR";     // Состояние воздуха
String mod_s = "ERR";     // Состояние влажности
bool num_lcd = 0;         // Номер выводимого экрана
bool cur_sost, last_sost; // Для обработки клика по кнопке

void setup() {
  Serial.begin(9600);
  vlg.begin();
  lcd.begin(16,2);
  pinMode(bt_pin, INPUT_PULLUP);
}

void loop() {
  cur_sost = digitalRead(bt_pin);
  //Обработка клика по кнопке
  if (cur_sost != last_sost) {
    if (cur_sost == 0) {
    //это клик. Можем сделать что нам надо. - меняем номер экрана
    Serial.print("Click"); // Для отладки
    num_lcd = !num_lcd;    // Меняем номер экрана (инвертируем т.к. всего 2)
    lcd.clear();           // Чистим экран
    }
    //Текущее состояния теперь предыдущее. Наступил новый момент времени
    last_sost = cur_sost;
  }
  //Читаем значения с датчика DHT11
  vlg.read();
  t = vlg.getTemperatureC();
  h = vlg.getHumidity();
  //Читаем значения с почвы
  soil = analogRead(soil_pin);
  //Анализируем состояние темп воздуха, чтобы вывести на экран OK или BAD
  if (t >= 20 && t <= 24) {
    mod_t = "OK";
  }
  else{
    mod_t = "BAD";
  }
  //Анализируем состояние влажности воздуха, чтобы вывести на экран OK или BAD
  if (h >= 33 && h <= 55) {
    mod_h = "OK";
  }
  else{
    mod_h = "BAD";
  }
  //Анализируем состояние почвы, чтобы вывести на экран OK или BAD
  if (soil >= 300 && soil <= 600) {
    mod_s = "OK";
  }
  else{
    mod_s = "OK";
  }

  //Выводим на экран. Воздух или Почва
  if (!num_lcd) {
    //Экран воздуха
    lcd.setCursor(0,0);
    lcd.print("temp=");
    lcd.print(t);
    lcd.print("/C");
    lcd.print(mod_t);
    lcd.setCursor(0,1);
    lcd.print("hum=");
    lcd.print(h);
    lcd.print("%");
    lcd.print(mod_h);
  }
  else {
    //Экран почвы
    lcd.setCursor(0,0);
    lcd.print("pochva=");
    lcd.print(soil);
    lcd.setCursor(0, 1);
  }
  //otladka(); // можно вызвать отладку датчиков и посмотреть показания в Serial.
  delay(50);
}

//Отладочная функция, выводим все в сериал порт, чтобы убидиться в работоспособности
void otladka () {
  Serial.print("Temp=");
  Serial.println(t);
  Serial.print("Hum=");
  Serial.println(h);
  Serial.print("Soil=");
  Serial.println(soil);
  delay(1300);             //Задержка для стабильности
}
