#ifndef MEMORY_HPP
#define MEMORY_HPP
#include <cstdint>
#include <iostream>

using namespace std;

#define EDL_NODES 65536

struct EDLNode{
  uint16_t next,prev;
  int32_t data;
};

//Efficient buffered implementation of douly linked list
//Node at position 0 is not an element of the list and contains
//the position of the hean and the tail of the list

class EDList{
private:
  // uint16_t s;
  EDLNode pool[EDL_NODES]; //Size of 8*65536 = 512ko
public:
  uint16_t s,rs;
  EDList();
  void clear(int32_t d=0);
  bool empty() const;
  uint16_t first() const;
  uint16_t last() const;
  uint16_t next(uint16_t) const;
  uint16_t prev(uint16_t) const;
  int32_t get(uint16_t) const;
  void set(uint16_t,int32_t);
  int32_t get_next(uint16_t) const;
  int32_t get_prev(uint16_t) const;
  int32_t get_first() const;
  int32_t get_last() const;
  void erase(uint16_t);
  uint16_t insert_after(uint16_t,int32_t);
  uint16_t insert_before(uint16_t,int32_t);
  uint16_t push_back(int32_t);
  uint16_t push_front(int32_t);
  void full_disp();
  size_t size() const;
};

inline EDList::EDList(){
}

inline void
EDList::clear(int32_t d){
  rs=s=0;
  pool[0].next=0;
  pool[0].prev=0;
  pool[0].data=d;
}

inline bool
EDList::empty() const{
  return rs==0;
}

inline uint16_t
EDList::first() const {
  return pool[0].next;
}

inline uint16_t
EDList::last() const{
  return pool[0].prev;
}

inline uint16_t
EDList::next(uint16_t i) const{
  return pool[i].next;
}

inline uint16_t
EDList::prev(uint16_t i) const{
  return pool[i].prev;
}

inline int32_t
EDList::get_first() const{
  return pool[first()].data;
}

inline int32_t
EDList::get_last() const{
  return pool[last()].data;
}

inline int32_t
EDList::get(uint16_t i) const{
  return pool[i].data;
}

inline void
EDList::set(uint16_t i,int32_t v){
  pool[i].data=v;
}
inline int32_t
EDList::get_next(uint16_t i) const{
  return pool[next(i)].data;
}

inline int32_t
EDList::get_prev(uint16_t i) const{
  return pool[prev(i)].data;
}

inline void
EDList::erase(uint16_t i){
  uint16_t p=pool[i].prev;
  uint16_t n=pool[i].next;
  pool[p].next=n;
  pool[n].prev=p;
  --rs;
}

inline uint16_t
EDList::insert_after(uint16_t i,int32_t d){
  uint16_t n=pool[i].next;
  EDLNode& node=pool[++s];
  pool[i].next=s;
  pool[n].prev=s;
  node.prev=i;
  node.next=n;
  node.data=d;
  ++rs;
  return s;
}

inline uint16_t
EDList::insert_before(uint16_t i,int32_t d){
  uint16_t p=pool[i].prev;
  EDLNode& node=pool[++s];
  pool[p].next=s;
  pool[i].prev=s;
  node.prev=p;
  node.next=i;
  node.data=d;
  ++rs;
  return s;
}

inline uint16_t
EDList::push_back(int32_t d){
  return insert_before(0,d);
}

inline uint16_t
EDList::push_front(int32_t d){
  return insert_after(0,d);
}

inline void
EDList::full_disp(){
  for(uint16_t i=0;i<=s;++i){
    cout<<"@"<<i<<" : "<<pool[i].prev<<" | "<<pool[i].data<<" | "<<pool[i].next<<endl;
  }
}

inline size_t
EDList::size() const{
  return rs;
}
#endif
