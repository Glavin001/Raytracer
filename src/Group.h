#ifndef GROUP_H
#define GROUP_H


#include "Object3D.h"
#include "Ray.h"
#include "Hit.h"
#include <iostream>

using  namespace std;

///TODO:
///Implement Group
///Add data structure to store a list of Object*
class Group : public Object3D
{
public:

    Object3D** objects;
    int numObjects = 0;

    Group(){

    }

    Group( int num_objects ){
        numObjects = num_objects;
        objects = new Object3D*[num_objects];
    }

    ~Group(){
        delete [] objects;
    }

    virtual bool intersect( const Ray& r, Hit& h, float tmin ) {
        bool didInsersect = false;
        for (int i = 0; i < numObjects; i++) {
            if (objects[i]->intersect(r, h, tmin)) {
                didInsersect = true;
            }
        }
        return didInsersect;
    }

    void addObject( int index, Object3D* obj ){
        objects[index] = obj;
    }

    int getGroupSize(){
        return numObjects;
    }

private:

};

#endif
