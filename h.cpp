#include <iostream>
#include <cstdio>

int main() {
  char filename[] = "program.cpp";

  // remove the file "program.cpp"
  int result = remove(filename);


  std::cout << result;

  return 0;
}