#pragma once

class LetSort
{
    char letter;
    int count;
    int fakeCount;
public:
    LetSort(char letter);
    void Addcount();
    void setFake();
    void SubFcount();

    char getLet() const;
    int getCount() const;
    int getFCount() const;
};