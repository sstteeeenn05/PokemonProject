#include "GameAI.h"

#include <queue>

using namespace std;

void GameAI::serve() {
    queue<string> outputs;
    for (string command; getline(cin, command);) {
        if (command == "Battle") {
            string moveName1;
            getline(cin, moveName1);

            BattlePokemon &pokemon1 = playerPokemonIt->second;
            BattlePokemon &pokemon2 = *opponentPokemonIt;
            Move &move1 = pokemon1.getMove(moveName1);

            //int damage1 = move1.calcDamage(pokemon1, pokemon2);
            calc();
        }
    }
}

Move& GameAI::atk( BattlePokemon& token, BattlePokemon& enemy){
    BattlePokemon &pokemon1 = enemy;
    BattlePokemon &pokemon2 = token;
    Move& temp = pokemon2.getMove("s");
    //get first move
    int maxDamage = 0;

    auto moves = pokemon2.getMoveMap();

    for(auto& move:moves){
        int damage = getDamage(move.second,pokemon1,pokemon2);
        if(pokemon2.hasStatus(Status::PARALYSIS)) damage *= 0.75;
        if(damage>maxDamage){
           // temp = move.second;
        }
    }
    return temp;
}


void GameAI::calc(){
    BattlePokemon &pokemon1 = playerPokemonIt->second;
    BattlePokemon &pokemon2 = *opponentPokemonIt;

    //heal
    Move& opponentMaxAct = atk(pokemon1,pokemon2);

    int maxOpponentDamage = getDamage(opponentMaxAct,pokemon1,pokemon2);

    if(maxOpponentDamage>pokemon2.getHp()){
        //use poision
        opponentUsePotion(pokemon2.getName(),"Hyper Potion");
    }

    // can kill
    Move& mineMaxAct = atk(pokemon2,pokemon1);

    if(getDamage(mineMaxAct,pokemon2,pokemon1) > pokemon1.getHp()){
        //TODO:do move
    }


    //the most damage
    int maxDamage;
    bool needSwap = 0;
    Pokemon temp = pokemon2 ;
    //Move t ;
    for(auto& pokemon:opponentPokemonList){
        Move& t = atk(pokemon1,pokemon);
        int cal = getDamage(t,pokemon,pokemon1);

        if(maxDamage<cal){
            maxDamage = cal;
            //mineMaxAct = t;
            //temp = pokemon;
        }
    }

    //if(temp!= pokemon2){
      //  opponentSwapPokemon(temp);
    //}
    //else {

        //TODO: do move
   // }
    //if (pokemon2.getHp() /  > pokemon1.getHp() / mineMaxAct.calcDamage(pokemon2,pokemon1))return;

}

int GameAI::getDamage(Move& move,Pokemon& attacker, Pokemon& defender) {
    const int baseDamage = move.calcBaseDamage(attacker, defender);
    const double stab = move.calcSTAB(defender.getTypeList());
    const double typeEffect = move.calcTypeEffect(defender.getTypeList());
    const int damage = static_cast<int>(baseDamage * stab * typeEffect);
    return damage;
}

