<?php
    $token = "yicZ5DfAT6";
    $string;
    
    function GetString(){
        global $token, $string;
            $url = "http://challenge.code2040.org/api/getstring";
            $values = array(
                "token" => $token
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
            $string = $res->result;
            echo("Your string is: $string<br />");
    }
    
    function RevStr(){
        global $string;
        $string = strrev($string);
        echo("The reversed string is: $string<br />");
    }
    
    function PostString(){
            global $token, $string;
            $url = "http://challenge.code2040.org/api/validatestring";
            $values = array(
                "token" => $token,
                "string" => $string
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
    
    function StageI(){
        GetString();
        RevStr();
        PostString();
    }
    
    StageI();
?>