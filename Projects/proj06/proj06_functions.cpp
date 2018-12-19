/*
Chris Jackson
CSE 232 Section 10
Project 06
3/1/18
*/

#include <iostream>
using std::cout; using std::endl;
#include <string>
using std::string; using std::to_string;
#include <vector>
using std::vector;
#include "proj06_functions.h"

//creates and returns a string that represents the values in the vector seperated by a comma.
string vec_2_str(const vector<long>& v){
    string str="", num;
    for(int i=0;i<v.size();i++){
        num=to_string(v[i]);
        str+=(num);
        str+=",";
    }
    str.pop_back();
    return str;
}
//creates and returns a vector of long values in the Fibbonaci sequence for the number provided
vector<long> gen_nstep_vector(long limit, long nstep){
    vector<long>v={1,1,2};
    long total=0,x,y;
    while(v.size()<=nstep){
        for(long i=0;i<v.size();i++){
            total=total+v[i];
        }
        v.push_back(total);
        total=0;
    }
    v.pop_back();
    
    while(v.back()<=limit){
        x=v.size();
        y=x-nstep;
        for(;y<x;y++){
            total=total+v[y];
        }
        v.push_back(total);
        total=0;
    }
    v.pop_back();
    
    return v;
}

//creates and returns an encoded binary string that represents the provided number
string num_to_nstep_coding(long num, long nstep){
    string str="";
    long N=num,remainder=num, max_num, position=0, max_position=0;
    vector<long> v_positions={};
    
    while(remainder>0){
        max_num=0;
        vector<long> v=gen_nstep_vector(N, nstep);
        for(long i=1;i<v.size();i++){
            if(v[i]<=N && v[i]>max_num){
                max_num=v[i];
                position=i;
            }
        }
        remainder=N-max_num;
        v_positions.push_back(position);
        N=remainder;
    }
    for(auto i : v_positions){
        if(i>max_position){
            max_position=i;
        }
    }
    for(long i=0;i<(max_position-1);i++){
        str.push_back('0');
    }
    str=str+'1';
    
    for(auto i : v_positions){
        if(i!=max_position){
            str[i-1]='1';
        }
    }
    
    return str;
}

//decodes a binary string that represents an unknown number and return the number
long nstep_coding_to_num(const string& coding,const vector<long>& nstep_sequence){
    long ctr=0,total=0;

    for(auto i : coding){
        ctr+=1;
        if(i=='1'){
            total=total+nstep_sequence[ctr];
        }
    }
    return total;
}
