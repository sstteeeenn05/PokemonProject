import './jsapi/Alpine.js'
import {Database} from "./jsapi/Database.js"
import {XHR} from "./jsapi/XHR.js"

let db=new Database();

document.addEventListener('alpine:init', ()=>{
  Alpine.store('home', {

  })
})

document.addEventListener('alpine:init', ()=>{
  Alpine.store('modal', {
    gameFile: "",
    open(name) {
      let modal = document.getElementById(name)
      modal.showModal()
    },
    close(name) {
      let modal = document.getElementById(name)
      modal.close();
    }
  })

  Alpine.store('db',{
    db:new Database(),
    upload(name,inputQueryName,statusQueryName){
      db.upload(name,document.querySelector(inputQueryName)).then((resolve)=>{
        console.log(resolve);
        document.querySelector(statusQueryName).innerHTML=resolve;
      }).catch((reject)=>{
        console.log(reject);
        document.querySelector(statusQueryName).innerHTML=reject;
      })
    },
    clear(statusQueryName){
      if(confirm('Clear Database, Really?')) db.clear().then((resolve)=>{
        console.log(resolve);
        document.querySelector(statusQueryName).innerHTML=resolve;
      }).catch((reject)=>{
        console.log(reject);
        document.querySelector(statusQueryName).innerHTML=reject;
      })
    },
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
    },
    getAllPokemon(){
      db.getAllPokemon().then((resolve)=>{
        resolve.forEach((pokemon)=>{
          console.log(pokemon);
          let xhr=new XHR(`https://bulbapedia.bulbagarden.net/wiki/${pokemon.name}_(Pok%C3%A9mon)`);
          xhr.get('document').then((resolve)=>{
            let img=document.createElement('img');
            img.src=resolve.querySelector('.image').firstChild.src;
            document.body.append(img);
          })
        })
      }).catch((reject)=>{

      })
    }
  })
})