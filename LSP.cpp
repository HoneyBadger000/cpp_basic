//Liskov substitution principle
// It shall always be possbile to replace a derived classes's function in a base class

#include<iostream>


using namespace std;

class Rectangle{
    int width, height;

    void setWidth(int width){
        width = width;
    }

    void setheight(int height){
        height = height;
    }

    int getWidth(){
        return width;
    }

    int getHeight(){
        return height;
    }



};


int main(){

    return 0;
}