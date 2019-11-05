#include <iostream>
#include <cstdlib>
#include <exception>
#include <string>

// SNCabling:
#include <sncabling/sncabling.h>
#include <sncabling/resource_files.h>

int main(void)
{
  sncabling::initialize();
  int error_code = EXIT_SUCCESS;
  try {
    std::clog << "Resource files dir = '"
              << sncabling::get_resource_files_dir() << "'\n";
  } catch (std::exception & err) {
    std::cerr << "[error] " << err.what() << std::endl;
  } catch (...) {
    std::cerr << "[error] " << "unexpected error!" << std::endl;
  }
  sncabling::terminate();
  return error_code;
}
