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

#ifndef INIT_HPP
#define INIT_HPP

#include <fstream>
#include "braid.hpp"
#include "signature.hpp"

using namespace std;

template<Gen G> void write_braid(char g,char l,Permutation p,char e12,char e23,char e34,char e14,fstream& stdfile_csv);
template<Gen G> void write_braid(char g1,char g2,char l,Permutation p,char e12,char e23,char e34,char e14,fstream& stdfile_csv);

template<Gen G> void init();

template<Gen G> inline void
write_braid(char g,char l,Permutation p,char e12,char e23,char e34,char e14,fstream& file_csv ){
  fstream file_data;
  Signature<G> s(l,p,e12,e23,e34,e14);
  file_data.open(DATA_DIR+s.filename(), ios::out | ios::binary);
  char c=Braid<G>::code(g);file_data.write(&c,1);
  file_data.close();
  file_csv<<s.csv()<<','<<s.rank()<<",1"<<endl;
}

template<Gen G> inline void
write_braid(char g1,char g2,char l,Permutation p,char e12,char e23,char e34,char e14,fstream& file_csv ){
  fstream file_data;
  Signature<G> s(l,p,e12,e23,e34,e14);
  file_data.open(DATA_DIR+s.filename(), ios::out | ios::binary);
  char c=Braid<G>::code(g1);file_data.write(&c,1);
  c=Braid<G>::code(g2);file_data.write(&c,1);
  file_data.close();
  file_csv<<s.csv()<<','<<s.rank()<<",2"<<endl;
}

#endif
