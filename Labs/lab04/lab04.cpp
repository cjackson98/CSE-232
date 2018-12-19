#include<iostream>
using std::cout; using std::endl; using std::cin;
#include<string>
using std::string;
#include<math.h>
using std::pow;

#include<algorithm>
using std::sort;

const string alphabet="abcdefghijklmnopqrstuvwxyz";

long loc_to_dec(string loc){
	
	long num=0;

	for(long i=0;i<loc.size();i++){

		for(long ctr=0;ctr<alphabet.size();ctr++){

			if(loc[i]==alphabet[ctr]){

				num += pow(2,(alphabet.find(loc[i])));
			}
		}
	}

	return num;
}

string abbreviate(string loc){
	
	sort(loc.begin(), loc.end());
	
	for(long i=0;i<loc.size();i++){
		if(loc[1]!=loc[i+1] && loc[i]==loc[i-1]){
			loc[i]=static_cast<char>(loc[i]+1);
			loc.erase(loc.begin()+(i-1));
			i=0;
			sort(loc.begin(), loc.end());
		}
	}
	return loc;
}

string dec_to_long(long dec){
	
	string result;
	string abbreviated;
	for(long i=0;i<dec;i++){
		result+="a";
	}
	abbreviated=abbreviate(result);
	
	return abbreviated;
}

long add_loc(string loc1, string loc2){
	
	string word=loc1+loc2;
	string abbreviated=abbreviate(word);
	long finalWord = loc_to_dec(abbreviated);
	
	return finalWord;
}


int main (){
	string loc1;
	long x;
	cin>>loc1>>x;
	
	cout<<loc_to_dec(loc1)<<" "<<abbreviate(loc1)<<" "<<dec_to_long(x)<<" "<<add_loc(loc1,loc1)<<endl;
	
}