#include "DHT.h"

// ===== PENGATURAN PIN =====
#define DHTPIN D4
#define DHTTYPE DHT22

const int pinMQ = A0;
const int pinKipas = D5;

const int pinLEDHijau = D6;   // Kondisi Normal
const int pinLEDMerah = D7;   // Kondisi Bahaya

// ===== THRESHOLD =====
const float BATAS_SUHU = 32.0;
const int BATAS_GAS = 400;

// Inisialisasi DHT22
DHT dht(DHTPIN, DHTTYPE);

void setup() {

  Serial.begin(9600);

  dht.begin();

  pinMode(pinKipas, OUTPUT);
  pinMode(pinLEDHijau, OUTPUT);
  pinMode(pinLEDMerah, OUTPUT);

  digitalWrite(pinKipas, LOW);
  digitalWrite(pinLEDHijau, HIGH); // Awal normal
  digitalWrite(pinLEDMerah, LOW);

  Serial.println();
  Serial.println("=================================");
  Serial.println(" SMART FARMING SYSTEM DIMULAI");
  Serial.println("=================================");
  Serial.println("Monitoring Kondisi Kandang...");
  Serial.println("Menunggu kalibrasi sensor...");

  delay(5000);
}

void loop() {

  float suhu = dht.readTemperature();
  float kelembapan = dht.readHumidity();

  int nilaiGas = analogRead(pinMQ);

  if (isnan(suhu) || isnan(kelembapan)) {

    Serial.println("ERROR : Gagal membaca DHT22");

    // Kedip merah jika sensor error
    digitalWrite(pinLEDHijau, LOW);
    digitalWrite(pinLEDMerah, HIGH);

    delay(2000);
    return;
  }

  Serial.println("---------------------------------");

  Serial.print("Suhu Kandang       : ");
  Serial.print(suhu);
  Serial.println(" C");

  Serial.print("Kelembapan Kandang : ");
  Serial.print(kelembapan);
  Serial.println(" %");

  Serial.print("Kadar Gas MQ-2     : ");
  Serial.println(nilaiGas);

  if (suhu >= BATAS_SUHU || nilaiGas >= BATAS_GAS) {

    digitalWrite(pinKipas, HIGH);

    digitalWrite(pinLEDHijau, LOW);
    digitalWrite(pinLEDMerah, HIGH);

    Serial.println("STATUS KANDANG : PERINGATAN");
    Serial.println("Fan Module     : AKTIF");
    Serial.println("LED Merah      : MENYALA");
    Serial.println("PERINGATAN : Suhu/Gas melebihi batas");

  } else {

    digitalWrite(pinKipas, LOW);

    digitalWrite(pinLEDHijau, HIGH);
    digitalWrite(pinLEDMerah, LOW);

    Serial.println("STATUS KANDANG : NORMAL");
    Serial.println("Fan Module     : MATI");
    Serial.println("LED Hijau      : MENYALA");
    Serial.println("Kondisi kandang aman");
  }

  delay(2000);
}
