#include "SortedLetter.hpp"

#include <iostream>

LetSort::LetSort(char letter)
:count(1)
,fakeCount(1)
{
    if(letter < 65 || letter > 90)throw std::invalid_argument("Invalid letter!");
    this->letter = letter;
}

void LetSort::Addcount(){this->count++;}
void LetSort::setFake(){this->fakeCount = this->count;}
void LetSort::SubFcount(){this->fakeCount--;}

char LetSort::getLet() const {return this->letter;}
int LetSort::getCount() const {return this->count;}
int LetSort::getFCount() const {return this->fakeCount;}