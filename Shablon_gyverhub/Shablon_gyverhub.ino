// логин-пароль от роутера
#define AP_SSID "CPOD"
#define AP_PASS "ApoX51s42wR7FDK8"
#define GH_INCLUDE_PORTAL // для работы веб морды
#define LED2 2

#include <Arduino.h>
#include <GyverHub.h>

GyverHub hub;
bool gflag = 0;   // флаг свитча
// обработчик кнопки (см. ниже)
void btn_cb() {
    Serial.println("click 4");
}

// билдер
void build(gh::Builder& b) {
  if (b.beginRow()) {
      //проверяем состояние свитча. Оно записывается в переменную gflag
      if(b.Switch(&gflag).size(1).click()) {
        digitalWrite(LED2, !gflag);
      }   
   }
  b.endRow();
}

void setup() {
    Serial.begin(115200);
    pinMode(LED2, OUTPUT);
#ifdef GH_ESP_BUILD
    // подключение к роутеру
    WiFi.mode(WIFI_STA);
    WiFi.begin(AP_SSID, AP_PASS);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println();
    Serial.println(WiFi.localIP());

    // если нужен MQTT - подключаемся
    //hub.mqtt.config("test.mosquitto.org", 1883);
    // hub.mqtt.config("test.mosquitto.org", 1883, "login", "pass");

    // ИЛИ

    // режим точки доступа
    // WiFi.mode(WIFI_AP);
    // WiFi.softAP("My Hub");
    // Serial.println(WiFi.softAPIP());    // по умолч. 192.168.4.1
#endif

    // указать префикс сети, имя устройства и иконку
    hub.config(F("Azrielshka"), F("Andrey"), F(""));

    // подключить билдер
    hub.onBuild(build);

    // запуск!
    hub.begin();
}

void loop() {
    // =================== ТИКЕР ===================
    // вызываем тикер в главном цикле программы
    // он обеспечивает работу связи, таймаутов и прочего
    hub.tick();


}