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
  
  //Анализируем состояние чтобы вывести на экран OK или BAD
  mod_t = (t >= 20 && t <= 24) ? "OK" : "BAD";          //Для темепературы
  mod_h = (h >= 33 && h <= 55) ? "OK" : "BAD";          //Для влажности
  mod_s = (soil >= 300 && soil <= 600) ? "OK" : "BAD";  //Для почвы

  // Буферы для строк
  char line1[17];  // 16 символов + завершающий ноль
  char line2[17];
  char tempStr[6]; // буфер для температуры с запасом
  char humStr[6];  // буфер для влажности
  //Выводим на экран. Воздух или Почва
  if (!num_lcd) {
    // Преобразуем float в строку с одним знаком после запятой
    dtostrf(t, 4, 1, tempStr);  // всего 4 символа, 1 после запятой (например, "23.5")
    dtostrf(h, 4, 1, humStr);
    // Формируем строки
    sprintf(line1, "temp=%s/C%s", tempStr, mod_t.c_str());
    sprintf(line2, "hum=%s%%%s", humStr, mod_h.c_str());
    lcd.setCursor(0, 0);
    lcd.print(line1);
    lcd.setCursor(0, 1);
    lcd.print(line2);
  }
  else {
    // Экран почвы
    sprintf(line1, "pochva=%d", soil);
    sprintf(line2, "%s", mod_s.c_str());
    lcd.setCursor(0, 0);
    lcd.print(line1);
    lcd.setCursor(0, 1);
    lcd.print(line2);
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
