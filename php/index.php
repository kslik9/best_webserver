<?php
    // 
    $url = 'https://www.example.com';
    $content = file_get_contents($url);
    if ($content === false) {
        die('Error fetching the web page');
    }
    // 
    // $content = "Hello World\n";
    echo $content;
?>
