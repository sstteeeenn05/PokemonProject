<?php
    require_once "../phpapi/React.php";
    system("\"".$_SERVER['DOCUMENT_ROOT']."\\exe\\Pokemon.exe\"");
    usleep(100);
    $file=fopen($_SERVER['DOCUMENT_ROOT']."\\exe\\TestOutput.txt",'r');
    echo React::arrayToDom(explode(';',preg_replace(
        '/[\x00-\x1F\x7F]/',
        '',
        stream_get_contents($file)
    )));
?>