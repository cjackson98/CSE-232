#include<iostream>
using std::cout; using std::cin; using std::endl; using std::boolalpha;
#include<string>
using std::string; using std::to_string;
#include<cmath>

/*
 Chris Jackson
 Section 010
 2/8/18
 CSE 232 Project 04
*/

const string the_chars = "0123456789abcdef";

string reverse_string(string word){
    string newString;
    for(long i=word.size()-1;i>=0;--i){
        newString+=word[i];
    }
    return newString;
}

bool is_palindrome(string word){
    bool palindrome=false;
    string reverse_word;
    reverse_word=reverse_string(word);
    if(word==reverse_word){
        palindrome=true;
    }
    return palindrome;
}

string long_to_base(long number, long base){
    long x;
    string result;
    while(number>0){
        x=number%base;
        result=the_chars[x]+result;
        number=number/base;
    }
    return result;
}

bool is_prime(long number){
    bool isPrime=true;
    for(long i = 2; i <= number / 2; ++i)
    {
        if(number % i == 0)
        {
            isPrime = false;
            break;
        }
    }
    return isPrime;
}


string is_pal_prime(long number){
    
    long base=2;
    string result;
    
    bool isPrime=is_prime(number);
    string word=long_to_base(number,base);
    bool isPalindrome=is_palindrome(word);
    if(isPrime==true && isPalindrome==true){
        if(base==2){
            result="binary-pal-prime";
        }
        else if(base==10){
            result="decimal-pal-prime";
        }
        else if(base==16){
            result="hex-pal-prime";
        }
        else{
            result="not-pal-prime";
        }
    }
    while(1){
        bool isPrime=is_prime(number);
        string word=long_to_base(number,base);
        bool isPalindrome=is_palindrome(word);
        if(isPrime==true && isPalindrome==true){
            if(base==2){
                result="binary-pal-prime";
            }
            else if(base==10){
                result="decimal-pal-prime";
            }
            else if(base==16){
                result="hex-pal-prime";
            }
            break;
        }
        else if(base==2){
            base=10;
            continue;
        }
        else if(base==10){
            base=16;
            continue;
        }
        else{
            result="not-pal-prime";
            break;
        }
    }
    
    return result;
}


int main (){
    long test_num;
    cin >> test_num;
    cout << boolalpha;
    
    switch(test_num) {
            
        case 1: {
            string input;
            cin >> input;
            cout << reverse_string(input);
            break;
        }
            
        case 2:{
            string input;
            cin >> input;
            cout << is_palindrome(input);
            break;
        }
            
        case 3:{
            long n, base;
            cin >> n >> base;
            cout << long_to_base(n,base);
            break;
        }
            
        case 4:{
            long n;
            cin >> n;
            cout << is_prime(n);
            break;
        }
            
        case 5:{
            long n;
            cin >> n;
            cout << is_pal_prime(n);
            break;
        }
            
    } // of switch
}  // of main


