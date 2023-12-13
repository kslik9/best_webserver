<?php $rawData = file_get_contents('php://input'); $postData = []; parse_str($rawData, $postData); foreach ($postData as $key => $value) { $_POST[$key] = $value; } ?>
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
    <style>
        body{
            background: rgb(2, 0, 21);
            color: white;
        }
    </style>
</head>

<body>
    <div style="text-align: left; padding: 6rem;">
        <?php
        echo "blog N: 1337<br>";
        echo "<hr>";
        foreach ($_SERVER as $key => $value)
            echo "<li>$key=$value</li>";
        ?>
    </div>
</body>
</html>