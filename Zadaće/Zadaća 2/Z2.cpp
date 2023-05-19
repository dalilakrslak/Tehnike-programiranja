//TP 2021/2022: Zadaća 2, Zadatak 2
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <cmath>
bool DaLiJeProst(int n){
    if(n<2) return false;
    for(int i=2; i<=std::sqrt(n); i++){
        if(n%i==0) return false;
    }
    return true;
}
void Goldbach(int n, int &p, int &q){
    if(n<=2) throw std::logic_error("Rastava ne postoji");
    bool nasao;
    for(int i=2; i<=n/2; i++){
        nasao=0;
        if(DaLiJeProst(i)){
            if(DaLiJeProst(n-i)){
                p=i;
                q=n-i;
                nasao=1;
                break;
            }
        }
    }
    if(!nasao) throw std::logic_error("Rastava ne postoji");
}
int main ()
{
    std::cout<<"Unesi broj: ";
    int n;
    std::cin>>n;
    int p, q;
    try{
        Goldbach(n, p, q);
        std::cout<<n<<" je zbir prostih brojeva "<<p<<" i "<<q;
    }
    catch(std::logic_error izuzetak){
        std::cout<<n<<" nije zbir dva prosta broja!";
    }
	return 0;
}
