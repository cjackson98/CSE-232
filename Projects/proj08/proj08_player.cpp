// Chris Jackson
// Section 010
// 2/8/18
// CSE 232 Project 08

#include <iostream>
using std::cout; using std::endl; using std::fixed;
#include <fstream>
using std::ifstream;
#include <vector>
using std::vector;
#include <map>
#include <string>
using std::string; using std::to_string;
#include <iomanip>
using std::setprecision;
#include <sstream>
using std::ostringstream;
#include "proj08_player.h"

/* Attempts to buy a stock for the player from the Market on the specified date. Returns true if the player has enough cash to make the purchase, the stock symbol is one of the valid 30 symbols, and if the date is valid (within the range of dates stored in Market). If true, purchase is made and the player info is updated (cash reduced, stocks updated). If false return, no action taken*/
bool Player::buy(Market &m, string stock, long date, long quantity){
    double price = m.get_price(stock, date);
    if(price==-1.0){
        return false;
    }
    price = price*quantity;
    if(price<cash){
        cash=cash-price;
        stocks[stock]+=quantity;
        return true;
    }
    else{
        return false;
    }
}

/*Returns true if the player has the stock to sell and has at least the quantity indicated. If true, player info is updated (cash is increased, stocks updated). If false, no action is taken.*/
bool Player::sell (Market &m, string stock, long date, long quantity){
    double price;
    if(stocks.find(stock)==stocks.end()){//doesnt have the stock
        return false;
    }
    else{//has the stock
        if(stocks[stock] >= quantity){//can sell that many
            price = m.get_price(stock, date);
            if(price!=-1.0){
                price = price * quantity;
                cash+=price;
                return true;
            }
            else{//invalid date
                return false;
            }
        }
        else{//cannot sell that many
            return false;
        }
    }
    return true;
}

/* Returns a string representation of the player in the format: cash,symbol:quantity,symbol:quantity... Numeric output is fixed, setprecision(2). Always prints the cash value (even if 0.00), but only prints stocks if the map is not empty.*/
string Player::to_str(){
    map<string,long>::iterator iter;
    
    ostringstream str;
    
    str << fixed;
    str << setprecision(2) << cash;
    for(iter = stocks.begin() ; iter!=stocks.end() ; iter++){
        str << "," << iter->first << ":" << iter->second;
    }
    
    return str.str();
}

/*Returns a new Player that combines the two provided player (new player cash would equal player1 cash + player2 cash). The caller and the argument Players then have their cash set to 0 and their stocks cleared*/
Player Player::combine(Player &p2){
    Player p3;
    map<string, long>::iterator iter1,iter2;
    long quantity;
    for(iter1 = stocks.begin() ; iter1 != stocks.end() ; iter1++){
        quantity = stocks[iter1->first];
        p3.stocks[iter1->first] = quantity;
    }
    for(iter2 = p2.stocks.begin() ; iter2 != p2.stocks.end() ; iter2++){
        quantity = p2.stocks[iter2->first];
        p3.stocks[iter2->first] = quantity;
    }
    p3.cash=p2.cash+cash;
    stocks.clear();
    cash=0;
    p2.stocks.clear();
    p2.cash=0;
    
    return p3;
}
