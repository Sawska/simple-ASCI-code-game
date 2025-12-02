#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <map>
#include <string>
#include <fstream>
#include "Level.h" 
#include "../libs/json/include/nlohmann/json.hpp" 

class GameManager {
private:
    std::map<std::string, Level> all_levels;
    std::string current_level_id;

public: 
    void load_game_data(std::string filename);
    Level* get_current_level();
    bool process_input(std::string user_input);
};

#endif //GAME_MANAGER_H