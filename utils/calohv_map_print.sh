#!/usr/bin/env bash

opwd=$(pwd)


calohvmap="calohv_mapping.csv"
# test=false
# if [ $test ] ; then
#     python3 ${opwd}/calohv_map_skel_gen.py
#     calohvmap="${opwd}/calohv_mapping-skel.csv"
# fi

if [ ! -f ${calohvmap} ]; then
    echo >&2 "[error] Missing CaloHV mapping file! Abort!"
    exit 1
fi

workdir="${opwd}/_calohv_table_out.d"
if [ -d ${workdir} ]; then
    rm -fr ${workdir}
fi
mkdir -p ${workdir}

python3 ./calohv_map_print.py ${calohvmap} ${workdir}
if [ $? -ne 0 ]; then
    echo >&2 "[error] Abort!"
    exit 1
fi

tree ${workdir}

sed -e "s@__WORKDIR__@${workdir}@g" ${opwd}/template/calohv_table_main.tex.in \
    > ${workdir}/calohv_table_main.tex

cd ${workdir}/
pdflatex calohv_table_main.tex
rm -f calohv_table_main.aux
rm -f calohv_table_main.log
cd ${opwd}
tree ${workdir}/
xdg-open ${workdir}/calohv_table_main.pdf &

exit 0

# end
