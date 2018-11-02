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

workdir="${opwd}/_calosignal_table_out.d"
if [ -d ${workdir} ]; then
    rm -fr ${workdir}
fi
mkdir -p ${workdir}

python3 ./calosignal_map_print.py ${calosignalmap} ${workdir}

tree ${workdir}

sed -e "s@__WORKDIR__@${workdir}@g" ${opwd}/template/calosignal_table_main.tex.in \
    > ${workdir}/calosignal_table_main.tex

cd ${workdir}/
pdflatex calosignal_table_main.tex
rm -f calosignal_table_main.aux
rm -f calosignal_table_main.log
cd ${opwd}
tree ${workdir}/
xdg-open ${workdir}/calosignal_table_main.pdf &

exit 0

# end
