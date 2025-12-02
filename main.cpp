#include <iostream>
#include <string>
#include <cstdlib> 

#include "headers/ImageParser.h"
#include "headers/GameManager.h"

void clear_screen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int main() {
    GameManager game;
    ImageParser img_parser;

    game.load_game_data("game_data.json");

    std::string user_input;
    std::string error_message = ""; 

    while (true) {
        Level* current_lvl = game.get_current_level();

        clear_screen();

        img_parser.load_image(current_lvl->image_path);
        img_parser.render_ascii(); 

        std::cout << "\n========================================\n";
        std::cout << current_lvl->description << "\n";
        std::cout << "========================================\n";

        if (current_lvl->options.empty()) {
            std::cout << "\n   GAME OVER   \n";
            std::cout << "Type 'quit' to exit or 'restart' to play again.\n> ";
            std::cin >> user_input;

            if (user_input == "restart") {
                game.load_game_data("game_data.json"); 
                continue;
            } else {
                break; 
            }
        }

        std::cout << "Available Actions:\n";
        for (size_t i = 0; i < current_lvl->options.size(); i++) {

            if (!current_lvl->options[i].keywords.empty()) {
                std::cout << " " << i + 1 << ". " << current_lvl->options[i].keywords[0] << "\n";
            }
        }

        if (!error_message.empty()) {
            std::cout << "\n[!] " << error_message << "\n";
            error_message = ""; 
        }

        std::cout << "\n> ";
        std::cin >> user_input;

        if (user_input == "quit" || user_input == "exit") {
            break;
        }

        bool success = game.process_input(user_input);
        
        if (!success) {
            error_message = "I don't know how to '" + user_input + "'. Try again.";
        }
    }

    std::cout << "Thanks for playing!\n";
    return 0;
}