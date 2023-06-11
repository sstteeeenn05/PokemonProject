import {XHR} from "./XHR.js"

export class Database{
    /**
     * Upload Pokemon Data to Database
     * @param {string} type 
     * @param {Element} element 
     */
    upload(name,element){
        let xhr=new XHR('/react/upload.php');
        let data=new FormData();
        data.append('uploadName',name);
        data.append('uploadFile',element.files[0]);
        return xhr.send(data);
    }
    clear(){
        let xhr=new XHR('/react/clear.php');
        let data=new FormData();
        data.append('confirmClear',true);
        return xhr.send(data);
    }
    getAllPokemon(){
        return new XHR('/lib/PokemonLib.json').get('json');
    }
}