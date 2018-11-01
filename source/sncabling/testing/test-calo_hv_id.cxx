#include <iostream>
#include <cstdlib>
#include <exception>
#include <string>

#include <sncabling/calo_hv_id.h>
#include <sncabling/label.h>

int main(void)
{
  int error_code = EXIT_SUCCESS;
  try {

    sncabling::calo_hv_id id1(sncabling::CALOHV_CRATE, 0);
    sncabling::label lbl1 = id1.to_label();
    std::cout << "Label #1 = " << lbl1 << std::endl;

    sncabling::calo_hv_id id2(sncabling::CALOHV_BOARD, 0, 3);
    sncabling::label lbl2 = id2.to_label();
    std::cout << "Label #2 = " << lbl2 << std::endl;
    if (id1 < id2) {
      std::cout << "Comparison : " << lbl1 << " < " << lbl2 << std::endl;
    }

    sncabling::calo_hv_id id3(sncabling::CALOHV_CHANNEL, 0, 3, 7);
    sncabling::label lbl3 = id3.to_label();
    std::cout << "Label #3 = " << lbl3 << std::endl;

    sncabling::calo_hv_id id4 = id3.get_crate_id();
    sncabling::label lbl4 = id4.to_label();
    std::cout << "Label #4 = " << lbl4 << std::endl;

    sncabling::calo_hv_id id5(sncabling::CALOHV_EXTHARNESS, 3);
    sncabling::label lbl5 = id5.to_label();
    std::cout << "Label #5 = " << lbl5 << std::endl;

    sncabling::calo_hv_id id6(sncabling::CALOHV_INTHARNESS, 3);
    sncabling::label lbl6 = id6.to_label();
    std::cout << "Label #6 = " << lbl6 << std::endl;

    sncabling::calo_hv_id id7(sncabling::CALOHV_INTCABLE, 3, 41);
    sncabling::label lbl7 = id7.to_label();
    std::cout << "Label #7 = " << lbl7 << std::endl;
 
 
  } catch (std::exception & err) {
    std::cerr << "[error] " << err.what() << std::endl;
  } catch (...) {
    std::cerr << "[error] " << "unexpected error!" << std::endl;
  }
  return error_code;
}
