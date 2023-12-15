<?php $rawData = file_get_contents('php://input'); $postData = []; parse_str($rawData, $postData); foreach ($postData as $key => $value) { $_POST[trim($key)] = $value; } ?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Send a form</title>
    <script src="https://cdn.tailwindcss.com"></script>
</head>
<body class="p-16 flex flex-col items-center">
    <h1 class="text-3xl font-bold py-16">Send a form</h1>
    <form class="border border-gray-500 p-8 rounded flex flex-col space-y-4" enctype="application/x-www-form-urlencoded" action="./upload.php" method="post">
        <input class="border border-gray-500 p-2 rounded" required placeholder="Name" name="name" type="text">
        <input class="border border-gray-500 p-2 rounded" required placeholder="Age" name="age" type="text">
        <input class="border border-gray-500 p-2 rounded" required placeholder="Phone" name="phone" type="text">
        <input class="bg-gray-500 p-1 px-2 text-white rounded cursor-pointer" type="submit" value="Submit">
    </form>
</body>
</html>
