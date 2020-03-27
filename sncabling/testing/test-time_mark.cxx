#include <iostream>
#include <cstdlib>
#include <exception>
#include <string>

#include <sncabling/time_mark.h>

int main()
{
  int error_code = EXIT_SUCCESS;
  try {

    const std::size_t NPERIODS = 7;
    auto tm = std::array<sncabling::time_mark, NPERIODS>{};
    tm[0].make_period(1);
    tm[1].make_period(2);
    tm[2].make_period(5);
    tm[4].make_time_point(boost::posix_time::ptime(boost::gregorian::date(2018, 11, 15),
                                                   boost::posix_time::time_duration(9, 52, 42)));
    tm[5].make_time_point("2018-11-15 09:46:23.123162");
    tm[6].make_time_point("20181115T094823,987654");
    //tm[6].make_time_point("?");

    for (auto i : tm) {
      std::clog << "Time mark: " << i << std::endl;
    }

  } catch (std::exception & err) {
    std::cerr << "[error] " << err.what() << std::endl;
  } catch (...) {
    std::cerr << "[error] " << "unexpected error!" << std::endl;
  }
  return error_code;
}
