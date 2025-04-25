
# Nama: Teuku Hafiz Izham
# NPM : 2308107010056

# Program Pengujian Algoritma Sorting

Program ini digunakan untuk menguji performa berbagai algoritma sorting pada data integer dan string.



## Cara Menjalankan Program

1. Pertama, jalankan program generator data:
   
      gcc -o data_generator data_generator.c
   
   Program ini akan membuat dua file:
   - `data_angka.txt`: berisi 2.000.000 angka acak
   - `data_kata.txt`: berisi 2.000.000 kata acak

2. Kemudian, jalankan program pengujian sorting:
   
      gcc -o sorting_program main.c -lpsapi
   ```
   Program ini akan:
   - Menguji 6 algoritma sorting (Bubble, Selection, Insertion, Merge, Quick, Shell)
   - Mengukur waktu eksekusi dan penggunaan memori
   - Menyimpan hasil di file `sorting_result.csv`

## Format Hasil

Hasil pengujian akan disimpan dalam file `sorting_result.csv` dengan format:
```

## Catatan

- Program menggunakan library `psapi.h` untuk mengukur penggunaan memori
- Pastikan semua file source code berada dalam satu direktori yang sama
- Jika terjadi error saat kompilasi, pastikan GCC sudah terinstal dengan benar