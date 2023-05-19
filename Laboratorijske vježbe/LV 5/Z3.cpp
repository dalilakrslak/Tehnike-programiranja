/* 
    TP 2018/2019: LV 5, Zadatak 3
	
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
#include <cmath>
int UnesiNiz(int element){
    std::cin>>element;
    return element;
}
bool PotpunKvadrat(double x){
    return (std::sqrt(x)==int(std::sqrt(x)));
}
bool ManjiBrojCifara(int x, int y){
    return log10(abs(x))<log10(abs(y));
}
bool Trocifren(int x){
    int cifre=log10(abs(x))+1;
    if(cifre==3) return true;
    return false;
}
void Ispisi(int x){
    std::cout<<x<<" ";
}
int main ()
{
    std::cout<<"Unesite broj elemenata (max. 1000): ";
    int n;
    std::cin>>n;
    std::cout<<"Unesite elemente: ";
    int niz[1000];
    std::transform(niz, niz+n, niz, UnesiNiz);
    int *max=std::max_element(niz, niz+n);
    std::cout<<"Najveci element niza je "<<*max<<std::endl;
	int *min=std::min_element(niz, niz+n);
    std::cout<<"Najmanji element niza se pojavljuje "<<std::count(niz, niz+n, *min)<<" puta u nizu"<<std::endl;
    std::cout<<"U nizu ima "<<std::count_if(niz, niz+n, PotpunKvadrat)<<" brojeva koji su potpuni kvadrati"<<std::endl;
    int *cifre=std::min_element(niz,niz+n,ManjiBrojCifara);
    std::cout<<"Prvi element sa najmanjim brojem cifara je "<<*cifre<<std::endl;
    int pom[1000];
    auto temp=std::remove_copy_if(niz, niz+n, pom, Trocifren);
    std::cout<<"Elementi koji nisu trocifreni su: ";
    std::for_each(pom, temp, Ispisi);
    return 0;
}