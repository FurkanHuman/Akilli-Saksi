
 
int sensor = A0; 
 int yagmur;             // Yağmur sensörümüzü Analog A0 pinimize tanımladık.

void setup() {
 pinMode(sensor, INPUT);     // Sensörümüzü giriş pini olarak tanımladık.
 Serial.begin(9600);         // Seri monitörü aktifleştirdik. 
 Serial.println("Yağış Durumu:");
 Serial.println("-------------");
}

void loop() {
yagmur = analogRead(A0);      // A0 pin değerini "yagmur" değişkenimize aktardık.

if(yagmur > 901){              // "yagmur" değişkenimizin değerini IF kontrol yapısıyla karşılaştırıyoruz.
Serial.println("Yagmur yok!");
delay(1000);
}
if(yagmur > 301 && yagmur <= 900){
Serial.println("Yagmur yagiyor!");
delay(1000);
}
if(300 > yagmur){
Serial.println("Sağanak Yağış!");
delay(1000);
}
}




