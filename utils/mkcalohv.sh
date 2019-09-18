#!/usr/bin/env bash

opwd=$(pwd)

version="actual_1"
python3 calohv_map_skel_gen.py ${version}
if [ -f calohv_mapping.csv ]; then
    rm -f calohv_mapping.csv
fi
cp -f calohv_mapping-skel.csv calohv_mapping.csv
bash calohv_map_print.sh
bash calohv_print_labels.sh

target_dir=${opwd}/SNCaloHVCabling

if [ -d ${target_dir} ]; then
    rm -fr ${target_dir}
fi
mkdir ${target_dir}
mkdir ${target_dir}/Labels
mkdir ${target_dir}/Tables
cp _calohv_labels_out.d/*.pdf ${target_dir}/Labels/
cp _calohv_labels_out.d/*.lis ${target_dir}/Labels/
cp _calohv_table_out.d/*.pdf ${target_dir}/Tables/
# cp calohv_mapping-skel.csv ${target_dir}/calohv_mapping.csv
cp calohv_mapping.csv ${target_dir}/

cd ../documentation/CaloHV/CaloHVScheme/
make final
cp SuperNEMO_CaloHV_CablingScheme-0.5.pdf ${target_dir}/

cd ${opwd}
tree ${target_dir}
tar cvzf ./SNCaloHVCabling.tar.gz  ${target_dir}/

exit 0

# end
