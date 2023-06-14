import './jsapi/Alpine.js'
import {Database} from "./jsapi/Database.js"
import {Game} from "./jsapi/Game.js"

let db = new Database();
let game=new Game();

window.addEventListener('beforeunload', (e) => {
  e.preventDefault();
  game.exit();
});

document.addEventListener('alpine:init', () => {
  Alpine.store('game',{
    constData:{},
    dynamicData:{},
    myPokemons:[],
    opponentPokemons:[],
    playerId:0,
    enemyId:0,
    queue:[],
    init(){
      game.start("Test").then((resolve)=>{
        console.log(resolve);
      }).catch((reject)=>{
        alert(reject);
        location.href="/";
      })
      game.initData().then((resolve)=>{
        this.constData=resolve;
        this.dynamicData=resolve;
        this.parsePicture(this.constData.player);
        this.parsePicture(this.constData.enemy);
      })
      setTimeout(()=>{
        game.getOutput((resolve)=>{
          this.queue=resolve;
          console.log(this.queue);
        })
      },1000);
      
    },
    parsePicture(pokemons){
      pokemons.forEach((pokemon)=>{
        pokemon.src=game.getPokemonPicByName(pokemon.name);
      })
    }
  })

  Alpine.store('loading',{
    isLoading: true,
    canMainShow: false,
    init() {
      setTimeout(()=>{
        this.isLoading = false
      }, 2500)
      setTimeout(()=>{
        this.canMainShow = true
      }, 1000)
    }
  })

  Alpine.store('modal', {
    type: '',
    listData: [1, 2, 3, 4],
    conIconList: [
      'BRN.svg',
      'PSN.svg',
      'PAR.svg'
    ],
    typeIconList: [
      'Normal.png',
      'Fire.png',
      'Water.png',
      'Electric.png',
      'Grass.png',
      'Ice.png',
      'Fight.png',
      'Poison.png',
      'Ground.png',
      'Flying.png',
      'Psychic.png',
      'Bug.png',
      'Rock.png',
      'Ghost.png',
      'Dragon.png',
      'Dark.png',
      'Steel.png',
      'Fairy.png'
    ],
    potionList: [
      ['potion.png', 'Potion', 'Heal 20 Hp of your pokémon'],
      ['superPotion.png', 'Super Potion', 'Heal 60 Hp of your pokémon'],
      ['hyperPotion.png', 'Hyper Potion', 'Heal 120 Hp of your pokémon'],
      ['maxPotion.png', 'Max Potion', 'Heal 100% Hp of your pokémon']
    ],
    selectingPokemon() {
      this.type = 'pokemon';
    },
    open(type) {
      this.type = type;
      let modal = document.getElementById('list')
      modal.showModal()
    },
    close() {
      let modal = document.getElementById('list')
      modal.close();
    }
  })
})