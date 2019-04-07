// Standard library:
#include <iostream>
#include <exception>
#include <cstdlib>

// This project:
#include <sncabling/sncabling.h>
#include <sncabling/om_id.h>
#include <sncabling/calo_hv_id.h>
#include <sncabling/calo_hv_cabling.h>
#include <sncabling/label.h>

int main()
{
  int error_code = EXIT_SUCCESS;
  sncabling::initialize();
  try {

    // Access to the calorimeter signal readout cabling map:
    sncabling::calo_hv_cabling caloHvCabling;
    caloHvCabling.load("@sncabling:config/snemo/demonstrator/cabling/CaloHV/tags/original/CaloHVCabling/calohv_mapping.csv");
    caloHvCabling.print(std::clog);

    // OM -> HV channel
    {
      // Instantiate the identifier of an optical module (OM):
      sncabling::om_id calo_id(sncabling::OM_MAIN, 0, 3, 1);

      // Search the identifier of the readout channel associated
      // to the OM identifier:
      if (caloHvCabling.has_om(calo_id)) {
        const sncabling::calo_hv_id & hv_channel
          = caloHvCabling.get_channel(calo_id);      
        std::clog << "OM [" << calo_id.to_label() << "] "
                  << "is associated to the HV channel "
                  << "[" << hv_channel.to_label() << "]\n";
      } else {
        std::clog << "OM [" << calo_id.to_label() << "] "
                  << "has no HV connection!\n";
      }
    }
    
    // HV channel -> OM
    {
      // Instantiate the identifier of a calorimeter HV channel:
      sncabling::calo_hv_id hv_id(sncabling::CALOHV_CHANNEL, 1, 12, 5);

      // Search the identifier of the OM associated to the HV channel identifier:
      if (caloHvCabling.has_channel(hv_id)) {
        const sncabling::om_id & calo_id = caloHvCabling.get_om(hv_id);
        std::clog << "HV channel [" << hv_id.to_label() << "] "
                  << "is associated to the OM "
                  << "[" << calo_id.to_label() << "]\n";
      } else {
        std::clog << "HV channel [" << hv_id.to_label() << "] "
                  << "has no OM!\n";
      }
    }

  } catch (std::exception & error) {
    std::cerr << "[error] " << error.what() << std::endl;
    error_code = EXIT_FAILURE;
  }
  sncabling::terminate();
  return error_code;
}
