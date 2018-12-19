// Chris Jackson
// Section 010
// 2/8/18
// CSE 232 Project 08

#include <iostream>
using std::cout; using std::endl;
#include <fstream>
using std::ifstream;
#include <vector>
using std::vector;
#include <map>
#include <string>
using std::string; using std::to_string;
#include "proj08_player.h"

/*a constructor method that takes a file name as a single string argument. Uses the file to populate the data member stocks .*/
Market::Market(string s){
    file_name = s;
    
    ifstream file(file_name);
    long date;
    double price;
    vector<double> prices;

    if(file)
    {
        while (!file.eof())
        {
            prices.clear();
            file >> date;
            if(!file.eof()){
                for(long i=0; i<30; i++)
                {
                    file >> price;
                    prices.push_back(price);
                }
                stocks[date]=prices;
            }
        }
    }
}

/*a method that returns the price of the stock on the date if the provided date is a valid date and the provided stock symbol is a valid stock symbol. Returns -1.0 otherwise.*/
double Market::get_price(string stock_name, long date) const{
    double price;
    long ctr=0;
    bool valid = true;
    string symbol;
    vector<double> prices;
    
    if (stocks.find(date) == stocks.end()) {//checks if valid date
        price = -1.0;
        return price;
    }
    prices = stocks.find(date)->second;
    valid=false;
    while(ctr<=symbol_list.size()){
        if(symbol_list[ctr]==stock_name){//checks if valid symbol
            valid = true;
            break;
        }
        ctr+=1;
    }
    
    if(valid){//checks if valid
        price = prices[ctr];
        return price;
    }
    else{
        price = -1.0;
        return price;
    }
}

/*Returns the high and low values (in that order) for that stock for the provided year as pair. If the year or the symbol does not exist, returns the pair {-1.0, -1.0}*/
pair<double, double> Market::high_low_year(long year, string symbol){
    double max=0,min=1000,value;
    long date;
    pair<double, double> high_low;
    vector<double> prices = stocks[year];
    string date_str,current_year;
    map<long, vector<double>>::iterator iter1;
    vector<double>::iterator iter2;
    bool valid;
    
    valid=false;
    for(iter1 = stocks.begin(); iter1 != stocks.end();iter1++){
        date_str = to_string(iter1->first);
        date = iter1->first;
        if(date_str.substr(0, 4)==to_string(year) && date_str.size()==8){
            valid=true;
            prices=iter1->second;
            value = get_price(symbol, date);
            if(value==-1.0){
                max=-1.0;
                min=-1.0;
                break;
            }
            if(value>max){
                max=value;
            }
            if(value<min){
                min=value;
            }
        }
        if(min==-1.0 || max==-1.0){
            break;
        }
    }
    if(valid){
        high_low.first=max;
        high_low.second=min;
    }
    else{
        high_low.first=-1.0;
        high_low.second=-1.0;
    }
    
    return high_low;
}
