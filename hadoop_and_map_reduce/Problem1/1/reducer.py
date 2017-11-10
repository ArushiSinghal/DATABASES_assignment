#!/usr/bin/python

import sys

airportTotal = 0
oldKey = None

for line in sys.stdin:
    data_mapped = line.strip().split()
    if len(data_mapped) != 1:
        continue
    
    thisKey = data_mapped[0]

    if oldKey and oldKey != thisKey:
        print oldKey, "\t", airportTotal
        oldKey = thisKey
        airportTotal = 0

    oldKey = thisKey
    airportTotal += 1

if oldKey != None:
    print oldKey, "\t", airportTotal

