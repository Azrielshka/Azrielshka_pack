/* 
 * Пример кода для вывода реального времени в монитор порта
 * Установка текущего времени осуществляется отправкой следующего сообщения в монитор порта
 * T1619866170 - установить время на 10:49:30 1 мая 2021 года
 * где 1619866170 - десятизначное значение времени https://www.epochconverter.com/
 */  
#include <TimeLib.h>

#define TIME_HEADER  "T"   // Заголовок сообщения для отправки в порт
#define TIME_REQUEST  35    // ASCII идентификатор запрашивает сообщение синхронизации времени
void setup()  {
  Serial.begin(9600);
  //while (!Serial) ; // Используется только для Leonardo
  Serial.println("Waiting for sync message");
  setSyncProvider(requestSync);  //синхронизация времени
  while(timeStatus() != timeSet){
    if (Serial.available()) {
    processSyncMessage();
  }
  }
}

void loop(){    
  digitalClockDisplay();
  delay(1000);
}

void digitalClockDisplay(){
  // функция вывода часов, минут, секунд и даты в порт
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.print(" ");
  Serial.print(day());
  Serial.print(" ");
  Serial.print(month());
  Serial.print(" ");
  Serial.print(year()); 
  Serial.println(); 
  // возвращает время в секундах 
  //прошедшее с 1 января 1970 года
  Serial.print(now()); 
  Serial.println(); 
}

void printDigits(int digits){
  // функция для отображения часов и минут 
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}


void processSyncMessage() { 
  // функция синхронизации времени
  unsigned long pctime;
  const unsigned long DEFAULT_TIME = 1357041600; // 1   Январь  2013

  if(Serial.find(TIME_HEADER)) { // Если заголовок совпадает ('Т')
     pctime = Serial.parseInt(); // Осуществляет поиск очередного целого числа во входном потоке
     if( pctime >= DEFAULT_TIME) { // проверка введенного времени
       setTime(pctime); // Синхронизирует часы Arduino со временем, полученным через последовательный порт
     }
  }
}

time_t requestSync()
{
  Serial.write(TIME_REQUEST);  
  return 0; // время будет отправлено позже в ответ на сообщение порта
}
