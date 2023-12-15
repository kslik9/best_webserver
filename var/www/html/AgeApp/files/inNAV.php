<?php
    //
    $SI_currpath = '\youssef.uk\signin';
    $SU_currpath = '\youssef.uk\signup';
    $mainPath = '\youssef.uk\index.php';
    $ageApp = '\youssef.uk\age';
    $owner = '\youssef.uk\owner';
    $actual_link =  "{$_SERVER['REQUEST_URI']}";
    $actual_link = strtolower($actual_link);

    // to controle every path i can use this:
    /*
    
    if($actual_link == "/youssef.uk/signup/"){
      $SI_currpath = '../signin/';
      $SU_currpath = '#';
      $mainPath = '../';
      $ageApp = '../age/';
      $owner = '../owner/';
    }
    elseif($actual_link == "/youssef.uk/signin/"){
      $SI_currpath = '#';
      $SU_currpath = '../signup/';
      $mainPath = '../';
      $ageApp = '../age/';
      $owner = '../owner/';
    }
    elseif($actual_link == "/youssef.uk/age/"){
      $SI_currpath = '../signin/';
      $SU_currpath = '../signup/';
      $mainPath = '../';
      $ageApp = '#';
      $owner = '../owner/';
    }
    elseif($actual_link == "/youssef.uk/age/ren.php"){
      $SI_currpath = '.././signin/';
      $SU_currpath = '.././signup/';
      $mainPath = 'youssef.uk\index.php';
      $ageApp = './';
      $owner = '.././owner/';
    }
    else{
      $SI_currpath = './signin/';
      $SU_currpath = './signup';
      $mainPath = '#';
      $ageApp = 'age/';
      $owner = 'owner/';
    }*/
    $navIN = '
    <nav id="navId" class="navbar navbar-expand-lg navbar-light ">
        <div class="container-fluid">
          <a id="Dev__" class="navbar-brand" href="'.$mainPath.'">DEV</a>
          <button class="navbar-toggler" type="button" data-bs-toggle="collapse" data-bs-target="#navbarSupportedContent" aria-controls="navbarSupportedContent" aria-expanded="false" aria-label="Toggle navigation">
            <span class="navbar-toggler-icon"></span>
          </button>
          <div class="collapse navbar-collapse" id="navbarSupportedContent">
            <ul class="navbar-nav me-auto mb-2 mb-lg-0">
              <li class="nav-item">
                <a class="nav-link" href="'.$owner.'" target="blank">Onwer</a>
              </li>
              <li class="nav-item">
                <a class="nav-link" href="'.$ageApp.'">AgeApp</a>
              </li>
              <li class="nav-item dropdown">
                <a class="nav-link dropdown-toggle" href="#" id="navbarDropdown" role="button" data-bs-toggle="dropdown" aria-expanded="false">
                  Identify
                </a>
                <ul class="dropdown-menu" aria-labelledby="navbarDropdown">
                  <li style="font-size: 80%;"><a class="dropdown-item" href="'.$SU_currpath.'">Sign up</a></li>
                  <li><hr class="dropdown-divider"></li>
                  <li style="font-size: 80%;"><a class="dropdown-item" href="'.$SI_currpath.'">Sign in</a></li>
                </ul>
              </li>
              <li class="nav-item">
                <a class="nav-link" href="#">Contact us</a>
              </li>
            </ul>
            <form class="d-flex">
              <input id="searchbar_" class="form-control me-2" type="search" placeholder="Search" aria-label="Search">
              <button id="searchbtn_" class="btn btn-outline-success" type="submit">Search</button>
            </form>
          </div>
        </div>
      </nav>
    ';

    echo $navIN;

?>