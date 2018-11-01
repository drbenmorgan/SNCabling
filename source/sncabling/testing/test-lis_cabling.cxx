#include <iostream>
#include <cstdlib>
#include <exception>
#include <string>

#include <sncabling/om_id.h>
#include <sncabling/lis_id.h>
#include <sncabling/label.h>
#include <sncabling/lis_cabling.h>

void run1();
void run2();

int main(void)
{
  int error_code = EXIT_SUCCESS;
  try {
    std::cerr << "[info] " << "run 1..." << std::endl;
    run1();
    std::cerr << "[info] " << "run 2." << std::endl;
    run2();
  } catch (std::exception & err) {
    std::cerr << "[error] " << err.what() << std::endl;
  } catch (...) {
    std::cerr << "[error] " << "unexpected error!" << std::endl;
  }
  return error_code;
}

void run1()
{
  sncabling::lis_cabling cabling;

  // Populate the cabling table:
  for (int iled = 0; iled < 3; iled++) {
    int bundle = 9 + iled;
    int side = 0;
    int column = 3 + iled; 
    for (int ifiber = 0; ifiber < 13; ifiber++) {
      int row = ifiber;
      cabling.add_fiber(sncabling::lis_id(sncabling::LIS_FIBER, bundle, ifiber),
                        sncabling::lis_id(sncabling::LIS_LED, iled),
                        sncabling::om_id(sncabling::OM_MAIN, side, column, row));
    }
  }

  for (int iled = 3; iled < 5; iled++) {
    int bundle = 9 + iled;
    int side = 0;
    int column = 1 + iled; 
    for (int ifiber = 0; ifiber < 13; ifiber++) {
      int row = ifiber;
      cabling.add_fiber(sncabling::lis_id(sncabling::LIS_FIBER, bundle, ifiber, true),
                        sncabling::lis_id(sncabling::LIS_LED, iled),
                        sncabling::om_id(sncabling::OM_MAIN, side, column, row));
    }
  }
    
  cabling.print(std::cout);

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
  
  std::cout << std::endl;
  return;
}

void run2()
{
  {
      sncabling::lis_cabling cabling;
      std::string lis_map_filename
        = "${SNCABLING_RESOURCE_FILES_DIR}/snemo/demonstrator/cabling/LIS/0.1/lis_mapping.csv";
      unsigned int load_tags
        = sncabling::lis_cabling::LOAD_DEBUG
        | sncabling::lis_cabling::LOAD_LED_BUNDLE_MATCH;
      cabling.load(lis_map_filename, load_tags);
      cabling.print(std::cout);
  }

  std::cout << std::endl;
  return;
}
