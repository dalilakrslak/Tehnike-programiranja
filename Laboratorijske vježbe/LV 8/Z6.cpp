//TP 2021/2022: LV 8, Zadatak 6
#include <iostream>
#include <cmath>
template <typename Tip>
struct Cvor{
    Tip element;
    Cvor<Tip> *veza;
};
template <typename TipElemenata>
    Cvor<TipElemenata> *KreirajPovezanuListu(TipElemenata zavrsni){
        Cvor<TipElemenata> *pocetak=nullptr, *prethodni;
        for(;;){
            TipElemenata pom;
            std::cin>>pom;
            if(pom==zavrsni) break;
            Cvor<TipElemenata> *novi=new Cvor<TipElemenata>{pom,nullptr};
            if(!pocetak) pocetak=novi;
            else prethodni->veza=novi;
            prethodni=novi;
        }
        return pocetak;
    }
template <typename TipElemenata>
    int BrojElemenata(Cvor<TipElemenata> *pocetak){
        int br_el=0;
        for(auto pom=pocetak; pom!=nullptr; pom=pom->veza) br_el++;
        return br_el;
    }
template <typename TipElemenata>
    TipElemenata SumaElemenata(Cvor<TipElemenata> *pocetak){
        TipElemenata suma{};
        for(auto pom=pocetak; pom!=nullptr; pom=pom->veza) suma+=pom->element;
        return suma;
    }
template <typename TipElemenata>
    int BrojVecihOd(Cvor<TipElemenata> *pocetak, TipElemenata prag){
        int br_vecih=0;
        for(auto pom=pocetak; pom!=nullptr; pom=pom->veza) 
            if(pom->element>prag) br_vecih++;
        return br_vecih;
    }
template <typename TipElemenata>
    void UnistiListu(Cvor<TipElemenata> *pocetak){
        if(!pocetak) return;
        int pom=BrojElemenata(pocetak);
        while(pom>1){
            auto p=pocetak;
            for(int i=0; i<pom-1; i++) p=p->veza;
            delete p;
            pom--;
        }
        delete pocetak;
    }    
int main ()
{
    std::cout<<"Unesite slijed brojeva (0 za kraj): ";
    Cvor<double> *cvorici=KreirajPovezanuListu(0.);
    double srvr=SumaElemenata(cvorici)/BrojElemenata(cvorici);
    std::cout<<"U slijedu ima "<<BrojVecihOd(cvorici,srvr)<<" brojeva vecih od njihove aritmeticke sredine ";
    UnistiListu(cvorici);
	return 0;
}
