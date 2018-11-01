#!/usr/bin/env python3

import sys
import os
import errno

from om_address import *
from snemo import *
from calohv import *

class CaloHVCablingPrintLabels:
    """CaloHV Cabling Label Printer """
   
    def __init__(self, csvfile_, printpath_):
        self._fcsv_ = open(csvfile_, "r")
        self._printpath_ = printpath_
        try:
            os.makedirs(self._printpath_)
        except OSError as ex:
            if ex.errno == errno.EEXIST and os.path.isdir(self._printpath_):
                pass
            else:
                raise
        self._pmt_to_cable_ = {}
        self._pmt_to_channel_ = {}
        self._internal_harnesses_ = []
        self._external_harnesses_ = {}

        return
 
    def _load(self):
        sys.stderr.write("[info] Loading CSV file...\n")
        lines = self._fcsv_.readlines()
        for l in lines:
            line = l[:-1].strip()
            if len(line) == 0 : continue
            if line[0] == '#' : continue
            tokens = line.split(";")
            channel_label    = tokens[0].strip()
            extharness_label = tokens[1].strip()
            intcable_label   = tokens[2].strip()
            pmt_label        = tokens[3].strip()
            pmtaddr      = OMaddress(pmt_label)
            sys.stderr.write(" === New record:\n")
            channeladdr = CaloHVChannelAddress(channel_label)
            channeladdr.print_me(sys.stderr, "HV channel address: ", "[debug] ")
            board_label = "B:{:d}.{:d}".format(channeladdr.crate, channeladdr.board)
            boardaddr = CaloHVBoardAddress(board_label)
            boardaddr.print_me(sys.stderr, "HV board address: ", "[debug] ")
            intcableaddr = CaloHVInternalCableAddress(intcable_label)
            pmtaddr.print_me(sys.stderr, "PMT address: ", "[debug] ")
            intcableaddr.print_me(sys.stderr, "Internal HV cable address: ", "[debug] ")
            self._pmt_to_cable_[pmt_label] = intcable_label
            self._pmt_to_channel_[pmt_label] = channel_label
            extharnessaddr = CaloHVExternalHarnessAddress(extharness_label)
            extharnessaddr.print_me(sys.stderr, "HV external harness address: ", "[debug] ")
            if not extharness_label in self._external_harnesses_.keys() :
                # self._external_harnesses_.append(extharnessaddr)
                self._external_harnesses_[extharness_label] = boardaddr
                intharness_label = extharness_label.replace("E:", "I:")
                intharnessaddr = CaloHVInternalHarnessAddress(intharness_label)
                intharnessaddr.print_me(sys.stderr, "HV internal harness address: ", "[debug] ")
                self._internal_harnesses_.append(intharnessaddr)
        #print(self._pmt_to_cable_)
        #print(self._pmt_to_channel_)
        print(self._internal_harnesses_)
        print(self._external_harnesses_)
        return

    def make_external_harness_labels(self):
        print("Labels for CaloHV external harnesses")
        foutname = "{:s}/calohv_labels_extharness.lis".format(self._printpath_)
        fout = open(foutname, "w") 
        external_harnesses = []
        board_to_harness_records = []
        for extharness_label in self._external_harnesses_.keys():
            extharnessaddr = CaloHVExternalHarnessAddress(extharness_label)
            external_harnesses.append(extharnessaddr)
            print("%s" % extharnessaddr.to_string())
            #fout.write("%s\n" % extharnessaddr.to_string())
            board_to_harness_records.append((extharnessaddr, self._external_harnesses_[extharness_label]))

        # Label for external harnesses:
        external_harnesses.sort()
        for extharnessaddr in external_harnesses:
            fout.write("%s\n" % extharnessaddr.to_string())
       
        # Label for external harnesses to HV boards associations:
        s = sorted(board_to_harness_records, key=lambda record: record[0]) 
        fout2name = "{:s}/calohv_labels_extharness_to_board.lis".format(self._printpath_)
        fout2 = open(fout2name, "w") 
        for record in s :
            fout2.write("%s -> %s\n" % (record[0].to_string(), record[1].to_string()))
        self._freadme_.write("* ``calohv_labels_extharness.lis`` : List of labels for external HV harnesses.\n")
        self._freadme_.write("* ``calohv_labels_extharness_to_board.lis`` : List of labels for associations of external HV harnesses and HV boards.\n")
        return
            
    def make_internal_harness_labels(self):
        print("Labels for CaloHV internal harnesses")
        foutname = "{:s}/calohv_labels_intharness.lis".format(self._printpath_)
        fout = open(foutname, "w") 
        self._internal_harnesses_.sort()
        for addr in self._internal_harnesses_:
            print("%s" % addr.to_string())
            fout.write("%s\n" % addr.to_string())
        self._freadme_.write("* ``calohv_labels_intharness.lis`` : List of labels for internal HV harnesses.\n")
        return

    def make_internal_cable_labels(self):
        labels_per_harness = {}
        for pmt_label in self._pmt_to_cable_.keys():
            cable_addr = CaloHVInternalCableAddress(self._pmt_to_cable_[pmt_label])
            harness_num = cable_addr.harness
            if not harness_num in labels_per_harness.keys() :
                labels_per_harness[harness_num] = []
            intcable_addr = CaloHVInternalCableAddress(self._pmt_to_cable_[pmt_label])
            pmt_addr = OMaddress(pmt_label)
            record = (intcable_addr, pmt_addr)
            labels_per_harness[harness_num].append(record)
        list_of_harness_nums = []
        for harness_num in labels_per_harness.keys():
            list_of_harness_nums.append(harness_num)
        list_of_harness_nums.sort()
        for harness_num in list_of_harness_nums:
            basename = "calohv_labels_intcable_to_pmt_{:d}.lis".format(harness_num)
            foutname = "{:s}/calohv_labels_intcable_to_pmt_{:d}.lis".format(self._printpath_, harness_num)
            fout = open(foutname, "w") 
            print("Labels for cables in CaloHV internal harness %d" % harness_num)
            sl = sorted(labels_per_harness[harness_num], key=lambda record: record[0]) 
            for record in sl :
                fout.write("%s -> %s\n" % (record[0].to_string(), record[1].to_string())) 
            self._freadme_.write("* ``%s`` : List of labels for associations of internal HV cables and PMTs (HV harness %d).\n" % (basename, harness_num))
        return
    
    def run(self):
        self._load()
        freadmename = "{:s}/calohv_labels_README.rst".format(self._printpath_)
        self._freadme_ = open(freadmename, "w")
        self._freadme_.write("===========================================================\n")
        self._freadme_.write("Calo High Voltage System Cabling Labels\n")
        self._freadme_.write("===========================================================\n\n")
        self._freadme_.write("""\n
This folder contains lists of CaloHV labels automatically generated by
the ``calohv_print_labels.py`` Python script from the SNCabling package. 
There are several categories of labels:

 * labels for *external HV harnesses* must be stuck on external HV harnesses at the Redel S Male side termination (patch panel).
 * labels for *associations of external HV harnesses and CAEN HV boards* must be stuck on the external HV harnesses at the Radial 
   connector side.
 * labels for *internal HV harnesses* must be stuck on the the HV internal harnesses at the Redel S Female side termination (patch panel).
 * labels for *associations of internal HV cables and PMTs* must be stuck on the individual HV cables at the PMT side.

\n""")
        self._freadme_.write("Lists of labels\n")
        self._freadme_.write("===============\n")
        self._freadme_.write("\n")
        self.make_external_harness_labels()
        self.make_internal_harness_labels()
        self.make_internal_cable_labels()
        self._freadme_.write("\n")
        self._freadme_.close()
        return

if __name__ == "__main__" :
    calohvmap = "calohv_mapping-skel.csv"
    workdir = "./_calohv_labels_out.d/"
    if len(sys.argv) > 1 :
        calohvmap = sys.argv[1]
    if len(sys.argv) > 2 :
        workdir = sys.argv[2]
    sys.stderr.write("CaloHV map file : '{:s}'\n".format(calohvmap))
    sys.stderr.write("Work directory  : '{:s}'\n".format(workdir)) 
    pm = CaloHVCablingPrintLabels(calohvmap, workdir)
    error_code = pm.run()
    sys.exit(error_code)

# end
