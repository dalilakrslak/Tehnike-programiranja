/* 
    TP 16/17 (LV 11, Zadatak 3)
	Autotestove napisao Haris Hasic. Sve primjedbe/zalbe, sugestije
	i pitanja slati na mail: hhasic2@etf.unsa.ba.
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include <cstring>
#include <stdexcept>
#include <iomanip>
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
int main ()
{
    Tim t("Real Madrid");
    t.ObradiUtakmicu(3, 1);
    std::cout<<"Tim "<<t.DajImeTima()<<" sa "<<t.DajGolRazliku()<<" gola razlike ima "<<t.DajBrojPoena()<<" poena."<<std::endl;
    t.ObradiUtakmicu(1,0);
    t.IspisiPodatke();
	return 0;
}