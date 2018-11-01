#!/usr/bin/env bash

opwd=$(pwd)

test=true

calohvmap="calohv_mapping.csv"
if [ $test ] ; then
    python3 ${opwd}/calohv_map_skel_gen.py
    calohvmap="${opwd}/calohv_mapping-skel.csv"
fi

if [ ! -f ${calohvmap} ]; then
    echo >&2 "[error] Missing CaloHV mapping file! Abort!"
    exit 1
fi

workdir="${opwd}/_calohv_labels_out.d"
if [ -d ${workdir} ]; then
    rm -fr ${workdir}
fi
mkdir -p ${workdir}

python3 ./calohv_print_labels.py ${calohvmap} ${workdir}

tree ${workdir}

cd ${workdir}/
rst2pdf calohv_labels_README.rst
cd ${opwd}
tree ${workdir}/
xdg-open ${workdir}/calohv_labels_README.pdf &

exit 0

# end
