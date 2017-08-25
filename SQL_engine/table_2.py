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

ops_dictionary = {'<': operator.lt, '<=': operator.le, '=':operator.eq, '>=':operator.ge, '>':operator.gt}

def query_two_table(mynames, res1):
	array = []
        array1 = []
        array2 = []
        array20 = []
        array21 = []
        array22 = []
	result = []
	result1 = []
	result2 = []

######################################################################################################################
	
	tablename = res1.tables[0]
        for i in range(len(mynames)):
        	if (tablename == mynames[i]) and (mynames[i-1]== '<begin_table>'):
                	k = i +1
                        while (k <= len(mynames) -2) and (mynames[k+1] != '<begin_table>'):
                        	array.append(mynames[k])
                                array1.append(tablename + "." +  mynames[k])
                                array2.append(k-i-1)
                                k +=1
                        break
	tablename = res1.tables[1]
        for i in range(len(mynames)):
                if (tablename == mynames[i]) and (mynames[i-1]== '<begin_table>'):
                        k = i +1
                        while (k <= len(mynames) -2) and (mynames[k+1] != '<begin_table>'):
                                array20.append(mynames[k])
                                array21.append(tablename + "." +  mynames[k])
                                array22.append(k-i-1)
                                k +=1
                        break
####################################################################################################################

	filename1 = res1.tables[0] +  ".csv"
	csv_reader = reader(open(filename1, 'rt'))
	for row in csv_reader:
		result1.append(row)
	arra = array1 + array21
	arr = []
        arr.append(arra)
        filename2 = res1.tables[1] +  ".csv"
        csv_reader = reader(open(filename2, 'rt'))
	for row in csv_reader:
                result2.append(row)
	for row in result1:
		for row1 in result2:
			result.append(row + row1)
	result = numpy.array(result)
	result = numpy.append(arr, result, axis=0)	
	result1 = result
	num_rows, num_cols = result.shape

#####################################################################################################################

	if (res1.columns[0] == "*") and (len(res1.where[0]) == 2):
		for m in range(len(res1.tables)):
                        for l in range(len(array[m])):
                                        if ((res1.where[0][1][0].upper() == array[m][l].upper()) or (res1.where[0][1][0] == array1[m][l])):
                                                res1.where[0][1][0] = array1[m][l]
		for m in range(len(res1.tables)):
                        for l in range(len(array[m])):
                                        if ((res1.where[0][1][2].upper() == array[m][l].upper()) or (res1.where[0][1][2] == array1[m][l])):
                                                res1.where[0][1][2] = array1[m][l]
		num_rows, num_cols = result1.shape
		for m in range(num_cols):
			if (result1[0][m] == res1.where[0][1][0]):
				k1 = m
				break
		j = 0
		for m in range(num_cols):
                        if (result1[0][m] == res1.where[0][1][2]):
				j = 1
                                k2 = m
                                break
		if j == 1:
                        num_rows, num_cols = result1.shape
                        i =1
                        l = 0
                        while i< num_rows:
                                cdd = float(result1[i][k1])
                                cddd = float(result1[i][k2])
                                if not (ops_dictionary[res1.where[0][1][1]](cdd, cddd)):
                                        result = numpy.delete(result, i - l,0)
                                        l += 1
                                i += 1
                elif j!=1:
                        num_rows, num_cols = result1.shape
                        i =1
                        l = 0
                        a = float(res1.where[0][1][2])
                        while i< num_rows:
                                cdd = float(result1[i][k1])
                                if not (ops_dictionary[res1.where[0][1][1]](cdd, a)):
                                        result = numpy.delete(result, i - l,0)
                                        l += 1
                                i += 1
                num_rows, num_cols = result.shape
                if (num_rows == 1):
                        result = numpy.delete(result, 0,0)
	elif (res1.columns[0] != "*") and (len(res1.where[0]) == 0):
		l = 0
		m = 0
		while m < num_cols:
			count = 0
			for k in range(len(res1.columns)):
				string1 = res1.tables[0] + "." + res1.columns[k]
				string2 = res1.tables[1] + "." + res1.columns[k]
				if ((res1.columns[k] == result[0][m]) or (string1 == result[0][m]) or (string2  == result[0][m])):
					count = 1
					m +=1
					break
			if count == 0:
				result = numpy.delete(result, m,1)
				num_rows, num_cols = result.shape
		num_rows, num_cols = result.shape
                if (num_rows == 1):
                        result = numpy.delete(result, 0,0)
	elif (res1.columns[0] != "*") and (len(res1.where[0]) == 2):
		l = 0
		m = 0
		while m < num_cols:
			count = 0
			for k in range(len(res1.columns)):
				if ((res1.columns[k] == result[0][m]) or (res1.tables[0]+"." + res1.columns[k] == result[0][m]) or (res1.tables[1]+"." + res1.columns[k] == result[0][m])):
					count = 1
					break
			if count == 0:	
				result = numpy.delete(result, m - l,1)
				num_rows, num_cols = result.shape
				l = l+1
			else:
				m += 1
		for m in range(len(res1.tables)):
                        for l in range(len(array[m])):
                                        if ((res1.where[0][1][0].upper() == array[m][l].upper()) or (res1.where[0][1][0] == array1[m][l])):
                                                res1.where[0][1][0] = array1[m][l]
		for m in range(len(res1.tables)):
                        for l in range(len(array[m])):
                                        if ((res1.where[0][1][2].upper() == array[m][l].upper()) or (res1.where[0][1][2] == array1[m][l])):
                                                res1.where[0][1][2] = array1[m][l]
		
		for m in range(num_cols):
			if (result1[0][m] == res1.where[0][1][0]):
				k1 = m
				break
		j = 0
		for m in range(num_cols):
                        if (result1[0][m] == res1.where[0][1][2]):
				j = 1
                                k2 = m
                                break
		if j == 1:
                        num_rows, num_cols = result1.shape
                        i =1
                        l = 0
                        while i< num_rows:
                                cdd = float(result1[i][k1])
                                cddd = float(result1[i][k2])
                                if not (ops_dictionary[res1.where[0][1][1]](cdd, cddd)):
                                        result = numpy.delete(result, i - l,0)
                                        l += 1
                                i += 1
                elif j!=1:
                        num_rows, num_cols = result1.shape
                        i =1
                        l = 0
                        a = float(res1.where[0][1][2])
                        while i< num_rows:
                                cdd = float(result1[i][k1])
                                if not (ops_dictionary[res1.where[0][1][1]](cdd, a)):
                                        result = numpy.delete(result, i - l,0)
                                        l += 1
                                i += 1
                num_rows, num_cols = result.shape
                if (num_rows == 1):
                        result = numpy.delete(result, 0,0)
	return result
