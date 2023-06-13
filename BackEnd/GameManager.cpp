//
// Created by tomjojo on 2023/6/3.
//
#include "GameManager.h"

//command type
//"command name";
//"success/ fail;
//<"data">

vector<string> spilt(string str, char tar){
    vector<string> ans;
    string temp;
    bool check = false;
    for(auto c:str){
        if(!check && c == tar){
            check = true;
        }
        else if(check && c == tar){
            ans.push_back(temp);
            temp.clear();
            check = false;
        }
        else if(check){
            temp += c;
        }
    }
    return ans;
}


void GameManager::readMove() {
    string atkPokemon,defPokemon, type, PP, con, conTemp;
    bool isPhysical;
    int power, accuracy;

    cin >> atkPokemon >> defPokemon >> type >> isPhysical >> power >> accuracy >> PP;

    vector<string> cons;

    while (getline(cin, conTemp, ' ')) {
        cons.push_back(conTemp);
    }

    output = game.move(atkPokemon,defPokemon,TypeMap[type],isPhysical,power,accuracy,StatusMap[PP]);
}

Pokemon GameManager::readPokemon(){
    string name,typeStr;
    int typeNum, hp, atk, def, spAtk, spDef, speed;
    vector<Type> types;

    cin >> name >> typeNum;

    for (int i = 0; i < typeNum; i++) {
        cin >> typeStr;
        types.push_back(TypeMap[typeStr]);
    }
    cin >> hp >> atk >> def >> spAtk >> spDef >> speed;

    return {name, types,hp,atk,def,spAtk,spDef,speed};
}

void GameManager::run(){
    string command,path,name;

    while(cin>>command){
        try{
            if(command == "FightBegin"){
                game.init(readPokemon(), readPokemon());
            }
            else if(command == "FightMove"){
                readMove();
                cout<<command<<spilt<<"success"<<spilt;
                outputCommand();
            }
            else if(command == "FightEnd"){
                game.reset();

            }
            else {
                cout<<"unknown"<<spilt;
            }
        }
        catch(commandError& e){
            cout<<command<<spilt<<"Fail"<<spilt;
        }
        cout<<endl;
    }

}


void GameManager::outputCommand() {
    while(!output.empty()){
        cout<<output.front()<<spilt;
        output.pop();
    }
}


void outPokemon(Pokemon data){
    cout<<data.name<<";";
    for(auto i:data.type)cout<<i<<";";
    cout<<data.hp<<";"<<data.atk<<";"<<data.def<<";"<<data.spAtk<<";"<<data.spDef<<";"<<data.speed<<";";
}
