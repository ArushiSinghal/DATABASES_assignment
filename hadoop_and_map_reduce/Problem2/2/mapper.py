#!/usr/bin/python

import sys
import csv
import StringIO

no_lines = 0

for line in sys.stdin:

    s = StringIO.StringIO(line)
    a = list(csv.reader(s, skipinitialspace=True))
    line = a[0]

    if no_lines == 0:
        no_lines = 1
        continue

    data = line

    if len(data) == 7:
        Id, Type, Name, Lat, Long, Country, Region = data
        print "{0}".format(Type)
