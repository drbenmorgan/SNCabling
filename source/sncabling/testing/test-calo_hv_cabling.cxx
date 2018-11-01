#include <iostream>
#include <cstdlib>
#include <exception>
#include <string>

#include <sncabling/om_id.h>
#include <sncabling/calo_hv_id.h>
#include <sncabling/label.h>
#include <sncabling/calo_hv_cabling.h>

void run1();
void run2();

int main(void)
{
  int error_code = EXIT_SUCCESS;
  try {
    std::cerr << "[info] " << "run 1..." << std::endl;
    run1();
    // std::cerr << "[info] " << "run 2." << std::endl;
    // run2();
  } catch (std::exception & err) {
    std::cerr << "[error] " << err.what() << std::endl;
  } catch (...) {
    std::cerr << "[error] " << "unexpected error!" << std::endl;
  }
  return error_code;
}

void run1()
{
  sncabling::calo_hv_cabling cabling;

  // Populate the cabling table:
  int side = 0;
  int column = 0;
  int row = 0;
  int crate = 0;
  int board = 0;
  int channel = 0;
  int extharness = 0;
  int intharness = 0;
  int intcable = 24;
  cabling.add(sncabling::om_id(sncabling::OM_MAIN, side, column, row),
              sncabling::calo_hv_id(sncabling::CALOHV_CHANNEL, crate, board, channel),
              sncabling::calo_hv_id(sncabling::CALOHV_EXTHARNESS, extharness),
              sncabling::calo_hv_id(sncabling::CALOHV_INTCABLE, intharness, intcable));
    
  cabling.print(std::cout);

  /*
  {
    sncabling::om_id calo_id(sncabling::OM_MAIN, 0, 3, 1);
    if (cabling.om_has_fiber(calo_id)) {
      std::cout << "OM " << calo_id.to_label() << " has a primary fiber." << std::endl;
    } else {
      std::cout << "OM " << calo_id.to_label() << " has no primary fiber." << std::endl;
    }
    if (cabling.om_has_fiber(calo_id, true)) {
      std::cout << "OM " << calo_id.to_label() << " has a secondary fiber." << std::endl;
    } else {
      std::cout << "OM " << calo_id.to_label() << " has no secondary fiber." << std::endl;
    }
  }

  {
    sncabling::om_id calo_id(sncabling::OM_MAIN, 0, 5, 4);
    if (cabling.om_has_fiber(calo_id)) {
      std::cout << "OM " << calo_id.to_label() << " has a primary fiber." << std::endl;
    } else {
      std::cout << "OM " << calo_id.to_label() << " has no primary fiber." << std::endl;
    }
    if (cabling.om_has_fiber(calo_id, true)) {
      std::cout << "OM " << calo_id.to_label() << " has a secondary fiber." << std::endl;
    } else {
      std::cout << "OM " << calo_id.to_label() << " has no secondary fiber." << std::endl;
    }
  }

  {
    sncabling::om_id calo_id(sncabling::OM_MAIN, 0, 5, 4);
    sncabling::lis_id led;
    if (cabling.build_led_from_om(calo_id, led, true)) {
      std::cout << "OM " << calo_id.to_label() << " is lid by (secondary) led " << led.to_label() << std::endl;
    }
  }

  {
    std::vector<sncabling::om_id> oms;
    sncabling::lis_id led(sncabling::LIS_LED, 1);
    std::cout << " ==> LED (primary) " << led.to_label() << std::endl;
    cabling.build_om_from_led(led, oms);
    for (const auto & om : oms) {
      std::cout << "OM " << om.to_label() << " is lid by led " << led.to_label() << " (primary)" << std::endl;
    }
  }

  {
    std::vector<sncabling::om_id> oms;
    sncabling::lis_id led(sncabling::LIS_LED, 3);
    std::cout << " ==> LED (secondary) " << led.to_label() << std::endl;
    cabling.build_om_from_led(led, oms, true);
    for (const auto & om : oms) {
      std::cout << "OM " << om.to_label() << " is lid by led " << led.to_label() << " (secondary)" << std::endl;
    }
  }
  */
  std::cout << std::endl;
  return;
}

void run2()
{
  {
    sncabling::calo_hv_cabling cabling;
    std::string calo_hv_map_filename
      = "${SNCABLING_RESOURCE_FILES_DIR}/snemo/demonstrator/cabling/CaloHV/0.1/calo_hv_mapping.csv";
    unsigned int load_tags
      = sncabling::calo_hv_cabling::LOAD_DEBUG;
    cabling.load(calo_hv_map_filename, load_tags);
    cabling.print(std::cout);
  }

  std::cout << std::endl;
  return;
}
