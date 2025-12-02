#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip> 

#include "libs/json/include/nlohmann/json.hpp"

std::string get_input(const std::string& prompt) {
    std::cout << prompt;
    std::string line;
    getline(std::cin,line);
    return line;
}

std::vector<std::string> split_string(const std::string& str) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;

    while (ss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

int main() {
    std::string filename = "game_data.json";
    nlohmann::json game_data;

    std::ifstream file_in(filename);

    if(file_in.is_open()) {
        try {
            file_in >> game_data;
            std::cout << "Loaded existing game data (" << game_data.size() << " levels).\n" << std::endl;
        } catch (...) {
            std::cout << "Could not parse existing JSON. Starting fresh.\n" << std::endl;
            game_data = nlohmann::json::object();
        }
        file_in.close();
    } else {
        std::cout << "No existing file found. Creating new database.\n" << std::endl;
        game_data = nlohmann::json::object();
    }

    while(true) {
        std::cout << "\n--- LEVEL EDITOR ---\n" << std::endl;

        std::string id = get_input("Enter Level ID (e.g., 'dungeon_hall'): ");
        if (id.empty()) continue;
        if (game_data.contains(id)) {
            std::cout << "Warning: ID '" << id << "' already exists. Overwriting!\n" << std::endl;
        }

        std::string image = get_input("Image Filename (e.g., 'hall.jpg'): ");
        std::string desc = get_input("Room Description: ");
        std::string fail_msg = get_input("Fail Message (Optional, press Enter for default): ");

        nlohmann::json options_array = nlohmann::json::array();
        std::cout << "--- Adding Options (Type 'done' as keyword to finish options) ---\n" << std::endl;

        while(true) {
            std::string keywords_raw = get_input(" Keywords (space separated, e.g. 'open door'): ");
            if (keywords_raw == "done" || keywords_raw.empty()) break;

            std::string target = get_input(" Target Level ID (where does this go?): ");

            nlohmann::json opt;
            opt["keywords"] = split_string(keywords_raw);
            opt["next_level"] = target;
            options_array.push_back(opt);
            std::cout << " [Option Added]\n" << std::endl;
        }

        game_data[id] = {
            {"image", image},
            {"text", desc},
            {"options", options_array}
        };
        
        if (!fail_msg.empty()) {
            game_data[id]["fail_message"] = fail_msg;
        }

        std::ofstream file_out(filename);
        file_out << std::setw(4) << game_data << std::endl;
        std::cout << ">>> Level '" << id << "' saved to" << filename << "!\n" << std::endl;

        std::string cont = get_input("Add another level? (y/n): ");
        if (cont != "y" && cont != "Y") break;
    }
    return 0;
}