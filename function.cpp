/* project 05 
Steganography
section 012
02/25/2019
*/

#include<iostream>
using std::cout; using std::cin; using std::endl; using std::boolalpha;
#include<string>
using std::string;
#include<stdio.h>
#include <bitset>
#include <cmath>
#include <cstdlib>
/*#include "proj05_functions.h"
#pragma once

#include<string>
using std::string;

string lower_case(const string&);
string to_binary(char);
char from_binary(const string&);
bool check_message(const string&, const string&);
string encode(const string&, const string&);
string decode(const string&);*/
string lower_case(string s){
    string word;
    word="";
    for (auto i : s){
        if (isalpha(i)) {
            i= tolower(i);
            word +=i;
        }
        if (! isalpha(i)){
            word+=i;
        }
    }
    return word;
}
// convert the chars which are in the string to lower case.

string to_binary(char c){
    int num,new_num;
    if (not islower(c)){
        return "";
    }
    if (islower(c)){

        num = int(c);
        new_num= num-97;
        string binary = std::bitset<5>(new_num).to_string(); //to binary
        return binary;
    }
}
//convert each char to its binary number.

char from_binary(string bit_str){
    int length, num=0;
    length=bit_str.size();
    if (length != 5){
        return '0';
    }
    for (auto c : bit_str) {
        if (c == '0' || c == '1') {
            num += 1;
            //return lower case
        }
        else{
            return '0';
        }
    }

     if (num ==5) {
         long new_num =std::atoi(bit_str.c_str());
         int decimalNum = 0;
         int i = 0, p_num;
         char re_word;

         //converting binary to decimal
         while (new_num != 0)
         {
             p_num = new_num % 10;
             new_num /= 10;
             decimalNum += p_num * pow(2, i);
             ++i;
         }
         // get alpha
         if (decimalNum>=0 && decimalNum<=25){
             re_word = char(decimalNum+97);
             return re_word;
         }
         else {
             return NULL;
         }
         /*re_word = char(decimalNum+97);
         return re_word;*/
     }
     else {
         return '0';
     }
}
// convert binary number to its decimal and then transfer it to char.

bool check_message(string plaintext, string secret_message){
    int words1=0, words2=0, num;
    for (auto i : plaintext) {
        if (isalpha(i)){
            words1 +=1;
        }
    }
    for (auto a :secret_message){
        if (isalpha(a)){
            words2+=1;
        }
    }
    num = words1 /(5*words2);
    return num >=1;
}
//check these messages, to see wether they are valid.

string encode(string plaintext, string secret_message) {
    string words1, words2, new_words = "", empty = "", count="";
    words1 = lower_case(plaintext);
    words2 = lower_case(secret_message);
    //check the message.
    if (check_message(words1, words2) == true) {
        string num;
        for (auto i : secret_message) {
            num = to_binary(i);
            new_words += num;
         
        }
        // get binary number of the char.
        for (int a=0; a<words1.size();++a) {
            if (isalpha(words1[a])){
                count += words1[a];
            }
        }
        for (int c = 0; c < new_words.size(); ++c) {
            if (new_words[c] == '0') {
                empty += tolower(count[c]);
            }
            else if (new_words[c] == '1') {
                empty += toupper(count[c]);
            }
        }
        // get the rest of the message.
        int as=new_words.size();
        int ad = plaintext.size();
        if (as == ad){
            return empty;
        }
        else if ( as <ad) {
            empty += count.substr(as);

            for (int d = 0; d < plaintext.size(); ++d) {
                if (!isalpha(plaintext[d])) {
                    string id;
                    id = plaintext[d];
                    empty.insert(d, id);
                }
            }
        }
        return empty;
    }
    else {
        return "Error";
    }
}

string decode(string to_decode){
    int words =0;
    //check the message.
    for (auto c: to_decode){
        if (isalpha(c)) {
            words +=1;
        }
    }
    if (words/5 >=1) {

        //decode the binary to its original char. 
        string num="", new_num="", new_words="";
        for (int i=0; i<=to_decode.size(); ++i){
            if (islower(to_decode[i])) {
                num +='0';
            }
            if (isupper(to_decode[i])){
                num+='1';
            }
        }
        for (int c=0; c<(num.size()/5); ++c){
            new_num = num.substr(5*c,5);
            new_words+=from_binary(new_num);
        }
        return new_words;
    }
}
