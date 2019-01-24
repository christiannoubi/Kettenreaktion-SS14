#include <iostream>
#include <vector>
using namespace std;
class Loescher;
struct Knoten {
    virtual void anhaengen(Loescher& loescher, int n, int tiefe) =0;
    virtual ~Knoten() {};
};
class Loescher {
private:
    vector<Knoten*> knoten;
public:
    void hinzufuegen(Knoten* k) {
       knoten.push_back(k);
    }
    void loeschen() {
        int i = 0;
        for (Knoten* k: knoten) {
            delete k;
            i++;
        }
        knoten.erase(knoten.begin(), knoten.begin()+i);
    }
    bool istLeer() const {
        return knoten.empty();
    }
};
class KnotenImpl : public Knoten {

private:
    vector<Knoten*> nachfolger;
    Loescher& loescher;
    int id;
    static int objektZaehler;

public:
    KnotenImpl(Loescher& loescher, KnotenImpl* vorgaenger = nullptr) : loescher(loescher) {
         id =++objektZaehler;
    if(vorgaenger!=nullptr) {
    vorgaenger->nachfolger.push_back(this);
    }
}
~KnotenImpl() {
    objektZaehler--; cout << id << "";
    for(Knoten* k : nachfolger) {
       loescher.hinzufuegen(k);
    }
}
void anhaengen(Loescher& loescher, int n, int tiefe) {
    if(tiefe>0) {
    for(int i=0; i<n; i++) {
            Knoten* k = new KnotenImpl(loescher,this);
              k->anhaengen(loescher,n,tiefe-1);
            }
        }
    }
};
int KnotenImpl:: objektZaehler = 0;
int main() {
    Loescher loescher;
    Knoten* knoten = new KnotenImpl(loescher);
    loescher.hinzufuegen(knoten);
    const int ANZAHL_NACHFOLGER = 3; const int TIEFE = 2;
    knoten->anhaengen(loescher,ANZAHL_NACHFOLGER,TIEFE);
    while(!loescher.istLeer()) {
        loescher.loeschen();
        cout << endl;
    }
}
