#include <iostream>
#include <cstdlib>
#include <exception>
#include <string>

#include <sncabling/service.h>
#include <sncabling/calo_hv_cabling.h>
#include <sncabling/calo_signal_cabling.h>
#include <sncabling/om_id.h>
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

void run1()
{
  sncabling::service cabling;

  datatools::properties cabling_config;
  cabling_config.store_path("logging.priority", "debug");
  // Force specific cabling maps:
  cabling_config.store_path("CaloHV.default_map",
                            "${SNCABLING_RESOURCE_FILES_DIR}/snemo/demonstrator/cabling/CaloHV/0.3/CaloHVCabling/calohv_mapping.csv");
  cabling_config.store_path("CaloSignal.default_map",
                            "${SNCABLING_RESOURCE_FILES_DIR}/snemo/demonstrator/cabling/CaloSignal/0.2/CaloSignalCabling/calosignal_mapping.csv");

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

void run2()
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

  // Terminate the cabling service:
  snCabling.reset();
  return;
}
