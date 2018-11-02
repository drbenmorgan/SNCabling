#!/usr/bin/env bash

opwd=$(pwd)

test=true

calosignalmap="calosignal_mapping.csv"
if [ $test ] ; then
    python3 ${opwd}/calosignal_map_skel_gen.py
    calosignalmap="${opwd}/calosignal_mapping-skel.csv"
fi

if [ ! -f ${calosignalmap} ]; then
    echo >&2 "[error] Missing Calosignal mapping file! Abort!"
    exit 1
fi

workdir="${opwd}/_calosignal_labels_out.d"
if [ -d ${workdir} ]; then
    rm -fr ${workdir}
fi
mkdir -p ${workdir}

python3 ./calosignal_print_labels.py ${calosignalmap} ${workdir}

tree ${workdir}

cd ${workdir}/
rst2pdf calosignal_labels_README.rst
cd ${opwd}
tree ${workdir}/
xdg-open ${workdir}/calosignal_labels_README.pdf &

exit 0

# end
