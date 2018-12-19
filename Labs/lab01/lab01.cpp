#include <iostream>
using std::cout; using std::cin; using std::endl; using std::fixed;
#include <iomanip>
using std::setprecision;

int main(){
	double initial_au_distance = 39.33;
	long au_in_km = 149598000;
	long au_in_mi = 92955800;
	double initial_km_distance = initial_au_distance * au_in_km;
	double initial_mi_distance = initial_au_distance * au_in_mi;
	double km_speed = 14.24;
	double mi_speed = 8.85;
	long day_seconds = 86400;
	long speed_of_light = 299792.458;//in km
	long days;

	std::cin>>days;

	double distance_in_km = (days * day_seconds * km_speed ) + initial_km_distance;
	double distance_in_mi = (days * day_seconds * mi_speed ) + initial_mi_distance;

	double radio_delay = ((distance_in_km/speed_of_light)/60)/60;

	cout<<fixed<<setprecision(2);
	cout<<distance_in_km<<endl;
	cout<<distance_in_mi<<endl;
	cout<<radio_delay*2<<endl;

	return 0;

}