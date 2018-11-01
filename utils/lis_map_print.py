#!/usr/bin/env python3

import sys
import os
import errno

from om_address import *
from snemo import *

class OptFiberaddress :
    
    def __init__(self, label_):
        self.label = label_.strip()
        self.fibtype = self.label[0].strip()
        address = self.label.split(':')[1].strip()
        self.address = address.split('.')
        self.led = 666
        self.fib = 666
        if self.address[0] != '?' :
            self.led = int(self.address[0])
        if self.address[1] != '?' :
            self.fib = int(self.address[1])
        return
    
    def print_me(self, out_ = sys.stderr, title_ = "", indent_ = ""):
        if len(title_) :
            out_.write("{:s}{:s}\n".format(indent_, title_))
        out_.write("{:s}|-- Type  = '{:s}'\n".format(indent_, self.fibtype))
        out_.write("{:s}|-- LED   = {:d}\n".format(indent_, self.led))
        out_.write("{:s}`-- Fiber = {:d}\n".format(indent_, self.fib))
        return
    
class LISCablingMapPrint:
    """LIS Cabling Map Printer """
   
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
        self._pri_oms_ = {}
        self._sec_oms_ = {}
        return
 
    def _load(self):
        sys.stderr.write("[info] Loading CSV file...\n")
        lines = self._fcsv_.readlines()
        for l in lines:
            line = l[:-1].strip()
            if len(line) == 0 : continue
            if line[0] == '#' : continue
            tokens = line.split(";")
            fiber_label = tokens[0].strip()
            om_label    = tokens[1].strip()
            omaddr = OMaddress(om_label)
            fibaddr = OptFiberaddress(fiber_label)
            omaddr.print_me(sys.stderr, "OM address: ", "[debug] ")
            fibaddr.print_me(sys.stderr, "Fiber address: ", "[debug] ")
            if fiber_label[0] == 'P' :
                self._pri_oms_[om_label] = fiber_label
            elif fiber_label[0] == 'S' :
                self._sec_oms_[om_label] = fiber_label
            else:
                raise Exception("Invalid fiber label ['{:s}']!".format(fiber_label))
        print(self._pri_oms_)
        print(self._sec_oms_)
        return
    
    def _mktable_calo(self, side_):
        ncols=20
        nrows=13
        foutname = "{:s}/calo_{:d}.tex".format(self._printpath_, side_)
        fout = open(foutname, "w") 
        sys.stderr.write("[info] Generating LaTeX table...\n")
        fout.write("\\begin{tabular}{|");
        fout.write("r|");
        for icol in range(ncols) :
            fout.write("|c");
            #fout.write("|C{1cm}");
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

            # Primary fibers:
            fout.write("\\textcolor{blue}{\\small %s} &" % (row));
            for icol in range(ncols) :
                column = icol
                if side == SuperNEMO.side_italy :
                    column = ncols - icol - 1
                om_label = "{:s}:{:d}.{:d}.{:d}".format("M", side, column, row)
                om_addr = OMaddress(om_label)
                om_addr.print_me(sys.stderr, "OM address: ", "[info] ")
                if om_label in self._pri_oms_ :
                    print("Found OM label '{:s}' with primary LIS fiber ".format(om_label))
                else:
                    print("Cannot found OM label '{:s}' with primary LIS fiber ".format(om_label))
                fiber_label = self._pri_oms_[om_label]
                #fiber_addr = OptFiberaddress(fiber_label)
                om_addr.print_me(sys.stderr, "OM address: ", "[info] ")
                #fiber_addr.print_me(sys.stderr, "Fiber address: ", "[info] ")
                fout.write(" {:s} ".format(fiber_label));
                if icol + 1 != ncols :
                    fout.write(" & ")               
            fout.write("& \\textcolor{blue}{\\small %s}" % (row));
            fout.write("\\\\\n");

            # Secondary fibers:
            fout.write(" &");
            for icol in range(ncols) :
                column = icol
                if side == SuperNEMO.side_italy :
                    column = ncols - icol - 1
                om_label = "{:s}:{:d}.{:d}.{:d}".format("M", side, column, row)
                om_addr = OMaddress(om_label)
                om_addr.print_me(sys.stderr, "OM address: ", "[info] ")
                fiber_label = " "
                if row > 0 and row < nrows - 1 :
                    if om_label in self._pri_oms_ :
                        print("Found OM label '{:s}' with primary LIS fiber ".format(om_label))
                        fiber_label = self._sec_oms_[om_label]
                        om_addr.print_me(sys.stderr, "OM address: ", "[info] ")
                    else:
                        print("Cannot found OM label '{:s}' with primary LIS fiber ".format(om_label))
                fout.write(" {:s} ".format(fiber_label));
                if icol + 1 != ncols :
                    fout.write(" & ")               
            fout.write("& ");
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
        foutname = "{:s}/xcalo_{:d}-{:d}.tex".format(self._printpath_, side_, wall_)
        fout = open(foutname, "w") 
        sys.stderr.write("[info] Generating LaTeX table...\n")
        fout.write("\\begin{tabular}{|");
        fout.write("r|");
        for icol in range(ncols) :
            fout.write("|c");
            #fout.write("|C{1cm}");
        fout.write("||");
        fout.write("l|}\n");
        fout.write("\\hline\n");    
        side = side_
        wall = wall_

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

            # Primary fibers:
            fout.write("\\textcolor{blue}{\\small %s} &" % (row));
            for icol in range(ncols) :
                column = icol
                if side == SuperNEMO.side_italy and wall == SuperNEMO.side_edelweiss:
                    column = ncols - 1 - icol
                if side == SuperNEMO.side_france and wall == SuperNEMO.side_tunnel:
                    column = ncols - 1 - icol
                om_label = "{:s}:{:d}.{:d}.{:d}.{:d}".format("X", side, wall, column, row)
                om_addr = OMaddress(om_label)
                om_addr.print_me(sys.stderr, "OM address: ", "[info] ")
                if om_label in self._pri_oms_ :
                    print("Found OM label '{:s}' with primary LIS fiber ".format(om_label))
                else:
                    print("Cannot found OM label '{:s}' with primary LIS fiber ".format(om_label))
                fiber_label = self._pri_oms_[om_label]
                om_addr.print_me(sys.stderr, "OM address: ", "[info] ")
                #fiber_addr = OptFiberaddress(fiber_label)
                #fiber_addr.print_me(sys.stderr, "Fiber address: ", "[info] ")
                fout.write(" {:s} ".format(fiber_label));
                if icol + 1 != ncols :
                    fout.write(" & ")               
            fout.write("& \\textcolor{blue}{\\small %s}" % (row));
            fout.write("\\\\\n");

            # Secondary fibers:
            fout.write(" &");
            for icol in range(ncols) :
                column = icol
                if side == SuperNEMO.side_italy and wall == SuperNEMO.side_edelweiss:
                    column = ncols - 1 - icol
                if side == SuperNEMO.side_france and wall == SuperNEMO.side_tunnel:
                    column = ncols - 1 - icol
                om_label = "{:s}:{:d}.{:d}.{:d}.{:d}".format("X", side, wall, column, row)
                om_addr = OMaddress(om_label)
                om_addr.print_me(sys.stderr, "OM address: ", "[info] ")
                if om_label in self._pri_oms_ :
                    print("Found OM label '{:s}' with primary LIS fiber ".format(om_label))
                else:
                    print("Cannot found OM label '{:s}' with primary LIS fiber ".format(om_label))
                fiber_label = self._sec_oms_[om_label]
                om_addr.print_me(sys.stderr, "OM address: ", "[info] ")
                fout.write(" {:s} ".format(fiber_label));
                if icol + 1 != ncols :
                    fout.write(" & ")               
            fout.write("& ");
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
        foutname = "{:s}/gveto_{:d}-{:d}.tex".format(self._printpath_, side_, wall_)
        fout = open(foutname, "w") 
        sys.stderr.write("[info] Generating LaTeX table...\n")
        fout.write("\\begin{tabular}{");
        for icol in range(ncols) :
            fout.write("|c");
            #fout.write("|C{1cm}");
        fout.write("|}\n");
        fout.write("\\hline\n");    
        side = side_
        wall = wall_

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

            # Primary fibers:
            for icol in range(ncols) :
                column = icol
                if side == SuperNEMO.side_italy:
                    column = ncols - 1 - icol
                om_label = "{:s}:{:d}.{:d}.{:d}".format("G", side, wall, column)
                om_addr = OMaddress(om_label)
                om_addr.print_me(sys.stderr, "OM address: ", "[info] ")
                if om_label in self._pri_oms_ :
                    print("Found OM label '{:s}' with primary LIS fiber ".format(om_label))
                else:
                    print("Cannot found OM label '{:s}' with primary LIS fiber ".format(om_label))
                fiber_label = self._pri_oms_[om_label]
                om_addr.print_me(sys.stderr, "OM address: ", "[info] ")
                fout.write(" {:s} ".format(fiber_label));
                if icol + 1 != ncols :
                    fout.write(" & ")               
            fout.write("\\\\\n");

            # Secondary fibers:
            for icol in range(ncols) :
                column = icol
                if side == SuperNEMO.side_italy:
                    column = ncols - 1 - icol
                om_label = "{:s}:{:d}.{:d}.{:d}".format("G", side, wall, column)
                om_addr = OMaddress(om_label)
                om_addr.print_me(sys.stderr, "OM address: ", "[info] ")
                if om_label in self._pri_oms_ :
                    print("Found OM label '{:s}' with primary LIS fiber ".format(om_label))
                else:
                    print("Cannot found OM label '{:s}' with primary LIS fiber ".format(om_label))
                fiber_label = self._sec_oms_[om_label]
                om_addr.print_me(sys.stderr, "OM address: ", "[info] ")
                fout.write(" {:s} ".format(fiber_label));
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
    lismap = "lis_mapping-skel.csv"
    workdir = "./_lis_table_out.d/"
    if len(sys.argv) > 1 :
        lismap = sys.argv[1]
    if len(sys.argv) > 2 :
        workdir = sys.argv[2]
    sys.stderr.write("LIS map file   : '{:s}'\n".format(lismap))
    sys.stderr.write("Work directory : '{:s}'\n".format(workdir)) 
    pm = LISCablingMapPrint(lismap, workdir)
    error_code = pm.run()
    sys.exit(error_code)

# end
