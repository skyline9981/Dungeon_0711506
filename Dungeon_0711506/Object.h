#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Object
{
private:
    string name;
    string tag;
public:
    Object();
    Object(string,string);

    /* pure virtual function */
    virtual void triggerEvent(Object *) ;

    /* Setter & Getter*/
    void setName(string);
    void setTag(string);
    string getName();
    string getTag();

    virtual void access(){} ;
};

#endif // OBJECT_H_INCLUDED
