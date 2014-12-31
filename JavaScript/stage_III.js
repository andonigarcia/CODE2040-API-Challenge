// Andoni Garcia. 2014.
// My source code for Stage III: Prefix

var token = "yicZ5DfAT6"; 
var xmlhttp = new XMLHttpRequest();
var response;
var array = [];


function GetPrefix(){
	var url = "http://challenge.code2040.org/api/prefix";
	var values = {"token":token};
	var JSONData = JSON.stringify(values);
	xmlhttp.onreadystatechange = function(){
		if (xmlhttp.readyState == 4 && xmlhttp.status == 200){
			response = JSON.parse(xmlhttp.responseText).result;
			console.log("Your prefix is: " + response.prefix);
			console.log("Your array is: " + response.array);
		}
	}
	xmlhttp.open("POST", url, false);
	xmlhttp.setRequestHeader("content-type", "application/json");
	xmlhttp.send(JSONData);
}

function FilterArray(){
	var prefix = response.prefix;
	var arr = response.array;
	for (i = 0; i < arr.length; i++){
		if(arr[i].indexOf(prefix) !== 0){
			array.push(arr[i]);
		}
	}
	console.log("Your filtered array is: " + array);
}

function PostArray(){
	var url = "http://challenge.code2040.org/api/validateprefix";
	var values = {"token":token,
				  "array":array};
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
	GetPrefix();
	console.time('FilterArray');
	FilterArray();
	console.timeEnd('FilterArray');
}

function StageIII(){
	GetPrefix();
	FilterArray();
	PostArray();
}

StageIII();