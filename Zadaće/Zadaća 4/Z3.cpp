//TP 2021/2022: Zadaća 4, Zadatak 3
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <string>
#include <iomanip>
#include <algorithm>
class Polazak{
    std::string odrediste;
    int broj_voza, broj_perona;
    bool brzi_voz;
    int sat_polaska, minute_polaska, trajanje_voznje, kasnjenje;
public:
    Polazak(std::string odrediste, int broj_voza, int broj_perona, bool brzi_voz, int sat_polaska, int minute_polaska, int trajanje_voznje): kasnjenje(0){
        if(broj_voza<0 || broj_voza>99999) throw std::domain_error("Neispravan broj voza!");
        if(broj_perona<1 || broj_perona>6) throw std::domain_error("Neispravan broj perona!");
        if(sat_polaska<0 || sat_polaska>23) throw std::domain_error("Neispravan sat polaska");
        if(minute_polaska<0 || minute_polaska>59) throw std::domain_error("Neispravne minute polaska");
        if(trajanje_voznje<0) throw std::domain_error("Neispravno trajanje voznje");
        Polazak::odrediste=odrediste; Polazak::broj_voza=broj_voza; Polazak::broj_perona=broj_perona; Polazak::brzi_voz=brzi_voz; Polazak::sat_polaska=sat_polaska; Polazak::minute_polaska=minute_polaska; Polazak::trajanje_voznje=trajanje_voznje;
    }
    void PostaviKasnjenje(int kasnjenje){
        Polazak::kasnjenje=kasnjenje;
    }
    bool DaLiKasni() const{
        return kasnjenje!=0;
    }
    int DajTrajanjeVoznje() const{
        return trajanje_voznje;
    }
    std::pair<int, int> DajOcekivanoVrijemePolaska() const{
        std::pair<int, int> vrati;
        vrati.first=sat_polaska;
        vrati.second=minute_polaska;
        if(kasnjenje!=0){
            vrati.second+=kasnjenje;
            while(vrati.second>59){
                vrati.second-=60;
                vrati.first++;
            }
            while(vrati.first>23) vrati.first-=24;
        }
        return vrati;
    }
    std::pair<int, int> DajOcekivanoVrijemeDolaska() const{
        std::pair<int, int> vrati;
        vrati.first=sat_polaska;
        vrati.second=minute_polaska;
        if(kasnjenje!=0){
            vrati.second+=kasnjenje;
            while(vrati.second>59){
                vrati.second-=60;
                vrati.first++;
            }
            while(vrati.first>23) vrati.first-=24;
        }
        vrati.second+=trajanje_voznje;
        while(vrati.second>59){
            vrati.second-=60;
            vrati.first++;
        }
        while(vrati.first>23) vrati.first-=24;
        return vrati;
    }
    void Ispisi() const{
        if(kasnjenje==0){
            if(brzi_voz) std::cout<<"Brzi";
            else std::cout<<"Lokalni";
            std::cout<<" voz broj "<<broj_voza<<", odrediste "<<odrediste<<", polazi sa perona "<<broj_perona<<" u "<<std::setw(2)<<std::setfill('0')<<sat_polaska<<":"<<std::setw(2)<<minute_polaska<<", a na odrediste stize u "<<std::setw(2)<<DajOcekivanoVrijemeDolaska().first<<":"<<std::setw(2)<<DajOcekivanoVrijemeDolaska().second<<". Putnicima i voznom osoblju zelimo ugodno putovanje.";
        }
        else{
            if(brzi_voz) std::cout<<"Brzi";
            else std::cout<<"Lokalni";
            std::cout<<" voz broj "<<broj_voza<<", odrediste "<<odrediste<<", sa predvidjenim vremenom polaska u "<<std::setw(2)<<std::setfill('0')<<sat_polaska<<":"<<std::setw(2)<<minute_polaska<<", kasni oko "<<kasnjenje<<" minuta, te ce poci oko "<<std::setw(2)<<DajOcekivanoVrijemePolaska().first<<":"<<std::setw(2)<<DajOcekivanoVrijemePolaska().second;
            std::cout<<". Ocekuje se da voz stigne na odrediste oko "<<std::setw(2)<<DajOcekivanoVrijemeDolaska().first<<":"<<std::setw(2)<<DajOcekivanoVrijemeDolaska().second<<". Izvinjavamo se putnicima zbog eventualnih neugodnosti.";
        }
    }
};
class RedVoznje{
    Polazak **polasci;
    int max_polazaka;
    int broj_polazaka;
public:
    explicit RedVoznje(int max_broj_polazaka): max_polazaka(max_broj_polazaka), broj_polazaka(0), polasci(new Polazak*[max_broj_polazaka]{}){}
    RedVoznje(std::initializer_list<Polazak> lista_polazaka): max_polazaka(lista_polazaka.size()), broj_polazaka(lista_polazaka.size()){
        polasci=new Polazak*[lista_polazaka.size()]{};
        auto pocetak=lista_polazaka.begin();
        for(int i=0; i<lista_polazaka.size(); i++){
            try{
                polasci[i]=new Polazak(*pocetak);
                pocetak++;
            }
            catch(...){
                for(int i=0; i<lista_polazaka.size(); i++){
                    delete polasci[i];
                }
                delete[] polasci;
                throw;
            }
        }
    }
    ~RedVoznje(){
        for(int i=0; i<broj_polazaka; i++) delete polasci[i];
        delete[] polasci;
    }
    RedVoznje(const RedVoznje &red_voznje): max_polazaka(red_voznje.max_polazaka), broj_polazaka(red_voznje.broj_polazaka){
        polasci=new Polazak*[max_polazaka]{};
        try{
            for(int i=0; i<broj_polazaka; i++) polasci[i]=new Polazak(*red_voznje.polasci[i]);
        }
        catch(...){
            for(int i=0; i<broj_polazaka; i++) delete polasci[i];
            delete[] polasci;
            throw;
        }
    }
    RedVoznje(RedVoznje &&red_voznje): max_polazaka(red_voznje.max_polazaka), broj_polazaka(red_voznje.broj_polazaka),polasci(red_voznje.polasci){
        red_voznje.polasci=nullptr; red_voznje.broj_polazaka=0;
    }
    RedVoznje &operator =(const RedVoznje &red_voznje){
        if(&red_voznje!=this){
            Polazak **pom=new Polazak*[red_voznje.max_polazaka]{};
            try{
                for(int i=0; i<red_voznje.broj_polazaka; i++){
                    pom[i]=new Polazak(*red_voznje.polasci[i]);
                }
            }
            catch(...){
                for(int i=0; i<red_voznje.broj_polazaka; i++) delete pom[i];
                delete [] pom;
                throw;
            }
            for(int i=0; i<broj_polazaka; i++) delete polasci[i];
            delete[] polasci;
            broj_polazaka=red_voznje.broj_polazaka;
            max_polazaka=red_voznje.max_polazaka;
            polasci=pom;
        }
        return *this;
    }
    RedVoznje &operator =(RedVoznje &&red_voznje){
        if(&red_voznje!=this){
            std::swap(broj_polazaka, red_voznje.broj_polazaka);
            std::swap(max_polazaka, red_voznje.max_polazaka);
            std::swap(polasci, red_voznje.polasci);
        }
        return *this;
    }
    void RegistrirajPolazak(std::string odrediste, int broj_voza, bool brzi_voz, int broj_perona, int sat_polaska, int minute_polaska, int trajanje_voznje){
        if(broj_polazaka>=max_polazaka) throw std::range_error("Dostignut maksimalni broj polazaka");
        polasci[broj_polazaka++]= new Polazak(odrediste,broj_voza, broj_perona, brzi_voz, sat_polaska, minute_polaska, trajanje_voznje);
    }
    void RegistrirajPolazak(Polazak *polazak){
        if(broj_polazaka>=max_polazaka) throw std::range_error("Dostignut maksimalni broj polazaka");
        polasci[broj_polazaka++]=polazak;
    }
    int DajBrojPolazaka() const{
        return broj_polazaka;
    }
    int DajBrojPolazakaKojiKasne() const{
        int brojac(0);
        for(int i=0; i<broj_polazaka; i++) if(polasci[i]->DaLiKasni()) brojac++;
        return brojac;
    }
    int DajProsjecnoTrajanjeVoznji() const{
        int suma(0);
        for(int i=0; i<broj_polazaka; i++) suma+=polasci[i]->DajTrajanjeVoznje();
        return suma/broj_polazaka;
    }
    Polazak &DajPrviPolazak() const{
        if(broj_polazaka==0) throw std::domain_error("Nema registriranih polazaka");
        auto polazak=std::min_element(polasci, polasci+broj_polazaka, [](Polazak *polazak1, Polazak *polazak2){
            int sat_polaska1=polazak1->DajOcekivanoVrijemePolaska().first;
            int minute_polaska1=polazak1->DajOcekivanoVrijemePolaska().second;
            int sat_polaska2=polazak2->DajOcekivanoVrijemePolaska().first;
            int minute_polaska2=polazak2->DajOcekivanoVrijemePolaska().second;
            if(sat_polaska1==sat_polaska2) return minute_polaska1<minute_polaska2;
            return sat_polaska1<sat_polaska2;
        });
        return **polazak;
    }
    Polazak &DajPosljednjiPolazak() const{
        if(broj_polazaka==0) throw std::domain_error("Nema registriranih polazaka");
        auto polazak=std::max_element(polasci, polasci+broj_polazaka, [](Polazak *polazak1, Polazak *polazak2){
            int sat_polaska1=polazak1->DajOcekivanoVrijemePolaska().first;
            int minute_polaska1=polazak1->DajOcekivanoVrijemePolaska().second;
            int sat_polaska2=polazak2->DajOcekivanoVrijemePolaska().first;
            int minute_polaska2=polazak2->DajOcekivanoVrijemePolaska().second;
            if(sat_polaska1==sat_polaska2) return minute_polaska1>minute_polaska2;
            return sat_polaska1>sat_polaska2;
        });
        return **polazak;
    }
    void IsprazniRedVoznje(){
        for(int i=0; i<broj_polazaka; i++){
            delete polasci[i];
            polasci[i]=nullptr;
        }
        broj_polazaka=0;
    }
    void Ispisi(int sati, int minute) const{
        std::sort(polasci, polasci+broj_polazaka, [](Polazak *polazak1, Polazak *polazak2){
            int sat_polaska1=polazak1->DajOcekivanoVrijemePolaska().first;
            int minute_polaska1=polazak1->DajOcekivanoVrijemePolaska().second;
            int sat_polaska2=polazak2->DajOcekivanoVrijemePolaska().first;
            int minute_polaska2=polazak2->DajOcekivanoVrijemePolaska().second;
            if(sat_polaska1==sat_polaska2) return minute_polaska1<minute_polaska2;
            return sat_polaska1<sat_polaska2;
        });
        for(int i=0; i<broj_polazaka; i++){
            if(polasci[i]->DajOcekivanoVrijemePolaska().first>sati || (polasci[i]->DajOcekivanoVrijemePolaska().first==sati && polasci[i]->DajOcekivanoVrijemePolaska().second>=minute)) polasci[i]->Ispisi();
            std::cout<<std::endl;
        }
    }
};
int main ()
{
    try{
        Polazak p1("Sarajevo", 411, 4, true, 11, 23, 67);
        p1.PostaviKasnjenje(4);
        if(p1.DaLiKasni()) std::cout<<"Voz ce kasniti!"<<std::endl;
        std::cout<<"Voznja traje "<<p1.DajTrajanjeVoznje()<<" minuta! Voz krece u "<<p1.DajOcekivanoVrijemePolaska().first<<":"<<p1.DajOcekivanoVrijemePolaska().second<<" sati, a stize u "<<p1.DajOcekivanoVrijemeDolaska().first<<":"<<p1.DajOcekivanoVrijemeDolaska().second<<std::endl;
        p1.Ispisi();
    	RedVoznje red(2);
        red.RegistrirajPolazak("Cazin", 5, true, 9, 13, 30, 400);
        red.RegistrirajPolazak(&p1);
        std::cout<<"Broj polazaka: "<<red.DajBrojPolazaka()<<", od kojih "<<red.DajBrojPolazakaKojiKasne()<<" kasni."<<std::endl;
        std::cout<<"Voznje u prosjeku traju"<<red.DajProsjecnoTrajanjeVoznji()<<std::endl;
        red.IsprazniRedVoznje();
    }
    catch(...){
        std::cout<<"Greska";
    }
	return 0;
}
