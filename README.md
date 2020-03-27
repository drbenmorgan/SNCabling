# SuperNEMO Demonstrator Cabling
This project aims to describe the cabling rules and schemes for all
submodules in the SuperNEMO Demonstrator: calorimeter signal and HV
cables, tracker signal & HV cables, Light Injection System (LIS)\...

## The `SNCabling` C++ library

The `SNCabling` C++ library provides a service which hosts all
searchable cabling tables of interest:

- `CaloHV`: Calorimeter HV system (*updated to the actual cabling*)
- `CaloSignal`: Calorimeter signal readout system (*should be up to date*)
- `TrackerHV`: Tracker HV system (*not implemented yet*)
- `TrackerSignal`: Tracker signal readout system (*not implemented yet*)
- `LIS`: Light injection system (*to be checked*)

**Example**: the following example illustrates how to, from the
SuperNEMO cabling API, search and find the identifier of a WaveCatcher
board readout channel from the identifier of a calorimeter optical
module. The SNCabling must be built using the
`-DSNCABLING_WITH_SERVICE=ON` options with explicit dependency on Bayeux
in order to implement the `sncabling::service` class:

```{.cpp}
#include <iostream>
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
  snCabling.initialize_simple();

  // Access to the calorimeter signal readout cabling map:
  const sncabling::calo_signal_cabling & caloSignalCabling
    = snCabling.get_calo_signal_cabling();

  // Instantiate the identifier of an optical module (OM):
  sncabling::om_id calo_id(sncabling::OM_MAIN, 0, 3, 1);

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
  sncabling::calo_signal_id readout_id(sncabling::CALOSIGNAL_CHANNEL, 2, 15, 5);

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
```

Output is then:

```{.console}
OM [M:0.3.1] is associated to the WaveCatcher readout channel [H:0.3.1]
WaveCatcher readout channel [H:2.15.5] is associated to the OM [G:1.1.5]
```

## Dependencies
- Boost (recommended \>= 1.69)
- Bayeux only for *service* support (recommended \>= 3.4.1)

## Installing SNCabling

First make sure a recent version (\>=3.4) of [Bayeux](https://github.com/BxCppDev/Bayeux)
is installed on your system in order to support the *service* object.

Clone the `SNCabling` source repository from GitLab IN2P3 to some
directory of your own:

```
$ git clone https://gitlab.in2p3.fr/SuperNEMO-DBD/SNCabling
$ cd SNCabling/
```

From the `SNCabling` source directory, create a separate build directory:

```
$ mkdir _build
$ cd _build
```

Configure `SNCabling` without *service* support:

```
$ cmake ..
$ cmake --build .
$ ctest
```

With *service* support, you need to specify the Bayeux installation
prefix path:

```
$ cmake -DSNCABLING_WITH_SERVICE=ON \
  -DBayeux_DIR:PATH=$(bxquery --cmakedir) \
  ..
```

## Using SNCabling

You must update your `PATH` environment variable:

```
$ export PATH="/opt/sw/SuperNEMO-DBD/SNCabling/bin:${PATH}"
```

The `sncabling-config` utility script is provided to locate `SNCabling`
components (shared library, header files, resource files) in the
installation directory:

```
$ sncabling-config --help
```

`SNCabling` is provided with CMake support. To build a package depending
on `SNCabling`, you may indicate the `SNCabling` location to CMake with
a command like:

```
$ cmake -DSNCabling_DIR=$(sncabling-config --cmakedir) ...
```

## Expert tools

Expert tools (Python 3) are provided to generate (template) cabling
tables and labels to help cabling operations at LSM. However no publicly
available Python API is provided for now.
