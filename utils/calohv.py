#!/usr/bin/env python3

import sys


class CaloHVSystem :

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
     
    @staticmethod
    def get_hv_crate_board_slots():
        hv_board_slots = [ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11]
        #hv_board_slots = [ 0, 1, 3, 4, 6, 7, 9, 10, 11, 13, 14, 15]
        return hv_board_slots

    @staticmethod
    def get_hv_crate_board_harness_assignment():
        b2h_map = {}
        b2h_map[0] = 0
        b2h_map[1] = 1
        b2h_map[2] = 2
        b2h_map[3] = 3
        b2h_map[4] = 4
        b2h_map[5] = 5
        b2h_map[6] = 6
        b2h_map[7] = 7
        b2h_map[8] = 8
        b2h_map[9] = 9
        b2h_map[10] = 10
        b2h_map[11] = 11
        
        # b2h_map[0] = 0
        # b2h_map[1] = 1
        # b2h_map[3] = 2
        # b2h_map[4] = 3
        # b2h_map[6] = 4
        # b2h_map[7] = 5
        # b2h_map[9] = 6
        # b2h_map[10] = 7
        # b2h_map[11] = 8
        # b2h_map[13] = 9
        # b2h_map[14] = 10
        # b2h_map[15] = 11
        return b2h_map

    @staticmethod
    def get_hv_crate_harness_board_assignment():
        h2b_map = {}
        h2b_map[0] = 0
        h2b_map[1] = 1
        h2b_map[2] = 2
        h2b_map[3] = 3
        h2b_map[4] = 4
        h2b_map[5] = 5
        h2b_map[6] = 6
        h2b_map[7] = 7
        h2b_map[8] = 8
        h2b_map[9] = 9
        h2b_map[10] = 10
        h2b_map[11] = 11
        h2b_map[12] = 0
        h2b_map[13] = 1
        h2b_map[14] = 2
        h2b_map[15] = 3
        h2b_map[16] = 4
        h2b_map[17] = 5
        h2b_map[18] = 6
        h2b_map[19] = 7
        h2b_map[20] = 8
        h2b_map[21] = 9
        h2b_map[22] = 10
        h2b_map[23] = 11

        # h2b_map[0] = 0
        # h2b_map[1] = 1
        # h2b_map[2] = 3
        # h2b_map[3] = 4
        # h2b_map[4] = 6
        # h2b_map[5] = 7
        # h2b_map[6] = 9
        # h2b_map[7] = 10
        # h2b_map[8] = 11
        # h2b_map[9] = 13
        # h2b_map[10] = 14
        # h2b_map[11] = 15
        # h2b_map[12] = 0
        # h2b_map[13] = 1
        # h2b_map[14] = 3
        # h2b_map[15] = 4
        # h2b_map[16] = 6
        # h2b_map[17] = 7
        # h2b_map[18] = 9
        # h2b_map[19] = 10
        # h2b_map[20] = 11
        # h2b_map[21] = 13
        # h2b_map[22] = 14
        # h2b_map[23] = 15
        return h2b_map
 
    @staticmethod
    def get_harness_colors(harness_num_):
        color_map = {}
        color_map[0]  = ("MainWallYellow", "black")
        color_map[1]  = ("MainWallOrange", "black")
        color_map[2]  = ("MainWallOrange", "black")
        color_map[3]  = ("MainWallYellow", "black")
        color_map[4]  = ("MainWallYellow", "black")
        color_map[5]  = ("MainWallOrange", "black")
        color_map[6]  = ("MainWallOrange", "black")
        color_map[7]  = ("MainWallYellow", "black")
        color_map[8]  = ("MainWallTopBlue", "white")
        color_map[9]  = ("XwallGreen",  "white")
        color_map[10] = ("XwallViolet", "white")
        color_map[11] = ("GvetoBlue",   "black")
        
        color_map[12] = ("MainWallYellow", "black")
        color_map[13] = ("MainWallOrange", "black")
        color_map[14] = ("MainWallOrange", "black")
        color_map[15] = ("MainWallYellow", "black")
        color_map[16] = ("MainWallYellow", "black")
        color_map[17] = ("MainWallOrange", "black")
        color_map[18] = ("MainWallOrange",  "black")
        color_map[19] = ("MainWallYellow", "black")
        color_map[20] = ("MainWallTopBlue", "white")
        color_map[21] = ("XwallGreen",  "white")
        color_map[22] = ("XwallViolet", "white")
        color_map[23] = ("GvetoBlue",   "black")
        return color_map[harness_num_]
    
class CaloHVBoardAddress :
    
    def __init__(self, label_):
        self.label = label_.strip()
        self.addrtype = self.label[0]
        if self.addrtype != "B" :
            raise Exception("Invalid CaloHV board address '%s'!" % self.label)
        address = self.label.split(':')[1].strip()
        self.address = address.split('.')
        self.crate = 666
        self.board = 666
        if self.address[0] != '?' :
            self.crate = int(self.address[0])
        if self.address[1] != '?' :
            self.board = int(self.address[1])
        return

    def __eq__(self, other_) :
        if isinstance(other_, self.__class__):
            return self.crate == other_.crate and self.board == other_.board
        return False
  
    def __ne__(self, other_) :
        return self.crate != other_.crate or self.board != other_.board
 
    def __lt__(self, other_) :
        if self.crate < other_.crate :
            return True
        elif self.crate == other_.crate :
            if self.board < other_.board :
                return True
        return False
  
    def to_string(self):
        return "B:{:d}.{:d}".format(self.crate, self.board)
    
    def print_me(self, out_ = sys.stderr, title_ = "", indent_ = ""):
        if len(title_) :
            out_.write("{:s}{:s}\n".format(indent_, title_))
        out_.write("{:s}|-- Crate = {:d}\n".format(indent_, self.crate))
        out_.write("{:s}`-- Board = {:d}\n".format(indent_, self.board))
        return
    
class CaloHVChannelAddress :
    
    def __init__(self, label_):
        self.label = label_.strip()
        self.addrtype = self.label[0]
        if self.addrtype != "H" :
            raise Exception("Invalid CaloHV board address '%s'!" % self.label)
        address = self.label.split(':')[1].strip()
        self.address = address.split('.')
        self.crate = 666
        self.board = 666
        self.channel = 666
        if self.address[0] != '?' :
            self.crate = int(self.address[0])
        if self.address[1] != '?' :
            self.board = int(self.address[1])
        if self.address[1] != '?' :
            self.channel = int(self.address[2])
        return

    def __eq__(self, other_) :
        if isinstance(other_, self.__class__):
            return self.crate == other_.crate and self.board == other_.board and self.channel == other_.channel
        return False
  
    def __ne__(self, other_) :
        return self.crate != other_.crate or self.board != other_.board or self.channel != other_.channel
 
    def __lt__(self, other_) :
        if self.crate < other_.crate :
            return True
        elif self.crate == other_.crate :
            if self.board < other_.board :
                return True
            elif self.board == other_.board :
                if self.channel < other_.channel :
                    return True
        return False
  
    def to_string(self):
        return "H:{:d}.{:d}.{:d}".format(self.crate, self.board, self.channel)
    
    def print_me(self, out_ = sys.stderr, title_ = "", indent_ = ""):
        if len(title_) :
            out_.write("{:s}{:s}\n".format(indent_, title_))
        out_.write("{:s}|-- Crate   = {:d}\n".format(indent_, self.crate))
        out_.write("{:s}|-- Board   = {:d}\n".format(indent_, self.board))
        out_.write("{:s}`-- Channel = {:d}\n".format(indent_, self.channel))
        return

class CaloHVInternalCableAddress :
    
    def __init__(self, label_):
        self.label = label_.strip()
        self.addrtype = self.label[0]
        if self.addrtype != "A" :
            raise Exception("Invalid CaloHV internal cable address '%s'!" % self.label)
        address = self.label.split(':')[1].strip()
        self.address = address.split('.')
        self.harness = 666
        self.cable   = 666
        if self.address[0] != '?' :
            self.harness = int(self.address[0])
        if self.address[1] != '?' :
            self.cable = int(self.address[1])
        return

    def __eq__(self, other_) :
        if isinstance(other_, self.__class__):
            return self.harness == other_.harness and self.cable == other_.cable
        return False
  
    def __ne__(self, other_) :
        return self.harness != other_.harness or self.cable != other_.cable
 
    def __lt__(self, other_) :
        if self.harness < other_.harness :
            return True
        elif self.harness == other_.harness :
            if self.cable < other_.cable :
                return True
        return False
  
    def to_string(self):
        return "A:{:d}.{:d}".format(self.harness, self.cable)
    
    def print_me(self, out_ = sys.stderr, title_ = "", indent_ = ""):
        if len(title_) :
            out_.write("{:s}{:s}\n".format(indent_, title_))
        out_.write("{:s}|-- Harness   = {:d}\n".format(indent_, self.harness))
        out_.write("{:s}`-- Cable = {:d}\n".format(indent_, self.cable))
        return

class CaloHVExternalHarnessAddress :
    
    def __init__(self, label_):
        self.label = label_.strip()
        self.addrtype = self.label[0]
        if self.addrtype != "E" :
            raise Exception("Invalid CaloHV external harness address '%s'!" % self.label)
        address = self.label.split(':')[1].strip()
        self.address = address.split('.')
        self.harness = 666
        if self.address[0] != '?' :
            self.harness = int(self.address[0])
        return

    def __eq__(self, other_) :
        if isinstance(other_, self.__class__):
            return self.harness == other_.harness
        return False
  
    def __ne__(self, other_) :
        return self.harness != other_.harness
 
    def __lt__(self, other_) :
        return self.harness < other_.harness
     
    def __le__(self, other_) :
        return self.harness <= other_.harness
   
    def to_string(self):
        return "E:{:d}".format(self.harness)
 
    def print_me(self, out_ = sys.stderr, title_ = "", indent_ = ""):
        if len(title_) :
            out_.write("{:s}{:s}\n".format(indent_, title_))
        out_.write("{:s}`-- Harness   = {:d}\n".format(indent_, self.harness))
        return

class CaloHVInternalHarnessAddress :
    
    def __init__(self, label_):
        self.label = label_.strip()
        self.addrtype = self.label[0]
        if self.addrtype != "I" :
            raise Exception("Invalid CaloHV internal harness address '%s'!" % self.label)
        address = self.label.split(':')[1].strip()
        self.address = address.split('.')
        self.harness = 666
        if self.address[0] != '?' :
            self.harness = int(self.address[0])
        return
 
    def __eq__(self, other_) :
        if isinstance(other_, self.__class__):
            return self.harness == other_.harness
        return False
  
    def __ne__(self, other_) :
        return self.harness != other_.harness
 
    def __lt__(self, other_) :
        return self.harness < other_.harness
     
    def __le__(self, other_) :
        return self.harness <= other_.harness
    
    def to_string(self):
        return "I:{:d}".format(self.harness)
 
    def print_me(self, out_ = sys.stderr, title_ = "", indent_ = ""):
        if len(title_) :
            out_.write("{:s}{:s}\n".format(indent_, title_))
        out_.write("{:s}`-- Harness   = {:d}\n".format(indent_, self.harness))
        return

# end
