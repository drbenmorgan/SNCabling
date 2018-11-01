#

.PHONY : all
all : build_calohv build_lis

.PHONY : build_calohv
build_calohv :
	# python3 calohv_map_skel_gen.py
	# mv calohv_mapping-skel.csv _calohv_table_out.d/
	# bash calohv_map_print.sh

.PHONY : build_lis
lis_calohv :
	# python3 lis_map_skel_gen.py

.PHONY : clean
clean : clean_lis clean_calohv
	find . -name "*~" -exec rm -f \{\} \;
	$(RM) -fr __pycache__/

.PHONY : clean_lis
clean_lis :
	$(RM) -fr _lis_table_out.d/

.PHONY : clean_calohv
clean_calohv :
	$(RM) -fr _calohv_table_out.d/

# end
