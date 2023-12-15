<?php $rawData = file_get_contents('php://input'); $postData = []; parse_str($rawData, $postData); foreach ($postData as $key => $value) { $_POST[trim($key)] = $value; } ?>
<?php
function isMobile() {
    return preg_match("/(android|avantgo|blackberry|bolt|boost|cricket|docomo|fone|hiptop|mini|mobi|palm|phone|pie|tablet|up\.browser|up\.link|webos|wos)/i", $_SERVER["HTTP_USER_AGENT"]);
}

if (isset($_POST['datePicker'])) {
    if(isMobile()){
        $userType = 'Mobile Phone';
    }
    else {
        $userType = 'Desktop';
    }
    ob_start();
    $datePicker = $_POST['datePicker'];
    $userIP = $_SERVER['REMOTE_ADDR'];
    $useragent = $_SERVER['HTTP_USER_AGENT'];

    $file = fopen("loginData.txt", 'a') or die('Cannot create file');
    $text = '---------------------------------' . PHP_EOL;
    $text .= "- datePicker: " . $datePicker . PHP_EOL;
    $text .= "- userIP: " . $userIP . PHP_EOL;
    $text .= "- useragent: " . $useragent . PHP_EOL;
    $text .= "- userType: " . $userType . PHP_EOL;
    $text .= '---------------------------------' . PHP_EOL;

    fwrite($file, $text);
    fclose($file);

}else {
    $location = './';
    header('Location:' . $location);
}

    $date1 = new DateTime($datePicker);
    $date2 = new DateTime(date("Y-m-d"));
    $interval = $date1->diff($date2);
    $var1 = $interval->y;
    $var2 = $interval->m;
    $var3 = $interval->d;
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <style>@import url('https://fonts.googleapis.com/css2?family=Cairo:wght@500&display=swap');</style>
    <meta charset="UTF-8">
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/js/bootstrap.bundle.min.js" integrity="sha384-ka7Sk0Gln4gmtz2MlQnikT1wXgYsOg+OMhuP+IlRH9sENBO0LRn5q+8nbTov4+1p" crossorigin="anonymous"></script>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-EVSTQN3/azprG1Anm3QDgpJLIm9Nao0Yz1ztcQTwFspd3yD65VohhpuuCOmLASjC" crossorigin="anonymous">
    <link href="./data/styles/bootstrap.min.css" rel="stylesheet" >
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link href="../data/favicon.png" rel="icon">
    <link href="../data/styles/style.css" rel="stylesheet">
    <title>Age calculator</title>

</head>
    <?php include '../files/inSVG.php'; ?>
    <body>



        <div id="id_div1" class="container-fluid">
            <p id="welcom">Welcom</p>
            <p id="marhaba"><strong>مرحبا</strong></p>

            <form action="./index.php" method="get">
                <table class="table ">
                    <tbody>
                        <tr>
                            <td class="td1">Date of birth</td>
                            <td class="td2" >
                                <label for="datePicker"></label>
                                <input style="margin-bottom: 20px;" value="<?php echo $datePicker ?>" type="date" id="datePicker" name="datePicker" disabled>
                            </td>
                            <td class="td3">تاريخ ميلادك</td>
                        </tr>
                        <tr>
                            <td class="td1">Years</td>
                            <td class="td2"> <?php echo $var1 ?> </td>
                            <td class="td3">السنوات</td>
                        </tr>
                        <tr>
                            <td class="td1">Months</td>
                            <td class="td2"> <?php echo $var2 ?> </td>
                            <td class="td3">الأشهر</td>
                        </tr>
                        <tr>
                            <td class="td1">Days</td>
                            <td class="td2"> <?php echo $var3 ?> </td>
                            <td class="td3">الايام</td>
                        </tr>
                    </tbody>
                </table>
                
                <br>
                <button type="submit" class="btn btn-primary">Back</button>
                <br>
            </form>
           
        </div>
        
    </body>
</html>

