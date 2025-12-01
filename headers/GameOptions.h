#ifndef GAME_OPTIONS_H

#define GAME_OPTIONS_H

#include <string>
#include <vector>

struct GameOption {
    std::vector<std::string> keywords;
    std::string target_id;
};

#endif //GAME_OPTIONS_H