#include<iostream>
#include<random>
#include<vector>
#include<time.h>
#include"SortedLetter.hpp"

class Game
{
public:
    static int Play(int &letterNum, int &rounds)
    {
        int points = 0;
        for(int i = 0; i < rounds; i++)
        {
            cout<<"Your given letters are: ";
            vector<LetSort> letters;
            for(int y = 0; y < letterNum; y++)
            {
                char tempC = rand() % 26 + 65;
                bool Nfound = 1;
                cout<<tempC<<" ";
                for(int z = 0; z < letters.size(); z++)
                {
                    if(tempC == letters[z].getLet())
                    {
                        letters[z].Addcount();
                        letters[z].setFake();
                        Nfound = 0;
                        break;
                    }
                }
                if(Nfound)
                {
                    LetSort temp(tempC);
                    temp.setFake();
                    letters.push_back(temp);
                }
            }
            cout<<endl<<"Enter a word with the given letters: ";
            string input;
            cin>>input;
            //Check if the word is Possible with given letters and if its a real word
        }
        return points;
    }
};
