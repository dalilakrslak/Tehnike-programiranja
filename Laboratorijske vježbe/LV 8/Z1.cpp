//TP 2021/2022: LV 8, Zadatak 1
#include <iostream>
#include <cmath>
#include <iomanip>
#include <stdexcept>
struct Vrijeme{
    int sati,minute,sekunde;
};
void TestirajVrijeme(const Vrijeme &v){
    if(v.sati<0 || v.sati>23 || v.minute<0 || v.minute>59 || v.sekunde<0 || v.sekunde>59){
        throw std::domain_error("Neispravno vrijeme");
    }
}
void IspisiVrijeme(const Vrijeme &v){
    TestirajVrijeme(v);
    std::cout<<std::setfill('0')<<std::setw(2)<<v.sati<<":"<<std::setw(2)<<v.minute<<":"<<std::setw(2)<<v.sekunde<<std::endl;
}
Vrijeme SaberiVrijeme(const Vrijeme &v1, const Vrijeme &v2){
    TestirajVrijeme(v1);
    TestirajVrijeme(v2);
    Vrijeme v;
    v.sati=v1.sati+v2.sati;
    v.minute=v1.minute+v2.minute;
    v.sekunde=v1.sekunde+v2.sekunde;
    if(v.sekunde>59){
        v.sekunde%=60;
        v.minute++;
    }
    if(v.minute>59){
        v.minute%=60;
        v.sati++;
    }
    if(v.sati>23) v.sati%=24;
    return v;
}
int main ()
{
    try{
        std::cout<<"Unesite prvo vrijeme (h m s): ";
        Vrijeme v1;
        std::cin>>v1.sati>>v1.minute>>v1.sekunde;
        TestirajVrijeme(v1);
        std::cout<<"Unesite drugo vrijeme (h m s): ";
        Vrijeme v2;
        std::cin>>v2.sati>>v2.minute>>v2.sekunde;
        TestirajVrijeme(v2);
        std::cout<<"Prvo vrijeme: ";
        IspisiVrijeme(v1);
        std::cout<<"Drugo vrijeme: ";
        IspisiVrijeme(v2);
        std::cout<<"Zbir vremena: ";
        IspisiVrijeme(SaberiVrijeme(v1, v2));
    }
    catch(std::domain_error izuzetak){
        std::cout<<izuzetak.what();
    }
	return 0;
}
