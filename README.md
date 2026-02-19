# Mikrodenetleyiciler İçin Dinamik Tensör ve Quantization Tasarımı

Bu proje, RAM kapasitesi kısıtlı olan gömülü sistem cihazlarında (Arduino, ESP32 vb.) yapay zeka modellerini verimli çalıştırabilmek için geliştirilmiş özel bir veri yapısıdır.

## 📌 Projenin Amacı
Gömülü sistemlerde 32-bit Float veriler belleği hızla doldurur. Bu projede:
- **Union Yapısı:** Bellek adresini ortak kullanarak Float32, Float16 ve Int8 verileri yöneten dinamik bir yapı kurulmuştur.
- **Quantization (Nicemleme):** Bellek kullanımı %75 oranında optimize edilmiştir.

## 🛠 Teknik Özellikler
- **Dinamik Tip Yönetimi:** Tek bir veri yapısı içinde duruma göre veri tipi değiştirilebilir.
- **Hassasiyet:** Quantization işlemi `q = round(f / scale + zero_point)` formülüyle uygulanmıştır.

## 🚀 Kullanım
`main.cpp` dosyası derlenerek terminal üzerinden bellek tasarrufu analizi gözlemlenebilir.
