#include <iostream>
#include <cstdlib>
#include <exception>
#include <string>

#include <sncabling/om_id.h>
#include <sncabling/label.h>

int main()
{
  int error_code = EXIT_SUCCESS;
  try {

    sncabling::om_id id1(sncabling::OM_MAIN, 1, 3, 6);
    sncabling::label lbl1 = id1.to_label();
    std::cout << "Label #1 = " << lbl1 << std::endl;

    sncabling::om_id id2(sncabling::OM_XWALL, 0, 1, 0, 8);
    sncabling::label lbl2 = id2.to_label();
    std::cout << "Label #2 = " << lbl2 << std::endl;
    if (id1 < id2) {
      std::cout << "Comparison : " << lbl1 << " < " << lbl2 << std::endl;
    }

    sncabling::om_id id3(sncabling::OM_REF, 3);
    sncabling::label lbl3 = id3.to_label();
    std::cout << "Label #3 = " << lbl3 << std::endl;

  } catch (std::exception & err) {
    std::cerr << "[error] " << err.what() << std::endl;
  } catch (...) {
    std::cerr << "[error] " << "unexpected error!" << std::endl;
  }
  return error_code;
}
