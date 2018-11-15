=================================================
SNCabling client package
=================================================

This package builds a single executable which depends
on the SNCabling library.


.. code:: bash

   $ mkdir _build
   $ cd _build
   $ cmake -DSNCabling_DIR=$(sncablingquery --cmakedir) ..
   $ make
   $ ./sncablingclient

..
