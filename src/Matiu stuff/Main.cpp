#include"Game.hpp"
#include"Menu.hpp"

using namespace std;

int Menu::letters;
int Menu::rounds;

int main()
{
    if(Menu::MainMenu())
    {
        cout<<Game::Play(Menu::letters, Menu::rounds);
    }

    return 0;
}
