#include<iostream>

using namespace std;

class Menu
{
    static void cls()
    {
        cout<<"Press enter to continue...";
        getchar();
        getchar();
        system("cls");
    }
    static void Options()
    {
        while(1)
        {
            cout<<"1. Change number of letters"<<endl<<"2. Change number of rounds"<<endl<<"3. Exit options"<<endl<<"Enter an action number:";
            int input;
            char trash;
            cin>>input;
            switch(input)
            {
                case 1:
                    cout<<"Enter new number of letters:";
                    cin>>Menu::letters;
                    cls();
                    break;
                case 2:
                    cout<<"Enter new number of rounds:";
                    cin>>Menu::rounds;
                    cls();
                    break;
                case 3:
                    return;
                default:
                    cout<<"Invalid input."<<endl;
                    cls();
                    break;
            }
        }
    }

public:


    static int MainMenu()
    {
        letters = 10;
        rounds = 10;
        while(1)
        {
            cout<<"1. Start new game"<<endl<<"2. Options"<<endl<<"3. Enter new word"<<endl<<"4. Exit"<<endl<<"Enter an action number:";
            int input;
            char trash;
            cin>>input;
            switch(input)
            {
                case 1:
                    return 1;
                case 2:
                    Options();
                    break;
                case 3:
                    //Enter new word
                    break;
                case 4:
                    return 0;
                default:
                    cout<<"Invalid input."<<endl;
                    cls();
                    break;
            }
        }
    }
    static int letters;
    static int rounds;
};
