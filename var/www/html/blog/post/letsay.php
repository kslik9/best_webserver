<?php
    $rawData = file_get_contents("php://input");
    $postData = [];
    parse_str($rawData, $postData);
    foreach ($postData as $key => $value) {
        $_POST[$key] = $value;
    }
?>

<?php
    var_dump($_POST);
?>
