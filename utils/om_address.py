#!/usr/bin/env python3

import sys

class OMaddress :
    
    def __init__(self, label_):
        self.label = label_.strip()
        self.omtype = self.label[0]
        address = self.label.split(':')[1].strip()
        self.address = address.split('.')
        if self.omtype == "M" :
            self.side = 666
            self.column = 666
            self.row = 666
            if self.address[0] != '?' :
                self.side = int(self.address[0])
            if self.address[1] != '?' :
                self.column = int(self.address[1])
            if self.address[2] != '?' :
                self.row = int(self.address[2])
        if self.omtype == "X" :
            self.side = 666
            self.wall = 666
            self.column = 666
            self.row = 666
            if self.address[0] != '?' :
                self.side = int(self.address[0])
            if self.address[1] != '?' :
                self.wall = int(self.address[1])
            if self.address[2] != '?' :
                self.column = int(self.address[2])
            if self.address[3] != '?' :
                self.row = int(self.address[3])
        if self.omtype == "G" :
            self.side = 666
            self.wall = 666
            self.column = 666
            if self.address[0] != '?' :
                self.side = int(self.address[0])
            if self.address[1] != '?' :
                self.wall = int(self.address[1])
            if self.address[2] != '?' :
                self.column = int(self.address[2])
        if self.omtype == "R" :
            self.ref = 666
            if self.address[0] != '?' :
                self.ref = int(self.address[0])
        return
 
    def to_string(self):
        if self.omtype == "M" :
            return "M:{:d}.{:d}.{:d}".format(self.side, self.column, self.row)
        if self.omtype == "X" :
            return "X:{:d}.{:d}.{:d}.{:d}".format(self.side, self.wall, self.column, self.row)
        if self.omtype == "G" :
            return "G:{:d}.{:d}.{:d}".format(self.side, self.wall, self.column)
        if self.omtype == "R" :
            return "R:{:d}".format(self.ref)
        return ""
    
    def print_me(self, out_ = sys.stderr, title_ = "", indent_ = ""):
        if len(title_) :
            out_.write("{:s}{:s}\n".format(indent_, title_))
        out_.write("{:s}|-- Type   = '{:s}'\n".format(indent_, self.omtype))
        if self.omtype == "M" :
            out_.write("{:s}|-- Side   = {:d}\n".format(indent_, self.side))
            out_.write("{:s}|-- Column = {:d}\n".format(indent_, self.column))
            out_.write("{:s}`-- Row    = {:d}\n".format(indent_, self.row))
        if self.omtype == "X" :
            out_.write("{:s}|-- Side   = {:d}\n".format(indent_, self.side))
            out_.write("{:s}|-- Wall   = {:d}\n".format(indent_, self.wall))
            out_.write("{:s}|-- Column = {:d}\n".format(indent_, self.column))
            out_.write("{:s}`-- Row    = {:d}\n".format(indent_, self.row))
        if self.omtype == "G" :
            out_.write("{:s}|-- Side   = {:d}\n".format(indent_, self.side))
            out_.write("{:s}|-- Wall   = {:d}\n".format(indent_, self.wall))
            out_.write("{:s}`-- Column = {:d}\n".format(indent_, self.column))
        if self.omtype == "R" :
            out_.write("{:s}`-- Ref    = {:d}\n".format(indent_, self.ref))
        return

if __name__ == "__main__" :

    addr = OMaddress("M:1.14.8")
    addr.print_me(sys.stdout, "PMT:")
    sys.exit(0)

# end
