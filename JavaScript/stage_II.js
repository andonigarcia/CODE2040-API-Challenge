// Andoni Garcia. 2014.
// My source code for Stage II: Needle in a Haystack

var token = "yicZ5DfAT6"; 
var xmlhttp = new XMLHttpRequest();
var response;
var index;


function GetHaystack(){
	var url = "http://challenge.code2040.org/api/haystack";
	var values = {"token":token};
	var JSONData = JSON.stringify(values);
	xmlhttp.onreadystatechange = function(){
		if (xmlhttp.readyState == 4 && xmlhttp.status == 200){
			response = JSON.parse(xmlhttp.responseText).result;
			console.log("Your needle is: " + response.needle);
			console.log("Your haystack is: " + response.haystack);
		}
	}
	xmlhttp.open("POST", url, false);
	xmlhttp.setRequestHeader("content-type", "application/json");
	xmlhttp.send(JSONData);
}

function FindIndex1(){
	var needle = response.needle;
	var haystack = response.haystack;
	index = haystack.indexOf(needle);
	console.log("The needle is at index: " + index);
}

function FindIndex2(){
	var needle = response.needle;
	var haystack = response.haystack;
	for (i = 0; i < haystack.length; i++){
		if (needle === haystack[i]){
			index = i;
			console.log("The needle is at index: " + index);
			return;
		}
	}
}

function PostIndex(){
	var url = "http://challenge.code2040.org/api/validateneedle";
	var values = {"token":token,
				  "needle":index};
	var JSONData = JSON.stringify(values);
	xmlhttp.onreadystatechange = function(){
		if (xmlhttp.readyState == 4 && xmlhttp.status == 200){
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
	GetHaystack();
	console.time('FindIndex1');
	FindIndex1();
	console.timeEnd('FindIndex1');
	console.time('FindIndex2');
	FindIndex2();
	console.timeEnd('FindIndex2');
}


function StageII(){
	GetHaystack();
	FindIndex1();
	PostIndex();
}

StageII();