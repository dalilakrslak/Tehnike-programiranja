/* 
    TP 16/17 (LV 7, Zadatak 7)
	Autotestove pisao Elmir Hodzic. Sva pitanja,
	prijave gresaka i sugestije slati na mail
	ehodzic3@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
#include <set>
template<typename Tip>
std::set<Tip> Unija(std::set<Tip> s1, std::set<Tip> s2){
    std::set<Tip> unija;
    for(auto pom: s1) unija.insert(pom);
    for(auto pom: s2) unija.insert(pom);
    return unija;
}
template<typename Tip>
std::set<Tip> Presjek(std::set<Tip> s1, std::set<Tip> s2){
    std::set<Tip> presjek;
    for(auto pom1: s1){
        for(auto pom2: s2){
            if(pom1==pom2) presjek.insert(pom2);
        }
    }
    return presjek;
}
int main ()
{
    std::set<std::string> s1={"Dalila", "Faris", "4", "11", "2019"};
    std::set<std::string> s2={"Progym", "4", "11"};
    auto unija=Unija(s1, s2);
    for(auto pom: unija) std::cout<<pom<<" ";
    std::cout<<std::endl;
    auto presjek=Presjek(s1, s2);
    for(auto pom: presjek) std::cout<<pom<<" ";
	return 0;
}