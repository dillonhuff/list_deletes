#include <cassert>
#include <iostream>
#include <list>
#include <numeric>
#include <sys/time.h>
#include <vector>

typedef unsigned long long timestamp_t;

static timestamp_t get_timestamp() {
  struct timeval now;
  gettimeofday(&now, NULL);
  return now.tv_usec + (timestamp_t)now.tv_sec * 1000000;
}

double time_vector(int num_elems) {
  std::vector<int> vints(num_elems);
  std::iota(begin(vints), end(vints), 0);
  auto start = get_timestamp();
  for (int i = 0; i < num_elems; i++) {
    int r = 0 + (rand() % (int)(vints.size() - 1 - 0 + 1));
    vints.erase(begin(vints) + r);
  }
  auto end = get_timestamp();
  double usecs = (end - start);
  return usecs;
}

double time_list(int num_elems) {
  std::list<int> vints(num_elems);
  std::iota(begin(vints), end(vints), 0);
  auto start = get_timestamp();
  for (int i = 0; i < num_elems; i++) {
    int r = 0 + (rand() % (int)(vints.size() - 1 - 0 + 1));
    auto it = begin(vints);
    std::advance(it, r);
    vints.erase(it);
  }
  auto end = get_timestamp();
  double usecs = (end - start);
  return usecs;
}

int main() {
  int num_elems = 1;
  int limit = 100000;
  std::vector<int> n_elems;
  std::vector<double> vector_times;
  std::vector<double> list_times;
  while (num_elems <= limit) {
    n_elems.push_back(num_elems);
    vector_times.push_back(time_vector(num_elems));
    list_times.push_back(time_list(num_elems));
    num_elems *= 10;
  }
  assert(vector_times.size() == list_times.size());
  assert(vector_times.size() == n_elems.size());
  std::cout << "# elems, vector time, list time" << std::endl;
  for (unsigned i = 0; i < vector_times.size(); i++) {
    std::cout << n_elems[i] << ", " << vector_times[i] << ", " << list_times[i] << std::endl;
  }
}
