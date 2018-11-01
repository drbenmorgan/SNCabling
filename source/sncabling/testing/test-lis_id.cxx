#include <iostream>
#include <cstdlib>
#include <exception>
#include <string>

#include <sncabling/lis_id.h>
#include <sncabling/label.h>

int main(void)
{
  int error_code = EXIT_SUCCESS;
  try {

    sncabling::lis_id id1(sncabling::LIS_LED, 9);
    sncabling::label lbl1 = id1.to_label();
    std::cout << "Label #1 = " << lbl1 << std::endl;

    sncabling::lis_id id2(sncabling::LIS_BUNDLE, 8);
    sncabling::label lbl2 = id2.to_label();
    std::cout << "Label #2 = " << lbl2 << std::endl;

    sncabling::lis_id id3(sncabling::LIS_FIBER, 8, 1);
    sncabling::label lbl3 = id3.to_label();
    std::cout << "Label #3 = " << lbl3 << std::endl;
    
  } catch (std::exception & err) {
    std::cerr << "[error] " << err.what() << std::endl;
  } catch (...) {
    std::cerr << "[error] " << "unexpected error!" << std::endl;
  }
  return error_code;
}
