/* 
    TP 2018/2019: LV 5, Zadatak 7
	
	Autotestove pisala Nina Slamnik. Prijave gresaka, sugestije i pitanja
	mozete slati na mail nslamnik1@etf.unsa.ba.
	
	NAPOMENA: Tutorijal 5 sadrzi veliki broj ZABRANA, tipa zabrana
			  da se koristi indeksiranje niz[i] ili simulacija indeksiranja
			  npr. *(niz + i); dalje, da su zabranjene for petlje i slicno.
			  
			  To ce tutori rucno pregledati u toku tutorijala te ako
			  student bude PREKRSIO BAREM JEDNU ZABRANU, smatrace se da
			  za taj zadatak NIJE PROSAO NITI JEDAN AUTOTEST!
*/
#include <iostream>
#include <stdexcept>
#include <deque>
#include <vector>
#include <string>
#include <algorithm>
template <typename Tip>
auto SumaBloka(Tip a, Tip b)-> decltype(*a+*a){
    if(a==b) throw std::range_error("Blok je prazan");
    auto suma=*a;
    while(++a!=b) suma+=*a;
    return suma;
}
void Unesi(double &x){
    std::cin>>x;
}
int main ()
{   try{
        int n;
        std::cout<<"Unesite velicinu deka: ";
        std::cin>>n;
        std::deque<double> dek(n);
        std::cout<<"Unesite elemente deka: ";
        std::for_each(dek.begin(), dek.end(), Unesi);
        std::cout<<"Suma deka je: "<<SumaBloka(dek.begin(), dek.end());
    }
    catch(std::range_error greska){
        std::cout<<greska.what();
    }
	return 0;
}