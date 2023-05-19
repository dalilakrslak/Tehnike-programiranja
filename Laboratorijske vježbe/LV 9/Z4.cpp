/* 
    TP 16/17 (LV 9, Zadatak 4)
	
	Testove pisao Kenan Ekinovic. Za sva pitanja, sugestije
	i zalbe obratiti se na mail: kekinovic1@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
#include <stdexcept>
#include <iomanip>
class Sat{
    int sati,minute,sekunde;
public:
    static bool DaLiJeIspravno(int h, int min, int s){
        if(h<0 || h>23 || min<0 || min>59 || s<0 || s>59) return false;
        return true;
    }
    void Postavi(int h, int min, int s){
        if(!DaLiJeIspravno(h, min, s)) throw std::domain_error("Neispravno vrijeme");
        sati=h; minute=min; sekunde=s;
    }
    void PostaviNormalizirano(int h, int min, int s){
        if(!DaLiJeIspravno(h, min, s)){
            while(s<0){
                s+=60;
                min--;
            }
            while(s>59){
                s-=60;
                min++;
            }
            while(min<0){
                min+=60;
                h--;
            }
            while(min>59){
                min-=60;
                h++;
            }
            while(h<0) h+=24;
            while(h>23) h-=24;
        }
        sati=h; minute=min; sekunde=s;
    }
    Sat Sljedeci(){
        sekunde++;
        if(!DaLiJeIspravno(sati, minute, sekunde)) PostaviNormalizirano(sati, minute, sekunde);
        return *this;
    }
    Sat Prethodni(){
        sekunde--;
        if(!DaLiJeIspravno(sati, minute, sekunde)) PostaviNormalizirano(sati, minute, sekunde);
        return *this;
    }
    Sat PomjeriZa(int parametar){
        sekunde+=parametar;
        if(!DaLiJeIspravno(sati, minute, sekunde)) PostaviNormalizirano(sati, minute, sekunde);
        return *this;
    }
    int DajSate() const { return sati; }
    int DajMinute() const { return minute; }
    int DajSekunde() const { return sekunde; }
    void Ispisi() const{
        std::cout<<std::setfill('0')<<std::setw(2)<<sati<<":"<<std::setfill('0')<<std::setw(2)<<minute<<":"<<std::setw(2)<<sekunde;
    }
    static int Razmak(Sat s1, Sat s2){
        int sekunde1=s1.sekunde+s1.minute*60+s1.sati*3600;
        int sekunde2=s2.sekunde+s2.minute*60+s2.sati*3600;
        return sekunde1-sekunde2;
    }
    friend int BrojSekundiIzmedju(Sat s1, Sat s2);
};
int BrojSekundiIzmedju(Sat s1, Sat s2){
    int sekunde1=s1.sekunde+s1.minute*60+s1.sati*3600;
    int sekunde2=s2.sekunde+s2.minute*60+s2.sati*3600;
    return sekunde1-sekunde2;
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