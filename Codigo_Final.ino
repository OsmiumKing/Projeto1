// C++ code
//

#include<LiquidCrystal.h>

LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

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

  //motor speed
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);

  // Specify the LCD's number of columns and rows:
  lcd.begin(16, 2);
  pinMode(A0, INPUT);

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

      delay(400);

      digitalWrite(motor2pin1, LOW);
      digitalWrite(motor2pin2, LOW);

      digitalWrite(motor1pin1, LOW);
      digitalWrite(motor1pin2, LOW);

    } else if (inputByte == 'B') {
      digitalWrite(motor1pin1, LOW);
      digitalWrite(motor1pin2, HIGH);

      digitalWrite(motor2pin1, HIGH);
      digitalWrite(motor2pin2, LOW);

      delay(400);

      digitalWrite(motor2pin1, LOW);
      digitalWrite(motor2pin2, LOW);

      digitalWrite(motor1pin1, LOW);
      digitalWrite(motor1pin2, LOW);

    } else if (inputByte == 'L') {
      digitalWrite(motor1pin1, HIGH);
      digitalWrite(motor1pin2, LOW);

      digitalWrite(motor2pin1, HIGH);
      digitalWrite(motor2pin2, LOW);

      delay(400);

      digitalWrite(motor2pin1, LOW);
      digitalWrite(motor2pin2, LOW);

      digitalWrite(motor1pin1, LOW);
      digitalWrite(motor1pin2, LOW);

    } else if (inputByte == 'R') {
      digitalWrite(motor2pin1, LOW);
      digitalWrite(motor2pin2, HIGH);

      digitalWrite(motor1pin1, LOW);
      digitalWrite(motor1pin2, HIGH);

      delay(400);

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


        //LDR
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



        //Thermistor
        Serial.print("Temperatura: ");
        int VRT = analogRead(A2);
        Serial.print(VRT);
        Serial.print("ºC");
        Serial.println();
        Serial.println();
        Serial.println();

        if (VRT < 10) {

          lcd.setCursor(2, 1);
          lcd.print(VRT);

        } else if (VRT < 100 && VRT > 9) {

          lcd.setCursor(1, 1);
          lcd.print(VRT);

        } else {

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





        //Sistema de movimento conforme a percentagem de luminosidade:


        //Controlling speed (0 = off and 255 = max speed):
        analogWrite(6, 100); //ENA pin
        analogWrite(7, 200); //ENB pin

        if ( value1 > value2 ) {
          if (value1 - value2 >= 6) {

            digitalWrite(motor1pin1, HIGH);
            digitalWrite(motor1pin2, LOW);

            digitalWrite(motor2pin1, HIGH);
            digitalWrite(motor2pin2, LOW);

            delay(500);

            digitalWrite(motor1pin1, LOW);
            digitalWrite(motor1pin2, LOW);

            digitalWrite(motor2pin1, LOW);
            digitalWrite(motor2pin2, LOW);


            Serial.print("Move-se x para a esquerda");
          } else {
            Serial.print("Nao se mexe");
          }
        } else if (value2 > value1) {
          if (value2 - value1 >= 6) {

            digitalWrite(motor2pin1, LOW);
            digitalWrite(motor2pin2, HIGH);

            digitalWrite(motor1pin1, LOW);
            digitalWrite(motor1pin2, HIGH);

            delay(500);

            digitalWrite(motor2pin1, LOW);
            digitalWrite(motor2pin2, LOW);

            digitalWrite(motor1pin1, LOW);
            digitalWrite(motor1pin2, LOW);

            Serial.print("Move-se x para a direita");
          } else {
            Serial.print("Nao se mexe");
          }
        } else if ( value1 == value2 ) {

          Serial.print("Nao se mexe");
        }

        delay(1000);

        lcd.clear();
      }

    }
  }
}
