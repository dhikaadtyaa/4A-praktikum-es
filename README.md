# Smart Exhaust System Berbasis ESP8266

## Deskripsi Sistem

Smart Exhaust System merupakan sistem ventilasi otomatis berbasis Internet of Things (IoT) yang dirancang untuk memantau kondisi lingkungan ruangan berdasarkan suhu, kelembapan, dan kadar gas di udara.

Sistem menggunakan sensor DHT22 untuk membaca suhu dan kelembapan, serta sensor gas MQ untuk mendeteksi konsentrasi gas di lingkungan sekitar. Data yang diperoleh kemudian diproses oleh mikrokontroler ESP8266 NodeMCU untuk menentukan apakah kondisi ruangan masih aman atau memerlukan ventilasi tambahan.

Apabila suhu ruangan melebihi 32°C atau kadar gas melebihi nilai ambang batas yang telah ditentukan, sistem akan secara otomatis mengaktifkan kipas exhaust melalui Fan Module L9110. Selain itu, LED indikator akan menyala sebagai tanda bahwa kondisi ruangan memerlukan perhatian.

Seluruh informasi sensor dan status sistem ditampilkan melalui Serial Monitor sehingga memudahkan proses monitoring dan pengujian.

---

## Tujuan Sistem

* Memantau suhu ruangan secara real-time.
* Memantau kelembapan udara.
* Mendeteksi peningkatan kadar gas di lingkungan.
* Mengaktifkan ventilasi secara otomatis ketika kondisi tidak aman.
* Memberikan indikator visual menggunakan LED.
* Mengurangi kebutuhan pemantauan secara manual.

---

## Komponen yang Digunakan

| No | Komponen         | Fungsi                              |
| -- | ---------------- | ----------------------------------- |
| 1  | ESP8266 NodeMCU  | Mikrokontroler utama                |
| 2  | Sensor DHT22     | Mengukur suhu dan kelembapan udara  |
| 3  | Sensor Gas MQ    | Mendeteksi kadar gas                |
| 4  | Fan Module L9110 | Driver untuk mengendalikan kipas DC |
| 5  | Kipas DC         | Exhaust fan otomatis                |
| 6  | LED              | Indikator kondisi ruangan           |
| 7  | Kabel Jumper     | Penghubung antar komponen           |
| 8  | Breadboard       | Media perakitan rangkaian           |
| 9 | Catu Daya 5V     | Sumber daya sistem                  |

---

## Fitur Utama

### Monitoring Suhu

Sensor DHT22 membaca suhu ruangan secara real-time.

### Monitoring Kelembapan

Kelembapan udara dipantau secara berkala untuk mengetahui kondisi lingkungan.

### Monitoring Kadar Gas

Sensor MQ membaca konsentrasi gas yang terdapat di udara.

### Kontrol Otomatis Exhaust Fan

Kipas akan menyala secara otomatis ketika:

* Suhu ≥ 32°C
* Nilai sensor gas ≥ 400

### LED Indikator

LED akan menyala bersamaan dengan kipas ketika kondisi ruangan melebihi batas aman.

### Monitoring Serial

Semua data sensor dan status aktuator ditampilkan pada Serial Monitor.

### Penanganan Error Sensor

Program mampu mendeteksi kegagalan pembacaan sensor DHT22 dan menampilkan pesan kesalahan.

---

## Cara Kerja Sistem

1. Sistem dinyalakan dan melakukan inisialisasi sensor.
2. Sensor DHT22 membaca suhu dan kelembapan.
3. Sensor MQ membaca kadar gas.
4. Data ditampilkan pada Serial Monitor.
5. ESP8266 membandingkan hasil pembacaan dengan nilai ambang batas.
6. Jika suhu ≥ 32°C atau kadar gas ≥ 400:

   * Kipas menyala.
   * LED indikator menyala.
7. Jika kondisi masih aman:

   * Kipas mati.
   * LED indikator mati.
8. Proses monitoring diulang setiap 2 detik.

---

---

## Konfigurasi Pin

### Koneksi ESP8266 NodeMCU

| Pin ESP8266 | Terhubung ke          | Fungsi                      |
| ----------- | --------------------- | --------------------------- |
| D4          | DATA DHT22            | Membaca suhu dan kelembapan |
| A0          | AO Sensor MQ          | Membaca kadar gas           |
| D5          | INA Fan Module L9110  | Kontrol kipas               |
| D6          | Anoda LED (+)         | Indikator kondisi           |
| 3V3         | VCC DHT22             | Catu daya DHT22             |
| VIN         | VCC Sensor MQ         | Catu daya sensor MQ         |
| VIN         | VCC Fan Module L9110  | Catu daya driver kipas      |
| GND         | Semua Ground Komponen | Ground bersama              |

---

### Detail Koneksi DHT22

| Pin DHT22 | Terhubung ke |
| --------- | ------------ |
| VCC       | 3V3 ESP8266  |
| DATA      | D4 ESP8266   |
| GND       | GND ESP8266  |

---

### Detail Koneksi Sensor MQ

| Pin MQ | Terhubung ke |
| ------ | ------------ |
| VCC    | VIN ESP8266  |
| GND    | GND ESP8266  |
| AO     | A0 ESP8266   |

---

### Detail Koneksi Fan Module L9110

| Pin L9110 | Terhubung ke        |
| --------- | ------------------- |
| VCC       | VIN ESP8266         |
| GND       | GND ESP8266         |
| INA       | D5 ESP8266          |
| INB       | Tidak digunakan     |


---

### Detail Koneksi LED

| Pin LED    | Terhubung ke             |
| ---------- | ------------------------ |
| Anoda (+)  | D6 melalui resistor 220Ω |
| Katoda (-) | GND ESP8266              |

---

## Konstanta Sistem

```cpp
const float BATAS_SUHU = 32.0;
const int BATAS_GAS = 400;
```

Keterangan:

* BATAS_SUHU digunakan sebagai batas maksimum suhu ruangan.
* BATAS_GAS digunakan sebagai batas maksimum kadar gas yang dianggap aman.

---

## Contoh Output Serial Monitor

### Kondisi Aman

```text
---------------------------------
Suhu       : 29.8 C
Kelembapan : 65 %
Kadar Gas  : 250

STATUS     : KIPAS MATI
STATUS LED : MATI

Kondisi ruangan aman
```

### Kondisi Tidak Aman

```text
---------------------------------
Suhu       : 33.5 C
Kelembapan : 72 %
Kadar Gas  : 450

STATUS     : KIPAS MENYALA
STATUS LED : MENYALA

PERINGATAN : Suhu/Gas melebihi batas
```

---

## Struktur Program

Program terdiri dari beberapa bagian utama:

### Inisialisasi Sensor

Mengaktifkan sensor DHT22 dan konfigurasi pin input/output.

### Pembacaan Sensor

Membaca suhu, kelembapan, dan kadar gas secara berkala.

### Pengambilan Keputusan

Membandingkan hasil pembacaan sensor dengan nilai ambang batas.

### Kontrol Aktuator

Mengendalikan kipas dan LED berdasarkan kondisi ruangan.

### Monitoring

Menampilkan seluruh informasi sistem pada Serial Monitor.

---

## Author

Proyek Smart Exhaust System dibuat sebagai implementasi sistem ventilasi otomatis berbasis ESP8266 untuk monitoring kualitas lingkungan secara real-time.
