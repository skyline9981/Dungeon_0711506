#include "Object.h"
#include <string>
#include <iostream>

Object::Object()
{}

Object::Object(string n,string t):name(n),tag(t)
{}

void Object::setName(string name)
{
    this->name=name;
}

void Object::setTag(string tag)
{
    this->tag=tag;
}

string Object::getName()
{
    return name;
}

string Object::getTag()
{
    return tag;
}

void Object::triggerEvent(Object * a){

}
