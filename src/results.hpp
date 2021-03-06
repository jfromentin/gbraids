#ifndef RESULTS_HPP
#define RESULTS_HPP

#include <cilk/cilk.h>
#include <cilk/reducer.h>
#include "config.hpp"

struct Results{
  size_t n_amp[MAXLEN+1];
  size_t n_red[MAXLEN+1];
  size_t n[MAXLEN+1];
  Results();
  void reset();
};

class ResultsReducer{
private:
  struct Monoid:cilk::monoid_base<Results>{
    static void reduce(Results* left, Results* Right);
  };
  
  cilk::reducer<Monoid> imp_;
public:
  ResultsReducer();
  size_t& n_amp(size_t i);
  size_t& n_red(size_t i);
  size_t& n(size_t i);
  void reset();
};

extern ResultsReducer cilk_results;

inline
Results::Results(){
  reset();
}

inline void
Results::reset(){
  for(size_t i=0;i<=MAXLEN;++i){
    n_amp[i]=0;
    n_red[i]=0;
    n[i]=0;
  }
}

inline
ResultsReducer::ResultsReducer(){
  reset();
}

inline void
ResultsReducer::Monoid::reduce(Results* left,Results* right){
  for(size_t i=0;i<=MAXLEN;++i){
    left->n_amp[i]+=right->n_amp[i];
    left->n_red[i]+=right->n_red[i];
    left->n[i]+=right->n[i];
  }
}

inline void
ResultsReducer::reset(){
  imp_.view().reset();
}

inline size_t&
ResultsReducer::n_amp(size_t i){
  return imp_.view().n_amp[i];
}

inline size_t&
ResultsReducer::n_red(size_t i){
  return imp_.view().n_red[i];
}

inline size_t&
ResultsReducer::n(size_t i){
  return imp_.view().n[i];
}

#endif
