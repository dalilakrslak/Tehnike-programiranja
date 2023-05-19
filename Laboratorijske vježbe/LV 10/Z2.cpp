/* 
    TP 16/17 (LV 10, Zadatak 2)
	Autotestove pisala Nina Slamnik. Za sva pitanja,
	sugestije i primjedbe poslati mail na:
	nslamnik1@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <iomanip>
const double PI=4*std::atan(1);
class Krug{
    double poluprecnik;
public:
    explicit Krug(double r){
        Postavi(r);
    }
    void Postavi(double r){
        if(r<=0) throw std::domain_error("Neispravan poluprecnik");
        poluprecnik=r;
    }
    double DajPoluprecnik() const{
        return poluprecnik;
    }
    double DajObim() const{
        return 2*poluprecnik*PI;
    }
    double DajPovrsinu() const{
        return std::pow(poluprecnik,2)*PI;
    }
    void Skaliraj(double faktor_skaliranja){
        if(faktor_skaliranja<=0) throw std::domain_error("Neispravan faktor skaliranja");
        poluprecnik*=faktor_skaliranja;
    }
    void Ispisi() const{
        std::cout<<std::fixed<<std::setprecision(5)<<"R="<<DajPoluprecnik()<<" O="<<DajObim()<<" P="<<DajPovrsinu();
    }
};
class Valjak{
    Krug baza;
    double visina;
public:
    Valjak(double b, double h): baza(b){
        Postavi(b, h);
    }
    void Postavi(double b, double h){
        if(h<0) throw std::domain_error("Neispravna visina");
        baza.Postavi(b);
        visina=h;
    }
    Krug DajBazu() const {
        return baza;
    }
    double DajPoluprecnikBaze() const{
        return baza.DajPoluprecnik();
    }
    double DajVisinu() const{
        return visina;
    }
    double DajPovrsinu() const{
        return 2*baza.DajPovrsinu()+baza.DajObim()*visina;
    }
    double DajZapreminu() const{
        return baza.DajPovrsinu()*visina;
    }
    void Skaliraj(double faktor_skaliranja){
        if(faktor_skaliranja<=0) throw std::domain_error("Neispravan faktor skaliranja");
        visina*=faktor_skaliranja;
        baza.Skaliraj(faktor_skaliranja);
    }
    void Ispisi() const{
        std::cout<<std::fixed<<std::setprecision(5)<<"R="<<baza.DajPoluprecnik()<<" H="<<DajVisinu()<<" P="<<DajPovrsinu()<<" V="<<DajZapreminu();
    }
};
int main ()
{
    try{
        Krug k=Krug(3);
        std::cout<<"poluprecnik: "<<k.DajPoluprecnik()<<std::endl;
        k.Postavi(4);
        std::cout<<"poluprecnik: "<<k.DajPoluprecnik()<<", obim: "<<k.DajObim()<<", povrsina: "<<k.DajPovrsinu()<<std::endl;
        k.Skaliraj(23);
        k.Ispisi();
        Valjak v=Valjak(4, 12);
        std::cout<<"baza: "<<v.DajBazu().DajPoluprecnik()<<", poluprecnik: "<<v.DajPoluprecnikBaze()<<", visina: "<<v.DajVisinu()<<", povrsina: "<<v.DajPovrsinu()<<", zapremina: "<<v.DajZapreminu()<<std::endl;
        v.Skaliraj(23);
        v.Ispisi();
        std::cout<<std::endl;
        v.Postavi(4,-11);
    }
    catch(std::domain_error izuzetak){
        std::cout<<izuzetak.what();
    }
	return 0;
}