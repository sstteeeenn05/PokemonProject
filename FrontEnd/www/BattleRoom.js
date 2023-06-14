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
    isDamaged: [false, false],
    isChanging: [false, false],
    queue:[],
    message:"You Enter A Battle!",
    init(){
      game.start("Test").then((resolve)=>{
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
        console.log("getting output");
        game.getOutput().then((resolve)=>{
          resolve.forEach((msg)=>this.queue.push(msg.split('$')));
          console.log(resolve);
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
    },
    nextQueueMsg(){
      this.queue.shift();
      this.message=this.queue[0].shift();
      let i=0;
      this.queue[0].forEach((data)=>{
        let list=data.split(' ');
        let name=list[0];
        let hp=list[1];
        if(i<3) damagePlayerPokemon(name,hp);
        else damageEnemyPokemon(name,hp);
        for(let i=0;i<4;i++){
          let moveName=list[i*2];
          let movePP=list[i*2+1];

        }
        i++;
      })
    },
    damagePlayerPokemon(name,hp){
      let id=this.constData.player.find(item=>item.name==name);
      if(this.dynamicData.player[id].hp!=hp){
        this.dynamicData.player[id].hp=hp;
        this.damage(0);
      }
    },
    damageEnemyPokemon(name,hp){
      let id=this.constData.enemy.find(item=>item.name==name);
      if(this.dynamicData.enemy[id].hp!=hp){
        this.dynamicData.enemy[id].hp=hp;
        this.damage(1);
      }
    },
    changePlayerMovePP(name,moveName,pp){
      let id=this.constData.player.find(item=>item.name==name);
      let pokemon=this.dynamicData.player[id];
      let moveId=pokemon.moves.find(move=>move.name==moveName);
      let move=pokemon.moves[moveId];
      if(move.pp!=pp){
        move.pp=pp;
      }
    },
    changeEnemyMovePP(name,moveName,pp){
      let id=this.constData.enemy.find(item=>item.name==name);
      let pokemon=this.dynamicData.player[id];
      let moveId=pokemon.moves.find(move=>move.name==moveName);
      let move=pokemon.moves[moveId];
      if(move.pp!=pp){
        move.pp=pp;
      }
    },
    givePlayerPokemonCon(con){

    },
    giveEnemyPokemonCon(con){

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