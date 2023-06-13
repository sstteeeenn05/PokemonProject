<?php
    session_start();
    $_SESSION['pipes']=['stdin'=>"../../node/exe/stdin.txt",'stdout'=>"../../node/exe/stdout.txt",'stderr'=>"../../node/exe/stderr.txt"];
    proc_open(
        "start ../../node/node.exe ../../node/game.js",
        array(
            0=>['pipe','r'],
            1=>['pipe','w'],
            2=>['file',$_SESSION['pipes']['stderr'],'a']
        ),
        $pipes
    );
    print_r($_SESSION['pipes']);
    echo "lesss goooo";
?>