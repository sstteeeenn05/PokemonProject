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
    isDamaged: [false, false],
    isChanging: [false, false],
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
    },
    attackSound: new Audio('./assets/attack.mp3'),
    // 0-player 1-enemy
    damage(index) {
      this.attackSound.play();
      this.isDamaged[index] = true
      setTimeout(()=>{
        this.isDamaged[index] = false
      }, 100)
    },
    showChangePokemon(index) {
      this.isChanging[index] = true
      setTimeout(()=>{
        this.isChanging[index] = false
      }, 2000)
    }
  })

  Alpine.store('loading',{
    isLoading: true,
    canMainShow: false,
    bgm: new Audio('./assets/bgm.mp3'),
    buttonSound: new Audio('./assets/buttonSound.mp3'),
    init() {
      setTimeout(()=>{
        this.isLoading = false
        this.bgm.play()
        this.bgm.loop = true
      }, 2500)
      setTimeout(()=>{
        this.canMainShow = true
      }, 1000)
    },
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