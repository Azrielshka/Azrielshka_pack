#define data 2  // задаем пин DS (DATA, передачи данных)
#define clock 3 // пин тактов синхронизации SH_CP (CLOCK)
#define latch 4 // пин защелки ST_CP(LATCH) 

// храним в массиве комбинации вкл. светодиодов (свет. шкалы) 
byte fire[9] = {
  0b00000000,    // все выкл
  0b00000001,    
  0b00000010,
  0b00000100,
  0b00001000,
  0b00010000,
  0b00100000,
  0b01000000,
  0b10000000,};
  
void setup()
{
  // установка пинов на выход
  pinMode(clock, OUTPUT);
  pinMode(latch, OUTPUT);
  pinMode(data, OUTPUT);
  //выкл передачу на всякий случай
  digitalWrite(latch, HIGH);
}

void loop()
{
  for (byte i = 0; i < 9; i++ ){
  //устанавливаем LOW на latchPin - передача байта начата.
  digitalWrite(latch, LOW);
  shiftOut(data, clock, MSBFIRST, fire[i]);
 //устанавливаем HIGH на latchPin, чтобы проинформировать регистр, что передача окончена.
  digitalWrite(latch, HIGH);
  delay(200);
  }
}
