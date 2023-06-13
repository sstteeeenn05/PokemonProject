<?php
    require_once "../phpapi/React.php";
    if(!isset($_POST['confirmClear'])) React::reject("Error");
    function removeDir($path):void{
        if(is_dir($path)){
            foreach(scandir($path) as $file){
                if($file=="."||$file=="..");
                else{
                    $file=$path.$file;
                    if(is_dir($file)){
                        if(count(scandir($file))==2) rmdir($file);
                        else File::removeDir($file."\\");
                    }else unlink($file);
                }
            }
            rmdir($path);
        }
    }
    try{
        removeDir($_SERVER['DOCUMENT_ROOT']."\\lib\\");
        mkdir($_SERVER['DOCUMENT_ROOT']."\\lib\\");
        removeDir($_SERVER['DOCUMENT_ROOT']."\\..\\node\\exe\\file\\");
        mkdir($_SERVER['DOCUMENT_ROOT']."\\..\\node\\exe\\file\\");
    }catch(Exception $e){
        React::reject($e->getMessage());
    }finally{
        React::resolve("Clear Ok!");
    }
?>