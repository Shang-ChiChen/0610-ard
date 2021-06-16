int latchPin = 8;
int clockPin = 12;
int dataPin = 11;
byte scan[8]={
  B11111110,
  B11111101,
  B11111011,
  B11110111,
  B11101111,
  B11011111,
  B10111111,
  B01111111
};

byte P[8]={
  B00111100,
  B01011010,
  B10011001,
  B10011001,
  B10111101,
  B11111111,
  B01011010,
  B00111100
};

void setup()
{
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}
void loop()
{
  for(int i = 0;i<8;i++){
    digitalWrite(latchPin,LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, scan[i]);
    shiftOut(dataPin, clockPin, LSBFIRST, A[i]);
    digitalWrite(latchPin,HIGH);
    delay(1);
  }
}
