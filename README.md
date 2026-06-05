# Smart Exhaust System Berbasis ESP8266

## Deskripsi Sistem

Smart Exhaust System merupakan sistem ventilasi otomatis yang dirancang untuk memantau kondisi lingkungan ruangan berdasarkan suhu, kelembapan, dan kadar gas di udara. Sistem menggunakan sensor DHT22 untuk membaca suhu dan kelembapan, serta sensor gas MQ untuk mendeteksi konsentrasi gas di lingkungan sekitar.

Data yang diperoleh dari sensor akan diproses oleh mikrokontroler ESP8266. Apabila suhu ruangan melebihi 32°C atau kadar gas melebihi nilai ambang batas yang telah ditentukan, sistem akan secara otomatis mengaktifkan kipas exhaust untuk membantu menurunkan suhu dan membuang udara yang terkontaminasi. Sebaliknya, jika kondisi ruangan masih dalam batas aman, kipas akan tetap dalam keadaan mati.

Selain itu, seluruh data sensor dan status sistem ditampilkan melalui Serial Monitor sehingga memudahkan proses pemantauan dan pengujian.

---

## Komponen yang Digunakan

| No | Komponen                                 | Fungsi                                                                     |
| -- | ---------------------------------------- | -------------------------------------------------------------------------- |
| 1  | ESP8266 NodeMCU                          | Mikrokontroler utama untuk mengolah data sensor dan mengendalikan aktuator |
| 2  | Sensor DHT22                             | Mengukur suhu dan kelembapan udara                                         |
| 3  | Sensor Gas MQ (MQ-2/MQ-135 atau sejenis) | Mendeteksi kadar gas di lingkungan                                         |
| 4  | Modul Relay (opsional)                   | Menghubungkan mikrokontroler dengan kipas berdaya lebih tinggi             |
| 5  | Kipas Exhaust DC                         | Mengeluarkan udara panas atau tercemar dari ruangan                        |
| 6  | Kabel Jumper                             | Penghubung antar komponen                                                  |
| 7  | Catu Daya                                | Menyuplai daya ke sistem                                                   |

---

## Fitur Utama

### Monitoring Suhu

Sistem membaca suhu ruangan secara real-time menggunakan sensor DHT22.

### Monitoring Kelembapan

Kelembapan udara dipantau secara berkala dan ditampilkan pada Serial Monitor.

### Deteksi Kadar Gas

Sensor MQ digunakan untuk mengukur tingkat konsentrasi gas di lingkungan sekitar.

### Kontrol Otomatis Kipas

Kipas akan menyala secara otomatis apabila:

* Suhu ≥ 32°C
* Nilai gas ≥ 400

### Informasi Status Sistem

Kondisi ruangan dan status kipas ditampilkan secara langsung melalui Serial Monitor.

### Sistem Keamanan Sensor

Program akan mendeteksi kegagalan pembacaan sensor DHT22 dan menampilkan pesan error apabila terjadi gangguan.

---

## Logika Kerja Sistem

1. Sistem dinyalakan dan melakukan inisialisasi sensor.
2. Sensor DHT22 membaca suhu dan kelembapan udara.
3. Sensor MQ membaca kadar gas di lingkungan.
4. Data sensor ditampilkan pada Serial Monitor.
5. Sistem membandingkan hasil pembacaan dengan nilai ambang batas.
6. Jika suhu atau kadar gas melebihi batas yang ditentukan, kipas exhaust akan menyala.
7. Jika kondisi masih aman, kipas tetap mati.
8. Proses monitoring diulang setiap 2 detik.

---

## Konfigurasi Pin

| Komponen                      | Pin ESP8266 |
| ----------------------------- | ----------- |
| DHT22 Data                    | D4          |
| Sensor Gas MQ (Analog Output) | A0          |
| Kipas Exhaust                 | D5          |

### Konstanta Sistem

```cpp
const float BATAS_SUHU = 32.0;
const int BATAS_GAS = 400;
```

Keterangan:

* BATAS_SUHU = 32°C digunakan sebagai batas maksimum suhu ruangan.
* BATAS_GAS = 400 digunakan sebagai batas maksimum kadar gas yang dianggap aman.

---

## Output Serial Monitor

Contoh tampilan pada Serial Monitor:

```text
---------------------------------
Suhu       : 33.5 C
Kelembapan : 72 %
Kadar Gas  : 450
STATUS     : KIPAS MENYALA
PERINGATAN : Suhu/Gas melebihi batas
```

atau

```text
---------------------------------
Suhu       : 29.8 C
Kelembapan : 65 %
Kadar Gas  : 250
STATUS     : KIPAS MATI
Kondisi ruangan aman
```

---


