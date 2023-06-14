import './jsapi/Alpine.js'
import {Database} from "./jsapi/Database.js"
import {Game} from "./jsapi/Game.js"

let db = new Database();
let game=new Game();

document.addEventListener('alpine:init', () => {
  Alpine.store('game',{
    myPokemons:[],
    opponentPokemons:[],
    init(){
      game.start().then((resolve)=>{
        console.log(resolve);
      }).catch((reject)=>{
        alert(reject);
        location.href="/";
      })
      game.initData().then((resolve)=>{
        this.myPokemons=resolve.myPokemons;
        this.parsePicture(this.myPokemons);
        this.opponentPokemons=resolve.opponentPokemons;
        this.parsePicture(this.opponentPokemons);
      })
    },
    parsePicture(pokemons){
      pokemons.forEach((pokemon)=>{
        pokemon.src=game.getPokemonPicByName(pokemon.name);
      })
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
    pokemonType: [false, true, true, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,],
    pokemonCondition: [false, true, true],
    skillType: [true, false, false, false, false, false, false, true, false, false, false, false, false, false, false, false, false, false,],
    skillCondition: [false, true, false],
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