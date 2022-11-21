int speakerPin=10;
int length=5;
char notes[]="cf";
int beats[]={1,1,1,1};
int tempo=300;

void playTone(int tone, int duration){
  for (long i=0; i< duration*1000L; i+=tone*2){
    digitalWrite(speakerPin,HIGH);
    delayMicroseconds(tone);
    digitalWrite(speakerPin,LOW);
    delayMicroseconds(tone);
  }
}

void playNote(char note,int duration){
  char names[]={'c','d','e','f','g','a','b','C'};
  int tones[]={1915,1700,1519,1432,1275,1136,1024,956};
  
  for(int i=0;i<8;i++){
    if(names[i]==note)
      playTone(tones[i],duration);
  }
}

void setup()
{
  pinMode(A0,INPUT);
  pinMode(speakerPin, OUTPUT);
  SerialBegin
}

  
void loop()
{
  for(int i=0;i<length;i++){
    if(notes[i]==' ')
      delay(beats[i]*tempo);
    else
    playNote(notes[i],beats[i]*tempo);
    
    delay(tempo/2);
}
}