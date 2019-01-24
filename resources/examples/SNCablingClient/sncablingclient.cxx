// Standard library:
#include <iostream>

// SNCabling:
#include <sncabling/sncabling.h>
#include <sncabling/service.h>
#include <sncabling/calo_signal_cabling.h>
#include <sncabling/om_id.h>
#include <sncabling/label.h>

int main()
{
  sncabling::initialize();
  
  // Instantiate and initialize the cabling service:
  sncabling::service snCabling;
  snCabling.initialize_simple(); // Use default configuration

  // Access to the calorimeter signal readout cabling map:
  const sncabling::calo_signal_cabling & caloSignalCabling
    = snCabling.get_calo_signal_cabling();
  std::clog << "Calorimeter signal readout cabling table:\n";
  caloSignalCabling.print(std::clog);
  std::clog << std::endl;
  
  // Instantiate the identifier of an optical module (OM):
  int16_t wall_num   = 0;
  int16_t column_num = 3;
  int16_t row_num    = 1;
  sncabling::om_id calo_id(sncabling::OM_MAIN,
                           wall_num, column_num, row_num);

  // Search the identifier of the readout channel associated
  // to the OM identifier:
  if (caloSignalCabling.has_om(calo_id)) {

    const sncabling::calo_signal_id & readout_channel
      = caloSignalCabling.get_channel(calo_id);
          
    std::cout << "OM [" << calo_id.to_label() << "] "
              << "is associated to the WaveCatcher readout channel "
              << "[" << readout_channel.to_label() << "]\n";
  }

  // Instantiate the identifier of a calorimeter signal readout channel:
  int16_t crate_num   = 2;
  int16_t board_num   = 15;
  int16_t channel_num = 5;
  sncabling::calo_signal_id readout_id(sncabling::CALOSIGNAL_CHANNEL,
                                       crate_num, board_num, channel_num);

  // Search the identifier of the OM associated to the readout channel identifier:
  if (caloSignalCabling.has_channel(readout_id)) {

    const sncabling::om_id & calo_id = caloSignalCabling.get_om(readout_id);
    std::cout << "WaveCatcher readout channel [" << readout_id.to_label() << "] "
              << "is associated to the OM "
              << "[" << calo_id.to_label() << "]\n";
  }

  // Terminate the cabling service:
  snCabling.reset();

  sncabling::terminate();
  return 0;
}
