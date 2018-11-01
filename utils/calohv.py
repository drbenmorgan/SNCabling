#!/usr/bin/env python3

import sys

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
