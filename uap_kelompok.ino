#include "DHT.h"

// ===== PENGATURAN PIN =====
#define DHTPIN D4
#define DHTTYPE DHT22

const int pinMQ = A0;
const int pinKipas = D5;

// ===== THRESHOLD =====
const float BATAS_SUHU = 32.0;
const int BATAS_GAS = 400;

// Inisialisasi DHT22
DHT dht(DHTPIN, DHTTYPE);

void setup() {

  // Samakan dengan baud rate Serial Monitor
  Serial.begin(9600);

  dht.begin();c:\Users\ADVAN\Documents\Arduino\uap_kelompok\uap_kelompok.ino

  pinMode(pinKipas, OUTPUT);
  digitalWrite(pinKipas, LOW);

  Serial.println();
  Serial.println("=================================");
  Serial.println(" SMART EXHAUST SYSTEM DIMULAI");
  Serial.println("=================================");
  Serial.println("Menunggu kalibrasi sensor...");
  
  delay(5000);
}

void loop() {

  float suhu = dht.readTemperature();
  float kelembapan = dht.readHumidity();

  int nilaiGas = analogRead(pinMQ);

  if (isnan(suhu) || isnan(kelembapan)) {
    Serial.println("ERROR : Gagal membaca DHT22");
    delay(2000);
    return;
  }

  Serial.println("---------------------------------");
  Serial.print("Suhu       : ");
  Serial.print(suhu);
  Serial.println(" C");

  Serial.print("Kelembapan : ");
  Serial.print(kelembapan);
  Serial.println(" %");

  Serial.print("Kadar Gas  : ");
  Serial.println(nilaiGas);

  if (suhu >= BATAS_SUHU || nilaiGas >= BATAS_GAS) {

    digitalWrite(pinKipas, HIGH);

    Serial.println("STATUS     : KIPAS MENYALA");
    Serial.println("PERINGATAN : Suhu/Gas melebihi batas");

  } else {

    digitalWrite(pinKipas, LOW);

    Serial.println("STATUS     : KIPAS MATI");
    Serial.println("Kondisi ruangan aman");
  }

  delay(2000);
}