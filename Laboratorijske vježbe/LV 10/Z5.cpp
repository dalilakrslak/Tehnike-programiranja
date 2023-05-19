/* 
    TP 16/17 (LV 10, Zadatak 5)
	Autotestove pisala Nina Slamnik. Za sva pitanja,
	sugestije i primjedbe poslati mail na:
	nslamnik1@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala (na kraju semestra)
*/
#include <iostream>
#include <iomanip>
#include <cmath>
const double PI=4*std::atan(1);
class Ugao{
    int stepeni, minute, sekunde;
public:
    Ugao(double radijani = 0){
        Postavi(radijani);
    }
    Ugao(int stepeni, int minute, int sekunde){
        Postavi(stepeni, minute, sekunde);
    }
    void Postavi(double radijani){
        while(radijani<0) radijani+=2*PI;
        while(radijani>=2*PI) radijani-=2*PI;
        radijani=radijani*180/PI;
        stepeni=radijani;
        radijani=(radijani-stepeni)*60;
        minute=radijani;
        radijani=(radijani-minute)*60;
        sekunde=radijani;
    }
    void Postavi(int stepeni, int minute, int sekunde){
        Ugao::stepeni=stepeni; Ugao::minute=minute; Ugao::sekunde=sekunde;
        while(Ugao::sekunde>59){
            Ugao::minute++;
            Ugao::sekunde-=60;
        }
        while(Ugao::minute>59){
            Ugao::stepeni++;
            Ugao::minute-=60;
        }
        while(Ugao:: stepeni>359) Ugao::stepeni-=360;
        while(Ugao::sekunde<0){
            Ugao::minute--;
            Ugao::sekunde+=60;
        }
        while(Ugao::minute<0){
            Ugao::stepeni--;
            Ugao::minute+=60;
        }
        while(Ugao::stepeni<0) Ugao::stepeni+=360;
    }
    double DajRadijane() const{
        return (stepeni+minute/60.+sekunde/3600.)*PI/180;
    }
    void OcitajKlasicneJedinice(int &stepeni, int &minute, int &sekunde){
        stepeni=DajStepene();
        minute=DajMinute();
        sekunde=DajSekunde();
    }
    int DajStepene() const{
        return stepeni;
    }
    int DajMinute() const{
        return minute;
    }
    int DajSekunde() const{
        return sekunde;
    }
    void Ispisi() const{
        std::cout<<std::fixed<<std::setprecision(5)<<DajRadijane();
    }
    void IspisiKlasicno() const{
        std::cout<<DajStepene()<<"deg "<<DajMinute()<<"min "<<DajSekunde()<<"sec";
    }
    Ugao &SaberiSa(const Ugao &u){
        stepeni+=u.stepeni;
        minute+=u.minute;
        sekunde+=u.sekunde;
        Postavi(stepeni, minute, sekunde);
        return *this;
    }
    Ugao &PomnoziSa(double x){
        stepeni*=x;
        minute*=x;
        sekunde*=x;
        return *this;
    }
    friend Ugao ZbirUglova(const Ugao &u1, const Ugao &u2){
        return Ugao(u1.stepeni+u2.stepeni, u1.minute+u2.minute, u1.sekunde+u2.sekunde);
    }
    friend Ugao ProduktUglaSaBrojem(const Ugao &u, double x){
        return Ugao(u.stepeni*x, u.minute*x, u.sekunde*x);
    }
};
int main ()
{
	Ugao u1;
    u1.Ispisi();
    std::cout<<std::endl;
    Ugao u2(23,11,01);
    u2.IspisiKlasicno();
    std::cout<<std::endl;
    u1.SaberiSa(u2);
    std::cout<<"radijani: "<<u1.DajRadijane()<<", "<<u1.DajStepene()<<"deg "<<u1.DajMinute()<<"min "<<u1.DajSekunde()<<"sec"<<std::endl;
    Ugao u3=ZbirUglova(u1, u2);
    u3.Ispisi();
    std::cout<<std::endl;
    u3.Postavi(411);
    u3.IspisiKlasicno();
    std::cout<<std::endl;
    int stepeni,minute, sekunde;
    u3.OcitajKlasicneJedinice(stepeni, minute, sekunde);
    std::cout<<"stepeni: "<<stepeni<<", minute: "<<minute<<", sekunde: "<<sekunde<<std::endl;
    u3.PomnoziSa(2);
    u3.Ispisi();
    std::cout<<std::endl;
    Ugao u4=ProduktUglaSaBrojem(u3,2);
    u4.Ispisi();
	return 0;
}