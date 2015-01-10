<?php
    $token = "yicZ5DfAT6";
    $prefix;
    $array;
    $filtArray = array();
    
    function GetPrefix(){
        global $token, $prefix, $array;
            $url = "http://challenge.code2040.org/api/prefix";
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
            $prefix = $res->result->prefix;
            $array = $res->result->array;
            echo("Your prefix is: $prefix<br />Your array is:<pre>");
            print_r($array);
            echo("</pre><br />");
    }
    
    function FilterArray(){
        global $prefix, $array, $filtArray;
        foreach($array as $str){
            if(strpos($str, $prefix) !== 0){
                    array_push($filtArray, $str);
            }
        }
        echo("The filtered array is:<pre>");
        print_r($filtArray);
        echo("</pre><br />");
    }
    
    function PostPrefix(){
            global $token, $filtArray;
            $url = "http://challenge.code2040.org/api/validateprefix";
            $values = array(
                "token" => $token,
                "array" => $filtArray
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
    
    function StageIII(){
        GetPrefix();
        FilterArray();
        PostPrefix();
    }
    
    StageIII();
?>