//TP 2021/2022: LV 8, Zadatak 4
#include <iostream>
#include <cmath>
#include <map>
#include <string>
std::string ZamijeniPremaRjecniku(std::string zamjena, std::map<std::string, std::string> mapa){
    std::string zamijenjen;
    for(int i=0; i<zamjena.length(); i++){
        std::string rijec;
        if((zamjena[i]>='a' && zamjena[i]<='z') || ispunct(zamjena[i]) || isdigit(zamjena[i])){
            int pocetak=i;
            while((i<zamjena.length() && zamjena[i]>='a' && zamjena[i]<='z') || ispunct(zamjena[i]) || isdigit(zamjena[i])) i++;
            rijec=zamjena.substr(pocetak, i-pocetak);
        }
        auto it=mapa.find(rijec);
        if(it!=mapa.end()) zamijenjen=zamijenjen+it->second+" ";
        else zamijenjen=zamijenjen+rijec+" ";
    }
    return zamijenjen;
}
int main ()
{
    std::map<std::string, std::string> rjecnik{
        {"da", "ne"},
        {"imam", "nemam"},
        {"jesam", "nisam"},
        {"hocu", "necu"},
    };
    std::cout<<ZamijeniPremaRjecniku("imam nemam jesam nisam",rjecnik);
	return 0;
}
