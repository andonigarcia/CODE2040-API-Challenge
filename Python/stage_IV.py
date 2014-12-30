# Andoni Garcia. 2014.
# My source code for Stage IV: The Dating Game

from urllib.request import Request, urlopen
from json import dumps, loads
import time
import datetime

token = "yicZ5DfAT6"
response = None
newTime = None

def GetTime():
	global token, response
	url = "http://challenge.code2040.org/api/time"
	values = {'token':token}
	JSONData = dumps(values).encode('utf-8')
	req = Request(url, data = JSONData, headers = {'content-type':'application/json'})
	resp = urlopen(req)
	response = loads(resp.read().decode('utf-8'))['result']
	print("Your interval is: " + str(response['interval']))
	print("Your datestamp is: " + response['datestamp'])

# I could not think of any other way to go about it
def AddTime():
	global response, newTime
	toDateTime = datetime.datetime(*(time.strptime(response['datestamp'], "%Y-%m-%dT%H:%M:%S.%fZ")[0:6]))
	newTime = toDateTime + datetime.timedelta(0, response['interval'])
	print("Your new time is: " + newTime.isoformat(sep="T")+'.000Z')

def PostTime():
	global token, newTime
	url = "http://challenge.code2040.org/api/validatetime"
	values = {'token':token,
			  'datestamp':(newTime.isoformat(sep="T")+'.000Z')}
	JSONData = dumps(values).encode('utf-8')
	req = Request(url, data = JSONData, headers = {'content-type':'application/json'})
	resp = urlopen(req)
	result = loads(resp.read().decode('utf-8'))['result']
	print("Result: " + result)

def StageIV():
	GetTime()
	AddTime()
	PostTime()

StageIV()