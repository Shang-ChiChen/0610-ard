#define B2 123
#define C3 131
#define D3 147
#define E3 165
#define F3 175
#define G3 196
#define A3 220
#define B3 247
#define C3 262

int latchPin = 8;
int clockPin = 12;
int dataPin = 11;

int btn =2;
int thisNote = -1, noteDuration = 0;
long previousTime = 0,
     presentTime = 0,
     pauseBetweenNotes = 0;

int melody[] = {
  D3, F3, G3, E3, D3, C3, D3, B2
};
int noteDurations[] ={
  8/3, 8/3, 8/3, 8/7, 8/3, 8/3, 8/3, 8/6,
};


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

byte L[8]={
  B00000000,
  B01100110,
  B10011001,
  B10000001,
  B10000001,
  B01000010,
  B00100100,
  B00011000
};

void checkToPlay(){
  presentTime = millis();
  if(presentTime - previousTime >= pauseBetweenNotes){
    thisNote++;
    if(thisNote >= 8){
      thisNote = -1;
      pauseBetweenNotes = 100;
      previousTime = millis();
    }
    else{
      noteDuration = 100/ noteDurations[thisNote];
      tone(9, melody[thisNote], noteDuration);
      pauseBetweenNotes = noteDuration * 1.2;
      previousTime = millis();
    }
  }
}

void setup()
{
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(btn,INPUT_PULLUP); 
}
int n = 0;
void loop()
{
  if(digitalRead(btn)== 0){
      n++;
      delay(100);
      while(digitalRead(2)== 0);
    }
  for(int i = 0;i<8;i++){
    digitalWrite(latchPin,LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, scan[i]);
    if(n%2==0){
      shiftOut(dataPin, clockPin, LSBFIRST, P[i]);
    }else{
      shiftOut(dataPin, clockPin, LSBFIRST, L[i]);
    }
    digitalWrite(latchPin,HIGH);
    checkToPlay();
    delay(1);
  }
}
