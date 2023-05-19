//TP 2021/2022: Zadaća 2, Zadatak 1
#include <iostream>
#include <cmath>
#include <ostream>
#include <vector>
enum class Smjer {Nalijevo, Nadesno};
enum class Pravci {Sjever, Sjeveroistok, Istok, Jugoistok, Jug, Jugozapad, Zapad, Sjeverozapad};
enum class KodoviGresaka {PogresnaKomanda, NedostajeParametar, SuvisanParametar, NeispravanParametar};
enum class Komande {Aktiviraj, Deaktiviraj, Nalijevo, Nadesno, Idi, Kraj};
bool aktivan=true;
void AktivirajRobota(){
    aktivan=true;
}
void DeaktivirajRobota(){
    aktivan=false;
}
void Rotiraj(Pravci &orijentacija, Smjer na_koju_stranu){
    if(aktivan){
    if((orijentacija==Pravci::Sjeverozapad && na_koju_stranu==Smjer::Nadesno) || (orijentacija==Pravci::Sjeveroistok && na_koju_stranu==Smjer::Nalijevo)) orijentacija=Pravci::Sjever;
    else if((orijentacija==Pravci::Sjever && na_koju_stranu==Smjer::Nadesno) || (orijentacija==Pravci::Istok && na_koju_stranu==Smjer::Nalijevo)) orijentacija=Pravci::Sjeveroistok;
    else if((orijentacija==Pravci::Sjeveroistok && na_koju_stranu==Smjer::Nadesno) || (orijentacija==Pravci::Jugoistok && na_koju_stranu==Smjer::Nalijevo)) orijentacija=Pravci::Istok;
    else if((orijentacija==Pravci::Istok && na_koju_stranu==Smjer::Nadesno) || (orijentacija==Pravci::Jug && na_koju_stranu==Smjer::Nalijevo)) orijentacija=Pravci::Jugoistok;
    else if((orijentacija==Pravci::Jugoistok && na_koju_stranu==Smjer::Nadesno) || (orijentacija==Pravci::Jugozapad && na_koju_stranu==Smjer::Nalijevo)) orijentacija=Pravci::Jug;
    else if((orijentacija==Pravci::Jug && na_koju_stranu==Smjer::Nadesno) || (orijentacija==Pravci::Zapad && na_koju_stranu==Smjer::Nalijevo)) orijentacija=Pravci::Jugozapad;
    else if((orijentacija==Pravci::Jugozapad && na_koju_stranu==Smjer::Nadesno) || (orijentacija==Pravci::Sjeverozapad && na_koju_stranu==Smjer::Nalijevo)) orijentacija=Pravci::Zapad;
    else orijentacija=Pravci::Sjeverozapad;
    }
}
void Idi(int &x, int &y, Pravci orijentacija, int korak){    
    if(aktivan){
    if(orijentacija==Pravci::Sjever || orijentacija==Pravci::Sjeverozapad || orijentacija==Pravci::Sjeveroistok) y+=korak;
    if(orijentacija==Pravci::Istok || orijentacija==Pravci::Sjeveroistok || orijentacija==Pravci::Jugoistok) x+=korak;
    if(orijentacija==Pravci::Jug || orijentacija==Pravci::Jugoistok || orijentacija==Pravci::Jugozapad) y-=korak;
    if(orijentacija==Pravci::Zapad || orijentacija==Pravci::Jugozapad || orijentacija==Pravci::Sjeverozapad) x-=korak;
    }
}
void IspisiPoziciju(int x, int y, Pravci orijentacija){
    if(aktivan) std::cout<<"Robot je aktivan, nalazi se na poziciji ("<<x<<","<<y<<") i gleda na ";
    else std::cout<<"Robot je neaktivan, nalazi se na poziciji ("<<x<<","<<y<<") i gleda na ";
    if(orijentacija==Pravci::Sjever) std::cout<<"sjever."<<std::endl;
    else if(orijentacija==Pravci::Sjeveroistok) std::cout<<"sjeveroistok."<<std::endl;
    else if(orijentacija==Pravci::Istok) std::cout<<"istok."<<std::endl;
    else if(orijentacija==Pravci::Jugoistok) std::cout<<"jugoistok."<<std::endl;
    else if(orijentacija==Pravci::Jug) std::cout<<"jug."<<std::endl;
    else if(orijentacija==Pravci::Jugozapad) std::cout<<"jugozapad."<<std::endl;
    else if(orijentacija==Pravci::Zapad) std::cout<<"zapad."<<std::endl;
    else std::cout<<"sjeverozapad."<<std::endl;
}
void PrijaviGresku(KodoviGresaka kod_greske){
    if(kod_greske==KodoviGresaka::PogresnaKomanda) std::cout<<"Nerazumljiva komanda!"<<std::endl;
    if(kod_greske==KodoviGresaka::NedostajeParametar) std::cout<<"Komanda trazi parametar koji nije naveden!"<<std::endl;
    if(kod_greske==KodoviGresaka::SuvisanParametar) std::cout<<"Zadan je suvisan parametar nakon komande!"<<std::endl;
    if(kod_greske==KodoviGresaka::NeispravanParametar) std::cout<<"Parametar komande nije ispravan!"<<std::endl;
}
void IzvrsiKomandu(Komande komanda, int parametar, int &x, int &y, Pravci &orijentacija){
    if(komanda==Komande::Aktiviraj) AktivirajRobota();
    else if(komanda==Komande::Deaktiviraj) DeaktivirajRobota();
    else if(komanda==Komande::Nalijevo) Rotiraj(orijentacija, Smjer::Nalijevo);
    else if(komanda==Komande::Nadesno) Rotiraj(orijentacija, Smjer::Nadesno);
    else if(komanda==Komande::Idi) Idi(x, y, orijentacija, parametar);
}
bool UnosKomande(Komande &komanda, int &parametar, KodoviGresaka &kod_greske){
    char komanda1=std::cin.get();
    while(komanda1==' ') komanda1=std::cin.get();
    if(komanda1=='A'){
        komanda1=std::cin.get();
        while(komanda1==' ') komanda1=std::cin.get();
        if(komanda1=='+') {
            komanda1=std::cin.get();
            while(komanda1==' ') komanda1=std::cin.get();
            if(komanda1=='\n') komanda=Komande::Aktiviraj;
            else{
                kod_greske=KodoviGresaka::SuvisanParametar;
                return false;
            }
        }
        else if(komanda1=='-') {
            komanda1=std::cin.get();
            while(komanda1==' ') komanda1=std::cin.get();
            if(komanda1=='\n') komanda=Komande::Deaktiviraj;
            else{
                kod_greske=KodoviGresaka::SuvisanParametar;
                return false;
            }
        }
        else{
            kod_greske=KodoviGresaka::NedostajeParametar;
            return false;
        }
    }
    else if(komanda1=='L'){
        komanda1=std::cin.get();
        while(komanda1==' ') komanda1=std::cin.get();
        if(komanda1=='\n') komanda=Komande::Nalijevo;
        else{
            kod_greske=KodoviGresaka::SuvisanParametar;
            return false;
        }
    }
    else if(komanda1=='D'){
        komanda1=std::cin.get();
        while(komanda1==' ') komanda1=std::cin.get();
        if(komanda1=='\n') komanda=Komande::Nadesno;
        else{
            kod_greske=KodoviGresaka::SuvisanParametar;
            return false;
        }
    }
    else if(komanda1=='K'){
        komanda1=std::cin.get();
        while(komanda1==' ') komanda1=std::cin.get();
        if(komanda1=='\n') komanda=Komande::Kraj;
        else{
            kod_greske=KodoviGresaka::SuvisanParametar;
            return false;
        }
    }
    else if(komanda1=='I'){
        komanda1=std::cin.get();
        while(komanda1==' ') komanda1=std::cin.get();
        if(komanda1=='\n'){
            kod_greske=KodoviGresaka::NedostajeParametar;
            return false;
        }
        else if((komanda1<'0' || komanda1>'9') && komanda1!='-'){
            kod_greske=KodoviGresaka::NeispravanParametar;
            return false;
        }
        else{
            parametar=0;
            int negativan=1;
            if(komanda1=='-'){
                negativan=-1;
                komanda1=std::cin.get();
            }
            if(komanda1>='0' && komanda1<='9'){
                parametar=int(komanda1)-48;
                komanda1=std::cin.get();
                while(komanda1>='0' && komanda1<='9'){
                    parametar=parametar*10+int(komanda1)-48;
                    komanda1=std::cin.get();
                }
                if(komanda1!=' ' && komanda1!='\n'){
                    kod_greske=KodoviGresaka::NeispravanParametar;
                    return false;
                }
                while(komanda1==' ') komanda1=std::cin.get();
                parametar*=negativan;
                if(komanda1=='\n') komanda=Komande::Idi;

            }
            
        }
    }
    else{
        kod_greske=KodoviGresaka::PogresnaKomanda;
        return false;
    }
    return true;
}
int main ()
{
    int x(0), y(0), parametar;
    Pravci orijentacija=Pravci::Sjever;
    Komande komanda;
    KodoviGresaka kod_greske;
    IspisiPoziciju(x, y, orijentacija);
    while(1){
        std::cout<<"Unesi komandu:"<<std::endl;
        auto unoskomande=UnosKomande(komanda, parametar, kod_greske);
        if(!unoskomande){
            PrijaviGresku(kod_greske);
            std::cin.clear();
            std::cin.ignore(1000,'\n');
            continue;
        }
        if(komanda==Komande::Kraj) {
            std::cout<<"Dovidjenja!";
            break;
        }
        IzvrsiKomandu(komanda, parametar, x, y, orijentacija);
        IspisiPoziciju(x,  y, orijentacija);
    }
    
	return 0;
}