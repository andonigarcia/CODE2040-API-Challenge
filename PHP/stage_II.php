<?php
    $token = "yicZ5DfAT6";
    $needle;
    $haystack;
    $index;
    
    function GetNeedle(){
        global $token, $needle, $haystack;
            $url = "http://challenge.code2040.org/api/haystack";
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
            $needle = $res->result->needle;
            $haystack = $res->result->haystack;
            echo("Your needle is: $needle<br />Your haystack is:<pre>");
            print_r($haystack);
            echo("</pre><br />");
    }
    
    function Index(){
        global $needle, $haystack, $index;
        $index = array_search($needle, $haystack);
        echo("The index of the needle is: $index<br />");
    }
    
    function PostNeedle(){
            global $token, $index;
            $url = "http://challenge.code2040.org/api/validateneedle";
            $values = array(
                "token" => $token,
                "needle" => $index
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
    
    function StageII(){
        GetNeedle();
        Index();
        PostNeedle();
    }
    
    StageII();
?>