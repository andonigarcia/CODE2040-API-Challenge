# Andoni Garcia. 2014.
# My source code for Stage I: Reverse a String

from urllib.request import Request, urlopen
from json import dumps, loads
import timeit

token = "yicZ5DfAT6"
string = ""
revString = ""

def GetString():
	global token, string
	url = "http://challenge.code2040.org/api/getstring"
	values = {'token':token}
	JSONData = dumps(values).encode('utf-8')
	req = Request(url, data = JSONData, headers = {'content-type':'application/json'})
	resp = urlopen(req)
	string = loads(resp.read().decode('utf-8'))['result']
	print("Your string is: " + string)

def ReverseString1():
	global string, revString
	revString = string[::-1]
	print("The reversed string is: " + revString)

# MUCH SLOWER...but uses loops (I think the point of this exercise)
def ReverseString2():
	global string, revString
	strlen = len(string)
	for i in range(strlen):
		revString = revString[:] + string[strlen - 1 - i]
	print("The reversed string is: " + revString)

# More readable loop taking advantage of Python splice syntax. Slower still (not sure why)
def ReverseString3():
	global string, revString
	for i in range(len(string)):
		revString = string[i] + revString[:]
	print("The reversed string is: " + revString)

def PostString():
	global token, revString
	url = "http://challenge.code2040.org/api/validatestring"
	values = {'token':token,
			  'string':revString}
	JSONData = dumps(values).encode('utf-8')
	req = Request(url, data = JSONData, headers = {'content-type':'application/json'})
	resp = urlopen(req)
	result = loads(resp.read().decode('utf-8'))['result']
	print("Result: " + result)

# HIGHLY ADVISED TO COMMENT OUT PRINT STATEMENTS BEFORE EXECUTING TIMEFUNCS
def TimeFuncs():
	global revString
	GetString()
	print(str(timeit.timeit(ReverseString1, number = 30000)))
	revString = ""
	print(str(timeit.timeit(ReverseString2, number = 30000)))
	revString = ""
	print(str(timeit.timeit(ReverseString3, number = 30000)))

def StageI():
	GetString()
	ReverseString1()
	PostString()

StageI()