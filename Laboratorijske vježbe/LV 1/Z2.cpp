//TP 2016/2017: Tutorijal 1, Zadatak 2
#include <iostream>
#include <cmath>
int main ()
{
    double a,b,c;
    std::cout<<"Unesite tri broja: ";
    std::cin>>a>>b>>c;
    if(a>0 && b>0 && c>0 && a+b>c && b+c>a && a+c>b){
        double obim=a+b+c;
        std::cout<<"Obim trougla sa duzinama stranica "<<a<<", "<<b<<" i "<<c<<" iznosi "<<obim<<"."<<std::endl;
        double s=(a+b+c)/2;
        double povrsina=std::sqrt(s*(s-a)*(s-b)*(s-c));
        std::cout<<"Njegova povrsina iznosi "<<povrsina<<"."<<std::endl;
        double gama=std::acos((pow(a,2)+pow(b,2)-pow(c,2))/(2*a*b));
        double beta=std::acos((pow(a,2)+pow(c,2)-pow(b,2))/(2*a*c));
        double alfa=std::acos((pow(b,2)+pow(c,2)-pow(a,2))/(2*b*c));
        double PI=4*std::atan(1);
        double ugao;
        if(alfa<=beta && alfa<=gama) ugao=alfa;
        else if(beta<=alfa && beta<=gama) ugao=beta;
        else ugao=gama;
        double stepen=(ugao*180)/PI;
        int stepeni=int(stepen);
        double min=(stepen-stepeni)*60;
        int minute=int(min);
        int sekunde=(min-minute)*60;
        std::cout<<"Njegov najmanji ugao ima "<<stepeni<<" stepeni, "<<minute<<" minuta i "<<sekunde<<" sekundi.";
    }
    else std::cout<<"Ne postoji trougao cije su duzine stranica "<<a<<", "<<b<<" i "<<c<<"!";
	return 0;
}