#include <iostream>
#include <cstdlib>
#include <exception>
#include <string>

#include <sncabling/calo_feb_id.h>
#include <sncabling/label.h>

int main(void)
{
  int error_code = EXIT_SUCCESS;
  try {

    sncabling::calo_feb_id id1(sncabling::CALOFEB_CRATE, 0);
    sncabling::label lbl1 = id1.to_label();
    std::cout << "Label #1 = " << lbl1 << std::endl;

    sncabling::calo_feb_id id2(sncabling::CALOFEB_BOARD, 0, 3);
    sncabling::label lbl2 = id2.to_label();
    std::cout << "Label #2 = " << lbl2 << std::endl;
    if (id1 < id2) {
      std::cout << "Comparison : " << lbl1 << " < " << lbl2 << std::endl;
    }

    sncabling::calo_feb_id id3(sncabling::CALOFEB_CHANNEL, 0, 3, 7);
    sncabling::label lbl3 = id3.to_label();
    std::cout << "Label #3 = " << lbl3 << std::endl;

    sncabling::calo_feb_id id4 = id3.get_crate_id();
    sncabling::label lbl4 = id4.to_label();
    std::cout << "Label #4 = " << lbl4 << std::endl;
 
  } catch (std::exception & err) {
    std::cerr << "[error] " << err.what() << std::endl;
  } catch (...) {
    std::cerr << "[error] " << "unexpected error!" << std::endl;
  }
  return error_code;
}
