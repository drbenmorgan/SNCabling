#include <iostream>
#include <cstdlib>
#include <exception>
#include <string>

#include <sncabling/label.h>

int main()
{
  int error_code = EXIT_SUCCESS;
  try {
    sncabling::label lbl1('M', 0, 3, 12);
    std::cout << "Label #1 = " << lbl1 << std::endl;

    std::string word = "X:0.2.1.7";

    sncabling::label lbl2;
    if (lbl2.parse_from(word)) {
      std::cout << "Label #2 = " << lbl2 << std::endl;
    }

    sncabling::label lbl3;
    if (lbl3.parse_from(word, 'X', 3)) {
      std::cout << "Label #3 = " << lbl3 << std::endl;
    } else {
      std::cerr << "Label #3 cannot be parsed from " << word << std::endl;
    }

    sncabling::label lbl4;
    if (lbl4.parse_from(word, 'G', 4)) {
      std::cout << "Label #4 = " << lbl4 << std::endl;
    } else {
      std::cerr << "Label #4 cannot be parsed from " << word << std::endl;
    }

    word = "H:0.0.23";
    sncabling::label lbl5;
    if (lbl5.parse_from(word)) {
      std::cout << "Label #5 = " << lbl5 << std::endl;
    } else {
      std::cerr << "Label #5 cannot be parsed from " << word << std::endl;
    }

  } catch (std::exception & err) {
    std::cerr << "[error] " << err.what() << std::endl;
  } catch (...) {
    std::cerr << "[error] " << "unexpected error!" << std::endl;
  }
  return error_code;
}
