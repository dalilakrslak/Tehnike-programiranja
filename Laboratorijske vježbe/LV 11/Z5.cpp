/* 
    TP 16/17 (LV 11, Zadatak 5)
	Autotestove napisao Haris Hasic. Sve primjedbe/zalbe, sugestije
	i pitanja slati na mail: hhasic2@etf.unsa.ba.
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include <cstring>
#include <sstream>
#include <stdexcept>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <memory>
class Tim{
    char ime_tima[20];
    int broj_odigranih, broj_pobjeda, broj_nerijesenih, broj_poraza, broj_datih, broj_primljenih, broj_poena;
public:
    Tim(const char ime[]){
        if(strlen(ime)>20) throw std::range_error("Predugacko ime tima");
        strncpy(ime_tima, ime, 20);
        broj_odigranih=0; 
        broj_pobjeda=0;
        broj_nerijesenih=0;
        broj_poraza=0;
        broj_datih=0;
        broj_primljenih=0;
        broj_poena=0;
    }
    void ObradiUtakmicu(int broj_datih, int broj_primljenih){
        if(broj_datih<0 || broj_primljenih<0) throw std::range_error("Neispravan broj golova");
        Tim::broj_datih+=broj_datih;
        Tim::broj_primljenih+=broj_primljenih;
        broj_odigranih++;
        if(broj_datih>broj_primljenih){
            broj_pobjeda++;
            broj_poena+=3;
        }
        else if(broj_datih==broj_primljenih){
            broj_nerijesenih++;
            broj_poena++;
        }
        else broj_poraza++;
    }
    const char *DajImeTima() const{
        return ime_tima;
    }
    int DajBrojPoena() const{
        return broj_poena;
    }
    int DajGolRazliku() const{
        return broj_datih-broj_primljenih;
    }
    void IspisiPodatke() const{
        std::cout<<std::left<<std::setw(20)<<ime_tima<<std::right<<std::setw(4)<<broj_odigranih<<std::setw(4)<<broj_pobjeda<<std::setw(4)<<broj_nerijesenih<<std::setw(4)<<broj_poraza<<std::setw(4)<<broj_datih<<std::setw(4)<<broj_primljenih<<std::setw(4)<<broj_poena<<std::endl;
    }
};
class Liga{
    std::vector<std::shared_ptr<Tim>> timovi;
public:
    explicit Liga(int velicina_lige);
    explicit Liga(std::initializer_list<Tim> lista_timova): timovi(lista_timova.size()){
        auto pocetak=lista_timova.begin();
        for(int i=0; i<lista_timova.size(); i++){
            timovi[i]=std::make_shared<Tim>(*pocetak++);
        }
    }
    ~Liga(){}
    Liga(const Liga &l){
        timovi.resize(l.timovi.size());
        for(int i=0; i<timovi.size(); i++) timovi.at(i)=std::make_shared<Tim>(*l.timovi.at(i));
    }
    Liga(Liga &&l)=default;
    Liga &operator =(const Liga &l){
        timovi.resize(l.timovi.size());
        for(int i=0; i<timovi.size(); i++) timovi.at(i)=std::make_shared<Tim>(*l.timovi.at(i));
        return *this;
    }
    Liga &operator =(Liga &&l)=default;
    void DodajNoviTim(const char ime_tima[]){
        if(strlen(ime_tima)>20) throw std::logic_error("Predugacko ime tima");
        for(int i=0; i<timovi.size(); i++){
            if(strcmp(timovi[i]->DajImeTima(), ime_tima)==0) throw std::logic_error("Tim vec postoji");
        }
    }
    void RegistrirajUtakmicu(const char tim1[], const char tim2[], int rezultat_1, int rezultat_2){
        bool nadjen1=false, nadjen2=false;
        for(int i=0; i<timovi.size(); i++) if(strcmp(timovi[i]->DajImeTima(),tim1)==0) nadjen1=true;
        for(int i=0; i<timovi.size(); i++) if(strcmp(timovi[i]->DajImeTima(),tim2)==0) nadjen2=true;
        if(!nadjen1 || !nadjen2) throw std::logic_error("Tim nije nadjen");
        if(rezultat_1<0 || rezultat_2<0) throw std::range_error("Neispravan broj golova");
        for(int i=0; i<timovi.size(); i++){
            if(strcmp(timovi[i]->DajImeTima(), tim1)==0) timovi[i]->ObradiUtakmicu(rezultat_1, rezultat_2);
            else if(strcmp(timovi[i]->DajImeTima(), tim2)==0) timovi[i]->ObradiUtakmicu(rezultat_2, rezultat_1);
        }
    }
    void IspisiTabelu(){
        std::sort(timovi.begin(), timovi.end(), [](std::shared_ptr<Tim> tim1, std::shared_ptr<Tim> tim2)->bool{
            if(tim1->DajBrojPoena()!=tim2->DajBrojPoena()) return tim1->DajBrojPoena()>tim2->DajBrojPoena();
            else if(tim1->DajBrojPoena()==tim2->DajBrojPoena() && tim1->DajGolRazliku()>tim2->DajGolRazliku()) return tim1->DajGolRazliku()>tim2->DajGolRazliku();
            else if(tim1->DajBrojPoena()==tim2->DajBrojPoena() && tim1->DajGolRazliku()==tim2->DajGolRazliku() && strcmp(tim1->DajImeTima(),tim2->DajImeTima())!=0){
                if(strcmp(tim1->DajImeTima(), tim2->DajImeTima())<0) return true;
            }
            return false;
        });
        for(int i=0; i<timovi.size(); i++) timovi[i]->IspisiPodatke();
    }
};
int main ()
{
    Liga l{"Celik", "Borac", "Jedinstvo", "Zeljeznicar", "Zrinjski", "Sarajevo"};
    l.IspisiTabelu();
    l.RegistrirajUtakmicu("Celik", "Zrinjski", 2, 3);
    l.IspisiTabelu();
    l.RegistrirajUtakmicu("Zeljeznicar", "Celik", 1, 1);
    l.IspisiTabelu();
	return 0;
}