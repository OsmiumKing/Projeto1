// C++ code
//
void setup()
{
  Serial.begin(9600);

  pinMode(A0, INPUT); //LDR esquerdo
  pinMode(A1, INPUT); //LDR direito
}

void loop()
{
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




  //Sistema de movimento conforme a percentagem de luminusidade:

  if( value1 > value2 ){
    if(value1-value2 >= 6){

      Serial.print("Move-se x para a esquerda");
    }else{
      Serial.print("Nao se mexe");
    }
  }else if(value2 > value1){
    if(value2-value1 >= 6){

      Serial.print("Move-se x para a direita");
    }else{
      Serial.print("Nao se mexe");
      }
    }else if( value1==value2 ){
      
      Serial.print("Nao se mexe");
    }

  




  delay(1000);
}
