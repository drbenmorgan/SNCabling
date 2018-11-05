#!/usr/bin/env bash

opwd=$(pwd)

bash calosignal_map_print.sh
bash calosignal_print_labels.sh

target_dir=${opwd}/SNCaloSignalCabling/

mkdir ${target_dir}
mkdir ${target_dir}/Labels
mkdir ${target_dir}/Tables
cp _calosignal_labels_out.d/*.pdf ${target_dir}/Labels/
cp _calosignal_labels_out.d/*.lis ${target_dir}/Labels/
cp _calosignal_table_out.d/*.pdf ${target_dir}/Tables/
cp calosignal_mapping-skel.csv ${target_dir}/

cd ../documentation/CaloSignal/CaloSignalScheme/
make final
cp SuperNEMO_CaloSignal_CablingScheme-0.2.pdf ${target_dir}/

cd ${opwd}
tree ${target_dir}

exit 0

# end
