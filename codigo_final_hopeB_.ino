// C++ code
//

#include<LiquidCrystal.h>
LiquidCrystal lcd(13, 12, 9, 8, 7, 6);
int speakerPin = 11;
int length = 5;
char notes[] = "e gd cde gd e gD cg";
int beats[] = {1, 1, 1, 1};
int tempo = 250;
int t=0;
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

void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(tone);
  }
}

void playNote(char note, int duration) {
  char names[] = {'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C', 'D'};
  int tones[] = {1915, 1700, 1519, 1432, 1275, 1136, 1024, 956, 294};

  for (int i = 0; i < 8; i++) {
    if (names[i] == note)
      playTone(tones[i], duration);
  }
}

char inputByte;

int motor1pin1 = 2;
int motor1pin2 = 3;

int motor2pin1 = 4;
int motor2pin2 = 5;


void setup()
{
  Serial.begin(9600);

  pinMode(A0, INPUT); //LDR esquerdo
  pinMode(A1, INPUT); //LDR direito


  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);


  // Specify the LCD's number of columns and rows:
  lcd.begin(16, 2);

  // Create a new characters:
  lcd.createChar(0, Degree);
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


void loop()
{

  while (Serial.available() > 0) {
    inputByte = Serial.read();
    Serial.println(inputByte);

    if (inputByte == 'F') {
      digitalWrite(motor1pin1, HIGH);
      digitalWrite(motor1pin2, LOW);

      digitalWrite(motor2pin1, LOW);
      digitalWrite(motor2pin2, HIGH);

      delay(600);

      digitalWrite(motor2pin1, LOW);
      digitalWrite(motor2pin2, LOW);

      digitalWrite(motor1pin1, LOW);
      digitalWrite(motor1pin2, LOW);

    } else if (inputByte == 'B') {
      digitalWrite(motor1pin1, LOW);
      digitalWrite(motor1pin2, HIGH);

      digitalWrite(motor2pin1, HIGH);
      digitalWrite(motor2pin2, LOW);

      delay(600);

      digitalWrite(motor2pin1, LOW);
      digitalWrite(motor2pin2, LOW);

      digitalWrite(motor1pin1, LOW);
      digitalWrite(motor1pin2, LOW);

    } else if (inputByte == 'L') {
      digitalWrite(motor1pin1, HIGH);
      digitalWrite(motor1pin2, LOW);

      digitalWrite(motor2pin1, HIGH);
      digitalWrite(motor2pin2, LOW);

      delay(300);

      digitalWrite(motor2pin1, LOW);
      digitalWrite(motor2pin2, LOW);

      digitalWrite(motor1pin1, LOW);
      digitalWrite(motor1pin2, LOW);

    } else if (inputByte == 'R') {
      digitalWrite(motor2pin1, LOW);
      digitalWrite(motor2pin2, HIGH);

      digitalWrite(motor1pin1, LOW);
      digitalWrite(motor1pin2, HIGH);

      delay(300);

      digitalWrite(motor2pin1, LOW);
      digitalWrite(motor2pin2, LOW);

      digitalWrite(motor1pin1, LOW);
      digitalWrite(motor1pin2, LOW);

    } else if (inputByte == 'S') {

      while (Serial.read() != 'E' ) {

        int value1 = analogRead(A0);
        value1 = map(value1, 1023, 0, 0, 100);
        Serial.println("Valor1: ");
        Serial.print(value1);

        Serial.println(" ");

        int value2 = analogRead(A1);
        value2 = map(value2, 1023, 0, 0, 100);
        Serial.println("Valor2: ");
        Serial.print(value2);

        Serial.println(" ");


        //LDR media
        Serial.print("Luminosidade: ");
        int value = (value1 + value2) / 2;
        value = map(value, 1023, 0, 0, 100);
        Serial.print(value);
        Serial.print("%");
        Serial.println();
        Serial.println();

        if (value < 10) {
          lcd.setCursor(4, 0);
          lcd.print(value);
          lcd.setCursor(5, 0);
          lcd.print("%");
        } else if (value < 100 && value > 9) {
          lcd.setCursor(3, 0);
          lcd.print(value);
          lcd.setCursor(5, 0);
          lcd.print("%");
        } else if (value == 100) {
          lcd.setCursor(2, 0);
          lcd.print(value);
          lcd.setCursor(5, 0);
          lcd.print("%");
        }
        //pode demorar 10 milissegundos a estabilizar

        

        //Voltage

        Serial.print("Voltagem: ");
        float sensorValue = analogRead(A3);
        float Volt = sensorValue * (5.0 / 1023.0);
        Serial.print(Volt);
        Serial.print(" V");
        Serial.println();
        Serial.println();
        Serial.println();

        //Voltagem

        lcd.setCursor(0, 0);
        lcd.print(Volt);

        lcd.setCursor(5, 0);
        lcd.print("V");



        //Capacity and battery



        if (Volt < 3.61) {
          lcd.setCursor(10, 1);
          lcd.print("0%");
          lcd.setCursor(14, 1);
          lcd.write(byte(1));
        } else if (Volt < 3.69) {
          lcd.setCursor(10, 1);
          lcd.print("5%");
          lcd.setCursor(14, 1);
          lcd.write(byte(1));
        } else if (Volt < 3.71 && Volt > 3.69) {
          lcd.setCursor(10, 1);
          lcd.print("10%");
          lcd.setCursor(14, 1);
          lcd.write(byte(1));
        } else if (Volt < 3.73 && Volt > 3.71) {
          lcd.setCursor(10, 1);
          lcd.print("15%");
          lcd.setCursor(14, 1);
          lcd.write(byte(1));
        } else if (Volt < 3.75 && Volt > 3.73) {
          lcd.setCursor(10, 1);
          lcd.print("20%");
          lcd.setCursor(14, 1);
          lcd.write(byte(1));
        } else if (Volt < 3.77 && Volt > 3.75) {
          lcd.setCursor(10, 1);
          lcd.print("25%");
          lcd.setCursor(14, 1);
          lcd.write(byte(2));
        } else if (Volt < 3.79 && Volt > 3.77) {
          lcd.setCursor(10, 1);
          lcd.print("30%");
          lcd.setCursor(14, 1);
          lcd.write(byte(2));
        } else if (Volt < 3.80 && Volt > 3.79) {
          lcd.setCursor(10, 1);
          lcd.print("35%");
          lcd.setCursor(14, 1);
          lcd.write(byte(2));
        } else if (Volt < 3.82 && Volt > 3.80) {
          lcd.setCursor(10, 1);
          lcd.print("40%");
          lcd.setCursor(14, 1);
          lcd.write(byte(2));
        } else if (Volt < 3.84 && Volt > 3.82) {
          lcd.setCursor(10, 1);
          lcd.print("45%");
          lcd.setCursor(14, 1);
          lcd.write(byte(3));
        } else if (Volt < 3.85 && Volt > 3.84) {
          lcd.setCursor(10, 1);
          lcd.print("50%");
          lcd.setCursor(14, 1);
          lcd.write(byte(3));
        } else if (Volt < 3.87 && Volt > 3.85) {
          lcd.setCursor(10, 1);
          lcd.print("55%");
          lcd.setCursor(14, 1);
          lcd.write(byte(3));
        } else if (Volt < 3.91 && Volt > 3.87) {
          lcd.setCursor(10, 1);
          lcd.print("60%");
          lcd.setCursor(14, 1);
          lcd.write(byte(3));
        } else if (Volt < 3.95 && Volt > 3.91) {
          lcd.setCursor(10, 1);
          lcd.print("65%");
          lcd.setCursor(14, 1);
          lcd.write(byte(4));
        } else if (Volt < 3.98 && Volt > 3.95) {
          lcd.setCursor(10, 1);
          lcd.print("70%");
          lcd.setCursor(14, 1);
          lcd.write(byte(4));
        } else if (Volt < 4.02 && Volt > 3.98) {
          lcd.setCursor(10, 1);
          lcd.print("75%");
          lcd.setCursor(14, 1);
          lcd.write(byte(4));
        } else if (Volt < 4.07 && Volt > 4.02) {
          lcd.setCursor(10, 1);
          lcd.print("80%");
          lcd.setCursor(14, 1);
          lcd.write(byte(4));
        } else if (Volt < 4.11 && Volt > 4.07) {
          lcd.setCursor(10, 1);
          lcd.print("85%");
          lcd.setCursor(14, 1);
          lcd.write(byte(5));
        } else if (Volt < 4.15 && Volt > 4.11) {
          lcd.setCursor(10, 1);
          lcd.print("90%");
          lcd.setCursor(14, 1);
          lcd.write(byte(5));
        } else if (Volt < 4.20 && Volt > 4.15) {
          lcd.setCursor(10, 1);
          lcd.print("95%");
          lcd.setCursor(14, 1);
          lcd.write(byte(5));
        } else if (Volt == 4.20) {
          lcd.setCursor(10, 1);
          lcd.print("100%");
          lcd.setCursor(14, 1);
          lcd.write(byte(5));
        }







        //sun

        lcd.setCursor(0, 0);
        lcd.write(byte(6));

        lcd.setCursor(1, 0);
        lcd.write(byte(7));

        delay(500);


        //Sistema de movimento conforme a percentagem de luminosidade:


        if ( value1 > value2 ) {
          if (value1 - value2 >= 6) {

            digitalWrite(motor1pin1, HIGH);
            digitalWrite(motor1pin2, LOW);

            digitalWrite(motor2pin1, HIGH);
            digitalWrite(motor2pin2, LOW);

            delay(200);

            digitalWrite(motor1pin1, LOW);
            digitalWrite(motor1pin2, LOW);

            digitalWrite(motor2pin1, LOW);
            digitalWrite(motor2pin2, LOW);


            Serial.print("Move-se x para a esquerda");
          } else {
            Serial.print("Nao se mexe");
          }
          }else if (value2 > value1) {
            
            if (value2 - value1 >= 6) {

              digitalWrite(motor2pin1, LOW);
              digitalWrite(motor2pin2, HIGH);

              digitalWrite(motor1pin1, LOW);
              digitalWrite(motor1pin2, HIGH);

              delay(200);

              digitalWrite(motor2pin1, LOW);
              digitalWrite(motor2pin2, LOW);

              digitalWrite(motor1pin1, LOW);
              digitalWrite(motor1pin2, LOW);

              Serial.print("Move-se x para a direita");
            }else {
            Serial.print("Nao se mexe");
            }
        } else if ( value1 == value2 ) {
          t += 1;
          if (t == 15) {
            for (int i = 0; i < length; i++) {
              if (notes[i] == ' ') {
                delay(tempo);
              }

              else {
                playNote(notes[i], 2 * tempo);

              }
            }
            t = 0;
          }
          Serial.print("Nao se mexe");
        }

        delay(1500);

        lcd.clear();
      }

    }
  }
}
