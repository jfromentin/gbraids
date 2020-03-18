#include "init.hpp"

void init(){
  fstream file;
  char c;
  //Length 0
  file.open("data/0abcd0", ios::out | ios::binary);
  file.close();
  //Length 1
  file.open("data/1bacd1", ios::out | ios::binary);
  c=Braid::code(1);file.write(&c,1);
  file.close();
  file.open("data/1bacd-1", ios::out | ios::binary);
  c=Braid::code(-1);file.write(&c,1);
  file.close();
  file.open("data/1acbd1", ios::out | ios::binary);
  c=Braid::code(2);file.write(&c,1);
  file.close();
  file.open("data/1acbd-1", ios::out | ios::binary);
  c=Braid::code(-2);file.write(&c,1);
  file.close();
  file.open("data/1abdc1", ios::out | ios::binary);
  c=Braid::code(3);file.write(&c,1);
  file.close();
  file.open("data/1abdc-1", ios::out | ios::binary);
  c=Braid::code(-3);;file.write(&c,1);
  file.close();
}
