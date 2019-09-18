#

.PHONY : all
all : build_calohv build_calosignal 

.PHONY : build_calohv
build_calohv :
	./mkcalohv.sh

.PHONY : build_calosignal
build_calosignal :
	./mkcalosignal.sh

.PHONY : clean
clean : clean_calohv clean_calosignal
	find . -name "*~" -exec rm -f \{\} \;
	$(RM) *.pyc
	$(RM) -fr __pycache__/

.PHONY : clean_calohv
clean_calohv :
	$(RM) -f calohv_mapping-skel.csv
	$(RM) -fr _calohv_table_out.d/ _calohv_labels_out.d/
	$(RM) -fr SNCaloHVCabling/
	$(RM) -f SNCaloHVCabling.tar.gz

.PHONY : clean_calosignal
clean_calosignal :
	$(RM) -f calosignal_mapping-skel.csv
	$(RM) -fr _calosignal_table_out.d/ _calosignal_labels_out.d/
	$(RM) -fr SNCaloSignalCabling/
	$(RM) -f SNCaloSignalCabling.tar.gz

# end
