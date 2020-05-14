#include <set>
#include <algorithm>
#include "../dist/task.hpp"
#include "signature.hpp"

struct GTaskInput{
  Signature signature;
  size_t estimation;
};

struct GTaskOutput{
  size_t number;
  size_t duration;
};

bool compare_gtask(const Task& t1,const Task& t2);
Task* generate_gtask(set<Signature>& signatures);




