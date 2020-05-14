#include "init.hpp"

#define add_info(b,p,e12,e23,e34) s=Signature(1,p,e12,e23,e34);\
file_data.open(DATA_DIR+s.filename(), ios::out | ios::binary);\
c=Braid::code(b);file_data.write(&c,1);\
file_data.close();\
file_csv<<s.csv()<<",2,1"<<endl;

void init(){
  fstream file_data,file_csv;;
  //Length 0
  file_csv.open(DATA_DIR+"0.csv",ios::out);
  Signature s(0,0,0,0,0);
  file_data.open(DATA_DIR+s.filename(), ios::out | ios::binary);
  file_csv<<s.csv()<<",1,1"<<endl;
  file_data.close();
  file_csv.close();

  //Length 1
  char c;
  file_csv.open(DATA_DIR+"1.csv",ios::out);
  add_info( 2,s2, 0, 1, 0);
  add_info( 3,s3, 0, 0, 1);
  file_csv.close();
}
