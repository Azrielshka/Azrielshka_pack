int values [20];
int arrsize = sizeof(values)/sizeof(int);
// структура для хранение обмененных переменных
/*struct sw {
  int x;
  int y;
};
sw str;*/
void setup() {
Serial.begin(9600);
randomSeed(analogRead(A1));
Serial.print(arrsize);
for (byte i = 0; i < arrsize;i++){
  values [i] = random(-100, 100);
  Serial.print("Очередное значение: ");
  Serial.println(values[i]);
  }
shoose ();
for (byte i = 0; i < arrsize; i++){
Serial.print("Очередное отсортированное значение: ");
Serial.println(values[i]);
}
}

void loop() {
}

void BubbleSort() {
  int c;
  for ( byte i = 0; i+1 < arrsize; i++){
    for (byte j = 0; j+1 < arrsize - i; j++){
      if (values[j+1] < values[j]){
        c = values[j];
        values[j] = values[j+1];
        values[j+1] = c;
       }
    }
  }
}

void shoose () {
  int index; // хранит индекс минимального числа в текущем подмассиве
  for (byte i = 0; i < arrsize; i++) {
     int min = values[i]; //хранит минимальное число подмассива
     for (byte j = i + 1; j < arrsize; j++) {
      if (values[j] < min){ 
      min = values[j]; 
      index = j;
      }
    }
    values[index] = values[i]; 
/* сохраняем то число которое стояло на месте i
(ячейки для минимального числа подмассива) на место, где было минимальное*/
    values[i] = min; // перемещаем минимальное в начало подмассива
  }
}

// функция свапа двух переменных через сохранение в структуру (не работает с массивом)
/*sw swap (int a, int b){
  int c;
  sw str;
  c = a;
  str.x = b;
  str.y = c;
  return (str);
}
*/
