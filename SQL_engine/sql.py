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
import pyparsing
from pyparsing import *

selectStmt = Forward()
SELECT = Keyword("select", caseless=True)
FROM = Keyword("from", caseless=True)
WHERE = Keyword("where", caseless=True)

ident          = Word( alphas, alphanums + "_$" ).setName("identifier")
columnName     = ( delimitedList( ident, ".", combine=True ) ).setName("column name").addParseAction(upcaseTokens)
columnNameList = Group( delimitedList( columnName ) )
tableName      = ( delimitedList( ident, ".", combine=True ) ).setName("table name").addParseAction(upcaseTokens)
tableNameList  = Group( delimitedList( tableName ) )

whereExpression = Forward()
and_ = Keyword("and", caseless=True)
or_ = Keyword("or", caseless=True)
in_ = Keyword("in", caseless=True)

E = CaselessLiteral("E")
binop = oneOf("= != < > >= <= eq ne lt le gt ge", caseless=True)
arithSign = Word("+-",exact=1)
intNum = Combine( Optional(arithSign) + Word( nums ) + 
            Optional( E + Optional("+") + Word(nums) ) )
intNum = Combine( Optional(arithSign) + Word( nums ) + 
            Optional( E + Optional("+") + Word(nums) ) )

columnRval = intNum | quotedString | columnName # need to add support for alg expressions
whereCondition = Group(
    ( columnName + binop + columnRval ) |
    ( columnName + in_ + "(" + delimitedList( columnRval ) + ")" ) |
    ( columnName + in_ + "(" + selectStmt + ")" ) |
    ( "(" + whereExpression + ")" )
    )
whereExpression << whereCondition + ZeroOrMore( ( and_ | or_ ) + whereExpression ) 

# define the grammar
selectStmt <<= (SELECT + ('*' | columnNameList)("columns") + 
                FROM + tableNameList( "tables" ) + 
                Optional(Group(WHERE + whereExpression), "")("where"))

simpleSQL = selectStmt

def retrive_tables(filename, column, passing):
    csv_reader = reader(open(filename, 'rt'))
    x = list(csv_reader)
    result = numpy.array(x)
    col = result[:,column]
    col = numpy.hstack((passing,col))
    #col = numpy.append(column, col)
    return col

def check_tablename(filename):
    mynames = []
    with open(filename, 'r') as inF:
        count = 0
        j = 0
        mynames= inF.readlines()
        mynames = [x[:-1] for x in mynames]
    return mynames

def check_tablename1(filename, mynames, tablename):
    with open(filename, 'r') as inF:
        count = 0
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
                    while True:
                        a = attributename.upper()
                        b = mynames[jj+1].upper()
                        if a == b:
                            return 1, x;
                        elif '<end_table>' == mynames[jj+1]:
                            break;
                        jj += 1
                        x = x + 1
        return 0, x

def main():
    while True:
        sqlquery = input("mysql>: ")
        if (sqlquery == "exit" or sqlquery == "quit"):
            sys.exit()
        else:
            string = sqlquery.rstrip()
            string = string[-1:]
            if (string != ';'):
                print ("wrong syntax; no semicolon after query.")
            else:
                process (sqlquery)

def process(sqlquery):
    metadata = 'metadata.txt'
    res = sqlparse.split(sqlquery)
    length = len(res)
    res1 = selectStmt.parseString(sqlquery)
    print (res1)
    print (res1.tables)
    print ("dsl;dkla;sdk")
    print (res1.columns)
    print ("dsl;dkla;sdk")
    print (res1.where)
    mynames = check_tablename(metadata)
    tablename = 'table1'
    attributename = 'A'
    result = 0
    count = check_tablename1(metadata, mynames, tablename)
    if count == 1:
        result, cordinate = check_attributename(metadata, mynames, tablename, attributename)
        if result == 1:
            tablefilename = tablename +  ".csv"
            tablename_change = tablename + "."
            passing = tablename_change + attributename
            col = retrive_tables(tablefilename, cordinate, passing)
            print (col)
        else:
            print ("column which you want to find does not exists. check syntax")
    else:
        print ("table doesnot exist. please check your tablename. check syntax")
    print (count)
    print (result)
    print (tablefilename)

if __name__ == "__main__":
        main()
