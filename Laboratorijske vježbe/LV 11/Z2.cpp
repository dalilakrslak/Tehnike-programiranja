/* 
    TP 16/17 (LV 11, Zadatak 2)
	Autotestove napisao Haris Hasic. Sve primjedbe/zalbe, sugestije
	i pitanja slati na mail: hhasic2@etf.unsa.ba.
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include <cmath>
#include <stdexcept>
static int kreirani=0;
static int aktivni=0;
class StedniRacun{
    double racun;
public:
    StedniRacun(double s=0){
        if(s<0) throw std::logic_error("Nedozvoljeno pocetno stanje");
        kreirani++; aktivni++;
        racun=s;
    }
    StedniRacun(const StedniRacun &stedni): racun(stedni.racun){
        kreirani++; aktivni++;
    }
    void Ulozi(double ulog){
        if(std::fabs(ulog)<=racun || ulog>0) racun+=ulog;
        else throw std::logic_error("Transakcija odbijena");
    }
    void Podigni(double uzeo){
        if(uzeo<=racun) racun-=uzeo;
        else throw std::logic_error("Transakcija odbijena");
    }
    double DajStanje() const {
        return racun;
    }
    void ObracunajKamatu(double kamatna_stopa){
        if(kamatna_stopa<0) throw std::logic_error("Nedozvoljena kamatna stopa");
        racun+=racun*kamatna_stopa/100;

    }
    static int DajBrojKreiranih() { 
        return kreirani; 
    }
    static int DajBrojAktivnih(){
        return aktivni;
    }
    ~StedniRacun(){
        aktivni--;
    }
};
int main ()
{
    try{
        StedniRacun racun=StedniRacun(411);
        racun.Ulozi(5);
        std::cout<<racun.DajStanje();
        racun.Podigni(5);
        std::cout<<std::endl<<racun.DajStanje();
        racun.ObracunajKamatu(10);
        std::cout<<std::endl<<racun.DajStanje();
    }
    catch(std::logic_error izuzetak){
        std::cout<<izuzetak.what();
    }
	return 0;
}