#include "Game.h"


int main(int argc, char* argv[]) {
    Game *game = nullptr;
    game = new Game();
    game->init("game_engine", 800, 600, false);
    while(game->running()) {
        game->handle_events();
        game->update();
        game->render();
    }

    game->clean();

    return 0;
}