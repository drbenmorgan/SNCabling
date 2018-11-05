#!/usr/bin/env python3

import sys
import os
import errno

from om_address import *
from snemo import *
from calosignal import *

class CaloSignalCablingPrintLabels:
    """CaloSignal Cabling Label Printer """
   
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
        self._pmt_to_intcable_ = {}
        self._pmt_to_channel_ = {}
        self._channel_to_extcable_ = {}
        self._internal_harnesses_ = []
        self._external_harnesses_ = []
        self._intcable_to_extcable_ = {}
        self._extcable_to_intcable_ = {}

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
            extcable_label   = tokens[1].strip()
            intcable_label   = tokens[2].strip()
            pmt_label        = tokens[3].strip()
            pmtaddr          = OMaddress(pmt_label)
            sys.stderr.write(" === New record:\n")
            channeladdr = CaloSignalChannelAddress(channel_label)
            channeladdr.print_me(sys.stderr, "Wavecatcher channel address: ", "[debug] ")
            board_label = "B:{:d}.{:d}".format(channeladdr.crate, channeladdr.board)
            boardaddr = CaloSignalBoardAddress(board_label)
            boardaddr.print_me(sys.stderr, "Wavecatcher board address: ", "[debug] ")
            intcableaddr = CaloSignalInternalCableAddress(intcable_label)
            pmtaddr.print_me(sys.stderr, "PMT address: ", "[debug] ")
            intcableaddr.print_me(sys.stderr, "Internal cable address: ", "[debug] ")
            self._pmt_to_intcable_[pmt_label]           = intcable_label
            self._pmt_to_channel_[pmt_label]            = channel_label
            self._channel_to_extcable_[channel_label]   = extcable_label
            self._intcable_to_extcable_[intcable_label] = extcable_label
            self._extcable_to_intcable_[extcable_label] = intcable_label
            extcableaddr = CaloSignalExternalCableAddress(extcable_label)
            extcableaddr.print_me(sys.stderr, "External cable address: ", "[debug] ")
            extharness_label = "E:{:d}".format(extcableaddr.harness)
            extharnessaddr = CaloSignalExternalHarnessAddress(extharness_label)
            extharnessaddr.print_me(sys.stderr, "External harness address: ", "[debug] ")
            if not extharness_label in self._external_harnesses_ :
                self._external_harnesses_.append(extharnessaddr)
                intharness_label = extharness_label.replace("E:", "I:")
                intharnessaddr = CaloSignalInternalHarnessAddress(intharness_label)
                intharnessaddr.print_me(sys.stderr, "Internal harness address: ", "[debug] ")
                self._internal_harnesses_.append(intharnessaddr)
        self._internal_harnesses_.sort()
        self._external_harnesses_.sort()
        print(self._internal_harnesses_)
        print(self._external_harnesses_)
        return

    def make_external_harness_labels(self):
        print("Labels for CaloSignal external harnesses")
        foutname = "{:s}/calosignal_labels_extharness.lis".format(self._printpath_)
        fout = open(foutname, "w") 
        # Label for external harnesses:
        for extharnessaddr in self._external_harnesses_:
            print("%s" % extharnessaddr.to_string())
            fout.write("%s\n" % extharnessaddr.to_string())
        self._freadme_.write("* ``calosignal_labels_extharness.lis`` : List of labels for external harnesses.\n")
        return
            
    def make_internal_harness_labels(self):
        print("Labels for CaloSignal internal harnesses")
        foutname = "{:s}/calosignal_labels_intharness.lis".format(self._printpath_)
        fout = open(foutname, "w") 
        for addr in self._internal_harnesses_:
            print("%s" % addr.to_string())
            fout.write("%s\n" % addr.to_string())
        self._freadme_.write("* ``calosignal_labels_intharness.lis`` : List of labels for internal harnesses.\n")
        return

    def make_internal_cable_labels(self):
        labels_per_harness = {}
        for pmt_label in self._pmt_to_intcable_.keys():
            cable_addr = CaloSignalInternalCableAddress(self._pmt_to_intcable_[pmt_label])
            harness_num = cable_addr.harness
            if not harness_num in labels_per_harness.keys() :
                labels_per_harness[harness_num] = []
            intcable_addr = CaloSignalInternalCableAddress(self._pmt_to_intcable_[pmt_label])
            pmt_addr = OMaddress(pmt_label)
            record = (intcable_addr, pmt_addr)
            labels_per_harness[harness_num].append(record)
        list_of_harness_nums = []
        for harness_num in labels_per_harness.keys():
            list_of_harness_nums.append(harness_num)
        list_of_harness_nums.sort()
        for harness_num in list_of_harness_nums:
            basename = "calosignal_labels_intcable_to_pmt_{:d}.lis".format(harness_num)
            foutname = "{:s}/calosignal_labels_intcable_to_pmt_{:d}.lis".format(self._printpath_, harness_num)
            fout = open(foutname, "w") 
            basename2 = "calosignal_labels_intcable_{:d}.lis".format(harness_num)
            fout2name = "{:s}/calosignal_labels_intcable_{:d}.lis".format(self._printpath_, harness_num)
            fout2 = open(fout2name, "w") 
            print("Labels for cables in CaloSignal internal harness %d" % harness_num)
            sl = sorted(labels_per_harness[harness_num], key=lambda record: record[0]) 
            for record in sl :
                fout.write("%s -> %s\n" % (record[0].to_string(), record[1].to_string())) 
                fout2.write("%s\n" % (record[0].to_string())) 
            self._freadme_.write("* ``%s`` : List of labels for associations of internal cables and PMTs (harness %d).\n" % (basename, harness_num))
            self._freadme_.write("* ``%s`` : List of labels for internal cables (harness %d).\n" % (basename2, harness_num))
        return

    def make_external_cable_labels(self):
        labels_per_harness = {}
        for channel_label in self._channel_to_extcable_.keys():
            cable_addr = CaloSignalExternalCableAddress(self._channel_to_extcable_[channel_label])
            harness_num = cable_addr.harness
            if not harness_num in labels_per_harness.keys() :
                labels_per_harness[harness_num] = []
            extcable_addr = CaloSignalExternalCableAddress(self._channel_to_extcable_[channel_label])
            channel_addr = CaloSignalChannelAddress(channel_label)
            record = (extcable_addr, channel_addr)
            labels_per_harness[harness_num].append(record)
        list_of_harness_nums = []
        for harness_num in labels_per_harness.keys():
            list_of_harness_nums.append(harness_num)
        list_of_harness_nums.sort()
        for harness_num in list_of_harness_nums:
            basename = "calosignal_labels_extcable_to_channel_{:d}.lis".format(harness_num)
            foutname = "{:s}/calosignal_labels_extcable_to_channel_{:d}.lis".format(self._printpath_, harness_num)
            fout = open(foutname, "w") 
            basename2 = "calosignal_labels_extcable_{:d}.lis".format(harness_num)
            fout2name = "{:s}/calosignal_labels_extcable_{:d}.lis".format(self._printpath_, harness_num)
            fout2 = open(fout2name, "w") 
            print("Labels for cables in CaloSignal external harness %d" % harness_num)
            sl = sorted(labels_per_harness[harness_num], key=lambda record: record[0]) 
            for record in sl :
                fout.write("%s -> %s\n" % (record[0].to_string(), record[1].to_string())) 
                fout2.write("%s\n" % (record[0].to_string())) 
            self._freadme_.write("* ``%s`` : List of labels for associations of external cables and FEB channels (harness %d).\n" % (basename, harness_num))
            self._freadme_.write("* ``%s`` : List of labels for external cables (harness %d).\n" % (basename2, harness_num))
        return
     
    def run(self):
        self._load()
        freadmename = "{:s}/calosignal_labels_README.rst".format(self._printpath_)
        self._freadme_ = open(freadmename, "w")
        self._freadme_.write("===========================================================\n")
        self._freadme_.write("Calo Signal Cabling Labels\n")
        self._freadme_.write("===========================================================\n\n")
        self._freadme_.write("""\n
This folder contains lists of CaloSignal labels automatically generated by
the ``calosignal_print_labels.py`` Python script from the SNCabling package. 
There are several categories of labels:

 * labels for *external harnesses* must be stuck on external harnesses at both terminations (Wavecatcher FEB and patch panel).
 * labels for *external cables* must be stuck on the individual cables at the patch panel side (MCX male connector).
 * labels for *associations of external cables and Calo FEB channels* must be stuck on the external cables at 
   the Wavecatcher FEB side (MCX male connector).
 * labels for *internal harnesses* must be stuck on internal harnesses at both terminations (patch panel and PMT).
 * labels for *internal cables* must be stuck on the individual cables at the patch panel side (MCX female connector).
 * labels for *associations of internal cables and PMTs* must be stuck on the individual cables at the PMT side (Souriau pin).

\n""")
        self._freadme_.write("Lists of labels\n")
        self._freadme_.write("===============\n")
        self._freadme_.write("\n")
        # self.make_external_harness_labels()
        # self.make_internal_harness_labels()
        self.make_internal_cable_labels()
        self.make_external_cable_labels()
        self._freadme_.write("\n")
        self._freadme_.close()
        return

if __name__ == "__main__" :
    calosignalmap = "calosignal_mapping-skel.csv"
    workdir = "./_calosignal_labels_out.d/"
    if len(sys.argv) > 1 :
        calosignalmap = sys.argv[1]
    if len(sys.argv) > 2 :
        workdir = sys.argv[2]
    sys.stderr.write("CaloSignal map file : '{:s}'\n".format(calosignalmap))
    sys.stderr.write("Work directory  : '{:s}'\n".format(workdir)) 
    pm = CaloSignalCablingPrintLabels(calosignalmap, workdir)
    error_code = pm.run()
    sys.exit(error_code)

# end
