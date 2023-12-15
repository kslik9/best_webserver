<?php $rawData = file_get_contents('php://input'); $postData = []; parse_str($rawData, $postData); foreach ($postData as $key => $value) { $_POST[trim($key)] = $value; } ?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Data</title>
    <script src="https://cdn.tailwindcss.com"></script>
    <style>
        .userInfo {
            background-color: #f0f0f0;
            padding: 10px;
            border: 1px solid #ccc;
            border-radius: 5px;
            width: 300px;
            margin: 20px;
            font-family: Arial, sans-serif;
            white-space: pre-line; /* Preserve line breaks */
        }
        .userInfo pre {
            margin: 0; /* Remove default margin for <pre> element */
        }
    </style>
</head>
<body class="p-16">
    <h1>Form Sent Successfully</h1>
    <div class="userInfo">
        GET
        <pre><?php echo var_dump($_GET); ?></pre>
    </div>
    <div class="userInfo">
        POST
        <pre><?php echo var_dump($_POST); ?></pre>
    </div>
</body>
</html>