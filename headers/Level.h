#ifndef LEVEL_H

#define LEVEL_H

#include <string>
#include "GameOptions.h"
#include <vector>

struct Level {
    std::string id;
    std::string image_path;
    std::string description;
    std::vector<GameOption> options;
    
};

#endif //LEVEL_H