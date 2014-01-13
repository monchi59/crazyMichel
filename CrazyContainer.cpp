/* 
 * File:   CrazyContainer.cpp
 * Author: monchi
 * 
 * Created on December 25, 2013, 11:54 PM
 */

#include "CrazyContainer.h"
#include "AsyncState.h"
#include <cstdlib>
#include "cflie/CCrazyflie.h"
#include "FL/Fl_Valuator.H"
#include <iostream>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/fl_ask.H>
#include "FLContainer.h"
#include <thread>
#include <cmath>
#include <fstream>
#include <chrono>
#include <ctime>
using namespace std;
CrazyContainer::CrazyContainer() {
    connected = false;
    crRadio = new CCrazyRadio("radio://0/10/250K");
    toDoList = new vector<AsyncState>();
}

CrazyContainer::~CrazyContainer() {
    kill();
    delete crRadio;
    connected = false;
}

CrazyContainer::CrazyContainer(CCrazyRadio* ncrRadio, CCrazyflie* ncflieCopter) {
    crRadio = ncrRadio;
    cflieCopter = ncflieCopter;
    connected = false;
    toDoList = new vector<AsyncState>();
}
void CrazyContainer::connect() {
    cout<<"Connection"<<endl;
   if (crRadio->startRadio()) {
        cflieCopter = new CCrazyflie(crRadio);
        connected = true;
        
        cflieCopter->setSendSetpoints(true);
        cflieCopter->cycle();
        cflieCopter->cycle();
        cflieCopter->cycle();
        
        loop();
    }
}
void CrazyContainer::kill(){
    delete cflieCopter;
}

void CrazyContainer::setPitch(double pitch) {
    if (isConnected()) {
        cflieCopter->setPitch(pitch);
    }
}

void CrazyContainer::setRoll(double roll) {
    if (isConnected()) {
        cflieCopter->setRoll(roll);
    }
}

void CrazyContainer::setThrust(double thrust) {
    cout<<"th:"<<thrust<<endl;
    if (isConnected()) {
        FLContainer::thrustOutput->value(thrust);
        cflieCopter->setThrust(thrust);
    }
}

void CrazyContainer::setYaw(double yaw) {
    if(yaw>180){
        yaw = yaw-360;
    }
    if (isConnected()) {
        cflieCopter->setYaw(yaw);
        cout<<"setyaw - "<<yaw<<endl;
    }
}
CCrazyflie* CrazyContainer::getCflieCopter() const {
        return cflieCopter;
    }

    void CrazyContainer::setCflieCopter(CCrazyflie* cflieCopter) {
        this->cflieCopter = cflieCopter;
    }

    bool CrazyContainer::isConnected() const {
        return connected;
    }

    void CrazyContainer::setConnected(bool connected) {
        this->connected = connected;
    }

    CCrazyRadio* CrazyContainer::getCrRadio() const {
        return crRadio;
    }

    void CrazyContainer::setCrRadio(CCrazyRadio* crRadio) {
        this->crRadio = crRadio;
    }
    void CrazyContainer::loop(){
        loopthread = new thread(&CrazyContainer::nloop,this);
    }
    
    double CrazyContainer::pulsePitch(double val){
        setPitch(val+offsetPitch);
        return val+offsetPitch;
    }
    double CrazyContainer::backPitch(){
        setPitch(offsetPitch);
        return offsetPitch;
    }
    
    double CrazyContainer::pulseRoll(double val){
        setRoll(val+offsetRoll);
        return val+offsetRoll;
    }
    double CrazyContainer::pulseThrust(double thrust){
        setThrust(thrust+offsetThrust);
        return thrust+offsetThrust;
    }
    
    void CrazyContainer::backThrust(){
        setThrust(offsetThrust);
    }
    
    double CrazyContainer::stopThrust(){
        setThrust(0);
        return 0;
    } 
    
    double CrazyContainer::backRoll(){
        setRoll(offsetRoll);
        return offsetRoll;
    }
    
    double CrazyContainer::getHighThrust() const {
        return highThrust;
    }

    void CrazyContainer::setHighThrust(double highThrust) {
        this->highThrust = highThrust;
    }

    thread* CrazyContainer::getLoopthread() const {
        return loopthread;
    }

    void CrazyContainer::setLoopthread(thread* loopthread) {
        this->loopthread = loopthread;
    }

    double CrazyContainer::getLowThrust() const {
        return lowThrust;
    }

    void CrazyContainer::setLowThrust(double lowThrust) {
        this->lowThrust = lowThrust;
    }

    double CrazyContainer::getOffsetPitch() const {
        return offsetPitch;
    }

    void CrazyContainer::setOffsetPitch(double offsetPitch) {
        this->offsetPitch = offsetPitch;
        FLContainer::offsetPitch->value(this->offsetPitch);
    }
    void CrazyContainer::addOffsetPitch(double offsetPitch) {
        this->offsetPitch += offsetPitch;
        cout<<"pitch : "<<this->offsetPitch<<endl;
        FLContainer::offsetPitch->value(this->offsetPitch);
    }

    double CrazyContainer::getOffsetRoll() const {
        return offsetRoll;
    }

    void CrazyContainer::setOffsetRoll(double offsetRoll) {
        this->offsetRoll = offsetRoll;
        FLContainer::offsetRoll->value(this->offsetRoll);
    }
    void CrazyContainer::addOffsetRoll(double offsetRoll) {
        this->offsetRoll += offsetRoll;
        cout<<"roll : "<<this->offsetRoll<<endl;
        FLContainer::offsetRoll->value(this->offsetRoll);
    }

    double CrazyContainer::getOffsetThrust() const {
        return offsetThrust;
    }

    void CrazyContainer::setOffsetThrust(double offsetThrust) {
        this->offsetThrust = offsetThrust;
    }
    void CrazyContainer::loadXML(){
        offsetPitch = 0.2;
        offsetRoll = 2.0;
        offsetThrust = 39000;
    }
    void CrazyContainer::saveXML(){
    }

void CrazyContainer::addToDoList(AsyncState* waiting) {
    toDoList->push_back(*waiting);
}

vector<AsyncState>* CrazyContainer::getToDoList() const {
    return toDoList;
}

void CrazyContainer::setToDoList(vector<AsyncState>* toDoList) {
    this->toDoList = toDoList;
}
void CrazyContainer::nloop() {
    int i =0;
    ofstream out("out.txt");
    //clock_t c_start = clock();
    auto t_start = chrono::high_resolution_clock::now();
    while (connected && cflieCopter->cycle()) {
        if(keepYaw&&(abs(cflieCopter->yaw()-yaw)>5)){
            cflieCopter->setYaw(yaw);
        }
        //clock_t c_end = clock();
        auto t_end = chrono::high_resolution_clock::now();
        auto elapsed = t_end - t_start;
        out<<elapsed.count()<<" "<<cflieCopter->accX()<<" "<<cflieCopter->accY()<<endl;
        if(i++%100==0){
            i=1;
            FLContainer::pitch->value(cflieCopter->pitch());
            FLContainer::yaw->value(cflieCopter->yaw());
            FLContainer::roll->value(cflieCopter->roll());
            
        }
        if(toDoList->size()>0){
            for (int i=0;i<toDoList->size();i++)
            {
                AsyncState* todo = &toDoList->at(i);
                cout<<"yep "<<todo->GetTicks()<<"-"<<todo->GetType()<<endl;
                if(todo->GetTicks()==0){
                    switch(todo->GetType()){
                        case Pitch:
                            pulsePitch(todo->GetValue());
                            break;
                        case Roll:
                            pulseRoll(todo->GetValue());
                            break;
                        case Thrust:
                            cout<<"thrust - "<<pulseThrust(todo->GetValue())<<endl;
                            break;
                        case Yaw:
                            break;
                    }
                    toDoList->erase(toDoList->begin()+i);
                    i--;
                }else{
                    todo->DecreaseTicks();
                }
            }
        }
    }
    connected = false;
    delete cflieCopter;
}

bool CrazyContainer::isKeepYaw() const {
    return keepYaw;
}

void CrazyContainer::setKeepYaw(bool keepYaw) {
    cout << keepYaw << " - " << cflieCopter->yaw() << endl;
    this->keepYaw = keepYaw;
}

void CrazyContainer::setYawVar(double yaw) {
    if(yaw>180){
        yaw = yaw-360;
    }
    this->yaw = yaw;
}
