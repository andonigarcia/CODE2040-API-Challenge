<?php
    $token = "yicZ5DfAT6";
    $datestamp;
    $interval;
    $newTime;
    
    function GetTime(){
        global $token, $datestamp, $interval;
            $url = "http://challenge.code2040.org/api/time";
            $values = array("token" => $token);
            $context = stream_context_create(array(
                "http" => array(
                    "method" => "POST",
                    "header" => "Content-type: application/json\r\n",
                    "content" => json_encode($values)
                )
            ));
            $resp = file_get_contents($url, FALSE, $context);
            if($resp === FALSE){
                die("ERROR: No response from server. Check internet connection.<br />");
            }
            $res = json_decode($resp);
            $interval = $res->result->interval;
            $datestamp = $res->result->datestamp;
            echo("Your interval is: $interval<br />Your datestamp is: $datestamp<br />");
    }
    
    function AddTime(){
        global $interval, $datestamp, $newTime;
        $date = new DateTime($datestamp);
        $secs = $date->getTimestamp() + $interval;
        $addedDate = new DateTime("@$secs");
        $newTime = str_replace("+",".",$addedDate->format(DateTime::ISO8601));
        $newTime[strlen($newTime) - 1] = "Z";
        
        echo("Your new date is: $newTime<br />");
    }
    
    function PostTime(){
            global $token, $newTime;
            $url = "http://challenge.code2040.org/api/validatetime";
            $values = array(
                "token" => $token,
                "datestamp" => $newTime
            );
            $context = stream_context_create(array(
                "http" => array(
                    "method" => "POST",
                    "header" => "Content-type: application/json\r\n",
                    "content" => json_encode($values)
                )
            ));
            $resp = file_get_contents($url, FALSE, $context);
            if($resp === FALSE){
                die("ERROR: No response from server. Check internet connection.<br />");
            }
            $res = json_decode($resp);
            echo("Result: $res->result<br />");
    }
    
    function StageIV(){
        GetTime();
        AddTime();
        PostTime();
    }
    
    StageIV();
?>