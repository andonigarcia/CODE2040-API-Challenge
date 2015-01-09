// Andoni Garcia. 2014.
// My source code for Stage I: Reverse a String

var token = "yicZ5DfAT6"; 
var xmlhttp = new XMLHttpRequest();
var response;
var revString = "";


function GetString(){
	var url = "http://challenge.code2040.org/api/getstring";
	var values = {"token":token};
	var JSONData = JSON.stringify(values);
	xmlhttp.onreadystatechange = function(){
		if(xmlhttp.readyState == 4 && xmlhttp.status == 200){
			response = JSON.parse(xmlhttp.responseText);
			console.log("Your string is: " + response.result);
		}
	}
	xmlhttp.open("POST", url, false);
	xmlhttp.setRequestHeader("content-type", "application/json");
	xmlhttp.send(JSONData);
}

// Reverse is so optimized that going from string to array and back is faster
function ReverseString1(){
	var string = response.result;
	var array = string.split("");
	var revArray = array.reverse();
	revString = array.join("");
	console.log("The reversed string is: " + revString);
}

// The traditional looping. Slower than above.
function ReverseString2(){
	var string = response.result;
	for (i = 0; i < string.length; i++){
		revString += string.charAt(string.length - 1 - i);
	}
	console.log("The reversed string is: " + revString);
}

function PostString(){
	var url = "http://challenge.code2040.org/api/validatestring";
	var values = {"token":token,
				  "string":revString};
	var JSONData = JSON.stringify(values);
	xmlhttp.onreadystatechange = function(){
		if(xmlhttp.readyState == 4 && xmlhttp.status == 200){
			var result = JSON.parse(xmlhttp.responseText);
			console.log("Result: " + result.result);
		}
	}
	xmlhttp.open("POST", url, false);
	xmlhttp.setRequestHeader("content-type", "application/json");
	xmlhttp.send(JSONData);
}

// HIGHLY ADVISED TO COMMENT OUT PRINT STATEMENTS BEFORE EXECUTING TIMEFUNCS
function TimeFuncs(){
	GetString();
	console.time('ReverseString1');
	ReverseString1();
	console.timeEnd('ReverseString1');
	console.time('ReverseString2');
	ReverseString2();
	console.timeEnd('ReverseString2');
}

function StageI(){
	GetString();
	ReverseString1();
	PostString();
}

StageI();