#include "Misc.h"

bool find(std::vector<EntityID> vec, EntityID value) {
  for (auto i : vec) {
    if (i == value) {
      return true;
    }
  }
  return false;
}