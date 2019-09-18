// Standard library:
#include <iostream>
#include <cstdlib>
#include <exception>
#include <string>

// This project:
#include <sncabling/service.h>
#include <sncabling/calo_hv_cabling.h>
#include <sncabling/calo_signal_cabling.h>
#include <sncabling/om_id.h>
#include <sncabling/calo_signal_id.h>
#include <sncabling/label.h>

void run1();
void run2();

int main(void)
{
  int error_code = EXIT_SUCCESS;
  try {

    std::cerr << "[info] " << "run 1..." << std::endl;
    run1();

    std::cerr << "[info] " << "run 2..." << std::endl;
    run2();

  } catch (std::exception & err) {
    std::cerr << "[error] " << err.what() << std::endl;
  } catch (...) {
    std::cerr << "[error] " << "unexpected error!" << std::endl;
  }
  return error_code;
}

void run2()
{
  sncabling::service cabling;

  datatools::properties cabling_config;
  cabling_config.store_path("logging.priority", "debug");
  // Force specific cabling maps:
  cabling_config.store_path("CaloHV.default_map",
                            "${SNCABLING_RESOURCE_FILES_DIR}/config/snemo/demonstrator/cabling/CaloHV/tags/actual_1/CaloHVCabling/calohv_mapping.csv");
  cabling_config.store_path("CaloSignal.default_map",
                            "${SNCABLING_RESOURCE_FILES_DIR}/config/snemo/demonstrator/cabling/CaloSignal/tags/original/CaloSignalCabling/calosignal_mapping.csv");

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

void run1()
{
  // Instantiate and initialize the cabling service:
  sncabling::service snCabling;
  snCabling.initialize_simple(); // Using default maps

  // Access to the calorimeter signal readout cabling map:
  const sncabling::calo_signal_cabling & caloSignalCabling = snCabling.get_calo_signal_cabling();

  // Search the readout channel associated to a given OM:
  sncabling::om_id calo_id(sncabling::OM_MAIN, 0, 3, 1);
  if (caloSignalCabling.has_om(calo_id)) {
    const sncabling::calo_signal_id & signal_channel = caloSignalCabling.get_channel(calo_id);
    std::cout << "OM [" << calo_id.to_label() << "] is associated to the WaveCatcher readout channel "
              << "[" << signal_channel.to_label() << "].\n";
  }

  // Access to the calorimeter signal readout cabling map:
  sncabling::calo_signal_id readout_id(sncabling::CALOSIGNAL_CHANNEL,
                                       2, 15, 5);
  // Search the OM associated to a given readout channel:
  if (caloSignalCabling.has_channel(readout_id)) {
    const sncabling::om_id & calo_id = caloSignalCabling.get_om(readout_id);
    std::cout << "WaveCatcher readout channel [" << readout_id.to_label() << "] is associated to the OM "
              << "[" << calo_id.to_label() << "].\n";
  }

 
  // Terminate the cabling service:
  snCabling.reset();
  return;
}
