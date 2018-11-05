#!/usr/bin/env python3

import sys

from snemo import *
from calosignal import *

class CaloSignalCablingMapSkelGen:
    """CaloSignal Cabling Map Skeleton Generator """

    def __init__(self, csvfile_, debug_ = False):
        self._fcsv_ = open(csvfile_, "w")
        self._debug_ = debug_
        return

    def _run_gveto(self, side_):
        crate_num   = 2
        nwalls   = 2
        ncolumns = 16
        self._fcsv_.write("# Gamma veto wall side {:d}:\n".format(side_))
        for om_wall in range(nwalls) :
            self._fcsv_.write("# Wall {:d}:\n".format(om_wall))
            harness_num = 20
            board_slot = 4
            if side_ == SuperNEMO.side_italy :
                 if om_wall == SuperNEMO.wall_top:
                     harness_num = 21
                     board_slot = 5
            elif side_ == SuperNEMO.side_france :
                harness_num = 9
                board_slot = 16
                if om_wall == SuperNEMO.wall_top:
                    harness_num = 10
                    board_slot = 15     
            for om_column in range(ncolumns):
                om_lbl = "{:s}:{:d}.{:d}.{:d}".format("G", side_, om_wall, om_column)
                if self._debug_ :
                    sys.stderr.write("==> Gveto label={:s}\n".format(om_lbl))
                channel_num = om_column
                board_num = board_slot
                cable_num = channel_num
                if self._debug_ :
                    sys.stderr.write("\tCrate    # ={:d}\n".format(crate_num))
                    sys.stderr.write("\tBoard    # ={:d}\n".format(board_num))
                    sys.stderr.write("\tChannel  # ={:d}\n".format(channel_num))
                    sys.stderr.write("\tHarness  # ={:d}\n".format(harness_num))
                    sys.stderr.write("\tCable    # ={:d}\n".format(cable_num))
                channel_lbl = "{:s}:{:d}.{:d}.{:d}".format("H", crate_num, board_num, channel_num)
                board_lbl = "{:s}:{:d}.{:d}".format("B", crate_num, board_num)
                extharness_lbl = "{:s}:{:d}".format("E", harness_num)
                intharness_lbl = "{:s}:{:d}".format("I", harness_num)
                extcable_lbl = "{:s}:{:d}.{:d}".format("L", harness_num, cable_num)
                intcable_lbl = "{:s}:{:d}.{:d}".format("A", harness_num, cable_num)
                self._fcsv_.write("{:9s} ; {:8s} ; {:8s} ; {:10s}\n".format(channel_lbl, extcable_lbl, intcable_lbl, om_lbl))
        return
 
    def _run_xcalo(self, side_):
        crate_num     = 2
        first_harness = 18
        last_harness  = 19
        if side_ == SuperNEMO.side_france :
            first_harness = 7
            last_harness  = 8
        self._fcsv_.write("# X wall side {:d}:\n".format(side_))
        nb_harnesses = last_harness - first_harness + 1
        nrows  = 16
        ncols  = 2
        nwalls = 2
        harness_num = -1
        channel_num = -1
        cable_num   = -1
        half_ncols  = ncols // 2
        for om_wall in range(nwalls):
            self._fcsv_.write("# Wall {:d}:\n".format(om_wall))
            harness_num = first_harness
            if om_wall == SuperNEMO.side_tunnel :
                harness_num = last_harness
            board_slot = 6
            for om_column in range(ncols):
                if side_ == SuperNEMO.side_italy :
                    if om_wall == SuperNEMO.side_edelweiss :
                        harness_num = 18
                        if om_column == 0:
                            board_slot = 6
                        if om_column == 1:
                            board_slot = 7
                    if om_wall == SuperNEMO.side_tunnel :
                        harness_num = 19
                        if om_column == 0:
                            board_slot = 8
                        if om_column == 1:
                            board_slot = 9              
                if side_ == SuperNEMO.side_france :
                    if om_wall == SuperNEMO.side_edelweiss :
                        harness_num = 7
                        if om_column == 0:
                            board_slot = 14
                        if om_column == 1:
                            board_slot = 13
                    if om_wall == SuperNEMO.side_tunnel :
                        harness_num = 8
                        if om_column == 0:
                            board_slot = 12
                        if om_column == 1:
                            board_slot = 11
                board_num = board_slot
                for om_row in range(nrows):
                    om_lbl = "{:s}:{:d}.{:d}.{:d}.{:d}".format("X", side_, om_wall, om_column, om_row)
                    if self._debug_ :
                        sys.stderr.write("==> X wall label={:s}\n".format(om_lbl))
                    cable_num = om_row
                    if om_column == 1:
                        cable_num += 16
                    # if harness_num == 18 or harness_num == 8 :
                    #     if om_column == 1:
                    #         cable_num += 16
                    # if harness_num == 18 andom_wall == SuperNEMO.side_tunnel :
                    #     if om_column == 1:
                    #         cable_num += 16
                    channel_num = om_row
                    if self._debug_ :
                        sys.stderr.write("\tCrate    # ={:d}\n".format(crate_num))
                        sys.stderr.write("\tBoard    # ={:d}\n".format(board_num))
                        sys.stderr.write("\tChannel  # ={:d}\n".format(channel_num))
                        sys.stderr.write("\tHarness  # ={:d}\n".format(harness_num))
                        sys.stderr.write("\tCable    # ={:d}\n".format(cable_num))
                    channel_lbl = "{:s}:{:d}.{:d}.{:d}".format("H", crate_num, board_num, channel_num)
                    board_lbl = "{:s}:{:d}.{:d}".format("B", crate_num, board_num)
                    extharness_lbl = "{:s}:{:d}".format("E", harness_num)
                    intharness_lbl = "{:s}:{:d}".format("I", harness_num)
                    intcable_lbl = "{:s}:{:d}.{:d}".format("A", harness_num, cable_num)
                    extcable_lbl = "{:s}:{:d}.{:d}".format("L", harness_num, cable_num)
                    self._fcsv_.write("{:9s} ; {:8s} ; {:8s} ; {:10s}\n".format(channel_lbl, extcable_lbl, intcable_lbl, om_lbl))
        return
    
    def _run_calo(self, side_):
        first_harness = 11
        last_harness  = 17
        crate_num     = 0
        if side_ == SuperNEMO.side_france :
            first_harness = 0
            last_harness  = 6
            crate_num     = 1
        self._fcsv_.write("# Main wall side {:d}:\n".format(side_))
        nb_harnesses = last_harness - first_harness + 1
        nrows = 13
        ncols = 20
        harness_num = -1
        channel_num = -1
        cable_num   = -1
        for om_column in range(ncols):
            self._fcsv_.write("# Column {:d}:\n".format(om_column))
            for om_row in range(nrows):
                om_lbl = "{:s}:{:d}.{:d}.{:d}".format("M", side_, om_column, om_row)
                if self._debug_ :
                    sys.stderr.write("==> Calo main label={:s}\n".format(om_lbl))
                if om_row == nrows - 1:
                    harness_num = last_harness
                    cable_num = om_column
                else:
                    harness_num = first_harness + (om_row // 2)
                    cable_num = om_column
                    if om_row % 2 :
                        cable_num += 20
                channel_num = om_row
                board_slot = om_column
                if om_column > 9:
                    board_slot += 1
                board_num = board_slot
                if self._debug_ :
                    sys.stderr.write("\tCrate    # ={:d}\n".format(crate_num))
                    sys.stderr.write("\tBoard    # ={:d}\n".format(board_num))
                    sys.stderr.write("\tChannel  # ={:d}\n".format(channel_num))
                    sys.stderr.write("\tHarness  # ={:d}\n".format(harness_num))
                    sys.stderr.write("\tCable    # ={:d}\n".format(cable_num))
                channel_lbl = "{:s}:{:d}.{:d}.{:d}".format("H", crate_num, board_num, channel_num)
                board_lbl = "{:s}:{:d}.{:d}".format("B", crate_num, board_num)
                extharness_lbl = "{:s}:{:d}".format("E", harness_num)
                intharness_lbl = "{:s}:{:d}".format("I", harness_num)
                intcable_lbl = "{:s}:{:d}.{:d}".format("A", harness_num, cable_num)
                extcable_lbl = "{:s}:{:d}.{:d}".format("L", harness_num, cable_num)
                self._fcsv_.write("{:9s} ; {:8s} ; {:8s} ; {:10s}\n".format(channel_lbl, extcable_lbl, intcable_lbl, om_lbl))
        return
        
 
    def run(self):
        self._fcsv_.write("##############\n")
        self._fcsv_.write("# Main walls #\n")
        self._fcsv_.write("##############\n")
        self._run_calo(SuperNEMO.side_italy)
        self._run_calo(SuperNEMO.side_france)
        self._fcsv_.write("####################\n")
        self._fcsv_.write("# X walls #\n")
        self._fcsv_.write("####################\n")
        self._run_xcalo(SuperNEMO.side_italy)
        self._run_xcalo(SuperNEMO.side_france)
        self._fcsv_.write("####################\n")
        self._fcsv_.write("# Gamma veto walls #\n")
        self._fcsv_.write("####################\n")
        self._run_gveto(SuperNEMO.side_italy)
        self._run_gveto(SuperNEMO.side_france)
        # self._run_ref_om()
        return

if __name__ == "__main__" :
    gm = CaloSignalCablingMapSkelGen("calosignal_mapping-skel.csv", True)
    error_code = gm.run()
    sys.exit(error_code)

# end
