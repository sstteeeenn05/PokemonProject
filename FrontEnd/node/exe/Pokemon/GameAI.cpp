#include "GameAI.h"

#include <sstream>

using namespace std;

void GameAI::serve(std::ostream&) {
    stringstream stream;
    for (string command; getline(input, command); flushOutputs(stream)) {
        if (command == "Status") {
            outputStatus();
            continue;
        } else if (command == "Check") {
            outputCheck();
            continue;
        } else if (command == "Run") {
            break;
        }

        if (command == "Battle") {
           battle();
        }else {
            throw InvalidCommandError("unknown command " + command);
        }
    }
    flushOutputs(stream);
    cout << stream.str() << endl;
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


void GameAI::battle(){
    BattlePokemon &pokemon1 = playerPokemonIt->second;
    BattlePokemon &pokemon2 = *opponentPokemonIt;

    //heal
    Move& opponentMaxAct = atk(pokemon1,pokemon2);

    int maxOpponentDamage = getDamage(opponentMaxAct,pokemon1,pokemon2);

    if(maxOpponentDamage>pokemon2.getHp()){
        //use potion
        opponentUsePotion(pokemon2.getName(),"Hyper Potion");
    }

    // can kill
    Move& mineMaxAct = atk(pokemon2,pokemon1);

    const int damage = getDamage(mineMaxAct,pokemon2,pokemon1);

    mineMaxAct.use();
    bool isOpponent = true;
    outputMove(pokemon2.getName(), mineMaxAct.getName(), isOpponent);
    if (pokemon2.hasStatus(Status::PARALYSIS)) {
        outputParalyzed(pokemon2.getName(), isOpponent);
        //return false;
    }

    const int baseDamage = mineMaxAct.calcBaseDamage(pokemon2, pokemon1);
    const double stab = mineMaxAct.calcSTAB(pokemon1.getTypeList());
    const double typeEffect = mineMaxAct.calcTypeEffect(pokemon1.getTypeList());
    outputTypeEffect(typeEffect);

    if (mineMaxAct.getAdditionalEffect() != Status::NONE) {
        pokemon1.addStatus(mineMaxAct.getAdditionalEffect());
        outputAdditionalEffect(pokemon2.getName(), mineMaxAct.getAdditionalEffect(), isOpponent);
    }


    pokemon1.damage(damage);





/*
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
*/
}

int GameAI::getDamage(Move& move,Pokemon& attacker, Pokemon& defender) {
    const int baseDamage = move.calcBaseDamage(attacker, defender);
    const double stab = move.calcSTAB(defender.getTypeList());
    const double typeEffect = move.calcTypeEffect(defender.getTypeList());
    const int damage = static_cast<int>(baseDamage * stab * typeEffect);
    return damage;
}
