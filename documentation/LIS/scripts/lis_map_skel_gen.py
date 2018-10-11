#!/usr/bin/env python3

import sys

class LISCablingMapSkelGen:
    """LIS Cabling Map Skeleton Generator """

    def __init__(self, csvfile_):
        self._fcsv_ = open(csvfile_, "w")
        return

    def _run_calo(self):
        sys.stderr.write("[info] Processing main wall OMs...\n")
        for ps in range(2):
            prefix = "P"
            if ps == 1:
                prefix = "S"
            sys.stderr.write("prefix={:s}\n".format(prefix))
            for side in range(2) :
                sys.stderr.write("side={:d}\n".format(side))
                for column in range(20):
                    sys.stderr.write("column={:d}\n".format(column))
                    for row in range(13):
                        sys.stderr.write("column={:d}\n".format(row))
                        self._fcsv_.write("{:s}:?.? ; M:{:d}.{:d}.{:d} \n".format(prefix, side, column, row))
                   
        return
 
    def _run_xcalo(self):
        sys.stderr.write("[info] Processing X-wall OMs...\n")
        for ps in range(2):
            prefix = "P"
            if ps == 1:
                prefix = "S"
            sys.stderr.write("prefix={:s}\n".format(prefix))
            for side in range(2) :
                sys.stderr.write("side={:d}\n".format(side))
                for wall in range(2):
                    sys.stderr.write("wall={:d}\n".format(wall))
                    for column in range(2):
                        sys.stderr.write("column={:d}\n".format(column))
                        for row in range(16):
                            sys.stderr.write("column={:d}\n".format(row))
                            self._fcsv_.write("{:s}:?.? ; X:{:d}.{:d}.{:d}.{:d} \n".format(prefix, side, wall, column, row))
                   
        return
 
    def _run_gveto(self):
        sys.stderr.write("[info] Processing gamma veto OMs...\n")
        for ps in range(2):
            prefix = "P"
            if ps == 1:
                prefix = "S"
                sys.stderr.write("prefix={:s}\n".format(prefix))
            for side in range(2) :
                sys.stderr.write("side={:d}\n".format(side))
                for wall in range(2):
                    sys.stderr.write("wall={:d}\n".format(wall))
                    for column in range(16):
                        sys.stderr.write("column={:d}\n".format(column))
                        self._fcsv_.write("{:s}:?.? ; G:{:d}.{:d}.{:d} \n".format(prefix, side, wall, column))
 
    def _run_ref_om(self):
        sys.stderr.write("[info] Processing reference OMs...\n")
        for ps in range(2):
            prefix = "P"
            if ps == 1:
                prefix = "S"
            sys.stderr.write("prefix={:s}\n".format(prefix))
            for ref_om in range(4):
                sys.stderr.write("ref={:d}\n".format(ref_om))
                self._fcsv_.write("{:s}:?.? ; R:{:d} \n".format(prefix, ref_om))

    def run(self):
        self._run_calo()
        self._run_xcalo()
        self._run_gveto()
        self._run_ref_om()
        return

    
if __name__ == "__main__" :
    gm = LISCablingMapSkelGen("lis_mapping-skel.csv")
    error_code = gm.run()
    sys.exit(error_code)

# end
