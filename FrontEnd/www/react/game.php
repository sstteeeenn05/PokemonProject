<?php
    $pipeName=['stdin'=>"../tmp/stdin.txt",'stdout'=>"../tmp/stdout.txt"];
    proc_open(
        "start ../exe/test.exe",
        array(
            0=>['pipe','r'],
            1=>['pipe','w'],
            2=>['file','stderr.txt','a']
        ),
        $pipes
    );
    while(true){
        while(!file_exists($pipeName['stdin'])) usleep(100);
        $stdin=fopen($pipeName['stdin'],'r');
        $input=fgets($stdin);
        fclose($stdin);
        unlink($pipeName['stdin']);
        fwrite($pipes[0],$input);
        $stdout=fopen($pipeName['stdout'],'w');
        fwrite($stdout,fgets($pipes[1]));
        fclose($stdout);
    }
    fclose($pipes[0]);
    fclose($pipes[1]);
?>