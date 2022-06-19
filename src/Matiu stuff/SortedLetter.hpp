#include<iostream>
#include<exception>

using namespace std;


class LetSort
{
    char letter;
    int count;
    int fakeCount;
public:
    LetSort(char letter)
    :count(1), fakeCount(1)
    {
        if(letter < 65 || letter > 90)throw invalid_argument("Invalid letter!");
        this->letter = letter;
    }
    void Addcount(){this->count++;}
    void setFake(){this->fakeCount = this->count;}
    void SubFcount(){this->fakeCount--;}

    char getLet() const {return this->letter;}
    int getCount() const {return this->count;}
    int getFCount() const {return this->fakeCount;}
};
