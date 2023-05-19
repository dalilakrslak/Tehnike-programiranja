/* 
    TP 2018/2019: LV 5, Zadatak 6
	
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
#include <vector>
#include <algorithm>
void Unesi(int &x){
    std::cin>>x;
}
int SumaCifara(int x){
    if(x==0) return 0;
    x=abs(x);
    return (x%10+SumaCifara(x/10));
}
bool ManjaSumaCifara(int a, int b){
    if(SumaCifara(a)==SumaCifara(b)) return a<b;
    return SumaCifara(a)<SumaCifara(b);
}
void Ispisi(int x){
    std::cout<<x<<" ";
}
int main ()
{
    std::cout<<"Unesite broj elemenata: ";
    int n;
    std::cin>>n;
    std::vector<int>v(n);
    std::cout<<"Unesite elemente: ";
    std::for_each(v.begin(), v.end(), Unesi);
    std::sort(v.begin(),v.end(),ManjaSumaCifara);
    std::cout<<"Niz sortiran po sumi cifara glasi: ";
    std::for_each(v.begin(),v.end(),Ispisi);
    std::cout<<"Unesite broj koji trazite: ";
    int br;
    std::cin>>br;
    auto pozicija=std::lower_bound(v.begin(),v.end(),br,ManjaSumaCifara);
    if(*pozicija==br) std::cout<<"Trazeni broj nalazi se na poziciji "<<pozicija-v.begin();
    else std::cout<<"Trazeni broj ne nalazi se u nizu!";

	return 0;
}