<?php
    session_start();
    require_once "../phpapi/React.php";
    if(!isset($_POST['command'])) React::reject("Lost argument");
    if(!isset($_SESSION['pipes'])) React::reject("Game not start");
    $stdin=fopen($_SESSION['pipes']['stdin'],'w');
    fwrite($stdin,$_POST['command']);
    fclose($stdin);
    while(!file_exists($_SESSION['pipes']['stdout'])) usleep(100);
    $stdout=fopen($_SESSION['pipes']['stdout'],'r');
    $output=stream_get_contents($stdout);
    fclose($stdout);
    unlink($_SESSION['pipes']['stdout']);
    React::resolve($output);
?>