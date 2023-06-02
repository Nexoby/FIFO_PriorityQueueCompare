#include <iostream>
#include <ctime>
using namespace std;

int topBeklenecekSure = 0;
int topTamamSure = 0;

struct Kisi {
    int numara;
    int beklenecekSure;
    int tamamSure;
    Kisi* sonraki;
};

Kisi* son = new Kisi;
int kuyrukboyutuList = 0;

struct KisiDizi {
    int numara;
    int beklenecekSure;
    int tamamSure;
};

int kuyrukBoyutuDizi = 0;
KisiDizi kuyruk[100];

void kuyrugaEkleList(int numara, int beklenecekSure, int tamamSure) {
    Kisi* yeni = new Kisi;
    yeni->numara = numara;
    yeni->beklenecekSure = beklenecekSure;
    yeni->tamamSure = tamamSure;
    if (kuyrukboyutuList == 0) {
        yeni->sonraki = NULL;
    }
    else {
        yeni->sonraki = son;
    }
    son = yeni;
    kuyrukboyutuList++;
}

void kuyruktanCikarList() {
    if (kuyrukboyutuList > 0) {
        Kisi* ptr = son;
        for (int i = 1; i < kuyrukboyutuList; i++) {
            ptr = ptr->sonraki;
        }
        topBeklenecekSure += ptr->beklenecekSure;
        ptr->tamamSure = topBeklenecekSure;
        topTamamSure += ptr->tamamSure;
        cout << "Sira: " << ptr->numara << " Bekleme Suresi: " << ptr->beklenecekSure << " Tamamlama Suresi: " << ptr->tamamSure << endl;
        kuyrukboyutuList--;
    }
    else {
        cout << "Kuyruk zaten bos" << endl;
    }
}

void kuyrugaEkleDizi(int numara, int beklenecekSure, int tamamSure) {
    if (kuyrukBoyutuDizi == 0) {
        kuyruk[0].numara = numara;
        kuyruk[0].beklenecekSure = beklenecekSure;
        kuyruk[0].tamamSure = tamamSure;
    }
    else {
        int i = kuyrukBoyutuDizi - 1;
        while (i >= 0 && beklenecekSure < kuyruk[i].beklenecekSure) {
            kuyruk[i + 1] = kuyruk[i];
            i--;
        }
        kuyruk[i + 1].numara = numara;
        kuyruk[i + 1].beklenecekSure = beklenecekSure;
        kuyruk[i + 1].tamamSure = tamamSure;
    }
    kuyrukBoyutuDizi++;
}

void kuyruktanCikarDizi(int i) {
    if (kuyrukBoyutuDizi > 0) {
        topBeklenecekSure += kuyruk[i].beklenecekSure;
        kuyruk[i].tamamSure = topBeklenecekSure;
        topTamamSure += kuyruk[i].tamamSure;
        cout << "Sira: " << kuyruk[i].numara << " Bekleme Suresi: " << kuyruk[i].beklenecekSure << " Tamamlama Suresi: " << kuyruk[i].tamamSure << endl;
        kuyrukBoyutuDizi--;
    }
    else {
        cout << "Kuyruk zaten bos" << endl;
    }
}

int main() {
    srand(time(0));
    int N;
    cout << "Kuyrukta kac kisi olacak: ";
    cin >> N;

    for (int i = 0; i < N; ++i) {
        int id = i + 1;
        int beklenecekSure = rand() % 271 + 30;
        int tamamSure = 0;
        kuyrugaEkleList(id, beklenecekSure, tamamSure);
        kuyrugaEkleDizi(id, beklenecekSure, tamamSure);
    }

    cout << "\n" << "FIFO Kuyruk - Liste" << endl;
    for (int i = 0; i < N; ++i) {
        kuyruktanCikarList();
    };
    cout << "Ortalama islem tamamlanma suresi: " << topTamamSure / N << endl;

    topBeklenecekSure = 0;
    topTamamSure = 0;

    cout << "\n" << "Oncelikli Kuyruk - Dizi" << endl;
    for (int i = 0; i < N; ++i) {
        kuyruktanCikarDizi(i);
    };
    cout << "Ortalama islem tamamlanma suresi: " << topTamamSure / N << endl;


    cout << "\n" << "FIFO kuyruga gore daha fazla sira bekleyenler" << endl;
    Kisi* current = son;
    while (current != NULL) {
        for (int i = 0; i < N; i++) {
            if (current->numara == kuyruk[i].numara && current->tamamSure < kuyruk[i].tamamSure) {
                cout << "Sira: " << kuyruk[i].numara << " Bekleme Suresi: " << kuyruk[i].beklenecekSure << " Tamamlama Suresi: " << kuyruk[i].tamamSure << "\t FIFO Tamamlama Suresi: " << current->tamamSure << endl;
            }
        }
        current = current->sonraki;
    }

    return 0;
}