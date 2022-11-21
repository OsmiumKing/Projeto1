void setup() {
  Serial.begin(9600);
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
  //pode demorar 10 milissegundos a estabilizar

  //Thermistor
  Serial.print("Temperatura: ");
  int VRT = analogRead(A1);
  Serial.print(VRT);
  Serial.print("ºC");
  Serial.println();
  Serial.println();
  Serial.println();
  delay(500);

}
