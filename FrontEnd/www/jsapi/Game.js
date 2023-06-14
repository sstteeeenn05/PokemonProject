import {XHR} from "./XHR.js"

export class Game{
    start(){
        return new XHR('/react/gameStart.php').send(null);
    }
    send(command){
        let data=new FormData();
        data.append('command',command); 
        return new Promise((resolve,reject)=>{
            new XHR('/react/gameExe.php').send(data).then((dom)=>{
                resolve(dom.querySelectorAll('item'));
            }).catch((err)=>{reject(err)})
        })
    }
    move(moveName){
        return this.send(`Battle ${moveName}`);
    }
    usePotion(potionName){
        return this.send(`Bag ${potionName}`);
    }
    changePokemon(pokemonName){
        return this.send(`Pokemon ${pokemonName}`);
    }
    opponentMove(name){
        return this.send(name);
    }
    get(){
        return this.send();
    }
    exit(){
        return this.send("kill");
    }
    getPokemonPicByName(name){
      return new Promise((resolve,reject)=>{
        new XHR(
          `https://bulbapedia.bulbagarden.net/wiki/${name}_(Pok%C3%A9mon)`
        ).get('document').then((doc)=>{
            resolve(doc.querySelector('.image').firstChild.src);
        }).catch((err)=>{
          reject(err);
        })
      })
    }
    initData(){
        return new Promise((resolve,reject)=>{
            new XHR('/lib/GameData.json').get('json').then((json)=>{
                resolve(JSON.parse(json));
            }).catch((err)=>{
                reject(err);
            })
        })
    }
}