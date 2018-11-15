#include <iostream>
#include <cstdlib>
#include <exception>
#include <string>

#include <sncabling/service.h>
#include <sncabling/calo_hv_cabling.h>
#include <sncabling/calo_signal_cabling.h>

void run1();

int main(void)
{
  int error_code = EXIT_SUCCESS;
  try {

    std::cerr << "[info] " << "run 1..." << std::endl;
    run1();

  } catch (std::exception & err) {
    std::cerr << "[error] " << err.what() << std::endl;
  } catch (...) {
    std::cerr << "[error] " << "unexpected error!" << std::endl;
  }
  return error_code;
}

void run1()
{
  sncabling::service cabling;

  datatools::properties cabling_config;
  cabling_config.store_path("logging.priority", "debug");
  // Force specific cabling maps:
  // cabling_config.store_path("CaloHV.default_map",
  //                           "${SNCABLING_RESOURCE_FILES_DIR}/snemo/demonstrator/cabling/CaloHV/0.3/CaloHVCabling/calohv_mapping.csv");
  // cabling_config.store_path("CaloSignal.default_map",
  //                           "${SNCABLING_RESOURCE_FILES_DIR}/snemo/demonstrator/cabling/CaloSignal/0.2/CaloSignalCabling/calosignal_mapping.csv");

  // Cabling service uses default cabling map (CaloHV, CaloSignal) if none are specified:
  cabling.initialize_standalone(cabling_config);
  std::clog << std::endl;

  // Fetch the calorimeter HV cabling:
  const sncabling::calo_hv_cabling & caloHvCabling = cabling.get_calo_hv_cabling();
  caloHvCabling.print(std::clog);
  std::clog << std::endl;

  // Fetch the calorimeter signal readout cabling:
  const sncabling::calo_signal_cabling & caloSignalCabling = cabling.get_calo_signal_cabling();
  caloSignalCabling.print(std::clog);
  std::clog << std::endl;
  
  cabling.reset();
  return;
}
