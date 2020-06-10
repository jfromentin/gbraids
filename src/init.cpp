/*
* This file is part of Gbraids (https://github.com/jfromentin/gbraids).
* Copyright (c) 2020 Jean Fromentin (fromentin@math.cnrs.fr).
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, version 3.
*
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
* General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include "init.hpp"

void init(){
  fstream file_data,file_csv;;
  //Length 0
  file_csv.open(DATA_DIR+"0.csv",ios::out);
  Signature<Artin> s(0,Permutation(),0,0,0,0);
  file_data.open(DATA_DIR+s.filename(), ios::out | ios::binary);
  file_csv<<s.csv()<<",1,1"<<endl;
  file_data.close();
  file_csv.close();

  //Length 1
  char c;
  file_csv.open(DATA_DIR+"1.csv",ios::out);
  s=Signature<Artin>(1,Permutation(1,3,2,4),0,-1,0,0);
  file_data.open(DATA_DIR+s.filename(), ios::out | ios::binary);
  c=Braid::code(-2);file_data.write(&c,1);
  file_data.close();
  file_csv<<s.csv()<<",2,1"<<endl;

  s=Signature<Artin>(1,Permutation(1,2,4,3),0,0,-1,0);
  file_data.open(DATA_DIR+s.filename(), ios::out | ios::binary);
  c=Braid::code(-3);file_data.write(&c,1);
  file_data.close();
  file_csv<<s.csv()<<",4,1"<<endl;
  file_csv.close();
}

