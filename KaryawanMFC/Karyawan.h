#pragma once
#include <string>
using namespace std;

// ANGGOTA 1 - Struktur Data dan Input Karyawan
struct Karyawan {
    string id;
    string nama;
    string jabatan;
    string divisi;
    double gajiPokok = 0.0; 
    string status;
};

// ANGGOTA 1 - Struktur node linked list
struct Node {
    Karyawan data;
    Node* next = nullptr;  
};

class LinkedList {
public:
    Node* head;
    int   total;

    LinkedList() : head(nullptr), total(0) {}
    ~LinkedList() { clear(); }

    string generateID() {
        total++;
        string id = "KRY";
        if (total < 10)  id += "00" + to_string(total);
        else if (total < 100) id += "0" + to_string(total);
        else                  id += to_string(total);
        return id;
    }

    void tambah(Karyawan k) {
        Node* baru = new Node();
        baru->data = k;
        baru->next = nullptr;

        if (!head) {
            head = baru;
        }
        else {
            Node* temp = head;
            while (temp->next) temp = temp->next;
            temp->next = baru;
        }
    }

    void clear() {
        Node* temp = head;
        while (temp) {
            Node* next = temp->next;
            delete temp;
            temp = next;
        }
        head = nullptr;
        total = 0;
    }

    // ANGGOTA 2 - Pencarian dan Penghapusan Data
    Node* cariByID(const string& id) {
        Node* temp = head;
        while (temp) {
            if (temp->data.id == id) return temp;
            temp = temp->next;
        }
        return nullptr;
    }

    Node* cariByNama(const string& nama) {
        Node* temp = head;
        string low = nama;
        for (auto& c : low) c = tolower(c);
        while (temp) {
            string n = temp->data.nama;
            for (auto& c : n) c = tolower(c);
            if (n.find(low) != string::npos) return temp;
            temp = temp->next;
        }
        return nullptr;
    }

    bool hapus(const string& id) {
        Node* temp = head;
        Node* prev = nullptr;
        while (temp) {
            if (temp->data.id == id) {
                if (prev) prev->next = temp->next;
                else      head = temp->next;
                delete temp;
                return true;
            }
            prev = temp;
            temp = temp->next;
        }
        return false;
    }

    // ANGGOTA 3 - Tampilan dan Pengolahan Data
    static double hitungGajiBersih(const Karyawan& k) {
        double tunjangan = 0;
        if (k.jabatan == "Manager")    tunjangan = k.gajiPokok * 0.20;
        else if (k.jabatan == "Supervisor") tunjangan = k.gajiPokok * 0.15;
        else if (k.jabatan == "Staff")      tunjangan = k.gajiPokok * 0.10;
        else                                tunjangan = k.gajiPokok * 0.05;
        double potongan = k.gajiPokok * 0.02;
        return k.gajiPokok + tunjangan - potongan;
    }
};