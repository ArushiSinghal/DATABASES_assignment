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
columnName     = ( delimitedList( ident, ".", combine=True ) ).setName("column name")
columnNameList = Group( delimitedList( columnName ) )
tableName      = ( delimitedList( ident, ".", combine=True ) ).setName("table name")
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
        sqlquery = raw_input("mysql>: ")
        print (type(sqlquery))
        if (sqlquery == "exit" or sqlquery == "quit"):
            sys.exit()
        else:
            sqlquery = sqlquery.rstrip()
            sqlquery = sqlquery.lstrip()
            sqlquery = ' '.join(sqlquery.split())
            string = sqlquery[-1:]
            tokens = filter(None, [str(x).strip() for x in sqlparse.parse(sqlquery)[0].tokens])
            tokens = tokens[0]
            aa = tokens.upper()
            b = len(tokens)
            if b <=3:
                print ("wrong syntax.")
            elif (aa != "SELECT"):
                print ("type select query.")
            elif (string != ';'):
                print ("wrong syntax; no semicolon after query.")
            else:
                process (sqlquery)

def process(sqlquery):
    metadata = 'metadata.txt'
    '''
    res = sqlparse.parse(sqlquery)
    stmt = res[0]
    res= stmt.tokens
    print (res)
    '''
    res1 = selectStmt.parseString(sqlquery)
    tabless = res1.tables
    columnss = res1.columns
    number_of_tables = len(tabless)
    number_of_columns = len(columnss)
    mynames = check_tablename(metadata)
    '''
    print (number_of_tables)
    print (res1)
    print (res1.tables)
    print (res1.columns)
    print (res1.where)
    tablename = 'table1'
    attributename = 'A'
    result = 0
    count = check_tablename1(metadata, mynames, tablename)
    '''
    count = 0
    for i in range(number_of_tables):
        count = check_tablename1(metadata, mynames, tabless[i])
        if count == 0:
            print ("wrong syntax, table doesnot exist.")
            break;

    if count == 1:
        for j in range(number_of_columns):
            for i in range(number_of_tables):
                result, cordinate = check_attributename(metadata, mynames, tabless[i], columnss[j])
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
