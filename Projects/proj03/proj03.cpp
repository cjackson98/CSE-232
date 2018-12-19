#include<iostream>
using std::cout; using std::cin; using std::endl; using std::boolalpha;
#include<cmath>
#include<string>
using std::to_string; using std::string;

/*
Chris Jackson
Section 010
Project 03
2/1/18
*/

string abIndex_friend(long ab_numerator, long ab_denominator, long f_pair){
    return to_string(ab_numerator) + "/" + to_string(ab_denominator) +
    ":" + to_string(f_pair);
}

// YOUR FUNCTIONS HERE

long divisor_sum(long num){
    long sum=0,divide;
    double square;
    square=sqrt(num);
    for(long i=1;i<=square;i++){
        if(num%i==0){
            divide=(num/i);
            if(divide!=i){
                sum=sum+divide+i;
            }
            else{
                sum=sum+i;
            }
        }
    }
    return sum;
}

long gcd(long x,long y){
    if(y==0){
        return x;
    }
    else{
        return gcd(y, x%y);
    }
}

bool is_solitary(long n){
    bool solitary=false;
    long d_sum,n_gcd;
    d_sum=divisor_sum(n);
    n_gcd=gcd(n,d_sum);
    if(n_gcd==1){
        solitary=true;
    }
    return solitary;
}

string friendly_check(long num,long upper){
    long d_sum,d_sum2,reduce_num,reduce_num2,og_i,numerator1,numerator2,denominator1,denominator2;
    string return_values;
    
    //abun is ratio of d_sum/num
    
    d_sum=divisor_sum(num);
    reduce_num=gcd(d_sum,num);
    numerator1=d_sum/reduce_num;
    denominator1=num/reduce_num;
    
    for(long i=2;i<=upper;i++){

        d_sum2=divisor_sum(i);
        reduce_num2=gcd(d_sum2,i);
        numerator2=d_sum2/reduce_num2;
        denominator2=i/reduce_num2;
        
        if(numerator1==numerator2 && denominator1==denominator2 && i!=num){
            og_i=i;
            return abIndex_friend(numerator1, denominator1, og_i);
        }

    }
    return abIndex_friend(numerator1, denominator1, -1);
}

int main (){
    cout << boolalpha;   // print true or false for bools
    int test;
    cin >> test;
    switch (test) {
        case 1 : {   // divisor sum test
            long input;
            cin >> input;
            cout << divisor_sum(input) << endl;
            break;
        } // of case 1
            
        case 2:{    // gcd test
            long first, second;
            cin >> first >> second;
            cout << gcd(first, second) << endl;
            break;
        } // of case 2
            
        case 3: {    // is_solitary test
            long input;
            cin >> input;
            cout << is_solitary(input) << endl;
            break;
        } // of case 3
            
        case 4: {
            // friend check. Make sure the return value is the
            // result of calling abIndex_friend, a string!
            long input, limit;
            cin >> input >> limit;
            cout << friendly_check(input, limit) << endl;
            break;
        } // of case 4
            
    } // of switch
} // of main
