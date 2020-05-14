#ifndef PERMUTATION_HPP
#define PERMUTATION_HPP

#include <iostream>
#include "config.hpp"

using namespace std;

static const string permutations[24] = {
  "abcd","abdc","acbd","acdb","adbc","adcb",
  "bacd","badc","bcad","bcda","bdac","bdca",
  "cabd","cadb","cbad","cbda","cdab","cdba",
  "dabc","dacb","dbac","dbca","dcab","dcba"};

static const string inverse[24] = {
  "abcd","abdc","acbd","adbc","acdb","adcb",
  "bacd","badc","cabd","dabc","cadb","dacb",
  "bcad","bdac","cbad","dbac","cdab","dcab",
  "bcda","bdca","cbda","dbca","cdba","dcba"};

static const char phi_image[24] = {0,6,2,12,8,14,1,7,4,18,10,20,3,13,5,19,16,22,9,15,11,21,17,23};

static const char s1 = 6;

static const char left_prod_s1[24] = {6,7,8,9,10,11,0,1,2,3,4,5,14,15,12,13,17,16,20,21,18,19,23,22};

static const char s2 = 2;

static const char left_prod_s2[24] = {2,3,0,1,5,4,12,13,14,15,16,17,6,7,8,9,10,11,19,18,22,23,20,21};

static const char s3 = 1;

static const char left_prod_s3[24] = {1,0,4,5,2,3,7,6,10,11,8,9,18,19,20,21,22,23,12,13,14,15,16,17};

static const char * left_prod[4]={nullptr,left_prod_s1,left_prod_s2,left_prod_s3};

char eval(char p,char i);

inline char eval(char p,char i){
  return permutations[p][i-1]-'a'+1;
}

inline char eval_inv(char p,char i){
  return inverse[p][i-1]-'a'+1;
}

#endif
