//TP 2021/2022: Zadaća 3, Zadatak 1
#include <algorithm>
#include <iostream>
#include <cmath>
#include <functional>
#include <stdexcept>
#include <vector>
#include <utility>
#include <iomanip>
std::function<double (double)> BaricentricnaInterpolacija(std::vector<std::pair<double, double>> cvorovi_interpolacije, int d){
    if(d<0 || d>cvorovi_interpolacije.size()) throw std::domain_error("Nedozvoljen red");
    for(int i=0; i<cvorovi_interpolacije.size(); i++){
        for(int j=i+1; j<cvorovi_interpolacije.size(); j++){
            if(std::fabs(cvorovi_interpolacije.at(i).first-cvorovi_interpolacije.at(j).first)<0.000001) throw std::domain_error("Neispravni cvorovi");
        }
    }
    std::vector<double> w;
    for(int i=1; i<=cvorovi_interpolacije.size(); i++){
        double suma{};
        int n=cvorovi_interpolacije.size();
        int min=std::min(i, n-d);
        int max=std::max(1,i-d);
        for(int k=max; k<=min; k++){
            double proizvod=1;
            for(int j=k; j<=k+d; j++){
                if(j!=i) proizvod*=1/(cvorovi_interpolacije.at(i-1).first-cvorovi_interpolacije.at(j-1).first);
            }
            suma+=std::pow(-1,k-1)*proizvod;
        }
        w.push_back(suma);
    }
    return [cvorovi_interpolacije, w](double x){
        double s1{}, s2{};
        for(int i=1; i<=cvorovi_interpolacije.size(); i++){
            if(std::fabs(x-cvorovi_interpolacije.at(i-1).first)<0.000001) return cvorovi_interpolacije.at(i-1).second;
            s1+=(w.at(i-1)*cvorovi_interpolacije.at(i-1).second)/(x-cvorovi_interpolacije.at(i-1).first);
            s2+=w.at(i-1)/(x-cvorovi_interpolacije.at(i-1).first);
        }
        return s1/s2;
    };
}
std::function<double(double)> BaricentricnaInterpolacija(std::function<double(double)> fja, double xmin, double xmax, double deltax, int d){
    if(xmin>xmax || deltax<=0) throw std::domain_error("Nekorektni parametri");
    std::vector<std::pair<double, double>> cvorovi_interpolacije;
    int i=0;
    for(;;){
        double x=xmin+i*deltax;
        if(x-xmax>0.000001) break;
        double y=fja(x);
        cvorovi_interpolacije.push_back(std::make_pair(x, y));
        i++;
    }
    try{
        auto rez=BaricentricnaInterpolacija(cvorovi_interpolacije,d);
        return rez;
    }
    catch(...){
        throw;
    }
}
double f(double x){
    return std::pow(x,2)+std::sin(x);
}
int main ()
{
    std::cout<<"Odaberite opciju (1 - unos cvorova, 2 - aproksimacija): ";
    int opcija;
    std::cin>>opcija;
    if(opcija==1){
        std::cout<<"Unesite broj cvorova: ";
        int n;
        std::cin>>n;
        std::cout<<"Unesite cvorove kao parove x y: ";
        std::vector<std::pair<double,double>> cvorovi_interpolacije;
        for(int i=0; i<n; i++){
            double x,y;
            std::cin>>x>>y;
            cvorovi_interpolacije.push_back(std::make_pair(x,y));
        }
        std::cout<<"Unesite red interpolacije: ";
        int d;
        std::cin>>d;
        try{
            auto rez=BaricentricnaInterpolacija(cvorovi_interpolacije,d);
            for(;;){
                std::cout<<std::endl<<"Unesite argument (ili \"kraj\" za kraj): ";
                double argument;
                std::cin>>argument;
                if(std::cin) std::cout<<"f("<<argument<<") = "<<rez(argument);
                else break;
            }
        }
        catch(std::domain_error greska){
            std::cout<<greska.what();
        }
    }
    if(opcija==2){
        std::cout<<"Unesite krajeve intervala i korak: ";
        double xmin, xmax, deltax;
        std::cin>>xmin>>xmax>>deltax;
        std::cout<<"Unesite red interpolacije: ";
        int d;
        std::cin>>d;
        try{
            auto rez=BaricentricnaInterpolacija(f,xmin,xmax,deltax,d);
            for(;;){
                std::cout<<std::endl<<"Unesite argument (ili \"kraj\" za kraj): ";
                double argument;
                std::cin>>argument;
                if(std::cin) std::cout<<"f("<<argument<<") = "<<f(argument)<<" fapprox("<<argument<<") = "<<rez(argument);
                else break;
            }
        }
        catch(std::domain_error greska){
            std::cout<<greska.what();
        }
    }
	return 0;
}
