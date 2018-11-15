#include <iostream>
#include <cstdlib>
#include <exception>
#include <string>

#include <sncabling/utils.h>

int main(void)
{
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

  } catch (std::exception & err) {
    std::cerr << "[error] " << err.what() << std::endl;
  } catch (...) {
    std::cerr << "[error] " << "unexpected error!" << std::endl;
  }
  return error_code;
}
