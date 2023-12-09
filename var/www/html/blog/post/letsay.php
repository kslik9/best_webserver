<?php
    $rawData = file_get_contents("php://input");
    $postData = [];
    parse_str($rawData, $postData);
    foreach ($postData as $key => $value) {
        $_POST[$key] = $value;
    }
?>

<?php
    echo $_POST['data_from_97'];
    echo "<br>\n";
    echo $_POST['musclues'];
?>
