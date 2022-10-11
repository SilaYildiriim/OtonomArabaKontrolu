/*
  Engelden kaçan robot, otonom olarak çevre kontrolü yapabilen ve hareketini önleyebilecek
  cisimlerden kaçmak amacıyla yön değişimi yaptırabilen program kodu.
*/

#define echoPin 12 // Ultrasonik sensörün echo pini Arduino'nun 12.pinine
#define trigPin 13 // Ultrasonik sensörün trig pini Arduino'nun 13.pinine tanımlandı.
#define MotorR1 7
#define MotorR2 6
#define MotorRE 9 // Motor pinleri tanımlıyoruz.
#define MotorL1 5
#define MotorL2 4
#define MotorLE 3

long sure, uzaklik; // süre ve uzaklık diye iki değişken tanımlandı.

void setup() {
  // ultrasonik sendör trig pininden ses dalgaları gönderdiği için OUTPUT (çıkış),
  //bu dalgaların echo pini ile geri aldığı için INPUT (giriş) olarak tanımlanır.
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT); // Motorlar çıkış olarak tanımlanır.
  pinMode(MotorR1, OUTPUT);
  pinMode(MotorR2, OUTPUT);
  pinMode(MotorRe, OUTPUT);
  pinMode(MotorL1, OUTPUT);
  pinMode(MotorL2, OUTPUT);
  pinMode(MotorLE, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(trigPin, LOW); // Sensör pasif hale getirildi.
  delayMicroseconds(5);

  digitalWrite(trigPin, HIGH); // Sensöre ses dalgası üretmesi için emir verildi.
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  sure = pulseIn(echoPin, HIGH); // Ses dalgasının geri dönmesi için geçen süre ölçülür.
  uzaklik = sure / 29.1 / 2 ; // Ölçülen süre uzaklığa çevrilir.
  Serial.println(uzaklik);

  if (uzaklik < 15) // uzaklık 15'ten küçük ise ;
  {
    geri(); // 150 ms geri git.
    delay(150);
    sag(); // 250 ms sağa dön.
    delay(250);
  }
  else ileri();
}

void ileri() { // Robotun ileri yönde hareketi için fonksiyon tanımlanır.
  digitalWrite(MotorR1, HIGH); // Sağ motorun ileri hareketi aktif
  digitalWrite(MotorR2, LOW); // Sağ motorun geri hareketi pasif
  analogWrite(MotorRE, 150); // Sağ motorun hızı 150
  digitalWrite(MotorL1, HIGH); // Sol motorun ileri hareketi aktif
  digitalWrite(MotorL2, LOW); // Sol motorun geri hareketi pasif
  analogWrite(MotorLE, 150); // Sol motorun hızı 150
}

void sag() {
  digitalWrite(MotorR1, HIGH);
  digitalWrite(MotorR2, LOW);
  analogWrite(MotorRE, 0); // Sağ motorun hızı 0 (motor duruyor)
  digitalWrite(MotorL1, HIGH);
  digitalWrite(MotorL2, LOW);
  analogWrite(MotorLE, 150);
}

void geri() {
  digitalWrite(MotorR1, LOW); // Sağ motorun ileri hareketi pasif
  digitalWrite(MotorR2, HIGH); // Sağ motorun geri hareketi aktif
  analogWrite(MotorRE, 150);
  digitalWrite(MotorL1, LOW); // Sol motorun ileri hareketi pasif
  digitalWrite(MotorL2, HIGH); // Sol motorun geri hareketi aktif
  analogWrite(MotorLE, 150);
}