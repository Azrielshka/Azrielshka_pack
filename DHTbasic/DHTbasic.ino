/*
Тестовая программа для работы с модулем температуры и влажности DHT11
Скетч выводит в монитор порт показания температуры 
в Цельсиях, Фаренгейтах, Кельвинах, влажность в % каждые 5 секунды по таймеру
*/
#include <TroykaDHT.h>
#define pinDHT 4 //пин датчика
DHT datchik(pinDHT, DHT11); // объект DHT, назовем именем datchik
double tmp_C, tmp_K, tmp_F;  // переменные для хранения температуры
float hum;                  // переменная для хранения влажности

void setup() {
  Serial.begin(9600); // открываем монитор порта
  datchik.begin();    //подключение связи с датчиком
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
  else {
    Serial.println(datchik.getState());
  }
  delay(5000);
}
