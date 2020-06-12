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

#ifndef WORK_HPP
#define WORK_HPP

#include <fstream>
#include <vector>
#include "stl.hpp"
#include "braid.hpp"
#include "permutation.hpp"
#include "signature.hpp"

//************************
//* Function declaration *
//************************

//! Load braids of a given signature
//! \param s a Signature
//! \param dst a container to load braids in (vector or unordored_set)
template<Gen G,class T> void load(const Signature<G>& s,T& dst);

//! Load braids of a given minimal signature and then apply an action to each of them
//! \param s a Signature
//! \param dst a container to load braids in (vector or unordored_set)
//! \praam action an Action to apply to each loaded braid
template<class T> void load(const Signature<Artin>& s,T& dst,Signature<Artin>::Action& action);

//! Write in a file certain braid with a given signature
//! \param s Signature to consider
//! \param braids a set of braids
template<Gen G> void output(const Signature<G>& s,const unordered_set<Braid<G>>& braids);

//! Enumerate all braids of signature s and record them in a file
//! \param s Signature to consider
template<Gen G> size_t work(const Signature<G>& s);


//***********************
//* Function definition *
//***********************

template<class T> void
load(const Signature<Artin>& s,T& dst){
  if(not s.has_length_zero()){
    pair<Signature<Artin>,Signature<Artin>::Action> res=s.minimize();
    load(res.first,dst,res.second);
  }
  else{
    Braid<Artin> b;
    insert(dst,b);
  }
}

template<class T> void
load(const Signature<Artin>& s,T& dst,Signature<Artin>::Action& action){
  string filename=s.filename();
  fstream file;
  file.open(DATA_DIR+filename.c_str(),ios::in);
  if(file.is_open()){
    size_t l=s.braid_length();
    size_t bsize=Braid<Artin>::compressed_size(l);
    char buffer[bsize];
    while(true){
      file.read(buffer,bsize);
      if(file.gcount()==0) break;
      Braid<Artin> b(buffer,l);
      if(action.apply_negation) b.negate();
      if(action.apply_phi) b.phi();
      insert(dst,b);
    }
  }
}

template<Gen G> void
output(const Signature<G>& s,const unordered_set<Braid<G>>& braids){
  string filename=s.filename();
  fstream file;
  char l=s.braid_length();
  file.open(DATA_DIR+filename.c_str(),ios::out|ios::app);
  for(auto it=braids.begin();it!=braids.end();++it){
    if(it->length()==l) it->write(file);
  }
  file.close();
}

template<Gen G> size_t
work(const Signature<G>& s_out){
  Signature<G> s_cmp=s_out.comparison();
  unordered_set<Braid<G>> cmp;
  load(s_cmp,cmp);
  size_t n=0;
  for(char i=-3;i<=3;++i){
    if(i!=0){
      Signature<G> s_src=s_out.father(i);
      vector<Braid<G>> src;
      load(s_src,src);
      size_t nsrc=src.size();
      for(size_t k=0;k<nsrc;++k){
	Braid<G> b=src[k];
	b*=i;
	auto p_ins=cmp.insert(b);
	if(p_ins.second) ++n;
      }
    }
  }
  if(n!=0) output(s_out,cmp);
  return n;
}

#endif
