🏢 Aplikasi Data Karyawan — MFC C++

Aplikasi pengelolaan data karyawan berbasis GUI menggunakan bahasa pemrograman 
C++ dengan framework MFC (Microsoft Foundation Class) pada Visual Studio 2022.
Dikembangkan sebagai Proyek UAS Mata Kuliah Pemrograman Dasar 2,
Program Studi D4 Teknik Komputer, Politeknik Elektronika Negeri Surabaya (PENS) 2026.


👥 Tim Pengembang

| 1 | Muhammad Alamsyah | 3225600013 | Struktur Data & Input Karyawan |
| 2 | Mohammad Muzakki Romadhoni | 3225600022 | Pencarian & Penghapusan Data |


📋 Deskripsi Aplikasi

Aplikasi ini dikembangkan dari versi CLI (Command Line Interface) menjadi 
aplikasi GUI (Graphical User Interface) menggunakan framework MFC. 
Aplikasi mengelola data karyawan secara dinamis menggunakan struktur data 
**Singly Linked List** dan menerapkan konsep **OOP (Object Oriented Programming)**.


✨ Fitur Utama

- ➕ **Tambah Data Karyawan** — Input data karyawan baru dengan ID otomatis
- 📋 **Tampil Data Karyawan** — Menampilkan seluruh data dalam bentuk tabel
- 🔍 **Pencarian Data** — Cari karyawan berdasarkan ID atau nama
- ✏️ **Edit Data Karyawan** — Perbarui data karyawan yang sudah tersimpan
- 🗑️ **Hapus Data Karyawan** — Hapus data karyawan dengan konfirmasi
- 💰 **Slip Gaji** — Hitung dan tampilkan slip gaji dengan tunjangan jabatan dan potongan BPJS


🏗️ Struktur Data

Aplikasi menggunakan **Singly Linked List** dengan struktur sebagai berikut:
head → [id | nama | jabatan | divisi | gajiPokok | status | next] → ... → NULL

Setiap node menyimpan satu data karyawan dan pointer `next` 
yang menunjuk ke node berikutnya.


💻 Teknologi yang Digunakan

| No | Tools | Kegunaan |
| 1 | Visual Studio 2022 | IDE Pemrograman |
| 2 | C++ | Bahasa Pemrograman Utama |
| 3 | MFC (Microsoft Foundation Class) | Framework GUI |
| 4 | Git & GitHub | Version Control |


📁 Struktur Project

KaryawanMFC/
├── Header Files/
│   ├── Karyawan.h          # Struktur data & linked list
│   ├── KaryawanMFC.h       # Header aplikasi utama
│   ├── KaryawanMFCDlg.h    # Header dialog utama
│   └── Resource.h          # Definisi ID kontrol GUI
├── Source Files/
│   ├── KaryawanMFC.cpp     # File aplikasi utama
│   └── KaryawanMFCDlg.cpp  # Implementasi dialog & semua fitur
├── Resource Files/
│   └── KaryawanMFC.rc      # Desain tampilan dialog GUI
└── KaryawanMFC.sln         # File solution Visual Studio 2022


🚀 Cara Menjalankan

1. Clone repository ini
```bash
git clone https://github.com/alamsyhh/Aplikasi-Data-Karyawan.git
```
2. Buka file `KaryawanMFC.sln` menggunakan **Visual Studio 2022**
3. Pastikan **MFC** sudah terinstall di Visual Studio 2022
4. Build Project
5. Jalankan program

📊 Perhitungan Gaji

Aplikasi menghitung gaji bersih dengan rumus:
Tunjangan Jabatan:

Manager    : Gaji Pokok × 20%
Supervisor : Gaji Pokok × 15%
Staff      : Gaji Pokok × 10%
Lainnya    : Gaji Pokok × 5%

Potongan BPJS  : Gaji Pokok × 2%
Gaji Bersih = Gaji Pokok + Tunjangan - Potongan BPJS

---

## 📌 Pembagian Tugas

Anggota 1 — Struktur Data & Input Karyawan
- Membuat struktur node linked list
- Membuat fungsi tambah data karyawan
- Membuat input data karyawan
- Mengelola pointer head dan node

Anggota 2 — Pencarian & Penghapusan Data
- Membuat fitur pencarian karyawan berdasarkan ID/nama
- Membuat fitur hapus data karyawan
- Membuat validasi input data
- Membuat menu program (Message Map & DoDataExchange)

Anggota 3 — Tampilan & Pengolahan Data (Dikerjakan bersama Anggota 1 dan 2)
- Membuat tampilan daftar karyawan
- Membuat fitur edit data karyawan
- Membuat perhitungan gaji sederhana
- Membuat tampilan output program yang rapi dan informatif

📝 Mata Kuliah

> Pemrograman Dasar 2 (PD2)
> Dosen Pengampu: Dr. Ir. Sigit Wasista, M.Kom.  
> Program Studi Sarjana Terapan Teknik Komputer  
> Politeknik Elektronika Negeri Surabaya  
> Tahun Akademik 2025/2026
