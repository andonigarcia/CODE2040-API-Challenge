<?php
    $token;
    function Register(){
        global $token;
            $url = "http://challenge.code2040.org/api/register";
            $values = array(
                "email" => "andoni@uchicago.edu",
                "github" => "https://github.com/andonigarcia/CODE2040-API-Challenge"
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
                die("ERROR: No response from server. Check internet connection.");
            }
            $res = json_decode($resp);
            $token = $res->result;
            echo($token);
    }
    Register();
?>