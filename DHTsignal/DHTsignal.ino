/*
Тестовая программа для работы с модулем температуры и влажности DHT11
Скетч выводит в монитор порт показания температуры в Цельсиях, Фаренгейтах, Кельвинах, влажность в % каждые 5 секунды по таймеру.
Также осуществляет звуковое оповещение при понижении предельных значений.
Предельными считаются: Температура - 22.0 С, Влажность - 33.0 

*/
#include <TroykaDHT.h>
#define pinDHT 4 //пин датчика
#define pinBuz 5 //пин пищалки
DHT datchik(pinDHT, DHT11); // объект DHT, назовем именем datchik
double tmp_C, tmp_K, tmp_F;  // переменные для хранения температуры
float hum;                  // переменная для хранения влажности

void setup() {
  Serial.begin(9600); // открываем монитор порта
  datchik.begin();    //подключение связи с датчиком
  pinMode(pinBuz, OUTPUT); // для пищалки
}

void loop() {
  //получение показаний
  datchik.read();
  if (!datchik.getState()) { //проверям состояние датчика
    //Считываем в переменные все данные
    tmp_C = datchik.getTemperatureC(); //Температура
    tmp_K = datchik.getTemperatureK(); //Температура
    tmp_F = datchik.getTemperatureF(); //Температура
    hum = datchik.getHumidity(); //Температура
    printData(); //Выводим все в порт
  }
  else {
    Serial.println(datchik.getState());
  }
  //Проверка на оповещение
  if (tmp_C < 22.0 || hum < 33.0) {
    //Показания ниже нормы - издаем звук
    tone(pinBuz, 3300);
    delay(300);
    noTone(pinBuz);
    delay(300);
    tone(pinBuz, 3300);
    delay(300);
    noTone(pinBuz);
  }
  delay(5000);
}

void printData() {
  //Выводим в нужном формате
  Serial.println("-------new_sample-------");
  Serial.print("TemperatureC = ");
  Serial.print(tmp_C);            // В цельсиях
  Serial.println("C");
  Serial.print("TemperatureK = ");
  Serial.print(tmp_K);            // В кельвинах
  Serial.println("K");
  Serial.print("TemperatureF = ");
  Serial.print(tmp_F);            // В фарингейтах
  Serial.println("F");
  Serial.print("Humidity = ");
  Serial.print(hum);            // В %
  Serial.println("%");
}
