<?php $rawData = file_get_contents('php://input'); $postData = []; parse_str($rawData, $postData); foreach ($postData as $key => $value) { $_POST[trim($key)] = $value; } ?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/js/bootstrap.bundle.min.js" integrity="sha384-ka7Sk0Gln4gmtz2MlQnikT1wXgYsOg+OMhuP+IlRH9sENBO0LRn5q+8nbTov4+1p" crossorigin="anonymous"></script>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-EVSTQN3/azprG1Anm3QDgpJLIm9Nao0Yz1ztcQTwFspd3yD65VohhpuuCOmLASjC" crossorigin="anonymous">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link href="./data/favicon.png" rel="icon">
    <link href="../data/styles/style.css" rel="stylesheet">
    <title>Login</title>

</head>
<?php include '../files/inSVG.php'; echo $svgIN;?>
    <body>

    <?php include '../files/inNAV.php';?>

          
      <div id="id_div1" class="container-fluid">
        <p class="h3"> Sign in </p>
          <form action="../files/getdata.php" method="POST">
            <div class="mb-3">
              <label for="exampleInputEmail1" class="form-label h6"></label>
              <input placeholder="Email address" type="Email" class="form-control" id="exampleInputEmail1" name="exampleInputEmail1" aria-describedby="emailHelp">
            </div>
          <div class="mb-3">
            <label for="exampleInputPassword1" class="form-label h6"></label>
            <input placeholder="Password" type="password" class="form-control" id="exampleInputPassword1" name="exampleInputPassword1">
          </div>
          <div class="mb-3"><br>
            <p>Don't have an account? <a href="../signup/">sign up</a></p>
          </div>
          <button type="submit" class="btn btn-primary">Submit</button><br><br>
        </form>
        </div>
        <?php include '../files/footer.php';?>

    </body>
</html>