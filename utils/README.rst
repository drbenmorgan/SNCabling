=========================================
Scripts to generate cabling documents
=========================================


Build documents
===============

Build ``SNCaloHVCabling.tar.gz`` and ``SNCaloSignalCabling.tar.gz``
archive files:

.. code:: bash

   $ make


Contents
========

CaloHV system
-------------

* ``calohv_map_skel_gen.py`` :  Generate a  skeleton CaloHV cabling  map CSV
  file.

  Usage:

  .. code:: bash

     $ python3 calohv_map_skel_gen.py
     $ ls -l calohv_mapping-skel.csv
  ..

* ``calohv_map_print.py`` : Generate LaTeX  files with CaloHV cabling tables
  corresponding to the different parts  of the detector. The generated
  files can then be included in a LaTeX master document.
* ``calohv_map_print.sh``  : Create  a  printable PDF  document with  CaloHV
  cabling tables.
 
  Usage:

  .. code:: bash

     $ bash calohv_map_print.sh

* ``calohv_print_labels.py`` : Generate LaTeX  files with CaloHV cabling labels
  corresponding to the different parts  of the detector. The generated
  files can then be included in a LaTeX master document.
* ``calohv_print_labels.sh`` : Wrapper script. 



CaloSignal system
-----------------

* ``calosignal_map_skel_gen.py`` :  Generate a  skeleton CaloSignal cabling  map CSV
  file.

  Usage:

  .. code:: bash

     $ python3 calosignal_map_skel_gen.py
     $ ls -l calosignal_mapping-skel.csv
  ..

* ``calosignal_map_print.py`` : Generate LaTeX  files with CaloSignal cabling tables
  corresponding to the different parts  of the detector. The generated
  files can then be included in a LaTeX master document.
* ``calosignal_map_print.sh``  : Create  a  printable PDF  document with  CaloSignal
  cabling tables.
 
  Usage:

  .. code:: bash

     $ bash calosignal_map_print.sh

* ``calosignal_print_labels.py`` : Generate LaTeX  files with CaloSignal cabling labels
  corresponding to the different parts  of the detector. The generated
  files can then be included in a LaTeX master document.
* ``calosignal_print_labels.sh`` : Wrapper script. 


Light Injection System (LIS)
----------------------------

* ``lis_map_skel_gen.py`` :  Generate an empty  skeleton LIS cabling  map CSV
  file.

  Usage:

  .. code:: bash

     $ python3 lis_map_skel_gen.py
     $ ls -l lis_mapping-skel.csv
  ..

* ``lis_map_print.py`` : Generate LaTeX  files with LIS cabling tables
  corresponding to the different parts  of the detector. The generated
  files can then be included in a LaTeX master document.
* ``lis_map_print.sh``  : Create  a  printable PDF  document with  LIS
  cabling tables.
 
  Usage:

  .. code:: bash

     $ bash lis_map_print.sh

.. end
   
