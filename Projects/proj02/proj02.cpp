#include <iostream>
using std::cout;using std::cin;using std::endl;using std::fixed;
#include <iomanip>
using std::setprecision;using std::setw;
#include <cmath>

/*
 Chris Jackson
 1/25/18
 Section 010
 Project 2
 */

int main(){
    long start,end,num,max_num=0,max_line=0,num_ctr=0,max_ctr=0,line_num=0,initial_start=0;
    bool print;
    
    cin>>start>>end>>print;
    initial_start=start;
    //add a counter that goes up for each line and resests the next line. add a max for that counter
    if(initial_start>=2 and end>=2){
        while(start<=end){
            num=start;
            num_ctr=0;
            
            //max_ctr=0;
            if(print){
                cout<<num<<": ";
            }
            while(num>1){
                if(num%2==0){
                    num=pow(num,.5);
                    num=floor(num);
                    num_ctr++;
                    if(num_ctr>max_ctr){
                        max_ctr=num_ctr;
                        line_num=start;
                    }
                    if(num!=1){
                        if(print){
                            cout<<num<<",";
                        }
                        if(num>max_num){
                            max_num=num;
                            max_line=start;
                        }
                    }
                    else{
                        if(print)
                            cout<<num;
                    }
                }
                else if (num%2!=0){
                    num=pow(num,1.5);
                    num=floor(num);
                    num_ctr++;
                    if(num_ctr>max_ctr){
                        max_ctr=num_ctr;
                        line_num=start;
                    }
                    if(num!=1){
                        if(print){
                            cout<<num<<",";
                        }
                        if(num>max_num){
                            max_num=num;
                            max_line=start;
                        }
                    }
                    else{
                        if(print)
                            cout<<num;
                    }
                }
            }
            if(print){
                cout<<endl;
            }
            start++;
        }
        if(initial_start<end and initial_start>=2 and end>=2){
            cout<<line_num<<", "<<max_ctr<<endl;
            cout<<max_line<<", "<<max_num<<endl;
        }
        else
            cout<<"Error"<<endl;
    }
    else
        cout<<"Error"<<endl;
    return 0;
}
