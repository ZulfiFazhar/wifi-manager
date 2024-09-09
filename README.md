# Wi-Fi Manager ESP32

Project ini memungkinkan ESP32 untuk beroperasi dalam dua mode: Access Point (AP) dan Station (Wi-Fi). Dalam mode AP, ESP32 membuat jaringan Wi-Fi yang dapat diakses oleh perangkat lain untuk mengonfigurasi kredensial Wi-Fi. Dalam mode Station, ESP32 akan terhubung ke jaringan Wi-Fi yang telah dikonfigurasi.

## Struktur Proyek

Proyek ini dibagi menjadi beberapa file:

- `wifi_manager.h` - Header file yang berisi deklarasi fungsi dan variabel global.
- `wifi_manager.cpp` - File implementasi fungsi yang dideklarasikan dalam header.
- `main.ino` - File sketsa utama Arduino yang menyertakan header dan memanggil fungsi-fungsi yang didefinisikan dalam file `.cpp`.

## Deskripsi File

### `wifi_manager.h`

File header ini mendeklarasikan fungsi dan variabel yang digunakan untuk mengelola Wi-Fi.

### `wifi_manager.cpp`

File implementasi ini berisi definisi fungsi-fungsi untuk mengatur mode AP, mode Station, serta menyimpan dan memuat kredensial Wi-Fi dari EEPROM.

### `main.ino`

File sketsa utama Arduino ini mengatur mode ESP32 berdasarkan input pengguna dan memulai server web untuk memungkinkan konfigurasi kredensial Wi-Fi.

## Penjelasan Mode

- **Mode Access Point (AP)**

  - ESP32 akan membuat jaringan Wi-Fi dengan SSID "ESP32_AP" dan kata sandi "esp32mantap".
  - Hubungkan perangkat ke jaringan ini dan buka alamat IP ESP32 di browser untuk mengonfigurasi SSID dan kata sandi Wi-Fi.

- **Mode Station**
  - ESP32 akan mencoba terhubung ke jaringan Wi-Fi dengan SSID dan kata sandi yang telah dikonfigurasi sebelumnya.
  - Jika berhasil terhubung, ESP32 akan mencetak alamat IP ke serial monitor.

<!-- ## Lisensi

Proyek ini dilisensikan di bawah [MIT License](https://opensource.org/licenses/MIT). -->

<!-- ## Kontak

Jika Anda memiliki pertanyaan atau umpan balik, silakan hubungi [email@example.com](mailto:email@example.com). -->
