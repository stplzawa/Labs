#include <iostream>
#include <cstdlib>
#include "libbmp.h"

using namespace std;

enum RGB
{
    RED,
    GREEN,
    BLUE,
};

bool touchChar(BmpImg* img, int x, int y, RGB RGB, int& val, int& count)
{
    switch (RGB)
    {
    case RED:
        val = val + (img->red_at(x, y) % 2) * pow(2, count);
        return true;
    case GREEN:
        val = val + (img->green_at(x, y) % 2) * pow(2, count);
        return true;
    case BLUE:
        val = val + (img->blue_at(x, y) % 2) * pow(2, count);
        return true;
    }

}

bool check(int& count, int& val)
{
    if (count == 0)
    {
        if (char(val) == '\0') return false;
        cout << char(val);
        count = 8;
        val = 0;
    }
    return true;
}

int main()
{
    BmpImg img;
    img.read("pic2.bmp");
    int count = 7;
    int val = 0;

    for (int j = 0; j <= img.get_height() - 1; j++)
    {
        for (int i = 0; i <= img.get_width() - 1; i++)
        {
            if (!(touchChar(&img, i, j, RED, val, count) && check(count, val)))
                return 0;
            count--;

            if (!(touchChar(&img, i, j, GREEN, val, count) && check(count, val)))
                return 0;
            count--;

            if (!(touchChar(&img, i, j, BLUE, val, count) && check(count, val)))
                return 0;
            count--;
        }
    }
}
