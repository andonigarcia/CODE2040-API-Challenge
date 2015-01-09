// Andoni Garcia. 2015.
// CODE2040 API Challenge

var token;
var getMessage;
var stages = {"register":0, "stageI":0, "stageII":0, "stageIII":0, "stageIV":0};
var port = 80;
var domain = "http://challenge.code2040.org/api/";

// Helper Functions

function GetMessage(token){
    var values = {"token":token};
    getMessage = JSON.stringify(values);
}

function CODE2040Post(page, message){
    console.log("Page:"+page+"\nMessage:"+message);
    var url = domain + page;
    return $.post(url, message, "json");
}

function makeStageObj(s1, s2, s3, s4){
    var obj = {"stageI":s1,
               "stageII":s2,
               "stageIII":s3,
               "stageIV":s4};
    return obj;
}

function checkBoxes(){
    for(var s in stages){
        var elem = "#" + s + "box";
        if(stages[s] === 0)
            $(elem).prop("checked", false);
        else
            $(elem).prop("checked", true);
    }
}

// Messaging Functions

function RegFirst(){
    var reg = "You need to register first silly! Click 'Register' on the left hand tabs first. We can't talk to the server otherwise!";
    $(".ioresponse #resp").empty().append(reg);
}

function StageComplete(){
    var resp = "You've already completed this stage! Go ahead and complete the next stage(s).";
    $(".ioresponse #resp").empty().append(resp);
}

function isComplete(){
    checkBoxes();
    for(var s in stages){
        if(stages[s] === 0)
            return 0;
    }
    $(".ioresponse #resp").empty();
    var Congrats = "<p class='named'>CONGRATULATIONS!</p>You have solved every single stage of the CODE2040 API Challenge. I hope you enjoyed it! You can see the <a href='https://github.com/andonigarcia/CODE2040-API-Challenge' target='_blank'>source code</a> or try to <a href='http://challenge.code2040.org' target='_blank'>do the challenge</a> yourself!";
    $(".ioresponse #desc").empty().append(Congrats);
    return 1;
}

// Stage Functions
function revStr(obj, obj2){
    var string = obj;
    string = string.split("").reverse().join("");
    return [string, string];
}

function needleIndex(obj, obj2){
    var index = obj2.indexOf(obj);
    return [index, index];
}

function filtArr(obj, obj2){
    var arr = [];
    for (var i = 0; i < obj2.length; i++){
	if(obj2[i].indexOf(obj) !== 0){
            arr.push(obj2[i]);
	}
    }
    return [arr.join(", "), arr];
}

function addTime(obj, obj2){
     var date = new Date(obj2);
     var ms = date.getTime() + (obj * 1000);
     var datestamp = new Date(ms).toISOString();
     return [datestamp, datestamp];
}

// The 3 Main Functions

function Validate(page, values, stage){
    var JSONData = JSON.stringify(values);
    $.when(CODE2040Post(page, JSONData)).then(function(data){
        var res = data.result;
        var output = "<br /><br />The result is: " + res;
        if(stage === "register"){
            $(".ioresponse #resp").empty();
            $("form").hide();
            token = res;
            GetMessage(token);
            output = "<br />Your token is: " + token;
        }
        $(".ioresponse #resp").append(output);
        stages[stage] = 1;
        setTimeout(isComplete(), 6000);
    });
}

function Register(){
    var regMessage = "<p class='named'>Welcome to the CODE2040 API Challenge</p>Please input the email-address and github repo url that you registered for CODE2040 with. If you are just looking at the site and aren't registered for CODE2040, you can click submit without entering anything to go through using Andoni's credentials.";
    $(".ioresponse #desc").empty().append(regMessage);
    $(".ioresponse #resp").empty();
    $("form").show();
    if (stages.register === 1){
        var resp = "<em>Sorry, you've already registered! If you want to reset everything, you are allowed to re-register (by simply filling out the form and clicking 'Register!' again.).</em>";
        $(".ioresponse #resp").append(resp);
    } else {
        var email = "andoni@uchicago.edu";
        var github = "https://github.com/andonigarcia/CODE2040-API-Challenge";
        $("#regform").submit(function(){
            var arr = $(this).serializeArray();
            if(arr[0].value !== "")
                email = arr[0].value;
            if(arr[1].value !== "")
                github = arr[1].value;
            var values = {"email":email,
                          "github":github};
            // Reset Everything
            for(var s in stages){
                stages[s] = 0;
            }
            token = "";
            getMessage = "";
            Validate("register", values, "register");
            return false;
        });
    }
}

function Stages(stage, func, objs){
    // Essential Variables
    var messages = makeStageObj("<p class='named'>Stage I: Reverse a String</p>In this stage, the server will give us a random string. We will then reverse it and send it back to the server!",
                                "<p class='named'>Stage II: Needle in a Haystack</p>Here, we are given a random string (the needle) and an array of strings (the haystack). We must parse the array and then send the server the index of the needle in the haystack!",
                                "<p class='named'>Stage III: Prefix</p>Again we are given an array. But this time we are also given a prefix and we must filter out all the elements of the array that start with the prefix!",
                                "<p class='named'>Stage IV: The Dating Game</p>This is the final challenge! Here, you will be given a random datestamp and an interval (in seconds). We must add the two and give the correct ISO 8601 datestamp back to the server!");
    var getPages = makeStageObj("getstring", "haystack", "prefix", "time");
    var sendPages = makeStageObj("validatestring", "validateneedle", "validateprefix", "validatetime");
    var respObjs = makeStageObj(["string", "reversed string", "string"],
                                ["needle", "haystack", "index of the needle", "needle"],
                                ["prefix", "array", "filtered array", "array"],
                                ["interval", "datestamp", "new datestamp", "datestamp"]);
    var values = {"token":token};
    var obj="", obj2="", tmp1, tmp2, fout, res, output;
    
    // Clears the content
    $(".ioresponse #desc").empty().append(messages[stage]);
    var writeTo = $(".ioresponse #resp").empty();
    $(".ioresponse #regform").hide();
    // Check if it the stages are already complete
    if(isComplete())
        return;
    // If not registered, you must register first.
    if(stages.register === 0){
        RegFirst();
        return;
    // If stage is already complete, you cannot resubmit it.
    } else if(stages[stage] === 1){
        StageComplete();
        return;
    // Else handle the stage
    } else {
        $.when(CODE2040Post(getPages[stage], getMessage)).then(function(data){
            res = data.result;
            // One object to handle
            if(objs === 0){
                obj = res;
                output = "Your " + respObjs[stage][objs++] + " is: " + obj;
            // Two objects to handle
            } else if(objs === 1){
                tmp1 = respObjs[stage][0];
                obj = res[tmp1];
                tmp2 = respObjs[stage][objs++];
                obj2 = res[tmp2];
                output = "Your " + tmp1 + " is: " + obj;
                if(stage === "stageIV")
                    output += "<br /><br />Your " + tmp2 + " is: " + obj2;
                else
                    output += "<br /><br />Your " + tmp2 + " is: " + obj2.join(", ");
            } else {
                output = "Error - check your objs";
            }
            writeTo.append(output);
            // Execute the function -- main point of the API Challenge
            fout = func(obj, obj2);
            writeTo.append("<br /><br />The " + respObjs[stage][objs++] + " is: " + fout[0]);
            
            // Add the value to the object and validate it
            values[respObjs[stage][objs]] = fout[1];
            Validate(sendPages[stage], values, stage);
        }, function(){
            writeTo.append("ERROR: POST request failed. Check your internet connection.");
        });
    }
}

$(document).ready(function(){
    Register();
    
    $("#register").click(function(){
        Register(); 
    });
    $("#stageI").click(function(){
        Stages("stageI", revStr, 0);
    });
    $("#stageII").click(function(){
        Stages("stageII", needleIndex, 1);
    });
    $("#stageIII").click(function(){
        Stages("stageIII", filtArr, 1);
    });
    $("#stageIV").click(function(){
        Stages("stageIV", addTime, 1);
    });
});