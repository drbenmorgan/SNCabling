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
        self._pmt_to_cable_ = {}
        self._pmt_to_channel_ = {}
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
            self._pmt_to_cable_[pmt_label]   = intcable_label
            self._pmt_to_channel_[pmt_label] = channel_label
        print(self._pmt_to_cable_)
        print(self._pmt_to_channel_)
        return
    
    def _mktable_calo(self, side_):
        ncols=20
        nrows=13
        foutname = "{:s}/calohv_main_{:d}.tex".format(self._printpath_, side_)
        fout = open(foutname, "w") 
        sys.stderr.write("[info] Generating LaTeX table...\n")
        fout.write("\\begin{tabular}{|");
        fout.write("r|");
        for icol in range(ncols) :
            #fout.write("|c{1cm}");
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
                backcolor = "orange!75"
                if row == nrows - 1:
                    textcolor = "white"
                    backcolor = "blue!75"
                    backcolor = "MainTopBlue"
                else:
                    if column < 10 and row in [ 0,1,2,6,7,8]:
                        backcolor = "yellow!75"
                    if column >= 10 and row in [ 3,4,5,9,10,11]:
                        backcolor = "yellow!75"
                pmt_label = "{:s}:{:d}.{:d}.{:d}".format("M", side, column, row)
                pmt_addr = OMaddress(pmt_label)
                pmt_addr.print_me(sys.stderr, "PMT address: ", "[info] ")
                if pmt_label in self._pmt_to_cable_ :
                    print("Found PMT label '{:s}' with CaloHV cable ".format(pmt_label))
                else:
                    print("Cannot found PMT label '{:s}' with CaloHV cable ".format(pmt_label))
                cable_label = self._pmt_to_cable_[pmt_label]
                pmt_addr.print_me(sys.stderr, "PMT address: ", "[info] ")
                fout.write("\\newline  \\cellcolor{%s}\\textcolor{%s}{\\texttt{%s}} \\newline " % (backcolor, textcolor, cable_label));
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
        foutname = "{:s}/calohv_xcalo_{:d}-{:d}.tex".format(self._printpath_, side_, wall_)
        fout = open(foutname, "w") 
        sys.stderr.write("[info] Generating LaTeX table...\n")
        fout.write("\\begin{tabular}{|");
        fout.write("r|");
        for icol in range(ncols) :
            #fout.write("|c");
            fout.write("|C{1.2cm}");
        fout.write("||");
        fout.write("l|}\n");
        fout.write("\\hline\n");    
        side = side_
        wall = wall_
        textcolor = "white"
        backcolor = "XwallGreen"
        if side == SuperNEMO.side_italy and wall == SuperNEMO.side_tunnel :
            backcolor = "XwallViolet"
        if side == SuperNEMO.side_france and wall == SuperNEMO.side_tunnel :
            backcolor = "XwallViolet"
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
                pmt_label = "{:s}:{:d}.{:d}.{:d}.{:d}".format("X", side, wall, column, row)
                pmt_addr = OMaddress(pmt_label)
                pmt_addr.print_me(sys.stderr, "PMT address: ", "[info] ")
                if pmt_label in self._pmt_to_cable_ :
                    print("Found PMT label '{:s}' with CaloHV cable ".format(pmt_label))
                else:
                    print("Cannot found PMT label '{:s}' with CaloHV fiber ".format(pmt_label))
                cable_label = self._pmt_to_cable_[pmt_label]
                pmt_addr.print_me(sys.stderr, "PMT address: ", "[info] ")
                fout.write("\\newline  \\cellcolor{%s}\\textcolor{%s}{\\texttt{%s}} \\newline " % (backcolor, textcolor, cable_label));
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
        foutname = "{:s}/calohv_gveto_{:d}-{:d}.tex".format(self._printpath_, side_, wall_)
        fout = open(foutname, "w") 
        sys.stderr.write("[info] Generating LaTeX table...\n")
        fout.write("\\begin{tabular}{");
        for icol in range(ncols) :
            #fout.write("|c");
            fout.write("|C{1.2cm}");
        fout.write("|}\n");
        fout.write("\\hline\n");    
        side = side_
        wall = wall_
        textcolor = "white"
        backcolor = "GvetoBlue"

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
                if pmt_label in self._pmt_to_cable_ :
                    print("Found OM label '{:s}' with CaloHV cable ".format(pmt_label))
                else:
                    print("Cannot found OM label '{:s}' with CaloHV cable ".format(pmt_label))
                cable_label = self._pmt_to_cable_[pmt_label]
                pmt_addr.print_me(sys.stderr, "OM address: ", "[info] ")
                fout.write("\\newline  \\cellcolor{%s}\\textcolor{%s}{\\texttt{%s}} \\newline " % (backcolor, textcolor, cable_label));
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
        return
        
if __name__ == "__main__" :
    calohvmap = "calohv_mapping-skel.csv"
    workdir = "./_calohv_table_out.d/"
    if len(sys.argv) > 1 :
        calohvmap = sys.argv[1]
    if len(sys.argv) > 2 :
        workdir = sys.argv[2]
    sys.stderr.write("CaloHV map file : '{:s}'\n".format(calohvmap))
    sys.stderr.write("Work directory  : '{:s}'\n".format(workdir)) 
    pm = CaloHVCablingMapPrint(calohvmap, workdir)
    error_code = pm.run()
    sys.exit(error_code)

# end
