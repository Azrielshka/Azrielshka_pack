/* === Пример для датчика температуры и влажности почвы DHT11 === 
Программа выводит значения температуры и влажности в serial порт */

#include <TroykaDHT.h> // библиотека для датчика DHT11

DHT dht(4, DHT11); // создаём объект класса DHT и передаем номер пина

//Создаем переменные для хранения показаний 
float t = 0.0;
float h = 0.0;
void setup()
{
  Serial.begin(9600);// открываем последовательный порт для мониторинга действий в программе
  dht.begin();
}
 
void loop()
{
  // считывание данных с датчика
  dht.read();
  t = dht.getTemperatureC();
  h = dht.getHumidity();
  //вывод показаний
  Serial.print("Temperature = ");
  Serial.print(t);
  Serial.println(" C \t");
  Serial.print("Humidity = ");
  Serial.print(h);
  Serial.println(" %");  
  // ждём две секунды перед обновлением показаний
  delay(2000);
}
