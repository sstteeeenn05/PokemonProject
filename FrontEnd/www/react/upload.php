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
        public $level=50;
        public $moves=array();
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

    class GameData{
        public $myPokemons=array();
        public $opponentPokemons=array();
    }

    function findByName($arr,$name){
        foreach($arr as $item){
            if($item->name==$name) return $item;
        }
        throw new Exception("item:".$name." not exist");
    }

    $stderr=fopen('stderr.txt','a');

    require_once "../phpapi/React.php";
    if(!isset($_POST['uploadName'])) React::reject("Lost argument");
    $libDir=$_SERVER['DOCUMENT_ROOT']."\\lib\\";
    $fileName=$_POST['uploadName'];
    $output;
    try{
        $file=fopen($_FILES['uploadFile']['tmp_name'],'r');
        switch($_POST['uploadName']){
            case "PokemonLib":
                $output=array();
                while(!feof($file)){
                    $pokemon=new Pokemon();
                    fscanf($file,"%s",$pokemon->name);
                    $pokemon->types=explode(' ',preg_replace('/[\x00-\x1F\x7F]/','',fgets($file)));
                    array_shift($pokemon->types);
                    fscanf($file,"%d %d %d %d %d %d",$pokemon->hp,$pokemon->atk,$pokemon->def,$pokemon->spatk,$pokemon->spdef,$pokemon->speed);
                    $output[]=$pokemon;
                    unset($pokemon);
                }
                break;
            case "MoveLib":
                $output=array();
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
                    $output[]=$move;
                    unset($move);
                }
                break;
            case "GameData":
                if(!file_exists($libDir."PokemonLib.json")) throw new Exception("Missing PokemonLib.json");
                if(!file_exists($libDir."MoveLib.json")) throw new Exception("Missing MoveLib.json");
                $tmpStream=fopen($libDir."PokemonLib.json",'r');
                $pokemonLib=json_decode(
                    preg_replace(
                        '/[\x00-\x1F\x7F]/',
                        '',
                        fread($tmpStream,filesize($libDir."PokemonLib.json")))
                );
                fclose($tmpStream);
                $tmpStream=fopen($libDir."MoveLib.json",'r');
                $moveLib=json_decode(
                    preg_replace(
                        '/[\x00-\x1F\x7F]/',
                        '',
                        fread($tmpStream,filesize($libDir."MoveLib.json")))
                );
                fclose($tmpStream);
                $output=new GameData();
                $myCount=0;
                $opponentCount=0;
                fscanf($file,"%d",$myCount);
                for($i=0;$i<$myCount;$i++){
                    $name="";
                    fscanf($file,"%s",$name);
                    $pokemon=findByName($pokemonLib,$name);
                    $pokemon->moves=array_map(
                        function($m_name)use($moveLib){
                            return findByName($moveLib,$m_name);
                        },
                        explode(' ',preg_replace(
                            '/[\x00-\x1F\x7F]/',
                            '',
                            fgets($file)
                        ))
                    );
                    $output->myPokemons[]=$pokemon;
                }
                fscanf($file,"%d",$opponentCount);
                for($i=0;$i<$opponentCount;$i++){
                    fscanf($file,"%s",$name);
                    $pokemon=findByName($pokemonLib,$name);
                    $pokemon->moves=array_map(
                        function($m_name)use($moveLib){
                            return findByName($moveLib,$m_name);
                        },
                        explode(' ',preg_replace(
                            '/[\x00-\x1F\x7F]/',
                            '',
                            fgets($file)
                        ))
                    );
                    $output->opponentPokemons[]=$pokemon;
                }
                break;
            default:
                throw new Exception("Bad Header");
        }
    }catch(Exception $e){
        React::reject($e->getMessage());
    }finally{
        fclose($file);
        move_uploaded_file($_FILES['uploadFile']['tmp_name'],$_SERVER['DOCUMENT_ROOT']."\\..\\node\\exe\\file\\".$fileName.".txt");
        $file=fopen($libDir.$fileName.".json",'w');
        fwrite($file,json_encode($output, JSON_PRETTY_PRINT));
        fclose($file);
        React::resolve("Upload Ok!");
    }
?>