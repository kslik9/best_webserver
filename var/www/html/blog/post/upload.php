<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Seeeeee ya</title>
    <script src="https://cdn.tailwindcss.com"></script>
</head>
<body class="p-16">
    <h1 class="flex py-2">let's send something using post</h1>
    <div>
        <form action="./send.php?id=1337" method="post">
            <div>
                <input class="p-2 border border-gray-500 rounded" placeholder="name" name="name" type="text">
                <input class="p-2 border border-gray-500 rounded" placeholder="age" name="age" type="text">
                <!-- <input type="file" name="file" id="file"> -->
            </div>
            <div class="flex py-2"></div>
            <input class="cursor-pointer border border-gray-500 p-1 px-2 rounded" type="submit" value="Submit">
        </form>
    </div>
</body>
</html>
