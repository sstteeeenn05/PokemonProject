<?php
    require_once "../phpapi/React.php";

    session_start();
    unset($_SESSION['pipes']);
    $_SESSION['pipes']=array(
        'stdin'=>$_SERVER['DOCUMENT_ROOT']."/../node/exe/stdin.txt",
        'stdout'=>$_SERVER['DOCUMENT_ROOT']."/../node/exe/stdout.txt",
        'stderr'=>$_SERVER['DOCUMENT_ROOT']."/../node/exe/stderr.txt"
    );
    popen("start ".$_SERVER['DOCUMENT_ROOT']."/../node/node.exe ".$_SERVER['DOCUMENT_ROOT']."/../node/buffer.js",'r');
    React::resolve("");
?>