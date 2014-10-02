#ifndef __OBJECT_H__
#define __OBJECT_H__ 

struct Object
{
    int x,y;
    virtual char getSymb() = 0;
};

#endif
