//TP 2021/2022: LV 4, Zadatak 4
#include <iostream>
#include <cmath>
#include <string>
template <typename NekiTip>
 void UnosBroja(std::string tekst, std::string upozorenje, NekiTip &broj){  
     std::cout<<tekst;
     while(!(std::cin>>broj) || std::cin.peek()!='\n'){
         std::cout<<std::endl<<upozorenje<<std::endl;
         std::cin.clear();
         std::cin.ignore(1000,'\n');
         std::cout<<tekst;
     }
 }
int main ()
{
    double x;
    UnosBroja("Unesite bazu: ", "Neispravan unos, pokusajte ponovo...", x);
    int n;
    UnosBroja("Unesite cjelobrojni eksponent: ", "Neispravan unos, pokusajte ponovo...", n);
    double stepen=1;
    if(n>0){
        for(int i=0;i<n;i++) stepen*=x;
    }
    else if(n<0){
        for(int i=0;i<std::fabs(n);i++){
            stepen*=1./x;
        }
    }
    std::cout<<x<<" na "<<n<<" iznosi "<<stepen;
	return 0;
}
