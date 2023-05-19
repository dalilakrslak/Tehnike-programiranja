/* 
    TP 2018/2019: LV 5, Zadatak 2
	
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
#include <string>
template<typename Tip1, typename Tip2>
void Razmijeni(Tip1 &pom1, Tip2 &pom2){
    Tip1 pom=pom1;
    pom1=pom2;
    pom2=pom;
}
template<typename Tip1, typename Tip2>
Tip2 RazmijeniBlokove(Tip1 p1, Tip1 p2, Tip2 p3){
    while(p1!=p2){
        Razmijeni(*p1, *p3);
        p1++;
        p3++;
    }
    return p3;
}
int main ()
{
    std::vector<int> v1(4,11);
    std::vector<int> v2(23,11);
    auto v=RazmijeniBlokove(v1.begin(), v1.end(), v2.begin());
    std::string s1="Dalila";
    std::string s2="Krslak";
    auto s=RazmijeniBlokove(s1.begin(), s1.end(), s2.begin());
	return 0;
}