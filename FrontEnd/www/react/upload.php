<?php
    class Pokemon{
        public $name="";
        public $types=array();
        public $hp=0;
        public $atk=0;
        public $def=0;
        public $spatk=0;
        public $spdef=0;
        public $speed=0;
    }

    class Move{
        public $name="";
        public $type="";
        public $isPhysical=false;
        public $power=0;
        public $accuracy=0;
        public $pp=0;
        public $con="";
    }

    require_once "../phpapi/React.php";
    if(!isset($_POST['uploadName'])) React::reject("Lost argument");
    $fileName=$_POST['uploadName'].".json";
    $libArray=array();
    try{
        switch($_POST['uploadName']){
            case "PokemonLib":
                $file=fopen($_FILES['uploadFile']['tmp_name'],'r');
                while(!feof($file)){
                    $pokemon=new Pokemon();
                    fscanf($file,"%s",$pokemon->name);
                    $pokemon->types=explode(' ',preg_replace('/[\x00-\x1F\x7F]/','',fgets($file)));
                    array_shift($pokemon->types);
                    fscanf($file,"%d %d %d %d %d %d",$pokemon->hp,$pokemon->atk,$pokemon->def,$pokemon->spatk,$pokemon->spdef,$pokemon->speed);
                    $libArray[]=$pokemon;
                    unset($pokemon);
                }
                fclose($file);
                break;
            case "MoveLib":
                $moveList=array();
                $file=fopen($_FILES['uploadFile']['tmp_name'],'r');
                while(!feof($file)){
                    $move=new Move();
                    $arr=explode(' ',preg_replace('/[\x00-\x1F\x7F]/','',fgets($file)));
                    if(count($arr)!=6&&count($arr)!=7) continue;
                    $move->name=$arr[0];
                    $move->type=$arr[1];
                    $move->isPhysical=$arr[2]=="Physical";
                    $move->power=intval($arr[3]);
                    $move->accuracy=intval($arr[4]);
                    $move->pp=intval($arr[5]);
                    if(isset($arr[6])) $move->con=$arr[6];
                    $libArray[]=$move;
                    unset($move);
                }
                fclose($file);
                break;
            case "GameData":

                break;
            default:
                React::reject("Bad Header");
        }
    }catch(Exception $e){
        React::reject($e->getMessage());
    }finally{
        $file=fopen($_SERVER['DOCUMENT_ROOT']."\\lib\\".$fileName,'w');
        fwrite($file,json_encode($libArray));
        fclose($file);
        React::resolve("Upload Ok!");
    }
?>