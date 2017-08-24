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

def query_one_table(mynames, res1):
	tablename = res1.tables[0]
	array = []
        array1 = []
        array2 = []
	array_new = []
        array1_new = []
        array2_new = []
	for i in range(len(mynames)):
		if (tablename == mynames[i]) and (mynames[i-1]== '<begin_table>'):
			k = i +1
			while (k <= len(mynames) -2) and (mynames[k+1] != '<begin_table>'):
				array.append(mynames[k])
				array1.append(tablename + "." +  mynames[k])
				array2.append(k-i-1)
				k +=1
			array_new = array
        		array1_new = array1
			break
	filename1 = tablename +  ".csv"		
	csv_reader = reader(open(filename1, 'rt'))
        x = list(csv_reader)
        result = numpy.array(x)
	result = result.astype(int)
	num_rows, num_cols = result.shape
	array11 = []
	array11.append(array)
	result = numpy.append(array11, result, axis=0)
	result1 = result
	object1 = res1.columns[0]
        object2 = res1.columns[0]
	if len(res1.columns[0]) >= 4:
		object1 = res1.columns[0][:3].upper()
		object1 = object1 + "("
	if len(res1.columns[0]) >= 8:
		object2 = res1.columns[0][:7].upper()
                object2 = object1 + "("
	if (len(res1.tables) == 1 and len(res1.columns) == 1 and ((len(res1.columns[0]) >= 4 and (object1 == "MAX(" or object1 == "MIN(" or object1 == "SUM(")) or (len(res1.columns[0]) >= 8 and object2 == "AVERAGE("))):
		j = 0
		for i in range(len(res1.columns[0])):
			if res1.columns[0][i] == ")":
				j = i
				break
		l = 0
		for i in range(len(res1.columns[0])):
                        if res1.columns[0][i] == "(":
                                l = i
                                break
		m = i+1
		columnnameee = res1.columns[0][m:j]
		res1.columns[0] = columnnameee
	if (res1.columns[0] != "*"):
		length = len(res1.columns)
		l = 0
		for ll in range(len(array)):
			count = 0
			for k in range(length):
				if (res1.columns[k].upper() == array[ll].upper()) or (res1.columns[k].upper() == array1[ll].upper()):
					count = 1
					break
			if count == 0:
				result = numpy.delete(result, array2[ll]-l,1)
				array2[ll] -= l
				l += 1
	for i in range(len(mynames)):
                if (tablename == mynames[i]) and (mynames[i-1]== '<begin_table>'):
                        k = i +1
                        while (k <= len(mynames) -2) and (mynames[k+1] != '<begin_table>'):
                                array2_new.append(k-i-1)
                                k +=1
                        break
	if (len(res1.where[0]) == 2):
		j =0
		for i in range(len(array_new)):
			if (array_new[i] == res1.where[0][1][0]) or (array1_new[i] == res1.where[0][1][0]):
				k1 = array2_new[i]
		for i in range(len(array_new)):
                        if (array_new[i] == res1.where[0][1][2]) or (array1_new[i] == res1.where[0][1][2]):
				j = 1
                                k2 = array2_new[i]
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

	elif (len(res1.where[0]) == 4):
		j = 0 
		m = 0
		for i in range(len(array_new)):
			if (array_new[i] == res1.where[0][1][0]) or (array1_new[i] == res1.where[0][1][0]):
					k1 = array2_new[i]
					break
		for i in range(len(array_new)):
                        if (array_new[i] == res1.where[0][1][2]) or (array1_new[i] == res1.where[0][1][2]):
                                        k2 = array2_new[i]
					j = 1
					break
		for i in range(len(array_new)):
			if (array_new[i] == res1.where[0][3][0]) or (array1_new[i] == res1.where[0][3][0]):
					k3 = array2_new[i]
					break
		for i in range(len(array_new)):
                        if (array_new[i] == res1.where[0][3][2]) or (array1_new[i] == res1.where[0][3][2]):
                                        k4 = array2_new[i]
					m = 1
					break
		if (j ==1 and m ==1)and ((k1 == k2) or (k3 == k4)):
				print ("same attributes, condition. wrong")
		else:
			num_rows, num_cols = result1.shape
			i =1
			l = 0
			if (res1.where[0][2] == "and"):
				if (j == 1) and (m == 1):
					while i< num_rows:
						cdd = result1[i][k1]
						cddd = result1[i][k2]
						cdddd = result1[i][k3]
						cddddd = result1[i][k4]
						if not (ops_dictionary[res1.where[0][1][1]](cdd, cddd) and ops_dictionary[res1.where[0][1][1]](cdddd, cddddd)):
							result = numpy.delete(result, i - l,0)
							l += 1
						i +=1
				elif j !=1 and m!=1:
					a = float(res1.where[0][1][2])
					b = float(res1.where[0][3][2])
					while i< num_rows:
						cdd = float(result1[i][k1])
                                        	cddd = float(result1[i][k3])
                                                if not (ops_dictionary[res1.where[0][1][1]](cdd, a) and ops_dictionary[res1.where[0][3][1]](cddd, b)):
                                                        result = numpy.delete(result, i - l,0)
                                                        l += 1
                                                i +=1
				elif j == 1 and m!=1:
					b = float(res1.where[0][3][2])
                                        while i< num_rows:
						cdd = result1[i][k1]
                                                cdddd = result1[i][k2]
						cddd = float(result1[i][k3])
                                                if not (ops_dictionary[res1.where[0][1][1]](cdd, cdddd) and ops_dictionary[res1.where[0][1][1]](cddd, b)):
                                                        result = numpy.delete(result, i - l,0)
                                                        l += 1
                                                i +=1
                                elif j !=1 and m==1:
                                        a = float(res1.where[0][1][2])
                                        while i< num_rows:
						cdd = float(result1[i][k1])
						cddd = float(result1[i][k3])
						cddddd = result1[i][k4]
                                                if not (ops_dictionary[res1.where[0][1][1]](cdd, a) and ops_dictionary[res1.where[0][1][1]](cddd, cddddd)):
                                                        result = numpy.delete(result, i - l,0)
                                                        l += 1
                                                i +=1

			elif (res1.where[0][2] == "or"):
				if (j == 1) and (m == 1):
					while i< num_rows:
						cdd = result1[i][k1]
						cddd = result1[i][k2]
						cdddd = result1[i][k3]
						cddddd = result1[i][k4]
						if not (ops_dictionary[res1.where[0][1][1]](cdd, cddd) or ops_dictionary[res1.where[0][1][1]](cdddd, cddddd)):
							result = numpy.delete(result, i - l,0)
							l += 1
						i +=1
				elif j !=1 and m!=1:
					a = float(res1.where[0][1][2])
					b = float(res1.where[0][3][2])
					while i< num_rows:
						cdd = float(result1[i][k1])
                                        	cddd = float(result1[i][k3])
                                                if not (ops_dictionary[res1.where[0][1][1]](cdd, a) or ops_dictionary[res1.where[0][3][1]](cddd, b)):
                                                        result = numpy.delete(result, i - l,0)
                                                        l += 1
                                                i +=1
				elif j == 1 and m!=1:
					b = float(res1.where[0][3][2])
                                        while i< num_rows:
						cdd = result1[i][k1]
                                                cdddd = result1[i][k2]
						cddd = float(result1[i][k3])
                                                if not (ops_dictionary[res1.where[0][1][1]](cdd, cdddd) or ops_dictionary[res1.where[0][1][1]](cddd, b)):
                                                        result = numpy.delete(result, i - l,0)
                                                        l += 1
                                                i +=1
                                elif j !=1 and m==1:
                                        a = float(res1.where[0][1][2])
                                        while i< num_rows:
						cdd = float(result1[i][k1])
						cddd = float(result1[i][k3])
						cddddd = result1[i][k4]
                                                if not (ops_dictionary[res1.where[0][1][1]](cdd, a) or ops_dictionary[res1.where[0][1][1]](cddd, cddddd)):
                                                        result = numpy.delete(result, i - l,0)
                                                        l += 1
                                                i +=1	
			num_rows, num_cols = result.shape
                        if (num_rows == 1):
                                result = numpy.delete(result, 0,0)
	return result
