<?php $rawData = file_get_contents('php://input'); $postData = []; parse_str($rawData, $postData); foreach ($postData as $key => $value) { $_POST[trim($key)] = $value; } ?>

<!-- // saaoudi dir khdemtk hna 🧏🏿‍♂️ -->

<?php
    echo $_SERVER['REQUEST_METHOD'] . "<br>";
    echo "<br> ---------- POST --------- <br>";
    var_dump($_POST);
    echo "<br> ------------------------- <br>";
    echo "<br> ---------- GET --------- <br>";
    var_dump($_GET);
    echo "<br> ------------------------- <br>";
?>