//TP 2021/2022: LV 4, Zadatak 2
#include <iostream>
#include <cmath>
#include <string>
void IzvrniString(std::string &s){
    for(int i=0; i<s.size()/2; i++){
        char pom=s[i];
        s[i]=s[s.size()-1-i];
        s[s.size()-1-i]=pom;
    }
}
int main ()
{
    std::cout<<"Unesi string: ";
    std::string s;
    getline(std::cin, s);
    IzvrniString(s);
    std::cout<<"Izvrnuti string je: "<<s<<std::endl;
	return 0;
}
