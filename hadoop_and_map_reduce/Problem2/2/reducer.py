#!/usr/bin/python

import sys

airportTotal = 0
oldKey = None

max_total = 0
Key = None

for line in sys.stdin:
    data_mapped = line.strip().split()
    if len(data_mapped) != 1:
        continue
    
    thisKey = data_mapped[0]

    if oldKey and oldKey != thisKey:
        if airportTotal > max_total:
            max_total = airportTotal
            Key = oldKey
        oldKey = thisKey
        airportTotal = 0

    oldKey = thisKey
    airportTotal += 1

if oldKey != None:
    if airportTotal > max_total:
        max_total = airportTotal
        Key = oldKey

#print "{0} {1}".format(Key, max_total)
print "{0}".format(Key)
