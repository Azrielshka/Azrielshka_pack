// указание размерности для матрицы
const byte ROW = 3;
const byte COLS = 5;
// создание массива 3х5
int arr [ROW][COLS];

void setup() {
  Serial.begin(9600);
// заполнение массива значениями    
    for (int i = 0; i < ROW; i++) { // перебор строк 
        for (int j = 0; j < COLS; j++) { // перебор стобцов
            arr[i][j] = i*10 + j;
        }
    }
// вывод элекментов массива в порт
for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COLS; j++) {
           Serial.print(arr[i][j]);
           // отделяем числа между собой
           Serial.print(" ");
        }
      // переводим на новую строку  
      Serial.println();  
    }
}

void loop() {


}
