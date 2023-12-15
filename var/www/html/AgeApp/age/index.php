<?php $rawData = file_get_contents('php://input'); $postData = []; parse_str($rawData, $postData); foreach ($postData as $key => $value) { $_POST[trim($key)] = $value; } ?>
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

            <form action="./ren.php" method="post">
                <table class="table ">
                    <tbody>
                        <tr>
                            <td class="td1">Date of birth</td>
                            <td class="td2" >
                                <label for="datePicker"></label>
                                <input style="margin-bottom: 20px;" value="2002-07-13" type="date" id="datePicker" name="datePicker" min="1900-01-01" max="<?php echo date("Y-m-d")?>">
                            </td>
                            <td class="td3">تاريخ ميلادك</td>
                        </tr>
                    </tbody>
                </table>
                
                <br>
                <button type="submit" class="btn btn-primary">calculate</button>
                <br>
            </form>
           
        </div>


        
    </body>
</html>