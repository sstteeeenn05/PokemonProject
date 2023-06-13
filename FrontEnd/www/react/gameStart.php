<?php
    session_start();
    $_SESSION['pipes']=array(
        'stdin'=>$_SERVER['DOCUMENT_ROOT']."/../node/exe/stdin.txt",
        'stdout'=>$_SERVER['DOCUMENT_ROOT']."/../node/exe/stdout.txt",
        'stderr'=>$_SERVER['DOCUMENT_ROOT']."/../node/exe/stderr.txt"
    );
    proc_open(
        "start ".$_SERVER['DOCUMENT_ROOT']."/../node/node.exe ".$_SERVER['DOCUMENT_ROOT']."/../node/buffer.js",
        array(
            0=>['pipe','r'],
            1=>['pipe','w'],
            2=>['file',$_SESSION['pipes']['stderr'],'a']
        ),
        $pipes
    );
    echo $_SERVER['DOCUMENT_ROOT'];
    echo "lesss goooo";
?>