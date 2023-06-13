import {XHR} from "./XHR.js"

export class Game{
    start(){
        return new XHR('/react/gameStart.php').send(null);
    }
    send(command){
        let data=new FormData();
        data.append('command',command); 
        return new XHR('/react/gameExe.php').send(data);
    }
}