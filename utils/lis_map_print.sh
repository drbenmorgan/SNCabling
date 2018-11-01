#!/usr/bin/env bash

opwd=$(pwd)

test=true

lismap="lis_mapping.csv"
if [ $test ] ; then
    python3 ${opwd}/lis_map_skel_gen.py
    lismap="${opwd}/lis_mapping-skel.csv"
fi

if [ ! -f ${lismap} ]; then
    echo >&2 "[error] Missing LIS mapping file! Abort!"
    exit 1
fi

workdir="${opwd}/_lis_table_out.d"
if [ -d ${workdir} ]; then
    rm -fr ${workdir}
fi
mkdir -p ${workdir}

python3 ./lis_map_print.py ${lismap} ${workdir}

tree ${workdir}

sed -e "s@__WORKDIR__@${workdir}@g" ${opwd}/template/lis_table_main.tex.in \
    > ${workdir}/lis_table_main.tex

cd ${workdir}/
pdflatex lis_table_main.tex
rm -f lis_table_main.aux
rm -f lis_table_main.log
cd ${opwd}
tree ${workdir}/
xdg-open ${workdir}/lis_table_main.pdf &

exit 0

# end
