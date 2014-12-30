# Andoni Garcia. 2014.
# My source code for the Registration Phase.
# Written in Python, because it is my newest language and I like challenges.
# JK (kinda), I have the most experience with URL requests with Python, because
# of my new project: https://github.com/andonigarcia/OHHLA-WebScraper

from urllib.request import Request, urlopen
from json import dumps, loads

token = ""

def Register():
	global token
	url = "http://challenge.code2040.org/api/register"
	values = {'email':'andoni@uchicago.edu', 
				'github':'https://github.com/andonigarcia/CODE2040-API-Challenge'}
	JSONData = dumps(values).encode('utf-8')
	req = Request(url, data = JSONData, headers = {'content-type':'application/json'})
	resp = urlopen(req)
	token = loads(resp.read().decode('utf-8'))
	print("Your token is: " + token['result'])

Register();