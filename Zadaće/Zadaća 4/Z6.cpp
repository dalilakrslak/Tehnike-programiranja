//TP 2021/2022: Zadaća 4, Zadatak 6
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <string>
#include <map>
#include <memory>
struct Student{
    int broj_indeksa;
    int godina_studija;
    std::string ime,prezime,adresa,telefon;
};
class Knjiga{
    int godina_izdanja;
    std::string naslov, ime_pisca, zanr;
    Student *korisnik;
public:
    Knjiga(std::string naslov_knjige, std::string ime, std::string zanric, int izdanje){
        naslov=naslov_knjige;
        ime_pisca=ime;
        zanr=zanric;
        godina_izdanja=izdanje;
        korisnik=nullptr;
    }
    std::string DajNaslov() const{
        return naslov;
    }
    std::string DajAutora() const{
        return ime_pisca;
    }
    std::string DajZanr() const{
        return zanr;
    }
    int DajGodinuIzdavanja() const{
        return godina_izdanja;
    }
    void ZaduziKnjigu(Student &student){
        korisnik=&student;
    }
    void RazduziKnjigu(){
        korisnik=nullptr;
    }
    bool DaLiJeZaduzena() const{
        if(korisnik==nullptr) return false;
        return true;
    }
    Student &DajKodKogaJe() const{
        if(korisnik==nullptr) throw std::domain_error("Knjiga nije zaduzena");
        return *korisnik;
    }
    Student *DajPokKodKogaJe() const{
        return korisnik;
    }
};
class Biblioteka{
    std::map<int,std::shared_ptr<Student>> mapa_korisnika;
    std::map<int,std::shared_ptr<Knjiga>> mapa_knjiga;
public:
    Biblioteka(){};
    Biblioteka(const Biblioteka &biblioteka){
        auto pocetak1=biblioteka.mapa_korisnika.begin();
        auto kraj1=biblioteka.mapa_korisnika.end();
        while(pocetak1!=kraj1){
            mapa_korisnika.insert({pocetak1->first, std::make_shared<Student>(*pocetak1->second)});
            pocetak1++;
        }
        auto pocetak2=biblioteka.mapa_knjiga.begin();
        auto kraj2=biblioteka.mapa_knjiga.end();
        while(pocetak2!=kraj2){
            mapa_knjiga.insert({pocetak2->first, std::make_shared<Knjiga>(*pocetak2->second)});
            pocetak2++;
        }
    }
    Biblioteka(Biblioteka &&biblioteka){
        mapa_knjiga=biblioteka.mapa_knjiga;
        mapa_korisnika=biblioteka.mapa_korisnika;
        auto pocetak1=biblioteka.mapa_korisnika.begin();
        auto kraj1=biblioteka.mapa_korisnika.end();
        while(pocetak1!=kraj1){
            pocetak1->second=nullptr;
            pocetak1++;
        }
        auto pocetak2=biblioteka.mapa_knjiga.begin();
        auto kraj2=biblioteka.mapa_knjiga.end();
        while(pocetak2!=kraj2){
            pocetak2->second=nullptr;
            pocetak2++;
        }
    }
    Biblioteka &operator =(const Biblioteka &biblioteka){
        if(&biblioteka!=this){
            auto pocetak1=biblioteka.mapa_korisnika.begin();
            auto kraj1=biblioteka.mapa_korisnika.end();
            while(pocetak1!=kraj1){
                mapa_korisnika.insert({pocetak1->first, std::make_shared<Student>(*pocetak1->second)});
                pocetak1++;
            }
            auto pocetak2=biblioteka.mapa_knjiga.begin();
            auto kraj2=biblioteka.mapa_knjiga.end();
            while(pocetak2!=kraj2){
                mapa_knjiga.insert({pocetak2->first, std::make_shared<Knjiga>(*pocetak2->second)});
                pocetak2++;
            }
        }
        return *this;
    }
    Biblioteka &operator =(Biblioteka &&biblioteka){
        if(&biblioteka!=this){
            mapa_knjiga=biblioteka.mapa_knjiga;
            mapa_korisnika=biblioteka.mapa_korisnika;
            auto pocetak1=biblioteka.mapa_korisnika.begin();
            auto kraj1=biblioteka.mapa_korisnika.end();
            while(pocetak1!=kraj1){
                pocetak1->second=nullptr;
                pocetak1++;
            }
            auto pocetak2=biblioteka.mapa_knjiga.begin();
            auto kraj2=biblioteka.mapa_knjiga.end();
            while(pocetak2!=kraj2){
                pocetak2->second=nullptr;
                pocetak2++;
            }
        }
        return *this;
    }
    ~Biblioteka(){}
    void RegistrirajNovogStudenta(int indeks, std::string ime, std::string prezime, int godina, std::string adresa, std::string telefon){
        if(mapa_korisnika.find(indeks)!=mapa_korisnika.end()) throw std::logic_error("Vec postoji student s tim brojem indeksa");
        auto novi_student=std::make_shared<Student>(Student{indeks, godina, ime, prezime, adresa, telefon});
        mapa_korisnika.insert({indeks,novi_student});
    }
    void RegistrirajNovuKnjigu(int broj, std::string naslov, std::string pisac, std::string zanr, int izdanje){
        if(mapa_knjiga.find(broj)!=mapa_knjiga.end()) throw std::logic_error("Knjiga s tim evidencijskim brojem vec postoji");
        auto nova_knjiga=std::make_shared<Knjiga>(Knjiga{naslov, pisac, zanr, izdanje});
        mapa_knjiga.insert({broj, nova_knjiga});    
    }
    Student NadjiStudenta (int indeks) const{
        if(mapa_korisnika.find(indeks)==mapa_korisnika.end()) throw std::logic_error("Student nije nadjen");
        return *mapa_korisnika.find(indeks)->second;
    }
    Knjiga NadjiKnjigu (int broj) const{
        if(mapa_knjiga.find(broj)==mapa_knjiga.end()) throw std::logic_error("Knjiga nije nadjena");
        return *mapa_knjiga.find(broj)->second;
    }
    void IzlistajStudente() const{
        auto pocetak=mapa_korisnika.begin();
        auto kraj=mapa_korisnika.end();
        while(pocetak!=kraj){
            std::cout<<"Broj indeksa: "<<pocetak->first<<std::endl<<"Ime i prezime: "<<(*pocetak->second).ime<<" "<<(*pocetak->second).prezime<<std::endl<<"Godina studija: "<<(*pocetak->second).godina_studija<<std::endl<<"Adresa: "<<(*pocetak->second).adresa<<std::endl<<"Broj telefona: "<<(*pocetak->second).telefon<<std::endl;
            pocetak++;
        }
    }
    void IzlistajKnjige() const{
        auto pocetak=mapa_knjiga.begin();
        auto kraj=mapa_knjiga.end();
        while(pocetak!=kraj){
            std::cout<<"Evidencijski broj: "<<pocetak->first<<std::endl<<"Naslov: "<<(*pocetak->second).DajNaslov()<<std::endl<<"Pisac: "<<(*pocetak->second).DajAutora()<<std::endl<<"Zanr: "<<(*pocetak->second).DajZanr()<<std::endl<<"Godina izdavanja: "<<(*pocetak->second).DajGodinuIzdavanja()<<std::endl;
            if((*pocetak->second).DaLiJeZaduzena()) std::cout<<"Zaduzena kod studenta: "<<(*pocetak->second).DajKodKogaJe().ime<<" "<<(*pocetak->second).DajKodKogaJe().prezime<<" ("<<(*pocetak->second).DajKodKogaJe().broj_indeksa<<")"<<std::endl;
            pocetak++;
        }
    }
    void ZaduziKnjigu(int broj, int indeks){
        if(mapa_knjiga.find(broj)==mapa_knjiga.end()) throw std::logic_error("Knjiga nije nadjena");
        if(mapa_korisnika.find(indeks)==mapa_korisnika.end()) throw std::logic_error("Student nije nadjen");
        if((*mapa_knjiga.find(broj)->second).DajPokKodKogaJe()!=nullptr) throw std::logic_error("Knjiga vec zaduzena");
        (*mapa_knjiga.find(broj)->second).ZaduziKnjigu(*mapa_korisnika.find(indeks)->second);
    }
    void RazduziKnjigu(int broj){
        if(mapa_knjiga.find(broj)==mapa_knjiga.end()) throw std::logic_error("Knjiga nije nadjena");
        if((*mapa_knjiga.find(broj)->second).DajPokKodKogaJe()==nullptr) throw std::logic_error("Knjiga nije zaduzena");
        (*mapa_knjiga.find(broj)->second).RazduziKnjigu();
    }
    void PrikaziZaduzenja(int indeks) const{
        if(mapa_korisnika.find(indeks)==mapa_korisnika.end()) throw std::logic_error("Student nije nadjen");
        bool zaduzio=false;
        auto pocetak=mapa_knjiga.begin();
        auto kraj=mapa_knjiga.end();
        while(pocetak!=kraj){
            if(indeks==(*mapa_korisnika.find(indeks)->second).broj_indeksa && (*pocetak->second).DaLiJeZaduzena()){
                std::cout<<"Evidencijski broj: "<<pocetak->first<<std::endl<<"Naslov: "<<(*pocetak->second).DajNaslov()<<std::endl<<"Pisac: "<<(*pocetak->second).DajAutora()<<std::endl<<"Zanr: "<<(*pocetak->second).DajZanr()<<std::endl<<"Godina izdavanja: "<<(*pocetak->second).DajGodinuIzdavanja()<<std::endl;
                zaduzio=true;
                pocetak++;
            }
        }
        if(!zaduzio) std::cout<<"Nema zaduzenja za tog studenta!";
    }
};
int main ()
{
    Biblioteka biblioteka;
    try{
        while(1){
            std::cout<<"MENI: "<<std::endl;
            std::cout<<" 1: Registracija novog studenta"<<std::endl;
            std::cout<<" 2: Registracije nove knjige"<<std::endl;
            std::cout<<" 3: Nadji studenta"<<std::endl;
            std::cout<<" 4: Nadji knjigu"<<std::endl;
            std::cout<<" 5: Izlistaj studente"<<std::endl;
            std::cout<<" 6: Izlistaj knjige"<<std::endl;
            std::cout<<" 7: Zaduzi knjigu"<<std::endl;
            std::cout<<" 8: Razduzi knjigu"<<std::endl;
            std::cout<<" 9: Prikazi zaduzenja"<<std::endl;
            std::cout<<" 10: Kraj"<<std::endl;
            std::cout<<std::endl<<"Odaberite sta zelite! "<<std::endl;
            int izbor;
            std::cin>>izbor;
            if(izbor==1){
                int indeks,godina;
                std::cout<<"Unesite indeks: ";
                std::cin>>indeks;
                std::string ime, prezime, adresa, broj;
                std::cout<<"Unesite ime, prezime, adresu i broj: ";
                std::cin>>ime>>prezime>>adresa>>broj;
                std::cout<<"Unesite godinu: ";
                std::cin>>godina;
                biblioteka.RegistrirajNovogStudenta(indeks, ime, prezime,  godina, adresa, broj);
            }
            if(izbor==2){
                int broj;
                std::cout<<"Unesite evidencijski broj: "; 
                std::cin>>broj;
                std::string naslov, pisac, zanr;
                std::cout<<"Unesite naslov, pisca i zanr: ";
                std::cin>>naslov>>pisac>>zanr;
                int izdanje;
                std::cout<<"Unesite izdanje: ";
                std::cin>>izdanje;
                biblioteka.RegistrirajNovuKnjigu(broj, naslov, pisac, zanr, izdanje);
            }
            if(izbor==3){
                int indeks;
                std::cout<<"Unesite indeks studenta: ";
                std::cin>>indeks;
                Student student=biblioteka.NadjiStudenta(indeks);
            }
            if(izbor==4){
                int broj;
                std::cout<<"Unesite evidencijski broj: ";
                std::cin>>broj;
                Knjiga knjiga=biblioteka.NadjiKnjigu(broj);
            }
            if(izbor==5){
                biblioteka.IzlistajStudente();
            }
            if(izbor==6) biblioteka.IzlistajKnjige();
            if(izbor==7){
                int broj, indeks;
                std::cout<<"Unesite evidencijski broj, te indeks studenta: ";
                std::cin>>broj>>indeks;
                biblioteka.ZaduziKnjigu(broj, indeks);
            }
            if(izbor==8){
                int broj;
                std::cout<<"Unesite evidencijski broj: ";
                std::cin>>broj;
                biblioteka.RazduziKnjigu(broj);
            }
            if(izbor==9){
                int indeks;
                std::cout<<"Unesite indeks studenta: ";
                std::cin>>indeks;
                biblioteka.PrikaziZaduzenja(indeks);
            }
            if(izbor==10){
                std::cout<<"Dovidjenja!";
                break;
            }
        }
    }
    catch(std::logic_error izuzetak){
        std::cout<<izuzetak.what();
    }
	return 0;
}
