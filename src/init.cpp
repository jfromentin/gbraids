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

template<> void init<Artin>(){
  fstream file_csv;
  //length 0
  file_csv.open(DATA_DIR+"0.csv",ios::out);
  Signature<Artin> s(0,Permutation(1,2,3,4),0,0,0,0);
  file_csv<<s.csv()<<",1,1"<<endl;
  file_csv.close();

  //Length 1
  char c;
  file_csv.open(DATA_DIR+"1.csv",ios::out);
  write_braid<Artin>(-2,1,Permutation(1,3,2,4),0,-1,0,0,file_csv);
  write_braid<Artin>(-3,1,Permutation(1,2,4,3),0,0,-1,0,file_csv);
  file_csv.close();
}

