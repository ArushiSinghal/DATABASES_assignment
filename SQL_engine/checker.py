#!/usr/bin/python
#coding=utf-8
import numpy
import re
import os
import csv
from csv import reader
from matplotlib import pyplot
import sys
import sqlparse
import operator
import pyparsing
from pyparsing import *
from sqlparser_grammar import *

def checking (mynames, res):
    #################CHECK FOR TABLE NAMES###########################################################
    for i in range(len(res.tables)):
        count = 0
        for k in range(len(mynames)):
            if (mynames[k]== '<begin_table>') and (mynames[k+1] == res.tables[i]):
                count = 1
                break
        if count == 0:
            return 1
    #################CHECK FOR ATTRIBUTE NAMES###########################################################
    for i in range(len(res.columns)):
        count = 0
        if res.columns[i] != "*":
            for k in range(len(mynames)):
                if (mynames[k]== '<begin_table>'):
                    j = k+2
                    tablename = mynames[k+1]
                    while (j < len(mynames) -1) and (mynames[j+1] != '<begin_table>'):
                        if (res.columns[i].upper() == mynames[j].upper()) or (res.columns[i] == (tablename + "." + mynames[j])) or (res.columns[i] == (tablename + "." + mynames[j].upper())):
                            if (len(res.tables)) == 1 and res.tables[0] != tablename:
                                return 2
                            elif (len(res.tables) == 2) and (not(res.tables[0] == tablename or res.tables[1] == tablename)):
                                return 2
                            count = 1
                            break
                        else:
                            j +=1
                    if count == 1:
                        break
#################CHECK FOR WHERE NAMES###########################################################
    if len(res.where[0]) != 0:
        k1 = res.where[0][1][0]
        count = 0
        for k in range(len(mynames)):
            if (mynames[k]== '<begin_table>'):
                j = k+2
                tablename = mynames[k+1]
                while (j < len(mynames) -1) and (mynames[j+1] != '<begin_table>'):
                    if (k1.upper() == mynames[j].upper()) or (k1 == (tablename + "." + mynames[j])) or (k1 == (tablename + "." + mynames[j].upper())):
                        count = 1
                        break
                    else :
                        j += 1
                if count == 1:
                    break
        if count == 0:
            return 3
#################CHECK FOR WHERE NAMES###########################################################
    if len(res.where[0]) == 4:
        k3 = res.where[0][3][0]
        count = 0
        for k in range(len(mynames)):
            if (mynames[k]== '<begin_table>'):
                j = k+2
                tablename = mynames[k+1]
                while (j < len(mynames) -1) and (mynames[j+1] != '<begin_table>'):
                    if (k3.upper() == mynames[j].upper()) or (k3 == (tablename + "." + mynames[j])) or (k3 == (tablename + "." + mynames[j].upper())):
                            count = 1
                            break
                    else:
                        j +=1
                if count == 1:
                    break
        if count == 0:
            return 4
    return 0
