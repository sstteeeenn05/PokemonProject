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
    isSwitchingClassName: ['', ''],
    queue:[[]],
    message:"You Enter A Battle!",
    init(){
      game.start("Test").then((resolve)=>{
      }).catch((reject)=>{
        alert(reject);
        location.href="/";
      })
      game.initData().then((resolve)=>{
        this.constData=structuredClone(resolve);
        this.dynamicData=resolve;
        this.parsePicture(this.constData.player);
        this.parsePicture(this.constData.enemy);
      })
      setTimeout(()=>{
        console.log("getting output");
        game.getOutput().then((resolve)=>{
          resolve.forEach((msg)=>this.queue.push(msg.split('$')));
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
    healSound: new Audio('./assets/heal.wav'),
    // 0-player 1-enemy
    damage(index) {
      this.attackSound.pause()
      this.attackSound.currentTime = 0;
      this.attackSound.play()
      this.isDamaged[index] = true
      setTimeout(()=>{
        this.isDamaged[index] = false
      }, 100)
    },
    switchPokemonOut(index) {
      this.isSwitchingClassName[index] = 'switch-out'
      setTimeout(()=>{
        this.isSwitchingClassName[index] = 'rotating'
      }, 995)
    },
    switchPokemonIn(index) {
      let listener = setInterval(() => {
        if (this.isSwitchingClassName[index] === 'rotating') {
          this.isSwitchingClassName[index] = 'switch-in'
          setTimeout(() => {
            this.isSwitchingClassName[index] = ''
          }, 995)
          clearInterval(listener);
        }
      }, 1)
    },
    nextQueueMsg(){
      this.queue.shift();
      this.message=this.queue[0].shift();
      if(this.message.includes('opposing')&&this.message.includes('fainted')) {
        this.switchPokemonOut(1)
        setTimeout(()=>{this.enemyId++;}, 1000);
        this.switchPokemonIn(1)
      }
      if(this.message.includes('Come back!')) this.switchPokemonOut(0);
      if(this.message.includes('Go!')){
        let name=this.message.split('!')[1].replace(' ','');
        this.playerId=this.constData.player.indexOf(this.constData.player.find((pokemon)=>pokemon.name===name));
        this.switchPokemonIn(0);
      }
      let i=0;//i=0~2:player i=4~5:enemy
      this.queue[0].forEach((data)=>{
        let list=data.split(' ');
        let name=list[0];
        let hp=list[1];
        console.log(list)
        if(i<3) this.damagePlayerPokemon(name,hp);
        else this.damageEnemyPokemon(name,hp);
        for(let j=1;j<5;j++){
          let moveName=list[j*2];
          let movePP=list[j*2+1];
          console.log(moveName)
          if(i<3) this.changePlayerMovePP(name, moveName, movePP);
          else this.changeEnemyMovePP(name, moveName, movePP);
        }
        let cons = [];
        for(let j= 10;j<list.length;j++){
          let con=list[j];
          cons.push(con);
        }
        if(i<3) this.givePlayerPokemonCon(name, cons);
        else this.giveEnemyPokemonCon(name, cons);
        i++;
      })
    },
    damagePlayerPokemon(name,hp){
      let pokemon=this.dynamicData.player.find(item=>item.name===name);
      if(pokemon.hp!==hp){
        if(hp<pokemon.hp) this.damage(0);
        else this.healSound.play();
        pokemon.hp=hp;
      }
    },
    damageEnemyPokemon(name,hp){
      let pokemon=this.dynamicData.enemy.find(item=>item.name===name);
      if(pokemon.hp!==hp){
        if(hp<pokemon.hp) this.damage(1);
        else this.healSound.play();
        pokemon.hp=hp;
      }
    },
    changePlayerMovePP(name,moveName,pp){
      let pokemon=this.dynamicData.player.find(item=>item.name===name);
      let move=pokemon.moves.find(move=>move.name===moveName);
      if(move.pp!==pp){
        move.pp=pp;
      }
    },
    changeEnemyMovePP(name,moveName,pp){
      let pokemon=this.dynamicData.enemy.find(item=>item.name===name);
      let move=pokemon.moves.find(move=>move.name===moveName);
      if(move.pp!==pp){
        move.pp=pp;
      }
    },
    givePlayerPokemonCon(name, cons){
      let pokemon = this.dynamicData.player.find(item=>item.name===name);
      if(pokemon.cons !== cons){
        pokemon.cons = cons
      }
    },
    giveEnemyPokemonCon(name, cons){
      let pokemon = this.dynamicData.enemy.find(item=>item.name===name);
      if(pokemon.cons !== cons){
        pokemon.cons = cons
      }
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
    buttonClick(){
      this.buttonSound.pause()
      this.buttonSound.currentTime = 0;
      this.buttonSound.play()
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