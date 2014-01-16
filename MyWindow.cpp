/* 
 * File:   MyWindow.cpp
 * Author: monchi
 * 
 * Created on December 26, 2013, 12:49 PM
 */

#include "MyWindow.h"
#include<iostream>
using namespace std;
MyWindow::MyWindow():Fl_Window(1000, 800, "Crazyyyy") {
}
MyWindow::~MyWindow() {
}
int backThrust(CrazyContainer * container){
    container->backThrust();
    return 0;
}
int MyWindow::handle(int e) {
    int key;
    switch(e){
        case FL_KEYDOWN:
            key = Fl::event_key();
            cout<<"down : "<< key <<endl;
            double yaw;
            switch(key){
                case 32://space
                case 118:
                case 98:
                case 110:
                    cout<<"stop"<<endl;
                    crazyContainer->stopThrust();
                    break;
                    
                case 107://K
                    //crazyContainer->pulseThrust(6835);
                    crazyContainer->setOscilating(!crazyContainer->isOscilating());
                    /*crazyContainer->addToDoList(new AsyncState(Thrust,10000,100));
                    crazyContainer->addToDoList(new AsyncState(Thrust,0,200));
                    crazyContainer->addToDoList(new AsyncState(Pitch,12.5,100));
                    crazyContainer->addToDoList(new AsyncState(Pitch,0,200));
                    crazyContainer->addToDoList(new AsyncState(Thrust,7000,500));
                    crazyContainer->addToDoList(new AsyncState(Thrust,0,600));
                    crazyContainer->addToDoList(new AsyncState(Pitch,-12.5,500));
                    crazyContainer->addToDoList(new AsyncState(Pitch,0,600));
                    crazyContainer->addToDoList(new AsyncState(Thrust,7000,1000));
                    crazyContainer->addToDoList(new AsyncState(Thrust,0,1100));
                    crazyContainer->addToDoList(new AsyncState(Pitch,-12.5,1200));
                    crazyContainer->addToDoList(new AsyncState(Pitch,0,1300));
                    crazyContainer->addToDoList(new AsyncState(Roll,-12.5,1500));
                    crazyContainer->addToDoList(new AsyncState(Roll,0,1600));
                    crazyContainer->addToDoList(new AsyncState(Thrust,7000,1600));
                    crazyContainer->addToDoList(new AsyncState(Thrust,0,1700));
                    crazyContainer->addToDoList(new AsyncState(Roll,12.5,1700));
                    crazyContainer->addToDoList(new AsyncState(Roll,0,1800));
                    crazyContainer->addToDoList(new AsyncState(Roll,12.5,1900));
                    crazyContainer->addToDoList(new AsyncState(Roll,0,2000));*/
                    break;
                case 65362://up
                    crazyContainer->pulsePitch(12.5);
                    break;
                case 65363://right
                    crazyContainer->pulseRoll(12.5);
                    break;
                case 65361://left
                    crazyContainer->pulseRoll(-12.5);
                    break;
                case 65364://Down
                    crazyContainer->pulsePitch(-12.5);
                    break;
                    
                case 101://E
                    crazyContainer->pulseThrust(15000);
                    break;
                case 102://F
                    crazyContainer->setOscilThurst(crazyContainer->getOscilThurst()+100);
                    //crazyContainer->setOffsetThrust(crazyContainer->getOffsetThrust()+300);
                    //crazyContainer->backThrust();
                    break;
                case 115://S
                    //crazyContainer->setOffsetThrust(crazyContainer->getOffsetThrust()-300);
                    crazyContainer->setOscilThurst(crazyContainer->getOscilThurst()-100);
                    //crazyContainer->backThrust();
                    break;
                
                case 104://H
                    //crazyContainer->setRoll(180);
                    break;
                    
                case 100://D
                    crazyContainer->setThrust(crazyContainer->getOffsetThrust()+10000);
                    break;
                case 99://C
                    crazyContainer->pulseThrust(-25000);
                    break;
                
                case 65464://up numpad
                    crazyContainer->addOffsetPitch(0.2);
                    crazyContainer->backPitch();
                    break;
                case 65462://right numpad
                    crazyContainer->addOffsetRoll(0.2);
                    crazyContainer->backRoll();
                    break;
                case 65460://left numpad
                    crazyContainer->addOffsetRoll(-0.2);
                    crazyContainer->backRoll();
                    break;
                case 65458://Down numpad
                    crazyContainer->addOffsetPitch(-0.2);
                    crazyContainer->backPitch();
                    break;
                
                case 42://*
                    crazyContainer->setYawVar(crazyContainer->getCflieCopter()->yaw());
                    break;
                
                case 65506:
                    crazyContainer->setKeepYaw(!crazyContainer->isKeepYaw());
                    break;
                case 33://!
                    yaw = crazyContainer->getCflieCopter()->yaw()-10;
                    crazyContainer->setYawVar(yaw);
                    crazyContainer->setYaw(yaw);
                    break;
                case 65457://1
                    yaw = crazyContainer->getCflieCopter()->yaw()+10;
                    crazyContainer->setYawVar(yaw);
                    crazyContainer->setYaw(yaw);
                    break;
                case 249:
                    crazyContainer->setYaw(0);
                    break;
            }
            break;
        case FL_KEYUP:
            key = Fl::event_key();
            switch(key){
                
                case 101://E
                    crazyContainer->backThrust();
                    break;
                case 100://D
                   // crazyContainer->addToDoList(new AsyncState(Thrust,0,100));
                   // crazyContainer->pulseThrust(10000);
                    break;
                case 65362://up
                    //crazyContainer->addToDoList(new AsyncState(Pitch,0,50));
                    //crazyContainer->pulsePitch(-6.5);
                    crazyContainer->backPitch();
                    break;
                case 65363://right
                case 104:
                    //crazyContainer->addToDoList(new AsyncState(Roll,0,50));
                    //crazyContainer->pulseRoll(-6.5);
                    crazyContainer->backRoll();
                    break;
                case 65361://left
                    //crazyContainer->addToDoList(new AsyncState(Roll,0,50));
                    //crazyContainer->pulseRoll(6.5);
                    crazyContainer->backRoll();
                    break;
                case 65364://Down
                    //crazyContainer->addToDoList(new AsyncState(Pitch,0,50));
                    //crazyContainer->pulsePitch(6.5);
                    crazyContainer->backPitch();
                    break;
            }
            cout<<"up : "<< Fl::event_key() <<endl;
            break;
        default:
            Fl_Window::handle(e);
            break;
    }
}

MyWindow::MyWindow(int width, int height):Fl_Window(width, height, "Crazyyyy") {

}

CrazyContainer* MyWindow::getCrazyContainer() const {
    return crazyContainer;
}

void MyWindow::setCrazyContainer(CrazyContainer* container) {
    this->crazyContainer = container;
}
