#include "headers/GameManager.h"
#include "GameManager.h"
#include <iostream> 

using namespace std;
using json = nlohmann::json;

void GameManager::load_game_data(string filename)
{
    ifstream f(filename);
    
    if (!f.is_open()) {
        return; 
    }
    
    json data = json::parse(f);

    for (auto& [key, value] : data.items()) {
        Level lvl;
        lvl.id = key;
        
        // Make sure your JSON keys match these strings exactly
        lvl.image_path = value["image"];
        lvl.description = value["text"];

        for (auto& opt : value["options"]) {
            GameOption go;
            go.keywords = opt["keywords"];
            go.target_id = opt["next_level"]; 
            
            lvl.options.push_back(go);
        }

        all_levels[key] = lvl;
    }

    current_level_id = "start_room";
}

Level* GameManager::get_current_level()
{
    return &all_levels[current_level_id];
}

bool GameManager::process_input(string user_input) {
    Level* current = get_current_level();

    for (auto& option : current->options) {
        for(auto& keyword : option.keywords)
        {
            if (keyword == user_input) {
            current_level_id = option.target_id;
            return true;
        }
        }
    }
    return false;
}