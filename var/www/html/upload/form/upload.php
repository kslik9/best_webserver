<?php $rawData = file_get_contents('php://input'); $postData = []; parse_str($rawData, $postData); foreach ($postData as $key => $value) { $_POST[trim($key)] = $value; } ?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Data</title>
    <script src="https://cdn.tailwindcss.com"></script>
</head>
<body class="p-16">
    <?php
        echo "- Form Sent Successfully -<br>";
        echo "<br>";
        echo "----- GET: ";
        echo var_dump($_GET);
        echo "<br><br>";
        echo "----- POST: ";
        echo var_dump($_POST);
    ?>
</body>
</html>