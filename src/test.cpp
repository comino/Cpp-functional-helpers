#include "./functionalHelper.h"
#include <iostream>
#include <vector>
#include <list>

using std::cout;
using std::vector;
using std::string;

int main(){

  vector<int> vec = {1,2,3,4,5,6};

  vec = ELI::filter( vec, [](const auto &i){ return i>=2;});
  auto vec2 = ELI::map(vec, [](const auto &i){ return std::to_string(i) + "!" ;});
  std::cout <<  ELI::reduce(vec, [](int a, int b){ return a+b;}, 0)  << "\n";

  std::cout << "\n";
  for(auto &v: vec2){
    std::cout << v << " ";
  }
  std::cout << "\n";
}
