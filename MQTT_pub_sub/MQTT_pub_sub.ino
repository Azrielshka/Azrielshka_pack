
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Настройки Wi-Fi
const char* ssid = "Podval";
const char* password = "12341234";

// Настройки MQTT
const char* mqtt_server = "m9.wqtt.ru";
const int mqtt_port = 19778;
const char* mqtt_user = "******C";
const char* mqtt_pass = "******";
const char* mqtt_topic_pub = "electro/wqtt/esp32/mes1"; // топик куда отправляем
const char* mqtt_topic_sub = "electro/wqtt/esp32/led";  // топик откуда принимаем


WiFiClient espClient;
PubSubClient client(espClient);

bool mqttConnected = false;  // Флаг подключения

void setup() {
  setupWiFi();
  client.setServer(mqtt_server, mqtt_port);
  client.setBufferSize(256);  // Увеличиваем буфер сообщений
  client.setCallback(callback);  // Функция обработки входящих сообщений
  Serial.begin(9600);

}

void loop() {
    if (!client.connected()) {
    mqttConnected = false;
    reconnectMQTT();
  } else {
    if (!mqttConnected) {
      mqttConnected = true;
      Serial.println("MQTT подключён стабильно!");
    }
  }
  client.loop();
  //Публикация сообещния
  char msg[10];
  int a = 22;
  snprintf(msg, 10, "%d", a);
  /*%d добавляем сюда c  Символ
    s  Символьная строка
    d, i  Целое десятичное число
    u  Целое без знаковое десятичное число
    o  Целое восьмеричное число
    x   Целое шестнадцатеричное число
    */
  client.publish(mqtt_topic_pub, msg);
}
// Подключение к WiFi
void setupWiFi() {
  Serial.println();
  Serial.print("Подключение к ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nWiFi подключён");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

//Подключение к серверу
void reconnectMQTT() {
  static unsigned long lastAttempt = 0;
  
  // Пытаемся переподключаться не чаще 1 раза в 5 секунд
  if (millis() - lastAttempt < 5000) {
    return;
  }
  lastAttempt = millis();
  
  Serial.print("Попытка подключения к MQTT...");
  
  // Случайный ID клиента для избежания конфликтов
  String clientId = "ESP32-" + String(random(0xFFFF), HEX);
  
  if (client.connect(clientId.c_str(), mqtt_user, mqtt_pass)) {
    Serial.println("Успешно!");
    // ВОТ тут подписка на топик
    client.subscribe(mqtt_topic_sub);
  } else {
    Serial.print("Ошибка, rc=");
    Serial.println(client.state());
  }
}


// обработка входящих MQTT-сообщений
void callback(char* topic, byte* payload, unsigned int length) {
  //Печатем топик с которого получено сообщение
  Serial.print("Получено сообщение [");
  Serial.print(topic);
  Serial.print("]: ");
  
  // Сохраняем сообщение в переменную  "message"
  String message;
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  //Печатаем само сообщение в сериал
  Serial.println(message);

  //Если получено сообщение с топика mqtt_topic_sub
  if (String(topic) == mqtt_topic_sub) {
    if (message == "ТОМУ ЧТО НУЖНО") {
      // делаем одно
    }
    if (message == "ТОМУ ЧТО НУЖНО2") {
       // делаем другое
    }  
  }
}

