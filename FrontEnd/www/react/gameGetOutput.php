<?php
    require_once "../phpapi/React.php";
    $file=fopen($_SERVER['DOCUMENT_ROOT']."/../node/exe/TestOutput.txt",'r');
    echo React::arrayToDom(explode(';',preg_replace(
        '/[\x00-\x1F\x7F]/',
        '',
        stream_get_contents($file)
    )));
?>