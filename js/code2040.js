// Andoni Garcia. 2015.
// CODE2040 API Challenge

var token;
var getMessage;
var stages = {"register":0, "stageI":0, "stageII":0, "stageIII":0, "stageIV":0};
var port = 80;
var domain = "http://challenge.code2040.org/api/";

// Functions

function CODE2040Post(page, message){
    var url = domain + page;
    return $.post(url, message, "json");
}

function GetMessage(token){
    var values = {"token":token};
    getMessage = JSON.stringify(values);
}

function Register(){
    if (stages.register === 1){
        var resp = "Sorry, you've already registered!";
        $(".ioresponse p").empty().append(resp);
    } else {
        var url = domain + "register";
        var values = {"email":"andoni@uchicago.edu",
                      "github":"https://github.com/andonigarcia/CODE2040-API-Challenge"};
        var JSONData = JSON.stringify(values);
        $.when(CODE2040Post("register", JSONData)).then(function(data){
            token = data.result;
            var output = "Your token is: " + token;
            $(".ioresponse p").empty().append(output);
            GetMessage(token);
            stages.register = 1; 
        });
    }
}

function StageI(){
    var string;
    var p = $(".ioresponse p");
    if(stages.register === 0){
        var resp = "You need to register first!";
        p.empty.append(resp);
        return;
    } else if(stages.stageI === 1){
        var resp = "You've already completed this stage!";
        p.empty().append(resp);
        return;
    } else {
        // Get String
        $.when(CODE2040Post("getstring", getMessage)).then(function(data){
            string = data.result;
            var output = "Your string is: " + string;
            p.empty().append(output);
            string = string.split("").reverse().join("");
            var output2 = "The reversed string is: " + string;
            p.append("<br />" + output2);
            
            var values = {"token":token, "string":string};
            var JSONData = JSON.stringify(values);
            $.when(CODE2040Post("validatestring", JSONData)).then(function(data){
                var res = data.result;
                var output = "The result: " + res;
                p.append("<br />" + output);
                stages.stageI = 1;
            });
        });
    }
}

function StageII(){
    var needle, haystack, index = -1;
    var p = $(".ioresponse p");
    if(stages.register === 0){
        var resp = "You need to register first!";
        p.empty.append(resp);
        return;
    } else if(stages.stageII === 1){
        var resp = "You've already completed this stage!";
        p.empty().append(resp);
        return;
    } else {
        // Get String
        $.when(CODE2040Post("haystack", getMessage)).then(function(data){
            needle = data.result.needle;
            haystack = data.result.haystack;
            var output = "Your needle is: " + needle;
            var output2 = "<br />Your haystack is: " + haystack;
            p.empty().append(output + output2);
            index = haystack.indexOf(needle);
            var output3 = "<br />Your needle is at index: " + index;
            p.append(output3);
            
            var values = {"token":token, "needle":index};
            var JSONData = JSON.stringify(values);
            $.when(CODE2040Post("validateneedle", JSONData)).then(function(data){
                var res = data.result;
                var output = "The result: " + res;
                p.append("<br />" + output);
                stages.stageII = 1;
            });
        });
    }
}

function StageIII(){
    var prefix, array, farr=[];
    var p = $(".ioresponse p");
    if(stages.register === 0){
        var resp = "You need to register first!";
        p.empty.append(resp);
        return;
    } else if(stages.stageIII === 1){
        var resp = "You've already completed this stage!";
        p.empty().append(resp);
        return;
    } else {
        // Get String
        $.when(CODE2040Post("prefix", getMessage)).then(function(data){
            prefix = data.result.prefix;
            array = data.result.array;
            var output = "Your prefix is: " + prefix;
            var output2 = "<br />Your array is: " + array;
            p.empty().append(output + output2);
            for (var i = 0; i < array.length; i++){
		if(array[i].indexOf(prefix) !== 0){
			farr.push(array[i]);
		}
            }
            var output3 = "<br />Your filtered array is: " + farr;
            p.append(output3);
            
            var values = {"token":token, "array":farr};
            var JSONData = JSON.stringify(values);
            $.when(CODE2040Post("validateprefix", JSONData)).then(function(data){
                var res = data.result;
                var output = "The result: " + res;
                p.append("<br />" + output);
                stages.stageIII = 1;
            });
        });
    }
}

function StageIV(){
    var interval, datestamp;
    var p = $(".ioresponse p");
    if(stages.register === 0){
        var resp = "You need to register first!";
        p.empty.append(resp);
        return;
    } else if(stages.stageIV === 1){
        var resp = "You've already completed this stage!";
        p.empty().append(resp);
        return;
    } else {
        // Get String
        $.when(CODE2040Post("time", getMessage)).then(function(data){
            interval = data.result.interval;
            datestamp = data.result.datestamp;
            var output = "Your interval is: " + interval;
            var output2 = "<br />Your datestamp is: " + datestamp;
            p.empty().append(output + output2);
            
            var date = new Date(datestamp);
            var ms = date.getTime() + (interval * 1000);
            datestamp = new Date(ms).toISOString();
            var output3 = "<br />Your new time is: " + datestamp;
            p.append(output3);
            
            var values = {"token":token, "datestamp":datestamp};
            var JSONData = JSON.stringify(values);
            $.when(CODE2040Post("validatetime", JSONData)).then(function(data){
                var res = data.result;
                var output = "The result: " + res;
                p.append("<br />" + output);
                stages.stageIV = 1;
            });
        });
    }
}

$(document).ready(function(){
    $("#register").click(function(){
        Register(); 
    });
    $("#stageI").click(function(){
        StageI();
    });
    $("#stageII").click(function(){
        StageII();
    });
    $("#stageIII").click(function(){
        StageIII();
    });
    $("#stageIV").click(function(){
        StageIV();
    });
});