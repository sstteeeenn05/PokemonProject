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

void GameManager::readPokemon(const string& path) {
    ifstream read(path);

    pokemonData.clear();

    string name;

    while(read>>name) {
        int typeNum;

        read >> typeNum;

        vector<Type> types;
        string typeStr;

        for (int i = 0; i < typeNum; i++) {
            read >> typeStr;
            types.push_back(TypeMap[typeStr]);
        }
        int hp, atk, def, spAtk, spDef, speed;
        read >> hp >> atk >> def >> spAtk >> spDef >> speed;

        pokemonData.insert(pair<string,Pokemon>(name, Pokemon(name, types, hp, atk, def, spAtk, spDef, speed, 1, 0)));
    }
}

void GameManager::readMove(const string& path) {
    ifstream read(path);

    string movePokemon, type, isPhysical;
    int power, accuracy , PP;

    while(read>>movePokemon) {
        read >> type >> isPhysical >> power >> accuracy >> PP;

        string con, conTemp;

        getline(read, con);

        stringstream ss(con);
        vector<string> cons;

        while (getline(ss, conTemp, ' ')) {
            cons.push_back(conTemp);
        }
        //TODO: save data format?
    }
}

void GameManager::readGame(const string& path) {
    ifstream read(path);

    int pokemonNum,skillNum;
    string name,skill;
    vector<string>skills;
    cin>>pokemonNum;
    //map<Pokemon,vector<string>>list;
    for(int i = 0 ; i < pokemonNum;i++){
        cin>>name>>skillNum;

        while(skillNum--){
            cin>>skill;
            skills.push_back(skill);
        }
        //list.insert(pokemonData[name],skills);

    }



    //TODO: Twice and Data Store?

}


void GameManager::run(){
    string command,path,name;
    while(cin>>command){
        try{
            if(command == "ReadLib"){
                cin>>path;
                readPokemon(path);
                // C:\Users\tomjojo\Desktop\PokemonSample\PokemonLib.txt
            }
            else if(command == "ReadMove"){
                cin>>path;
                readMove(path);
                //TODO :In frontEnd
            }
            else if(command == "ReadCase"){
                //TODO :In frontEnd
            }
            else if(command == "FightBegin"){
                cin>>name;
                // Fight function
            }
            else if(command == "FightMove"){
                
            }
            else if(command == "FightEnd"){

            }
            else {
                cout<<"unknown"<<endl;
            }
        }
        catch(commandError& e){
            cout<<command<<spilt<<"Fail"<<spilt<<endl;
        }
    }

}




















void GameManager::moveIO() {
    string atkPokemon,defPokemon,type, isPhysical,status;
    int power,accuracy;

    cin>>atkPokemon>>defPokemon>>type>>isPhysical>>power>>accuracy;
    // cin>>atkPokemon>>defPokemon>>skill?
    cout<<status;
    //TODO: (call Game.h move) or (be called and save data)?
}


void outPokemon(Pokemon data){
    cout<<data.name<<";";
    for(auto i:data.type)cout<<i<<";";
    cout<<data.hp<<";"<<data.atk<<";"<<data.def<<";"<<data.spAtk<<";"<<data.spDef<<";"<<data.speed<<";";
}
void GameManager::command(){
    string command,target;
    cin>>command;
    if(command == "getPokemon"){
        cin>>target;
        auto aim = pokemonData[target];
        outPokemon(aim);
    }
}

