// Andoni Garcia. 2014.
// My source code for the Registration Phase.

var token; 
var xmlhttp = new XMLHttpRequest();

function Register(){
	var url = "http://challenge.code2040.org/api/register";
	var values = {"email":"andoni@uchicago.edu", 
			 	  "github":"https://github.com/andonigarcia/CODE2040-API-Challenge"};
	var JSONData = JSON.stringify(values);
	xmlhttp.onreadystatechange = function(){
		if(xmlhttp.readyState == 4 && xmlhttp.status == 200){
			token = JSON.parse(xmlhttp.responseText);
			console.log("Your token is: " + token.result);
		}
	}
	xmlhttp.open("POST", url, true);
	xmlhttp.setRequestHeader("content-type", "application/json");
	xmlhttp.send(JSONData);
}

Register();