#ifndef DIST_MESSAGE_HPP
#define DIST_MESSAGE_HPP

#include <iostream>
#include <cassert>
#include <cstdint>
#include <cstring>
#include "task.hpp"

#define MAX_MSG_SIZE 1024

enum MessageType : char{UNKOWN,CODE,STRING,INTEGER,DATA};

using Integer=int64_t;


using namespace std;

struct Data{
  char* buffer;
  size_t size;
};

class Message{
private:
  size_t csize;
public:
  char buffer[MAX_MSG_SIZE];
  size_t size;
  void set_code(char c);
  void set_string(string s);
  void set_integer(Integer i);
  void set_data(const char* buffer,size_t s);
  void clear();
  bool add(char l);
  bool add_to_code(char l);
  bool add_to_string(char l);
  bool add_to_integer(char l);
  bool add_to_data(char l);
  MessageType get_type();
  char get_code();
  string get_string();
  Integer get_integer();
  size_t get_data_size();
  char* get_data_buffer();
};

inline void
Message::set_code(char c){
  size=2;
  buffer[0]=CODE;
  buffer[1]=c;
}

inline void
Message::clear(){
  csize=0;
  size=0;
}

inline MessageType
Message::get_type(){
  return (MessageType)buffer[0];
}

inline char
Message::get_code(){
  assert(buffer[0]==CODE);
  return buffer[1];
}

inline string
Message::get_string(){
  assert(buffer[0]==STRING);
  size_t s=size-3;
  return string(&buffer[3],s);
}

inline Integer
Message::get_integer(){
  assert(buffer[0]==INTEGER);
  Integer i;
  memcpy(&i,&buffer[1],sizeof(Integer));
  return i;
}



#endif
