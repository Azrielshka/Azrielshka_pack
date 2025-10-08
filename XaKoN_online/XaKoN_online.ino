/* Система управления освещения домом 
c запоминаением яркости
*/

#define but 5      //порт кнопки 
#define led_1 9    //порт индикатора 1
#define led_2 6    //порт индикатора 2
#define led_3 3    //порт индикатора 3
#define pinPot A0  //порт потенциометра
#define photo A1   //порт фото

uint8_t bt;                                     //переменная кнопоки
uint16_t brith;                                 //хранение освещенности
const uint16_t porogBrith = 600;                //хранение порога освещенности
uint8_t numLed = 1;                             //хранения активного светодиода 
uint8_t flag_br = 0;                            // флаг регулировки яркости
uint8_t light1 = 125,light2 = 125,light3 = 125; //переменная для хранения яркости светодиодов
uint8_t sPot;                                   //переменная для хранения значений потенциометра
uint16_t porog_1 = 170, porog_2 = 85;           //пороги для WokWi
//uint16_t porog_1 = 680, porog_2 = 340;           //пороги для "физической сборк"
 
void setup() {
  pinMode(but, INPUT_PULLUP);
  pinMode(led_1, OUTPUT);
  pinMode(led_2, OUTPUT);
  pinMode(led_3, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  bt = !digitalRead(but);
  //кнопка отпущена
  if (!bt) {
    brith = analogRead(photo); //читаем освещенность
    //проверяем не упала ли освещенность
    if (brith > porogBrith) {
      Serial.println("Низкая яркость");
      //если упала опускаем флаг и включаем все на макс
      flag_br = false; //флаг выбора активного светодиода
      analogWrite(led_1, 255);
      analogWrite(led_2, 255);
      analogWrite(led_3, 255);
    }
    else {
      //если не упала
      flag_br = true;
    }
    //если кнопка ненажата и освещение в норме
    if (flag_br) {
      chooseActive();
      Serial.print("Активный светодиод = ");
      Serial.println(numLed);            
    }
  }
  //кнопка нажата
  else {
    Serial.print("Режим - установки яркости для светодиода = ");
    Serial.println(numLed);
    set_brith(numLed);
  }
 
}

//функция настройки яркости на пине
void set_brith (uint8_t pin) {
  uint16_t pot = analogRead(pinPot); //читаем с потенциометра
  switch (pin) {
    case 1:
      light1 = pot;
      //light1 = map(pot, 0, 1023, 0, 255);
    break;
    case 2:
      light2 = pot;
      //light2 = map(pot, 0, 1023, 0, 255);
    break;
    case 3:
      light3 = pot;
      //light3 = map(pot, 0, 1023, 0, 255);
    break;
    default:
    break;        
  }  
}

//функция выбора активного светодиода
void chooseActive () {
  sPot = analogRead(pinPot);
  Serial.print("sPot = ");
  Serial.println(sPot);
      //в 3 положении
      if (sPot >= porog_1) {
        numLed = 3;
        analogWrite(led_1, 0);
        analogWrite(led_2, 0);
        analogWrite(led_3, light3); 
      }
      //во 2 положении
      else if (sPot < porog_1 && sPot > porog_2) {
        numLed = 2;
        analogWrite(led_1, 0);
        analogWrite(led_2, light2);
        analogWrite(led_3, 0); 
      }
      else {
        numLed = 1;
        analogWrite(led_1, light1);
        analogWrite(led_2, 0);
        analogWrite(led_3, 0);         
      }
}
