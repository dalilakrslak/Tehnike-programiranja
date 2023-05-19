/* 
    TP 16/17 (LV 10, Zadatak 1)
	Autotestove pisala Nina Slamnik. Za sva pitanja,
	sugestije i primjedbe poslati mail na:
	nslamnik1@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include <cmath>
#include <stdexcept>
class StedniRacun{
    double racun;
public:
    StedniRacun(double s=0){
        if(s<0) throw std::logic_error("Nedozvoljeno pocetno stanje");
        racun=s;
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