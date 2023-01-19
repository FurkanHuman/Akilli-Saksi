/*
Lezzetli Robot Tarifleri
https://lezzetlirobottarifleri.com/toprak-nem-sensoru-arduino-ile-nasil-kullanilir
*/

const int prob = A0;

int olcum_sonucu;

void setup() {
Serial.begin(9600);
}
 
void loop() {
  olcum_sonucu = analogRead(prob);

  Serial.print("Nem Seviyesi ");
  Serial.println(olcum_sonucu);
  delay(500);
}




  



