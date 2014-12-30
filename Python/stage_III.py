# Andoni Garcia. 2014.
# My source code for Stage III: Prefix

from urllib.request import Request, urlopen
from json import dumps, loads
import timeit

token = "yicZ5DfAT6"
response = None
newArray = []

def GetArray():
	global token, response
	url = "http://challenge.code2040.org/api/prefix"
	values = {'token':token}
	JSONData = dumps(values).encode('utf-8')
	req = Request(url, data = JSONData, headers = {'content-type':'application/json'})
	resp = urlopen(req)
	response = loads(resp.read().decode('utf-8'))['result']
	print("Your prefix is: " + response['prefix'])
	print("Your array is: " + str(response['array']))

# Surprisingly string splicing is the fastest
def FilterArray1():
	global response, newArray
	prefix = response['prefix']
	preflen = len(prefix)
	for var in response['array']:
		if prefix == var[:preflen]:
			continue
		else:
			newArray.append(var)
	print("Your filtered array is: " + str(newArray))

# Next fastest is using the optimized str function startswith
def FilterArray2():
	global response, newArray
	prefix = response['prefix']
	for var in response['array']:
		if var.startswith(prefix):
			continue
		else:
			newArray.append(var)
	print("Your filtered array is: " + str(newArray))

# Very similar idea as above, but without the optimized function
def FilterArray3():
	global response, newArray
	prefix = response['prefix']
	for var in response['array']:
		if var.find(prefix) == 0:
			continue
		else:
			newArray.append(var)
	print("Your filtered array is: " + str(newArray))

# Nastier way without using str functions (just list functions) - slowest
def FilterArray4():
	global response, newArray
	prefix = response['prefix']
	for var in response['array']:
		try:
			index = var.find(prefix)
			if index == 0:
				continue
			else:
				newArray.append(var)
		except:
			newArray.append(var)
	print("Your filtered array is: " + str(newArray))

def PostArray():
	global token, newArray
	url = "http://challenge.code2040.org/api/validateprefix"
	values = {'token':token,
			  'array':newArray}
	JSONData = dumps(values).encode('utf-8')
	req = Request(url, data = JSONData, headers = {'content-type':'application/json'})
	resp = urlopen(req)
	result = loads(resp.read().decode('utf-8'))['result']
	print("Result: " + result)

# HIGHLY ADVISED TO COMMENT OUT PRINT STATEMENTS BEFORE EXECUTING TIMEFUNCS
def TimeFuncs():
	global newArray
	GetArray()
	print(str(timeit.timeit(FilterArray1, number = 1000000)))
	newArray = []
	print(str(timeit.timeit(FilterArray2, number = 1000000)))
	newArray = []
	print(str(timeit.timeit(FilterArray3, number = 1000000)))
	newArray = []
	print(str(timeit.timeit(FilterArray4, number = 1000000)))

def StageIII():
	GetArray()
	FilterArray1()
	PostArray()

StageIII()