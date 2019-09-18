#!/usr/bin/env python3

import sys

class GeigerCellAdress :
    
    def __init__(self, label_):
        self.label = label_.strip()
        objid = self.label[0]
        if objid != "G" :
            raise Exception("Not a Geiger cell label '{:s}'!".format(label_))
        address = self.label.split(':')[1].strip()
        self.address = address.split('.')
        self.side   = -1
        self.layer = -1
        self.row    = -1
        if self.address[0] != '?' :
            self.side = int(self.address[0])
        if self.address[1] != '?' :
            self.layer = int(self.address[1])
        if self.address[2] != '?' :
            self.row = int(self.address[2])
        return 

    def to_string(self):
        return "G:{:d}.{:d}.{:d}".format(self.side, self.column, self.row)
    
    def print_me(self, out_ = sys.stderr, title_ = "", indent_ = ""):
        if len(title_) :
            out_.write("{:s}{:s}\n".format(indent_, title_))
        out_.write("{:s}|-- Side  = {:d}\n".format(indent_, self.side))
        out_.write("{:s}|-- Layer = {:d}\n".format(indent_, self.layer))
        out_.write("{:s}`-- Row   = {:d}\n".format(indent_, self.row))
        return
    
if __name__ == "__main__" :

    addr = GeigerCellAdress("G:1.43.0")
    addr.print_me(sys.stdout, "Geiger cell:")
    sys.exit(0)

# end
