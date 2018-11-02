#

.PHONY : all
all : build_calohv build_calosignal build_lis

.PHONY : build_calohv
build_calohv :
	bash calohv_map_print.sh
	bash calohv_print_labels.sh

.PHONY : build_calosignal
build_calosignal :
	bash calosignal_map_print.sh
	bash calosignal_print_labels.sh

.PHONY : build_lis
build_lis :
	# python3 lis_map_skel_gen.py

.PHONY : clean
clean : clean_lis clean_calohv clean_calosignal
	find . -name "*~" -exec rm -f \{\} \;
	$(RM) *.pyc
	$(RM) -fr __pycache__/

.PHONY : clean_lis
clean_lis :
	$(RM) -fr _lis_table_out.d/

.PHONY : clean_calohv
clean_calohv :
	$(RM) -fr _calohv_table_out.d/ _calohv_labels_out.d/

.PHONY : clean_calosignal
clean_calosignal :
	$(RM) -fr _calosignal_table_out.d/ _calosignal_labels_out.d/

# end
