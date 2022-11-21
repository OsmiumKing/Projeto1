#include<LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
// Make custom characters:
byte Degree[] = {
B00110,
B00110,
B00000,
B00000,
B00000,
B00000,
B00000,
B00000
};
/*byte Battery1[] = {
B01110,
B11111,
B10001,
B10001,
B10001,
B10001,
B10001,
B11111
};*/
byte Battery2[] = {
B01110,
B11111,
B10001,
B10001,
B10001,
B10001,
B11111,
B11111
};
byte Battery3[] = {
B01110,
B11111,
B10001,
B10001,
B10001,
B11111,
B11111,
B11111
};
byte Battery4[] = {
B01110,
B11111,
B10001,
B10001,
B11111,
B11111,
B11111,
B11111
};
byte Battery5[] = {
B01110,
B11111,
B10001,
B11111,
B11111,
B11111,
B11111,
B11111
};
byte Battery6[] = {
B01110,
B11111,
B11111,
B11111,
B11111,
B11111,
B11111,
B11111
};
byte Sun1[] = {
B10001,
B01000,
B00011,
B11011,
B00011,
B01000,
B10001,
B00000
};
byte Sun2[] = {
B10001,
B00010,
B11000,
B11011,
B11000,
B00010,
B10001,
B00000
};

void setup() {
  Serial.begin(9600);
  
// Specify the LCD's number of columns and rows:
  lcd.begin(16, 2);
  pinMode(A0, INPUT);

// Create a new characters:
lcd.createChar(0, Degree);/*
lcd.createChar(1, Battery1);*/
lcd.createChar(1, Battery2);
lcd.createChar(2, Battery3);
lcd.createChar(3, Battery4);
lcd.createChar(4, Battery5);
lcd.createChar(5, Battery6);
lcd.createChar(6, Sun1);
lcd.createChar(7, Sun2);
  
// Clears the LCD screen:
lcd.clear();
}


void loop() {
  
  
  //LDR
  Serial.print("Luminosidade: ");
  int value = analogRead(A0);
  value= map(value, 1023, 0, 0, 100);
  Serial.print(value);
  Serial.print("%");
  Serial.println();
  Serial.println();
  
  if(value<10){
  lcd.setCursor(4, 0);
  lcd.print(value);
  lcd.setCursor(5, 0);
  lcd.print("%");
  }else if(value<100 && value>9){
  lcd.setCursor(3, 0);
  lcd.print(value);
  lcd.setCursor(5, 0);
  lcd.print("%");
  }else if(value==100){
  lcd.setCursor(2, 0);
  lcd.print(value);
  lcd.setCursor(5, 0);
  lcd.print("%");
  }
  //pode demorar 10 milissegundos a estabilizar

  
  //Thermistor
  Serial.print("Temperatura: ");
  int VRT = analogRead(A1);
  Serial.print(VRT);
  Serial.print("ºC");
  Serial.println();
  Serial.println();
  Serial.println();
  
  if(VRT<10){
  
  lcd.setCursor(2, 1);
  lcd.print(VRT); 
    
  }else if(VRT<100 && VRT>9){
    
  lcd.setCursor(1, 1);
  lcd.print(VRT);
  
  }else {
    
  lcd.setCursor(0, 1);
  lcd.print(VRT);
  }
  
  
  lcd.setCursor(4, 1);
  lcd.print("C");
  
  
  lcd.setCursor(3, 1);
  lcd.write(byte(0));

// Print all the custom characters:
  


  
lcd.setCursor(8, 1);
lcd.write(byte(1));

lcd.setCursor(9, 1);
lcd.write(byte(2));
  
lcd.setCursor(10, 1);
lcd.write(byte(3));

lcd.setCursor(11, 1);
lcd.write(byte(4));
  
lcd.setCursor(12, 1);
lcd.write(byte(5));
  
lcd.setCursor(0, 0);
lcd.write(byte(6));
  
lcd.setCursor(1, 0);
lcd.write(byte(7));
  
  delay(500);
  
  lcd.clear();
}
