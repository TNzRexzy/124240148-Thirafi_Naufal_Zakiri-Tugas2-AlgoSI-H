#include <iostream>
#include <string>
using namespace std;

// Struct buat nyimpen data pasien, ada nomor antrian, nama, keluhan, dan pointer kiri-kanan
struct Pasien
{
    int nomor;
    string nama;
    string keluhan;
    Pasien *prev;
    Pasien *next;
};

// Penanda antrian paling depan dan paling belakang
Pasien *head = nullptr;
Pasien *tail = nullptr;

// Fungsi buat bikin node pasien baru
// Ini kayak nge-create 1 orang pasien lengkap datanya
Pasien *buatPasien(int nomor, string nama, string keluhan)
{
    Pasien *baru = new Pasien;
    baru->nomor = nomor;
    baru->nama = nama;
    baru->keluhan = keluhan;
    baru->prev = nullptr;
    baru->next = nullptr;
    return baru;
}

// Fungsi buat masukin pasien ke antrian, otomatis ditaro urut berdasarkan nomor antrian
// Jadi kagak asal nambah di depan/belakang doang
void tambahPasien(int nomor, string nama, string keluhan)
{
    Pasien *baru = buatPasien(nomor, nama, keluhan);

    if (!head)
    {
        // Kalo antrian masih kosong, ya langsung jadi kepala dan buntut
        head = tail = baru;
    }
    else if (nomor < head->nomor)
    {
        // Kalo nomornya paling kecil, masukin di depan
        baru->next = head;
        head->prev = baru;
        head = baru;
    }
    else
    {
        // Cari posisi yang pas buat nyisipin di tengah-tengah
        Pasien *temp = head;
        while (temp->next && temp->next->nomor < nomor)
        {
            temp = temp->next;
        }
        // Masukin node baru ke posisi yang bener
        baru->next = temp->next;
        baru->prev = temp;
        if (temp->next)
            temp->next->prev = baru;
        else
            tail = baru; // Kalo ternyata dia paling akhir
        temp->next = baru;
    }
    cout << "Pasien berhasil ditambahkan ke daftar.\n";
}

// Buat nampilin antrian dari awal sampe akhir
// Cocok buat lihat urutan antrian yang bener
void tampilDepan()
{
    if (!head)
    {
        cout << "Antrian kosong.\n";
        return;
    }

    cout << "\nDaftar Antrian (Dari Awal)\n";
    cout << "============================\n";
    Pasien *temp = head;
    while (temp)
    {
        cout << "No Antrian : " << temp->nomor << endl;
        cout << "Nama       : " << temp->nama << endl;
        cout << "Keluhan    : " << temp->keluhan << endl;
        cout << "----------------------------\n";
        temp = temp->next;
    }
}

// Buat nampilin antrian dari belakang ke depan
// Misalnya buat ngecek siapa yang paling baru daftar
void tampilBelakang()
{
    if (!tail)
    {
        cout << "Antrian kosong.\n";
        return;
    }

    cout << "\nDaftar Antrian (Dari Akhir)\n";
    cout << "============================\n";
    Pasien *temp = tail;
    while (temp)
    {
        cout << "No Antrian : " << temp->nomor << endl;
        cout << "Nama       : " << temp->nama << endl;
        cout << "Keluhan    : " << temp->keluhan << endl;
        cout << "----------------------------\n";
        temp = temp->prev;
    }
}

// Buat nyari pasien berdasarkan nomor antriannya
// Jadi kalo pengen ngecek data seseorang, tinggal masukin nomornya
void cariPasien(int nomor)
{
    Pasien *temp = head;
    while (temp)
    {
        if (temp->nomor == nomor)
        {
            cout << "\nPasien Ditemukan:\n";
            cout << "No Antrian : " << temp->nomor << endl;
            cout << "Nama       : " << temp->nama << endl;
            cout << "Keluhan    : " << temp->keluhan << endl;
            return;
        }
        temp = temp->next;
    }
    // Kalo gak ketemu
    cout << "Pasien dengan nomor antrian " << nomor << " tidak ditemukan.\n";
}

// Fungsi buat ngapus pasien berdasarkan nomor antrian
// Biasanya dipake kalo pasien batal atau udah selesai diperiksa
void hapusPasien(int nomor)
{
    if (!head)
    {
        cout << "Antrian kosong.\n";
        return;
    }

    Pasien *temp = head;
    while (temp && temp->nomor != nomor)
    {
        temp = temp->next;
    }

    if (!temp)
    {
        cout << "Pasien tidak ditemukan.\n";
        return;
    }

    // Update pointer kanan-kiri biar node-nya lepas
    if (temp == head)
        head = temp->next;
    if (temp == tail)
        tail = temp->prev;
    if (temp->prev)
        temp->prev->next = temp->next;
    if (temp->next)
        temp->next->prev = temp->prev;

    delete temp;
    cout << "Data pasien berhasil dihapus.\n";
}

// Ini menu utama, isinya pilihan yang bisa dipilih user
void tampilMenu()
{
    cout << "\n=== MENU ANTRIAN PASIEN KLINIK SEHAT SELALU ===\n";
    cout << "1. Tambah Data Pasien\n";
    cout << "2. Tampilkan Antrian dari Awal\n";
    cout << "3. Tampilkan Antrian dari Akhir\n";
    cout << "4. Cari Data Pasien\n";
    cout << "5. Hapus Data Pasien\n";
    cout << "6. Keluar\n";
}

int main()
{
    int pilihan, nomor;
    string nama, keluhan;

    // Data default biar gak kosong pas awal-awal
    // Udah langsung ada namaku ni, keluhannya pusing ngoding aokwoakwokwo
    tambahPasien(2, "Nopal", "Pusing Ngoding");

    do
    {
        tampilMenu();
        cout << "Pilih menu : ";
        cin >> pilihan;
        cin.ignore(); // biar getline nggak diskip

        switch (pilihan)
        {
        case 1:
            cout << "Masukkan No Antrian : ";
            cin >> nomor;
            cin.ignore();
            cout << "Masukkan Nama Pasien: ";
            getline(cin, nama);
            cout << "Masukkan Keluhan     : ";
            getline(cin, keluhan);
            tambahPasien(nomor, nama, keluhan);
            break;

        case 2:
            tampilDepan();
            break;

        case 3:
            tampilBelakang();
            break;

        case 4:
            cout << "Masukkan No Antrian yang dicari: ";
            cin >> nomor;
            cariPasien(nomor);
            break;

        case 5:
            cout << "Masukkan No Antrian yang ingin dihapus: ";
            cin >> nomor;
            hapusPasien(nomor);
            break;

        case 6:
            cout << "Terima kasih!\n";
            break;

        default:
            cout << "Pilihan tidak valid.\n";
        }

    } while (pilihan != 6);

    return 0;
}
