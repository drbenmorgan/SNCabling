=========================================
Scripts to generate cabling documents
=========================================


CaloHV system
=============

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




Light Injection System (LIS)
============================

* ``lis_map_skel_gen.py`` :  Generate a  skeleton LIS cabling  map CSV
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
   
