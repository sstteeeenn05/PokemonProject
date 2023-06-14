<?php
    require_once "../phpapi/React.php";
    if(!isset($_POST['param'])) React::reject("Lost Argument");
    session_start();
    unset($_SESSION['pipes']);
    $_SESSION['pipes']=array(
        'stdin'=>$_SERVER['DOCUMENT_ROOT']."/../node/exe/stdin.txt",
        'stdout'=>$_SERVER['DOCUMENT_ROOT']."/../node/exe/stdout.txt",
        'stderr'=>$_SERVER['DOCUMENT_ROOT']."/../node/exe/stderr.txt"
    );
    popen("start ".$_SERVER['DOCUMENT_ROOT']."/../node/node.exe ".$_SERVER['DOCUMENT_ROOT']."/../node/buffer.js ".$_POST['param'],'r');
    React::resolve("");
?>