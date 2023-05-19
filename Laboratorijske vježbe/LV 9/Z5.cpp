/* 
    TP 16/17 (LV 9, Zadatak 5)
	
	Testove pisao Kenan Ekinovic. Za sva pitanja, sugestije
	i zalbe obratiti se na mail: kekinovic1@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
#include <stdexcept>
#include <iomanip>
class Sat{
    int sekunde;
public:
    static bool DaLiJeIspravno(int h, int min, int s){
        if(h<0 || h>23 || min<0 || min>59 || s<0 || s>59) return false;
        return true;
    }
    void Postavi(int h, int min, int s){
        if(!DaLiJeIspravno(h, min, s)) throw std::domain_error("Neispravno vrijeme");
        sekunde=s+min*60+h*3600;
    }
    void PostaviNormalizirano(int h, int min, int s){
        int pom=s+min*60+h*3600;
        int sek=pom%(24*3600);
        if(sek<0) sek+=(24*3600);
        sekunde=sek;
    }
    Sat Sljedeci() {
        PomjeriZa(1);
        return *this;
    }
    Sat Prethodni(){
        PomjeriZa(-1);
        return *this;
    }
    Sat PomjeriZa(int pomak){
        sekunde+=pomak;
        PostaviNormalizirano(DajSate(), DajMinute(), DajSekunde());
        return *this;
    }
    int DajSate() const { return sekunde/3600; }
    int DajMinute() const { return (sekunde%3600)/60; }
    int DajSekunde() const { return (sekunde%3600)%60; }
    void Ispisi() const{
        std::cout<<std::setfill('0')<<std::setw(2)<<DajSate()<<":"<<std::setw(2)<<DajMinute()<<":"<<std::setw(2)<<DajSekunde();
    }
    static int Razmak(Sat s1,Sat s2){
        return s1.sekunde-s2.sekunde;
    }
    friend int BrojSekundiIzmedju(Sat s1, Sat s2);
};
int BrojSekundiIzmedju(Sat s1, Sat s2){
    return s1.sekunde-s2.sekunde;
}
int main ()
{
    try{
        Sat s1,s2;
        s1.Postavi(4, 11, 18);
        s2.PostaviNormalizirano(23, 11, 2);
        s1.Sljedeci();
        s2.Prethodni();
        s1.Ispisi();
        std::cout<<std::endl;
        std::cout<<s2.DajSate()<<":"<<s2.DajMinute()<<":"<<s2.DajSekunde()<<std::endl;
        std::cout<<"Broj sekundi izmedju: "<<std::endl<<BrojSekundiIzmedju(s1,s2)<<std::endl<<Sat::Razmak(s1,s2);
        s2.PomjeriZa(21);
    }
    catch(...){
        std::cout<<"Greska!";
    }
	return 0;
}