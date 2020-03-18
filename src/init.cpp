#include "init.hpp"

void init(){
  fstream file;
  char c;
  //Length 0
  file.open(DATA_DIR+"0abcd0", ios::out | ios::binary);
  file.close();
  //Length 1
  file.open(DATA_DIR+"1bacd1", ios::out | ios::binary);
  c=Braid::code(1);file.write(&c,1);
  file.close();
  file.open(DATA_DIR+"1bacd-1", ios::out | ios::binary);
  c=Braid::code(-1);file.write(&c,1);
  file.close();
  file.open(DATA_DIR+"1acbd1", ios::out | ios::binary);
  c=Braid::code(2);file.write(&c,1);
  file.close();
  file.open(DATA_DIR+"1acbd-1", ios::out | ios::binary);
  c=Braid::code(-2);file.write(&c,1);
  file.close();
  file.open(DATA_DIR+"1abdc1", ios::out | ios::binary);
  c=Braid::code(3);file.write(&c,1);
  file.close();
  file.open(DATA_DIR+"1abdc-1", ios::out | ios::binary);
  c=Braid::code(-3);;file.write(&c,1);
  file.close();
}
