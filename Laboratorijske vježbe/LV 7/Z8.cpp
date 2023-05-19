/* 
    TP 16/17 (LV 7, Zadatak 8)
	Autotestove pisao Elmir Hodzic. Sva pitanja,
	prijave gresaka i sugestije slati na mail
	ehodzic3@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
#include <string>
#include <algorithm>
std::string IzvrniBezRazmaka(std::string string){
    std::string pom;
    std::remove_copy(string.rbegin(), string.rend(), std::back_inserter(pom),' ');
    return pom;
}
int main ()
{
    std::string s="Dalila Krslak";
    std::cout<<IzvrniBezRazmaka(s);
	return 0;
}