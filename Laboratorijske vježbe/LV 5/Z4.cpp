/* 
    TP 2018/2019: LV 5, Zadatak 4
	
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
#include <algorithm>
#include <deque>
#include <cmath>
int main ()
{
    std::cout<<"Unesite broj elemenata: ";
    int n;
    std::cin>>n;
    std::cout<<"Unesite elemente: ";
    std::deque<int> dek(n);
    std::transform(dek.begin(), dek.end(), dek.begin(), [](int x){std::cin>>x; return x;});
    auto max=std::max_element(dek.begin(), dek.end());
    std::cout<<"Najveci element deka je "<<*max<<std::endl;
    auto min=std::min_element(dek.begin(), dek.end());
    std::cout<<"Najmanji element deka se pojavljuje "<<std::count(dek.begin(), dek.end(),*min)<<" puta u deku"<<std::endl;
    std::cout<<"U deku ima "<<std::count_if(dek.begin(), dek.end(), [](double x){if (std::sqrt(x)==int(std::sqrt(x))) return true; return false;})<<" brojeva koji su potpuni kvadrati"<<std::endl;
    auto cifre=std::min_element(dek.begin(), dek.end(), [](int x, int y){return int(log10(abs(x)))<int(log10(abs(y)));});
    std::cout<<"Prvi element sa najmanjim brojem cifara je "<<*cifre<<std::endl;
    std::deque<int> pom(n);
    auto temp=std::remove_copy_if(dek.begin(), dek.end(), pom.begin(), [](int x){int cifra=int(log10(abs(x))+1); if(cifra==3)return true; return false;});
    std::cout<<"Elementi koji nisu trocifreni su: ";
    std::for_each(pom.begin(),temp,[](int x){std::cout<<x<<" ";});
	return 0;
}