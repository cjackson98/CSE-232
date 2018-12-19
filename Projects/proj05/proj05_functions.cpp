/*
Chris Jackson
CSE 232 Section 10
Project 05
2/23/18
*/
#include <iostream>
using std::cout; using std::endl;
#include <string>
#include "proj05_functions.h"
//clean_string function removes spaces, punctuation, and numbers from the string and returns the result.
string clean_string(string s){
    
    string final_word;
    for(int i=0;i<s.length();i++){
        s[i]=char(tolower(s[i]));
        if(isalpha(s[i])){
            final_word+=s[i];
        }
    }
    return final_word;
}
//create_encoding function creates the block of text for the encoded words. It adds the keyword to the beginning of the alphabet and then removes duplicates and returns the end result.
string create_encoding(string key){
    
    string alphabet="abcdefghijklmnoprstuvwxyz",word=key+alphabet;
    
    for(auto i=0;i<word.size();i++)
    {
        int x=i+1;
        while(x<word.size())
        {
            if(word[i]==word[x] || word[x]=='q')
            {
                word.erase(x,1);
            }
            else
            {
                x+=1;
            }
        }
    }
    return word;
}
//endcode_digraph function encodes the provided digraph (two letter word) by getting the row and column from the two plain alphabet blocks and transfering those to the keyword blocks and converting it to indexes. Returns the encoded digraph.
string encode_digraph(string dg, string block1, string block2){
    
    string key_block2,key_block1,block0="abcdefghijklmnoprstuvwxyz",block3=block0,encoded_string;
    int index1,row1,col1,index2,row2,col2;
    
    key_block2=create_encoding(block1);
    key_block1=create_encoding(block2);
    
    for(auto i=0;i<=block3.length();i++){
        if(block3[i]==dg[0]){
            index1=i;
            break;
        }
    }
    row1=index1/5;
    col1=index1%5;
    for(auto i=0;i<=block0.length();i++){
        if(block0[i]==dg[1]){
            index2=i;
            break;
        }
    }
    row2=index2/5;
    col2=index2%5;
    index1=row1*5+col2;
    index2=row2*5+col1;
    
    encoded_string.push_back(key_block2[index1]);
    encoded_string.push_back(key_block1[index2]);
    
    return encoded_string;
}
//decode_digraph function does the same as the encode_digraph function but in reverse. Takes the encoded digraph, finds its row/column in the plain alphabet block(s) and uses them to transfer the encoded digraph back to its original form. Returns the decoded digraph.
string decode_digraph(string dg, string block1, string block2){
    
    string block0="abcdefghijklmnoprstuvwxyz",block3=block0,decoded_string;
    int index1,row1,col1,index2,row2,col2;
    
    string key_block2=create_encoding(block2);
    string key_block1=create_encoding(block1);
    
    for(auto i=0;i<=key_block1.length();i++){
        if(key_block1[i]==dg[0]){
            index1=i;
        }
    }
    row1=index1/5;
    col1=index1%5;
    
    for(auto i=0;i<=key_block2.length();i++){
        if(key_block2[i]==dg[1]){
            index2=i;
        }
    }
    row2=index2/5;
    col2=index2%5;
    
    index1=row1*5+col2;
    index2=row2*5+col1;
    
    decoded_string.push_back(block0[index1]);
    decoded_string.push_back(block3[index2]);
    
    return decoded_string;
}
//encode function takes the word to be encoded, sends it to the clean_string function, then adds an 'x' if it has an odd number of characters. Then it splits the words into digraphs and sends them to the encoded_string function along with the keywords and adds the resulting encoded digraph to a string. Returns the fully encoded string.
string encode(string msg, string key1, string key2){
    
    string dg,encoded_string;
    msg=clean_string(msg);
    
    if(msg.length()%2!=0){
        msg=msg+'x';
    }
    for(auto i=1;i<=msg.length();i+=2){
        dg.push_back(msg[i-1]);
        dg.push_back(msg[i]);
        encoded_string=encoded_string+(encode_digraph(dg, key1, key2));
        dg.erase(0);
    }
    
    return encoded_string;
}
//decode function takes the encoded word and decodes it. If the word has an odd number of characters, it adds x. It then splits the word into digraphs and sends them to the decode_digraph function and adds the result to a final decoded string which is returned at the end.
string decode(string msg, string key1, string key2){
    
    string dg,decoded_string;
    if(msg.length()%2!=0){
        msg=msg+'x';
    }
    for(auto i=1;i<=msg.length();i+=2){
        dg.push_back(msg[i-1]);
        dg.push_back(msg[i]);
        decoded_string=decoded_string+(decode_digraph(dg, key1, key2));
        dg.erase(0);
    }
    return decoded_string;
}
