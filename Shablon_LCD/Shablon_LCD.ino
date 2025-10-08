/* Пример работы с LCD дисплеем
Показаны: вывод текста, переменной, числа. Использование нескольких строк
*/
#include <LiquidCrystal.h>
//Указываем порты подключения
LiquidCrystal lcd(11, 12, 5, 4, 4, d3);
int num = 21; //переменная

void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(0, 0); // указываем строку для вывода
  lcd.print("hello, world!"); //вывод текста
  delay(5000);
  lcd.clear(); //очищаем экран
  lcd.print(num); //выводим значение переменной
}

void loop() {
  lcd.setCursor(0, 1);
  //выводим значение таймера на 2 строке
  lcd.print(millis() / 1000);
}
