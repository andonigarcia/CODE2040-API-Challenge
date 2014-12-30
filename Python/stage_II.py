# Andoni Garcia. 2014.
# My source code for Stage I: Needle in a Haystack

from urllib.request import Request, urlopen
from json import dumps, loads

token = "yicZ5DfAT6"
response = None
index = None

def GetHaystack():
	global token, response
	url = "http://challenge.code2040.org/api/haystack"
	values = {'token':token}
	JSONData = dumps(values).encode('utf-8')
	req = Request(url, data = JSONData, headers = {'content-type':'application/json'})
	resp = urlopen(req)
	response = loads(resp.read().decode('utf-8'))['result']
	print("Your needle is: " + response['needle'])
	print("Your haystack is: " + str(response['haystack']))

def FindIndex1():
	global response, index
	try:
		index = response['haystack'].index(response['needle'])
	except ValueError as e:
		print("Error: Needle not in haystack")
		print(e.code())
	else:
		print("Needle is at position: " + str(index))

# Again, slower but uses loops (the point of the exercise)
def FindIndex2():
	global response, index
	needle = response['needle']
	haystack = response['haystack']
	for i in range(len(haystack)):
		if needle == haystack[i]:
			index = i
			print("Needle is at position: " + str(index))
			return
	print("Error: Needle is not in the haystack")

def PostIndex():
	global token, index
	url = "http://challenge.code2040.org/api/validateneedle"
	values = {'token':token,
			  'needle':index}
	JSONData = dumps(values).encode('utf-8')
	req = Request(url, data = JSONData, headers = {'content-type':'application/json'})
	resp = urlopen(req)
	result = loads(resp.read().decode('utf-8'))['result']
	print("Result: " + result)

def StageII():
	GetHaystack()
	FindIndex1()
	PostIndex()

StageII()