#!/usr/bin/python
import numpy
import re
import os
import csv
from csv import reader
from matplotlib import pyplot
import sys
'''
def load_csv(filename):
    csv_reader = reader(open(filename, 'rt'))
    x = list(csv_reader)
    result = numpy.array(x).astype("int")
    col = result[:,0]
    result = numpy.delete(result, 0, 1)
    num_rows, num_cols = result.shape
    b = numpy.ones((num_rows,1))
    result = numpy.hstack((result,b))
    result = numpy.array(result).astype("int")
    return result, col
'''
def check(filename):
    with open(filename, 'r') as inF:
        count = 0
        for line in inF:
            if '<begin_table>' in line:
                count +=1
    return count

metadata = sys.argv[1]
#dataset_train = sys.argv[2]
#dataset_train = 'datasets/MNIST_data_updated/mnist_train.csv'
#dataset_train = 'datasets/MNIST_data_updated/a_train.csv'
#result , label = load_csv(dataset_train)
count = check(metadata)
#print (count)
#num_rows, num_cols = result.shape
