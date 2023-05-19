/* 
    TP 16/17 (LV 7, Zadatak 10)
	Autotestove pisao Elmir Hodzic. Sva pitanja,
	prijave gresaka i sugestije slati na mail
	ehodzic3@etf.unsa.ba
	
	Vrsit ce se provjera na prepisivanje tutorijala.
*/
#include <iostream>
#include <functional>
std::function<int(int)> IteriranaFunkcija(std::function<int(int)> f, int n){
    std::function<int(int)> g;
    for(int i=0; i<n; i++){
        if(i==0) g=[f](int x){return f(x);};
        else g=[f,g](int x){return f(g(x));};
    }
    return g;
}
int main ()
{
    auto g=IteriranaFunkcija([](int x){return x*x;},10);
    std::cout<<g(5);
	return 0;
}