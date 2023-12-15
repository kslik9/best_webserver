<?php $rawData = file_get_contents('php://input'); $postData = []; parse_str($rawData, $postData); foreach ($postData as $key => $value) { $_POST[trim($key)] = $value; } ?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Upload File</title>
    <script src="https://cdn.tailwindcss.com"></script>
</head>
<body class="p-16 flex flex-col items-center">
    <h1 class="text-3xl font-bold py-16">File upload</h1>
    <form class="border border-gray-500 p-8 rounded" enctype="multipart/form-data" action="./upload.php" method="post">
        <input required type="file" name="file" id="file">
        <input class="bg-gray-500 p-1 px-2 text-white rounded cursor-pointer" type="submit" value="Submit">
    </form>
</body>
</html>
