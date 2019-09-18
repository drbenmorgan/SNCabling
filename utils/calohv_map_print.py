#!/usr/bin/env python3

import sys
import os
import errno

from om_address import *
from snemo import *
from calohv import *
         
class CaloHVCablingMapPrint:
    """CaloHV Cabling Map Printer """
   
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
        self._channel_to_pmt_ = {}
        self._channel_to_intcable_ = {}
        self._mode_ = "cable"
        return

    def set_mode(self, mode_):
        if mode_ != "cable" and mode_ != "other" :
            raise Exception("CaloHVCablingMapPrint.set_mode: Invalid mode '%s'!" % mode_)
        self._mode_ = mode_
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
            intcableaddr = CaloHVInternalCableAddress(intcable_label)
            pmtaddr.print_me(sys.stderr, "PMT address: ", "[debug] ")
            intcableaddr.print_me(sys.stderr, "Internal HV cable address: ", "[debug] ")
            self._pmt_to_intcable_[pmt_label]   = intcable_label
            self._pmt_to_channel_[pmt_label] = channel_label
            self._channel_to_pmt_[channel_label] = pmt_label
            self._channel_to_intcable_[channel_label] = intcable_label
        print(self._pmt_to_intcable_)
        print(self._pmt_to_channel_)
        return
    
    def _mktable_calo(self, side_):
        ncols=20
        nrows=13
        foutname = "{:s}/calohv_main_{:s}_{:d}.tex".format(self._printpath_, self._mode_, side_)
        fout = open(foutname, "w") 
        sys.stderr.write("[info] Generating LaTeX table...\n")
        fout.write("\\begin{tabular}{|");
        fout.write("r|");
        for icol in range(ncols) :
            fout.write("|C{1.2cm}");
        fout.write("||");
        fout.write("l|}\n");
        fout.write("\\hline\n");    
        side = side_

        fout.write(" & ")
        for icol in range(ncols) :
            column = icol
            if side == SuperNEMO.side_italy :
                column = ncols - icol - 1
            fout.write("\\textcolor{blue}{\\small %s}" % (column));
            if icol + 1 != ncols :
                fout.write(" & ")
        fout.write(" & ")
        fout.write("\\\\\n");
                 
        fout.write("\\hline\n\\hline\n");
        
        for irow in range(nrows) :
            row = nrows - 1 - irow
            # HV cables:
            fout.write("\\textcolor{blue}{\\small %s} &" % (row));
            for icol in range(ncols) :
                column = icol
                if side == SuperNEMO.side_italy :
                    column = ncols - icol - 1
                textcolor = "black"
                backcolor = "white"
                # backcolor = "MainWallYellow"
                # if row == nrows - 1:
                #     textcolor = "white"
                #     backcolor = "MainWallTopBlue"
                # else:
                #     if column < 10 and row in [0,1,2,6,7,8]:
                #         backcolor = "MainWallYellow"
                #     if column >= 10 and row in [3,4,5,9,10,11]:
                #         backcolor = "MainWallYellow"
                pmt_label = "{:s}:{:d}.{:d}.{:d}".format("M", side, column, row)
                pmt_addr = OMaddress(pmt_label)
                pmt_addr.print_me(sys.stderr, "PMT address: ", "[info] ")
                if pmt_label in self._pmt_to_intcable_ :
                    print("Found PMT label '{:s}' with CaloHV cable ".format(pmt_label))
                else:
                    print("Cannot found PMT label '{:s}' with CaloHV cable ".format(pmt_label))
                cable_label = self._pmt_to_intcable_[pmt_label]
                channel_label = self._pmt_to_channel_[pmt_label]
                cable_addr = CaloHVInternalCableAddress(cable_label)
                harness_num = cable_addr.harness
                colors = CaloHVSystem.get_harness_colors(harness_num)
                textcolor = colors[1]
                backcolor = colors[0]
                label = cable_label
                txtsize = "normalsize"
                hshift=""  
                if self._mode_ == "other" :
                    label = channel_label
                    txtsize = "small"
                if len(label)>=9:
                    hshift="~\\hskip -6pt" 
                pmt_addr.print_me(sys.stderr, "PMT address: ", "[info] ")
                fout.write("\\newline  \\cellcolor{%s}{\\%s \\textcolor{%s}{%s\\texttt{%s}}} \\newline" % (backcolor, txtsize, textcolor, hshift, label));
                if icol + 1 != ncols :
                    fout.write(" & ")               
            fout.write("& \\textcolor{blue}{\\small %s}" % (row));
            fout.write("\\\\\n");
            fout.write("\\hline\n");
      
        fout.write("\\hline\n");
        fout.write(" & ")
        for icol in range(ncols) :
            column = icol
            if side == SuperNEMO.side_italy :
                column = ncols - icol - 1
            fout.write("\\textcolor{blue}{\\small %s}" % (column));
            if icol + 1 != ncols :
                fout.write(" & ")
        fout.write(" & ")
        fout.write("\\\\\n");
        fout.write("\\hline\n");    

        fout.write("\\end{tabular}\n");
        return
   
    def _mktable_xcalo(self, side_, wall_):
        nrows=16
        ncols=2
        foutname = "{:s}/calohv_xcalo_{:s}_{:d}-{:d}.tex".format(self._printpath_, self._mode_, side_, wall_)
        fout = open(foutname, "w") 
        sys.stderr.write("[info] Generating LaTeX table...\n")
        fout.write("\\begin{tabular}{|");
        fout.write("r|");
        for icol in range(ncols) :
            fout.write("|C{1.2cm}");
        fout.write("||");
        fout.write("l|}\n");
        fout.write("\\hline\n");    
        side = side_
        wall = wall_
        textcolor = "black"
        backcolor = "white"
        # textcolor = "white"
        # backcolor = "XwallGreen"
        # if side == SuperNEMO.side_italy and wall == SuperNEMO.side_tunnel :
        #     backcolor = "XwallViolet"
        # if side == SuperNEMO.side_france and wall == SuperNEMO.side_tunnel :
        #     backcolor = "XwallViolet"
        fout.write(" & ")
        for icol in range(ncols) :
            column = icol
            if side == SuperNEMO.side_italy and wall == SuperNEMO.side_edelweiss:
                column = ncols - 1 - icol
            if side == SuperNEMO.side_france and wall == SuperNEMO.side_tunnel:
                column = ncols - 1 - icol
            fout.write("\\textcolor{blue}{\\small %s}" % (column));
            if icol + 1 != ncols :
                fout.write(" & ")
        fout.write(" & ")
        fout.write("\\\\\n");
                 
        fout.write("\\hline\n\\hline\n");    
        for irow in range(nrows) :
            row = nrows - 1 - irow
            # Cables:
            fout.write("\\textcolor{blue}{\\small %s} &" % (row));
            for icol in range(ncols) :
                column = icol
                if side == SuperNEMO.side_italy and wall == SuperNEMO.side_edelweiss:
                    column = ncols - 1 - icol
                if side == SuperNEMO.side_france and wall == SuperNEMO.side_tunnel:
                    column = ncols - 1 - icol
                pmt_label = "{:s}:{:d}.{:d}.{:d}.{:d}".format("X", side, wall, column, row)
                pmt_addr = OMaddress(pmt_label)
                pmt_addr.print_me(sys.stderr, "PMT address: ", "[info] ")
                if pmt_label in self._pmt_to_intcable_ :
                    print("Found PMT label '{:s}' with CaloHV cable ".format(pmt_label))
                else:
                    print("Cannot found PMT label '{:s}' with CaloHV fiber ".format(pmt_label))
                cable_label = self._pmt_to_intcable_[pmt_label]
                cable_addr = CaloHVInternalCableAddress(cable_label)
                harness_num = cable_addr.harness
                colors = CaloHVSystem.get_harness_colors(harness_num)
                textcolor = colors[1]
                backcolor = colors[0]
                channel_label = self._pmt_to_channel_[pmt_label]
                pmt_addr.print_me(sys.stderr, "PMT address: ", "[info] ")
                label = cable_label
                txtsize = "normalsize"
                hshift="" 
                if self._mode_ == "other" :
                    label = channel_label
                    txtsize = "footnotesize"
                # if len(label)>=9:
                #     hshift="~\\hskip -6pt" 
                fout.write("\\newline  \\cellcolor{%s}{\\%s \\textcolor{%s}{%s\\texttt{%s}}} \\newline" % (backcolor, txtsize, textcolor,  hshift, label));
                if icol + 1 != ncols :
                    fout.write(" & ")               
            fout.write("& \\textcolor{blue}{\\small %s}" % (row));
            fout.write("\\\\\n");
           
            fout.write("\\hline\n");
      
        fout.write("\\hline\n");
        fout.write(" & ")
        for icol in range(ncols) :
            column = icol
            if side == SuperNEMO.side_italy and wall == SuperNEMO.side_edelweiss:
                column = ncols - 1 - icol
            if side == SuperNEMO.side_france and wall == SuperNEMO.side_tunnel:
                column = ncols - 1 - icol
            fout.write("\\textcolor{blue}{\\small %s}" % (column));
            if icol + 1 != ncols :
                fout.write(" & ")
        fout.write(" & ")
        fout.write("\\\\\n");
        fout.write("\\hline\n");    

        fout.write("\\end{tabular}\n");
        return
  
    def _mktable_gveto(self, side_, wall_):
        nrows=1
        ncols=16
        foutname = "{:s}/calohv_gveto_{:s}_{:d}-{:d}.tex".format(self._printpath_, self._mode_, side_, wall_)
        fout = open(foutname, "w") 
        sys.stderr.write("[info] Generating LaTeX table...\n")
        fout.write("\\begin{tabular}{");
        for icol in range(ncols) :
            fout.write("|C{1.2cm}");
        fout.write("|}\n");
        fout.write("\\hline\n");    
        side = side_
        wall = wall_
        textcolor = "black"
        backcolor = "white"
        # textcolor = "white"
        # backcolor = "GvetoBlue"
        # colors = CaloHVSystem.get_harness_colors(harness_num)
        # backcolor = colors[0]
        # textcolor = colors[1]
        if wall == SuperNEMO.wall_top :
            for icol in range(ncols) :
                column = icol
                if side == SuperNEMO.side_italy:
                    column = ncols - 1 - icol
                fout.write("\\textcolor{blue}{\\small %s}" % (column));
                if icol + 1 != ncols :
                    fout.write(" & ")
            fout.write("\\\\\n");
            fout.write("\\hline\n\\hline\n");
            
        for irow in range(nrows) :
            row = nrows - 1 - irow
            # Cables:
            for icol in range(ncols) :
                column = icol
                if side == SuperNEMO.side_italy:
                    column = ncols - 1 - icol
                pmt_label = "{:s}:{:d}.{:d}.{:d}".format("G", side, wall, column)
                pmt_addr = OMaddress(pmt_label)
                pmt_addr.print_me(sys.stderr, "OM address: ", "[info] ")
                if pmt_label in self._pmt_to_intcable_ :
                    print("Found OM label '{:s}' with CaloHV cable ".format(pmt_label))
                else:
                    print("Cannot found OM label '{:s}' with CaloHV cable ".format(pmt_label))
                cable_label = self._pmt_to_intcable_[pmt_label]
                cable_addr = CaloHVInternalCableAddress(cable_label)
                harness_num = cable_addr.harness
                colors = CaloHVSystem.get_harness_colors(harness_num)
                textcolor = colors[1]
                backcolor = colors[0]
                channel_label = self._pmt_to_channel_[pmt_label]
                label = cable_label
                txtsize = "normalsize" 
                if self._mode_ == "other" :
                    label = channel_label
                    txtsize = "footnotesize"
                pmt_addr.print_me(sys.stderr, "OM address: ", "[info] ")
                fout.write("\\newline  \\cellcolor{%s}{\\%s \\textcolor{%s}{\\texttt{%s}}} \\newline" % (backcolor, txtsize, textcolor, label));
                if icol + 1 != ncols :
                    fout.write(" & ")               
            fout.write("\\\\\n");
            
            fout.write("\\hline\n");
      
        if wall == SuperNEMO.wall_bottom :
            fout.write("\\hline\n");
            for icol in range(ncols) :
                column = icol
                if side == SuperNEMO.side_italy:
                    column = ncols - 1 - icol
                fout.write("\\textcolor{blue}{\\small %s}" % (column));
                if icol + 1 != ncols :
                    fout.write(" & ")
            fout.write("\\\\\n");
            fout.write("\\hline\n");    

        fout.write("\\end{tabular}\n");
        return
  
    def _mktable_crate(self, crate_num_):
        nboards=16
        nchannels=32
        foutname = "{:s}/calohv_crate-{:d}_{:s}.tex".format(self._printpath_, crate_num_, self._mode_)
        fout = open(foutname, "w") 
        sys.stderr.write("[info] Generating LaTeX table...\n")
        fout.write("\\begin{tabular}{|");
        fout.write("c|");
        for iboard in range(nboards) :
            fout.write("|C{1.5cm}");
        fout.write("||");
        fout.write("c|}\n");
        
        fout.write("\\hline\n");    
        fout.write(" & \\multicolumn{%d}{c||}{\\textbf{Board}} & \\\\\n" % (nboards));
        
        fout.write("\\hline\n");    
        fout.write(" \\textbf{Channel} & ")
        for iboard in range(nboards) :
            fout.write("\\textcolor{blue}{\\small %s}" % (iboard));
            if iboard + 1 != nboards :
                fout.write(" & ")
        fout.write(" & \\textbf{Channel [Pin]}")
        fout.write("\\\\\n");
        fout.write("\\hline\n\\hline\n");
        for ichannel in range(nchannels) :
            fout.write("\\textcolor{blue}{\\small %s} &" % (ichannel));
            for iboard in range(nboards) :
                textcolor = "black"
                backcolor = "white"                    
                channel_label = "{:s}:{:d}.{:d}.{:d}".format("H", crate_num_, iboard, ichannel)
                channel_addr = CaloHVChannelAddress(channel_label)
                channel_addr.print_me(sys.stderr, "Channel address: ", "[info] ")
                extcable_label = ""
                pmt_label = ""
                if channel_label in self._channel_to_intcable_ :
                    print("Found channel label '{:s}' with CaloHV external cable ".format(channel_label))
                    intcable_label = self._channel_to_intcable_[channel_label]
                    pmt_label = self._channel_to_pmt_[channel_label]
                    intcable_addr = CaloHVInternalCableAddress(intcable_label)
                    harness_num = intcable_addr.harness
                    colors = CaloHVSystem.get_harness_colors(harness_num)
                    backcolor = colors[0]
                    textcolor = colors[1]
                else:
                    print("Cannot find channel label '{:s}' with CaloSignal external cable ".format(channel_label))
                label = extcable_label
                txtsize = "normalsize"
                hshift=""
                if self._mode_ == "other" :
                    label = pmt_label
                    txtsize = "footnotesize"
                hshift=""
                if len(label)>=10:
                    #txtsize = "small" 
                    txtsize = "footnotesize"
                    hshift="~\\hskip -6pt" 
                #fout.write("\\newline  \\cellcolor{%s}{\\%s \\textcolor{%s}{%s\\texttt{%s}}} \\newline " % (backcolor, txtsize, textcolor, hshift, label));
                fout.write("\\cellcolor{%s}{\\%s \\textcolor{%s}{%s\\texttt{%s}}}" % (backcolor, txtsize, textcolor, hshift, label));
                if iboard + 1 != nboards :
                    fout.write(" & ")
            ipin = CaloHVSystem.get_calohv_pin_board_channel_assignment()[ichannel]
            fout.write("& \\textcolor{blue}{\\small %s [%s]}" % (ichannel, ipin));
            #fout.write("& \\textcolor{blue}{\\small %s}" % (ipin));
            fout.write("\\\\\n");
            fout.write("\\hline\n");               

        fout.write("\\end{tabular}\n");

        return
 
    def _mktable_crates(self):
        self._mktable_crate(0)
        self._mktable_crate(1)
        return
    
    def run(self):
        self._load()
        self._mktable_xcalo(SuperNEMO.side_italy, SuperNEMO.side_tunnel)
        self._mktable_calo(SuperNEMO.side_italy)
        self._mktable_xcalo(SuperNEMO.side_italy, SuperNEMO.side_edelweiss)
        self._mktable_gveto(SuperNEMO.side_italy, SuperNEMO.wall_bottom)
        self._mktable_gveto(SuperNEMO.side_italy, SuperNEMO.wall_top)
        self._mktable_xcalo(SuperNEMO.side_france, SuperNEMO.side_edelweiss)
        self._mktable_calo(SuperNEMO.side_france)
        self._mktable_xcalo(SuperNEMO.side_france, SuperNEMO.side_tunnel)
        self._mktable_gveto(SuperNEMO.side_france, SuperNEMO.wall_bottom)
        self._mktable_gveto(SuperNEMO.side_france, SuperNEMO.wall_top)
        if self._mode_ == "other":
            self._mktable_crates()
        return
        
if __name__ == "__main__" :
    calohvmap = "calohv_mapping.csv"
    workdir = "./_calohv_table_out.d/"
    if len(sys.argv) > 1 :
        calohvmap = sys.argv[1]
    if len(sys.argv) > 2 :
        workdir = sys.argv[2]
    sys.stderr.write("CaloHV map file : '{:s}'\n".format(calohvmap))
    sys.stderr.write("Work directory  : '{:s}'\n".format(workdir)) 
    pm = CaloHVCablingMapPrint(calohvmap, workdir)
    pm.set_mode("cable")
    error_code = pm.run()
    pm.set_mode("other")
    error_code = pm.run()
    sys.exit(error_code)

# end
