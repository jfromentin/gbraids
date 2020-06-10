#include <set>
#include <algorithm>
#include "../dist/task.hpp"
#include "signature.hpp"

struct GTaskInput{
  Signature<Artin> signature;
};

struct GTaskOutput{
  size_t number;
};

bool compare_gtask(const Task& t1,const Task& t2);
Task* generate_gtask(set<Signature<Artin>>& signatures);




