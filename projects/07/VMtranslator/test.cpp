#include <iostream>
#include <sstream>
#include <string>

int main() {
  std::string w1 = "hello how 3";
  std::string w2 = " not ";

  std::istringstream s1stream(w1);
  std::istringstream s2stream(w2);

  std::string s1;
  std::string s2;
  int s3;

  s1stream >> s1 >> s2 >> s3;
  std::cout << s1 << " " << s2 << " " << s3 << std::endl;

  std::string s4;
  std::string s5 = "";
  int s6;

  s2stream >> s4 >> s5 >> s6;
  std::cout << s4 << " " << s5 << " " << s6 << std::endl;

  return 0;
}