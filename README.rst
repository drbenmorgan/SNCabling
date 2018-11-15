========================================
SuperNEMO Demonstrator Cabling
========================================


:Author: F.Mauger, Y.Lemière
:Date: 2018-10-08

.. role:: c++(code)
   :language: c++

Introduction
============

This project  aims to describe the  cabling rules and schemes  for all
submodules in  the SuperNEMO Demonstrator: calorimeter  signal and HV cables,
tracker signal & HV cables, Light Injection System (LIS)...

Expert tools (Python) are also provided to generate cabling tables and labels to help
cabling operations at LSM.

A C++ library, namely ``SNCabling`` is also built and provides a service
which hosts all searchable cabling tables of interest.

Example:

.. code:: c++

   #include <iostream>
   #include <sncabling/service.h>
   #include <sncabling/calo_signal_cabling.h>
   #include <sncabling/om_id.h>
   #include <sncabling/label.h>

   int main() {
	  // Instantiate and initialize the cabling service:
	  sncabling::service snCabling;
	  snCabling.initialize_simple();

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
	  return 0;
   }
..

Output is then: ``OM [M:0.3.1] is associated to the WaveCatcher readout channel [H:0.3.1]``


