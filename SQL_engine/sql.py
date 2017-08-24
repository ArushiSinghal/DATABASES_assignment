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
from table_1 import *

def retrive_tables(filename, column, passing):
    csv_reader = reader(open(filename, 'rt'))
    x = list(csv_reader)
    result = numpy.array(x)
    col = result[:,column]
    col = numpy.hstack((passing,col))
    #col = numpy.append(column, col)
    return col

def store_metadata(filename):
    mynames = []
    with open(filename, 'r') as inF:
        count = 0
        j = 0
        mynames= inF.readlines()
        mynames = [x[:-1] for x in mynames]
	length = len(mynames)
	for l in range(length):
		mynames[l] = mynames[l][:-1]
	return mynames

def check_tablename(filename, mynames, tablename):
    with open(filename, 'r') as inF:
        j = 0
        for line in inF:
            j +=1
            if '<begin_table>' in line:
                if tablename == mynames[j]:
                    return 1
        return 0

def check_attributename(filename, mynames , tablename, attributename):
    with open(filename, 'r') as inF:
        j = 0
        for line in inF:
            j += 1
            if '<begin_table>' in line:
                if tablename == mynames[j]:
                    jj = j
                    x = 0
		    k = len(mynames)
                    while jj < (k -1):
                        a = attributename.upper()
                        b = mynames[jj+1].upper()
                        if a == b:
                            return 1, x
                        jj += 1
                        x = x + 1
        return 0, x

def main():
	while True:
        	sqlquery = raw_input("mysql>: ")
        	if (sqlquery == "exit" or sqlquery == "quit"):
            		sys.exit()
        	else:
            		sqlquery = sqlquery.rstrip()
            		sqlquery = sqlquery.lstrip()
            		sqlquery = ' '.join(sqlquery.split())
            		string = sqlquery[-1:]
            		tokens = filter(None, [str(x).strip() for x in sqlparse.parse(sqlquery)[0].tokens])
            		token = tokens[0]
            		aa = token.upper()
            		b = len(tokens)
            		if b <=3:
                		print ("wrong syntax. you have missed something in your query.")
            		elif (aa != "SELECT"):
                		print ("type 'select' query.")
            		elif (string != ';'):
                		print ("wrong syntax; no semicolon after query.")
            		else:
                		process (sqlquery)

def process(sqlquery):
    metadata = 'metadata.txt'
    res = selectStmt.parseString(sqlquery)
    tabless = res.tables
    columnss = res.columns
    wheree = res.where
    number_of_tables = len(tabless)
    number_of_columns = len(columnss)
    mynames = store_metadata(metadata)
    count = 0
    for i in range(number_of_tables):
        count = check_tablename(metadata, mynames, tabless[i])
        if count == 0:
            print ("wrong syntax, table doesnot exist. Please enter valid tablename")
            return
    if (count == 1) and (len(tabless) == 1):
	result = query_one_table(mynames, res)
	res = selectStmt.parseString(sqlquery)
	object1 = res.columns[0]
	object2 = res.columns[0]
	if len(res.columns[0]) >= 4:
                object1 = res.columns[0][:3].upper()
                object1 = object1 + "("
	if len(res.columns[0]) >= 8:
                object2 = res.columns[0][:7].upper()
                object2 = object2 + "("
	num_rows, num_cols = result.shape
        if (len(res.columns) == 1 and len(res.tables) == 1 and ((len(res.columns[0]) >= 4 and (object1 == "MAX(" or object1 == "MIN(" or object1 == "SUM(")) or (len(res.columns[0]) >= 8 and object2 == "AVERAGE(")) and num_rows > 1 and num_cols == 1):
		if (object1 == "MAX("):
			p = float(result[1][0])
			i =  2
			j = 2
			while i < num_rows:
				if p < float(result[i][0]):
					p = float(result[i][0])
					j = i
				i += 1
		if (object1 == "MIN("):
			p = float(result[1][0])
                        i =  2
                        j = 2
                        while i < num_rows:
                                if p > float(result[i][0]):
                                        p = float(result[i][0])
                                        j = i
				i += 1
		if (object1 == "SUM("):
			p = float(result[1][0])
			i = 2
			while i < num_rows:
				p = p + float(result[i][0])
				i +=1
		if (object2 == "AVERAGE("):
			p = float(result[1][0])
			i = 2
                        while i < num_rows:
                                p = p + float(result[i][0])
				i +=1
			p = p/(num_rows-1)
		i = num_rows -1
		while i > 1 :
			result = numpy.delete(result, i, axis=0)
			i -= 1
		result[0][0] = res.columns[0]
		result[1][0] = p
	else:
		for i in range(len(res.columns)):
                	if len(res.columns[i]) >= 9:
                        	object1 = res.columns[i][:8].upper()
                        	object1 = object1 + "("
                        	if (object1 == "DISTINCT("):
                                	j = 0
                                	for k in range(len(res.columns[i])):
                                        	if res.columns[i][k] == ")":
                                                	j = k
                                                	break
                                	l = 0
                                	for k in range(len(res.columns[i])):
                                        	if res.columns[i][k] == "(":
                                                	l = k
                                                	break
                                	m = l + 1
                                	cole = res.columns[i][m:j]
					num_rows, num_cols = result.shape
                                	for k in range(num_cols):
						if result[0][k] == cole:
							n = 1
							while n < num_rows:
								jj = n+1
								while jj < num_rows:
									if (result[n][k] == result[jj][k]):
										result = numpy.delete(result, jj, axis=0)
										num_rows, num_cols = result.shape
									else:
										jj += 1
								num_rows, num_cols = result.shape
								n +=1
	print (result)
    elif count == 1:
        for j in range(number_of_columns):
            for i in range(number_of_tables):
		result, cordinate = check_attributename(metadata, mynames, tabless[i], columnss[j])
		if result == 0:
			print ("Attribute doesnot exist. Please enter valid tablename")
			break
	    if result == 0:
		break
        if result == 1:
            tablefilename = tablename +  ".csv"
            tablename_change = tablename + "."
            passing = tablename_change + attributename
            col = retrive_tables(tablefilename, cordinate, passing)
            print (col)
        else:
            print ("column which you want to find does not exists. check syntax")

if __name__ == "__main__":
	main()
