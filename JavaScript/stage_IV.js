// Andoni Garcia. 2014.
// My source code for Stage IV: The Dating Game

var token = "yicZ5DfAT6"; 
var xmlhttp = new XMLHttpRequest();
var response;
var newTime;


function GetTime(){
	var url = "http://challenge.code2040.org/api/time";
	var values = {"token":token};
	var JSONData = JSON.stringify(values);
	xmlhttp.onreadystatechange = function(){
		if (xmlhttp.readyState == 4 && xmlhttp.status == 200){
			response = JSON.parse(xmlhttp.responseText).result;
			console.log("Your interval is: " + response.interval);
			console.log("Your datestamp is: " + response.datestamp);
		}
	}
	xmlhttp.open("POST", url, false);
	xmlhttp.setRequestHeader("content-type", "application/json");
	xmlhttp.send(JSONData);
}

function AddTime(){
	var interval = response.interval;
	var datestamp = response.datestamp;
	var date = new Date(datestamp);
	var ms = date.getTime() + (interval * 1000);
	newTime = new Date(ms).toISOString();
	console.log("New datestamps is: " + newTime);
}

function PostTime(){
	var url = "http://challenge.code2040.org/api/validatetime";
	var values = {"token":token,
				  "datestamp":newTime};
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
	GetTime();
	console.time('AddTime');
	AddTime();
	console.timeEnd('AddTime');
}

function StageIV(){
	GetTime();
	AddTime();
	PostTime();
}

StageIV();