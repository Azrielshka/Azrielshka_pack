#include <Key.h>
#include <Keypad.h>
/*
 ====================Для клавиатуры 4х3 ====================
 */
const byte ROWS = 4; // количество строк
const byte COLS = 4; // количество столбцов
// устанавливаем имена на кнопках клавиатуры
char nameKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6', 'B'},
  {'7','8','9', 'C'},
  {'*','0','#', 'D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; // выводы для управления строками 
byte colPins[COLS] = {5, 4, 3,2}; // выводы для управления столбцами
// инициализирует внутреннюю раскладку клавиатуры c указанныеми портами и указанным 
//количеством строк и столбцов
Keypad customKeypad = Keypad( makeKeymap(nameKeys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600);
}

void loop() {
  // проверяем какая из кнопок нажата 
  char key = customKeypad.getKey();
  if (key){
    Serial.print("Key Pressed : ");
    Serial.println(key);
  }
}
