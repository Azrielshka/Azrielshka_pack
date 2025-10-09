// Пины: 14 - светодиод, 13 - мотор, 27 - dht11, 26 - mq135, 18 - mq135
#include <FastBot.h>
#include <ESP32Servo.h>
#include <TroykaDHT.h>

#define BOT_TOKEN "7781093283:AAF7-1K0jWBGKdkmDMualAmimnS2pGPRysI"
#define WIFI_SSID "login"
#define WIFI_PASS "pass"
#define CHAT_ID "YOUR_CHAT_ID"  // Добавьте ваш CHAT_ID

int a = 43;
int b = 68;
int v = 67;
int flag = 0; // логические переменные
int flag2 = 0; // логические переменные 
const int analogSignal = 26; // подключение аналогового сигнального пина mq135
const int digitalSignal = 18; // подключение цифрового сигнального пина mq135
int gasValue = 0; // переменная для хранения количества газа
DHT dht(27, DHT11); // пин для dht
FastBot bot(BOT_TOKEN);
Servo servo1;

void setup() {
  pinMode(14, OUTPUT); // светодиод
  pinMode(3, OUTPUT);  // добавлен пин 3 для светодиода
  servo1.attach(13); // пин 13 у мотора
  
  Serial.begin(115200);
  dht.begin();
  
  connectWiFi();
  bot.setChatID(CHAT_ID);
  bot.sendMessage("Приветствую тебя в боте для управления умным домом");
  bot.sendMessage("Помощь по управлению - help");

  // подключаем функцию-обработчик
  bot.attach(newMsg);

  // показать юзер меню (\t - горизонтальное разделение кнопок, \n - вертикальное)
  bot.showMenu("Pokaz1 \t Pokaz2 \t Pokaz3 \n OknON \n OknOFF \n Close \n help");
}

// обработчик сообщений
void newMsg(FB_msg& msg) {
  if (msg.text == "Close") {
    bot.closeMenu();
  }
  
  if (msg.text == "Pokaz1") {
    dht.read();
    String message = "Показания первого датчика: " + String(dht.getTemperatureC()) + " C";
    bot.sendMessage(message);
  }

  if (msg.text == "Pokaz2") {
    dht.read();
    String message = "Показания второго датчика: " + String(dht.getHumidity()) + " %";
    bot.sendMessage(message);
  }

  if (msg.text == "OknON" && flag == 0) {
    servo1.write(90);
    bot.sendMessage("Открытие окон");
    flag++;
  }
  
  if (msg.text == "OknOFF" && flag == 1) {
    servo1.write(0);
    bot.sendMessage("Закрытие окон");
    flag = 0;
  }
  
  if (msg.text == "help") {
    bot.sendMessage("Примеры команд: Pokaz1, Pokaz2, Pokaz3, OknON, OknOFF, SvetON, SvetOFF, Close");
    bot.sendMessage("Pokaz1 - выписывает показания температуры");
    bot.sendMessage("Pokaz2 - выписывает показания влажности");
    bot.sendMessage("OknON - открывает окна");
    bot.sendMessage("OknOFF - закрывает окна");
    bot.sendMessage("SvetOFF - выключает свет");
    bot.sendMessage("SvetON - включает свет");
    bot.sendMessage("Close - закрывает меню программы");
  }

  if (msg.text == "SvetON" && flag2 == 0) {
    digitalWrite(14, HIGH); // исправлено с 3 на 14 (по вашему описанию пинов)
    flag2++;
  }
  
  if (msg.text == "SvetOFF" && flag2 == 1) {
    digitalWrite(14, LOW); // исправлено с 3 на 14
    flag2 = 0;
  }
}

void loop() {
  dht.read();
  gasValue = analogRead(analogSignal); // считываем значение с MQ135
  proverka();
  bot.tick(); // тикаем в луп
}

void connectWiFi() {
  delay(2000);
  Serial.println();

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (millis() > 15000) ESP.restart();
  }
  Serial.println("Connected");
}

void proverka() {
  if (gasValue >= 200) {
    servo1.write(90);
    while(true) {
      digitalWrite(14, HIGH); // мигание светодиода (исправлено с 3 на 14)
      delay(500);
      digitalWrite(14, LOW);
      delay(500);
    }
  }
}