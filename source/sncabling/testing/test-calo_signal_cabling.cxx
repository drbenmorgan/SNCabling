#include <iostream>
#include <cstdlib>
#include <exception>
#include <string>

#include <sncabling/om_id.h>
#include <sncabling/calo_signal_id.h>
#include <sncabling/label.h>
#include <sncabling/calo_signal_cabling.h>

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
  sncabling::calo_signal_cabling cabling;

  // Populate the cabling table:
  int side = 0;
  int column = 0;
  int row = 0;
  int crate = 0;
  int board = 0;
  int channel = 0;
  int extharness = 0;
  int extcable = 24;
  int intharness = extharness;
  int intcable = extcable;
  cabling.add(sncabling::om_id(sncabling::OM_MAIN, side, column, row),
              sncabling::calo_signal_id(sncabling::CALOSIGNAL_CHANNEL,  crate, board, channel),
              sncabling::calo_signal_id(sncabling::CALOSIGNAL_EXTCABLE, extharness, extcable),
              sncabling::calo_signal_id(sncabling::CALOSIGNAL_INTCABLE, intharness, intcable));
  cabling.print(std::cout);
  std::cout << std::endl;
  return;
}

void run2()
{
  {
    sncabling::calo_signal_cabling cabling;
    std::string calo_signal_map_filename
      = "${SNCABLING_RESOURCE_FILES_DIR}/snemo/demonstrator/cabling/CaloSignal/0.2/CaloSignalCabling/calosignal_mapping-skel.csv";
    unsigned int load_tags = sncabling::calo_signal_cabling::LOAD_DEBUG;
    cabling.load(calo_signal_map_filename, load_tags);
    cabling.print(std::cout);

    {
      sncabling::om_id calo_id(sncabling::OM_MAIN, 0, 3, 1);
      if (cabling.has_om(calo_id)) {
        const sncabling::calo_signal_id & signal_channel = cabling.get_channel(calo_id);
        std::cout << "OM [" << calo_id.to_label() << "] has a signal readout channel: "
                  << "[" << signal_channel.to_label() << "]." << std::endl;
      } else {
        std::cout << "OM [" << calo_id.to_label() << "] has no signal readout connection." << std::endl;
      }
    }
    
    {
      sncabling::om_id calo_id(sncabling::OM_GVETO, 1, 1, 14);
      if (cabling.has_om(calo_id)) {
        const sncabling::calo_signal_id & signal_channel = cabling.get_channel(calo_id);
        std::cout << "OM [" << calo_id.to_label() << "] has a signal readout channel: "
                  << "[" << signal_channel.to_label() << "]." << std::endl;
      } else {
        std::cout << "OM [" << calo_id.to_label() << "] has no signal readout connection." << std::endl;
      }
    }
    
    {
      sncabling::om_id calo_id(sncabling::OM_XWALL, 1, 1, 0, 9);
      if (cabling.has_om(calo_id)) {
        const sncabling::calo_signal_id & signal_channel = cabling.get_channel(calo_id);
        std::cout << "OM [" << calo_id.to_label() << "] has a signal readout channel: "
                  << "[" << signal_channel.to_label() << "]." << std::endl;
      } else {
        std::cout << "OM [" << calo_id.to_label() << "] has no signal readout connection." << std::endl;
      }
    }

  }

  std::cout << std::endl;
  return;
}
