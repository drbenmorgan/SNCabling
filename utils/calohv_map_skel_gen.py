#!/usr/bin/env python3

import sys

from snemo import *

class CaloHVCablingMapSkelGen:
    """CaloHV Cabling Map Skeleton Generator """

    def __init__(self, csvfile_, debug_ = False):
        self._fcsv_ = open(csvfile_, "w")
        self._debug_ = debug_
        return

    @staticmethod
    def get_redel_female_pins_xwall():
        redel_female_pins = [ 3, 4, 5, 6, 7, 8, 14, 15, 16, 17, 18, 19, 20, 24, 25, 26, 27, 28, 29, 30, 34, 35, 36, 37, 38, 39, 45, 46, 47, 48, 49, 50]
        return redel_female_pins

    @staticmethod
    def get_redel_female_pins_gveto():
        redel_female_pins = [ 3, 4, 5, 6, 7, 8, 14, 15, 16, 17, 18, 19, 20, 24, 25, 26, 27, 28, 29, 30, 34, 35, 36, 37, 38, 39, 45, 46, 47, 48, 49, 50]
        return redel_female_pins

    @staticmethod
    def get_redel_female_pins():
        redel_female_pins = [ 3, 4, 5, 6, 7, 8, 14, 15, 16, 17, 18, 19, 20, 24, 25, 26, 27, 28, 29, 30, 34, 35, 36, 37, 38, 39, 45, 46, 47, 48]
        return redel_female_pins

    @staticmethod
    def get_redel_female_spare_pins():
        redel_female_spare_pins = [ 49, 50]
        return redel_female_spare_pins

    @staticmethod
    def get_redel_female_pins_top():
        redel_female_pins = [ 3, 4, 5, 6, 7, 8, 14, 15, 16, 17, 18, 19, 20, 24, 25, 26, 27, 28, 29, 30]
        return redel_female_pins

    @staticmethod
    def get_redel_female_spare_pins_top():
        redel_female_spare_pins = [ 34, 35, 36, 37, 38, 39, 45, 46, 47, 48, 49, 50]
        return redel_female_spare_pins

    @staticmethod
    def get_calohv_board_channel_pin_assignment():
        calohv_pins_assignment = {}
        calohv_pins_assignment[3]  = 23 
        calohv_pins_assignment[4]  = 24
        calohv_pins_assignment[5]  = 25
        calohv_pins_assignment[6]  = 26
        calohv_pins_assignment[7]  = 27
        calohv_pins_assignment[8]  = 28
        calohv_pins_assignment[14] = 18
        calohv_pins_assignment[15] = 19
        calohv_pins_assignment[16] = 20
        calohv_pins_assignment[17] = 21
        calohv_pins_assignment[18] = 22
        calohv_pins_assignment[19] = 29
        calohv_pins_assignment[20] = 30
        calohv_pins_assignment[24] = 12
        calohv_pins_assignment[25] = 13
        calohv_pins_assignment[26] = 14
        calohv_pins_assignment[27] = 15
        calohv_pins_assignment[28] = 16
        calohv_pins_assignment[29] = 17
        calohv_pins_assignment[30] = 31
        calohv_pins_assignment[34] = 6
        calohv_pins_assignment[35] = 7
        calohv_pins_assignment[36] = 8
        calohv_pins_assignment[37] = 9
        calohv_pins_assignment[38] = 10
        calohv_pins_assignment[39] = 11
        calohv_pins_assignment[45] = 0
        calohv_pins_assignment[46] = 1
        calohv_pins_assignment[47] = 2
        calohv_pins_assignment[48] = 3
        calohv_pins_assignment[49] = 4
        calohv_pins_assignment[50] = 5
        return calohv_pins_assignment

    @staticmethod
    def get_calohv_pin_board_channel_assignment():
        calohv_pins_assignment = {}
        calohv_pins_assignment[23] = 3 
        calohv_pins_assignment[24] = 4 
        calohv_pins_assignment[25] = 5 
        calohv_pins_assignment[26] = 6
        calohv_pins_assignment[27] = 7
        calohv_pins_assignment[28] = 8
        calohv_pins_assignment[18] = 14
        calohv_pins_assignment[19] = 15
        calohv_pins_assignment[20] = 16
        calohv_pins_assignment[21] = 17
        calohv_pins_assignment[22] = 18
        calohv_pins_assignment[29] = 19
        calohv_pins_assignment[30] = 20
        calohv_pins_assignment[12] = 24
        calohv_pins_assignment[13] = 25
        calohv_pins_assignment[14] = 26
        calohv_pins_assignment[15] = 27
        calohv_pins_assignment[16] = 28
        calohv_pins_assignment[17] = 29
        calohv_pins_assignment[31] = 30
        calohv_pins_assignment[6]  = 34
        calohv_pins_assignment[7]  = 35
        calohv_pins_assignment[8]  = 36
        calohv_pins_assignment[9]  = 37
        calohv_pins_assignment[10] = 38
        calohv_pins_assignment[11] = 39
        calohv_pins_assignment[0]  = 45
        calohv_pins_assignment[1]  = 46
        calohv_pins_assignment[2]  = 47
        calohv_pins_assignment[3]  = 48
        calohv_pins_assignment[4]  = 49
        calohv_pins_assignment[5]  = 50
        return calohv_pins_assignment
 
    def _run_gveto(self, side_):
        board_num   = 11
        crate_num   = 0
        harness_num = 23
        if side_ == SuperNEMO.side_france :
            crate_num   = 1
            harness_num = 11
        nwalls   = 2
        ncolumns = 16
        self._fcsv_.write("# Gamma veto wall side {:d}:\n".format(side_))
        for om_wall in range(nwalls) :
            self._fcsv_.write("# Wall {:d}:\n".format(om_wall))
            for om_column in range(ncolumns):
                om_lbl = "{:s}:{:d}.{:d}.{:d}".format("G", side_, om_wall, om_column)
                if self._debug_ :
                    sys.stderr.write("==> Gveto label={:s}\n".format(om_lbl))
                pin_index = om_wall * ncolumns + om_column
                pin_num = CaloHVCablingMapSkelGen.get_redel_female_pins_gveto()[pin_index]
                cable_num = pin_num
                channel_num = CaloHVCablingMapSkelGen.get_calohv_board_channel_pin_assignment()[pin_num]
                if self._debug_ :
                    sys.stderr.write("\tHarness  # ={:d}\n".format(harness_num))
                    sys.stderr.write("\tCrate    # ={:d}\n".format(crate_num))
                    sys.stderr.write("\tBoard    # ={:d}\n".format(board_num))
                    sys.stderr.write("\tChannel  # ={:d}\n".format(channel_num))
                    sys.stderr.write("\tPin index  ={:d}\n".format(pin_index))
                    sys.stderr.write("\tPin      # ={:d}\n".format(pin_num))
                    sys.stderr.write("\tCable    # ={:d}\n".format(cable_num))
                channel_lbl = "{:s}:{:d}.{:d}.{:d}".format("H", crate_num, board_num, channel_num)
                board_lbl = "{:s}:{:d}.{:d}".format("B", crate_num, board_num)
                extharness_lbl = "{:s}:{:d}".format("E", harness_num)
                intcable_lbl = "{:s}:{:d}.{:d}".format("A", harness_num, cable_num)
                self._fcsv_.write("{:9s} ; {:5s} ; {:8s} ; {:10s}\n".format(channel_lbl, extharness_lbl, intcable_lbl, om_lbl))
        return
 
    def _run_xcalo(self, side_):
        first_harness = 21
        last_harness  = 22
        crate_num     = 0
        if side_ == SuperNEMO.side_france :
            first_harness = 9
            last_harness  = 10
            crate_num     = 1
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
            pin_index = -1
            for om_column in range(ncols):
                for om_row in range(nrows):
                    om_lbl = "{:s}:{:d}.{:d}.{:d}.{:d}".format("X", side_, om_wall, om_column, om_row)
                    if self._debug_ :
                        sys.stderr.write("==> X wall label={:s}\n".format(om_lbl))
                    ### harness_num = first_harness + 2 * (om_row // nrows)
                    pin_index += 1
                    print("======> X-wall Pin index : %d" % pin_index) 
                    # pin_index = (om_row % nrows) * 2 + om_column
                    # if om_column >= half_ncols :
                    #     pin_index = (om_row % nrows) * 2 + (om_column - nrows)
                    pin_num = CaloHVCablingMapSkelGen.get_redel_female_pins_xwall()[pin_index]
                    cable_num = pin_num
                    channel_num = CaloHVCablingMapSkelGen.get_calohv_board_channel_pin_assignment()[pin_num]
                    board_num = harness_num % 12
                    if self._debug_ :
                        sys.stderr.write("\tHarness  # ={:d}\n".format(harness_num))
                        sys.stderr.write("\tCrate    # ={:d}\n".format(crate_num))
                        sys.stderr.write("\tBoard    # ={:d}\n".format(board_num))
                        sys.stderr.write("\tChannel  # ={:d}\n".format(channel_num))
                        sys.stderr.write("\tPin index  ={:d}\n".format(pin_index))
                        sys.stderr.write("\tPin      # ={:d}\n".format(pin_num))
                        sys.stderr.write("\tCable    # ={:d}\n".format(cable_num))
                    channel_lbl = "{:s}:{:d}.{:d}.{:d}".format("H", crate_num, board_num, channel_num)
                    board_lbl = "{:s}:{:d}.{:d}".format("B", crate_num, board_num)
                    extharness_lbl = "{:s}:{:d}".format("E", harness_num)
                    intcable_lbl = "{:s}:{:d}.{:d}".format("A", harness_num, cable_num)
                    self._fcsv_.write("{:9s} ; {:5s} ; {:8s} ; {:10s}\n".format(channel_lbl, extharness_lbl, intcable_lbl, om_lbl))
        return
    
    def _run_calo(self, side_):
        first_harness = 12
        last_harness  = 20
        crate_num     = 0
        if side_ == SuperNEMO.side_france :
            first_harness = 0
            last_harness  = 8
            crate_num     = 1
        self._fcsv_.write("# Main wall side {:d}:\n".format(side_))
        nb_harnesses = last_harness - first_harness + 1
        nrows = 13
        ncols = 20
        harness_num = -1
        channel_num = -1
        cable_num   = -1
        half_ncols  = ncols // 2
        for om_column in range(ncols):
            self._fcsv_.write("# Column {:d}:\n".format(om_column))
            for om_row in range(nrows):
                om_lbl = "{:s}:{:d}.{:d}.{:d}".format("M", side_, om_column, om_row)
                if self._debug_ :
                    sys.stderr.write("==> Calo main label={:s}\n".format(om_lbl))
                if om_row == nrows - 1:
                    harness_num = last_harness
                    pin_index = om_column
                    pin_num = CaloHVCablingMapSkelGen.get_redel_female_pins_top()[pin_index]
                else:
                    harness_num = first_harness + 2 * (om_row // 3)
                    pin_index = (om_row % 3) * 10 + om_column
                    if om_column >= half_ncols :
                        harness_num += 1
                        pin_index = (om_row % 3) * 10 + (om_column - 10)
                    pin_num = CaloHVCablingMapSkelGen.get_redel_female_pins()[pin_index]
                cable_num = pin_num
                channel_num = CaloHVCablingMapSkelGen.get_calohv_board_channel_pin_assignment()[pin_num]
                board_num = harness_num
                harness_bias = 12
                if harness_num >= harness_bias :
                    board_num = harness_num - harness_bias
                if self._debug_ :
                    sys.stderr.write("\tHarness  # ={:d}\n".format(harness_num))
                    sys.stderr.write("\tCrate    # ={:d}\n".format(crate_num))
                    sys.stderr.write("\tBoard    # ={:d}\n".format(board_num))
                    sys.stderr.write("\tChannel  # ={:d}\n".format(channel_num))
                    sys.stderr.write("\tPin index  ={:d}\n".format(pin_index))
                    sys.stderr.write("\tPin      # ={:d}\n".format(pin_num))
                    sys.stderr.write("\tCable    # ={:d}\n".format(cable_num))
                channel_lbl = "{:s}:{:d}.{:d}.{:d}".format("H", crate_num, board_num, channel_num)
                board_lbl = "{:s}:{:d}.{:d}".format("B", crate_num, board_num)
                extharness_lbl = "{:s}:{:d}".format("E", harness_num)
                intcable_lbl = "{:s}:{:d}.{:d}".format("A", harness_num, cable_num)
                self._fcsv_.write("{:9s} ; {:5s} ; {:8s} ; {:10s}\n".format(channel_lbl, extharness_lbl, intcable_lbl, om_lbl))
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
    gm = CaloHVCablingMapSkelGen("calohv_mapping-skel.csv", True)
    error_code = gm.run()
    sys.exit(error_code)

# end
