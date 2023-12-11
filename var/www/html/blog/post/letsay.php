<?php
    $rawData = file_get_contents("php://input");
    $postData = [];
    parse_str($rawData, $postData);
    foreach ($postData as $key => $value) {
        $_POST[$key] = $value;
    }
?>

<?php
    // echo $_SERVER['REQUEST_METHOD'] . "<br>";
    var_dump($_GET);
?>
