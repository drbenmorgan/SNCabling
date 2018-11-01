#!/usr/bin/env python3

import sys

class SuperNEMO:
    """SuperNEMO's constants"""
    
    invalid_id = -1
    side_italy = 0
    side_france = 1
    side_edelweiss = 0
    side_tunnel = 1
    wall_bottom = 0
    wall_top = 1

    @staticmethod
    def get_systems() :
        systems = {}
        systems["lis"]      = ("LIS",      "yellow")
        systems["calohv"]   = ("CaloHV",   "blue")
        systems["calosig"]  = ("CaloSig",  "green")
        systems["trackhv"]  = ("TrackHV",  "red")
        systems["tracksig"] = ("TrackSig", "orange")
        return systems

    
if __name__ == "__main__" :

    print("Side Italy      : {}".format(SuperNEMO.side_italy))
    print("Side France     : {}".format(SuperNEMO.side_france))
    print("Side Edelweiss  : {}".format(SuperNEMO.side_edelweiss))
    print("Side tunnel     : {}".format(SuperNEMO.side_tunnel))
    print("Wall bottom     : {}".format(SuperNEMO.wall_bottom))
    print("Wall top        : {}".format(SuperNEMO.wall_top))
    sys.exit(0)

# end
