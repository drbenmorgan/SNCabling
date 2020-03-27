#include <iostream>
#include <cstdlib>
#include <exception>
#include <string>

// This project:
#include <sncabling/sncabling.h>
#include <sncabling/resource_files.h>
#include <sncabling/utils.h>

int main()
{
  sncabling::initialize();
  int error_code = EXIT_SUCCESS;
  try {

    std::clog << "List of SuperNEMO cabling systems : " << std::endl;
    for (const auto & sysitem : sncabling::systems_map()) {
      std::clog << " - " << sysitem.second.label << " : "
                << sysitem.second.description << " [tag=" << sysitem.first << "]" << std::endl;
    }

    std::clog << "List of SuperNEMO cabling system tags : " << std::endl;
    for (const auto & systag : sncabling::list_of_system_tags()) {
      std::clog << systag << std::endl;
    }

    {
      std::string p1("/usr/local");
      std::string rp1 = sncabling::resolve_path(p1);
      std::clog << "rp1 : " << rp1 << std::endl;
    }

    {
      // std::cerr << "*** DEVEL *** path = " <<  sncabling::get_resource_files_dir() << std::endl;
      std::string p2("@sncabling:config/snemo/demonstrator/cabling/CaloHV/tags/ideal/CaloHVCabling/calohv_mapping.csv");
      std::string rp2 = sncabling::resolve_path(p2);
      std::clog << "rp2 : " << rp2 << std::endl;
    }

  } catch (std::exception & err) {
    std::cerr << "[error] " << err.what() << std::endl;
  } catch (...) {
    std::cerr << "[error] " << "unexpected error!" << std::endl;
  }
  sncabling::terminate();
  return error_code;
}
