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
#include <vector>
#include <list>
#include <cmath>
#include <fstream>
#include <chrono>
#include <ctime>
#include "gnuplot-iostream.h"
#include "MartinsIntegrator.h"
#include "Integrator.h"
#include "PIDCorrector.h"

using namespace std;

CrazyContainer::CrazyContainer() {
    connected = false;
    crRadio = new CCrazyRadio("radio://0/10/1M");
    toDoList = new vector<AsyncState > ();
    oscilThurst = 0;
    plotting = false;
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
    toDoList = new vector<AsyncState > ();
}

void CrazyContainer::connect() {
    cout << "Connection" << endl;
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

void CrazyContainer::kill() {
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
    cout << "th:" << thrust << endl;
    if (isConnected()) {
        FLContainer::thrustOutput->value(thrust);
        cflieCopter->setThrust(thrust);
    }
}

void CrazyContainer::setYaw(double yaw) {
    if (yaw > 180) {
        yaw = yaw - 360;
    }
    if (isConnected()) {
        cflieCopter->setYaw(yaw);
        cout << "setyaw - " << yaw << endl;
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

void CrazyContainer::loop() {
    loopthread = new thread(&CrazyContainer::nloop, this);
}

double CrazyContainer::pulsePitch(double val) {
    setPitch(val + offsetPitch);
    return val + offsetPitch;
}

double CrazyContainer::backPitch() {
    setPitch(offsetPitch);
    return offsetPitch;
}

double CrazyContainer::pulseRoll(double val) {
    setRoll(val + offsetRoll);
    return val + offsetRoll;
}

double CrazyContainer::pulseThrust(double thrust) {
    setOscilating(false);
    setHovering(false);
    setThrust(thrust + offsetThrust);
    return thrust + offsetThrust;
}

void CrazyContainer::backThrust() {
    setOscilating(false);
    setHovering(false);
    setThrust(offsetThrust);
}

double CrazyContainer::stopThrust() {
    setOscilating(false);
    setHovering(false);
    setThrust(0);
    return 0;
}

double CrazyContainer::backRoll() {
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
    cout << "pitch : " << this->offsetPitch << endl;
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
    cout << "roll : " << this->offsetRoll << endl;
    FLContainer::offsetRoll->value(this->offsetRoll);
}

double CrazyContainer::getOffsetThrust() const {
    return offsetThrust;
}

void CrazyContainer::setOffsetThrust(double offsetThrust) {
    this->offsetThrust = offsetThrust;
}

void CrazyContainer::loadXML() {
    offsetPitch = 0.2;
    offsetRoll = 2.0;
    offsetThrust = 39000;//41500;//39000
}

void CrazyContainer::saveXML() {
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
    MartinsIntegrator *integrator = new MartinsIntegrator();
    PIDCorrector* corrector = new PIDCorrector();
    Gnuplot gp;
    list<pair<double, double> > plotAccX;
    list<pair<double, double> > plotAccY;
    list<pair<double, double> > plotAccZ;
    
    list<pair<double, double> > plotCAccZ;

    list<pair<double, double> > plotAccXm;
    list<pair<double, double> > plotAccYm;

    list<pair<double, double> > plotX;
    list<pair<double, double> > plotY;

    list<pair<double, double> > plotXm;
    list<pair<double, double> > plotYm;

    list<pair<double, double> > plotVX;
    list<pair<double, double> > plotVY;

    list<pair<double, double> > plotVXm;
    list<pair<double, double> > plotVYm;
    
    plotY.push_back(std::make_pair(0, 0));
    plotYm.push_back(std::make_pair(0, 0));
     
    int i = 0;
    int nbPoints = 0;
    int nbPointsPosition =0;
    int nbZ = 0;
    double lastX = 0;
    double lastXm = 0;
    double lastY = 0;
    double lastYm = 0;
    double corrected;
    double lastZ = 0;
    
    ofstream out("out.dat");
    //clock_t c_start = clock();
    double last = 0;
    double lastProx = 0;
    auto t_start = chrono::high_resolution_clock::now();
    auto t_last = chrono::high_resolution_clock::now();
    while (connected && cflieCopter->cycle()) {
        if (keepYaw && (abs(cflieCopter->yaw() - yaw) > 5)) {
            cflieCopter->setYaw(yaw);
        }
        //clock_t c_end = clock();
        auto t_end = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = chrono::duration_cast < chrono::duration<double >> (t_end - t_start);
        //out<<elapsed.count()<<" "<<cflieCopter->accX()<<" "<<cflieCopter->accY()<<endl;

        if (cflieCopter->accX() != last) {
            chrono::duration<double> elapsed2 = chrono::duration_cast < chrono::duration<double >> (t_end - t_last);
            last = cflieCopter->accX();
            //cout<<1/elapsed2.count()<<" "<<last<<endl;
            t_last = t_end;
            if (plotting&&false) {
                


                integrator->integrate(cflieCopter->accX(), cflieCopter->accY(), elapsed.count());
                //out<<elapsed.count()<<" "<<integrator->x<<" "<<integrator->y<<endl;
                if (nbPoints++ % 10 == 0) {
                    plotAccX.push_back(std::make_pair(elapsed.count(), cflieCopter->accX()));
                    plotAccY.push_back(std::make_pair(elapsed.count(), cflieCopter->accY()));
                    
                    //plotAccZ.push_back(std::make_pair(elapsed.count(), cflieCopter->accZ()));
                    
                    plotAccXm.push_back(std::make_pair(elapsed.count(), integrator->ax1m));
                    plotAccYm.push_back(std::make_pair(elapsed.count(), integrator->ay1m));

                    plotVX.push_back(std::make_pair(elapsed.count(), integrator->vx1));
                    plotVXm.push_back(std::make_pair(elapsed.count(), integrator->vx1m));
                    plotVY.push_back(std::make_pair(elapsed.count(), integrator->vy1));
                    plotVYm.push_back(std::make_pair(elapsed.count(), integrator->vy1m));

                    //plotX.push_back(std::make_pair(elapsed.count(),integrator->x1));
                    //plotXm.push_back(std::make_pair(elapsed.count(),integrator->x1m));
                    if(integrator->x1!=lastX|| integrator->y1 != lastY || integrator->x1m!=lastXm || integrator->y1m != lastYm){
                        lastX = integrator->x1;
                        lastXm = integrator->x1m;
                        lastY = integrator->y1;
                        lastYm = integrator->y1m;
                        
                        plotY.push_back(std::make_pair(integrator->x1, integrator->y1));
                        plotYm.push_back(std::make_pair(integrator->x1m, integrator->y1m));
                        nbPointsPosition++;
                    }




                    gp << "set multiplot layout 3,2;set yrange [-1:1];set autoscale x; plot" << gp.file1d(plotAccX) << "with lines title 'Accelerometer x'," << gp.file1d(plotAccY) << " with lines title 'Accelerometer y';" <<
                            "plot" << gp.file1d(plotAccXm) << "with lines title 'Accelerometer smoothed x'," << gp.file1d(plotAccYm) << " with lines title 'Accelerometer smoothed y';"
                            << "set autoscale y;plot" << gp.file1d(plotVX) << "with lines title 'Speed x'," << gp.file1d(plotVY) << " with lines title 'Speed y';"
                            << "plot" << gp.file1d(plotVXm) << "with lines title 'Speed smoothed x'," << gp.file1d(plotVYm) << " with lines title 'Speed smoothed y';"
                            //<<"plot" << gp.file1d(plotX) << "with lines title 'Position x',"<< gp.file1d(plotY) <<" with lines title 'Position x/y';"
                            //<<"plot" << gp.file1d(plotXm) << "with lines title 'Position smoothed x',"<< gp.file1d(plotYm) <<" with lines title 'Position smoothed x/y';"
                            << "set yrange [-0.3:0.3];set xrange [-0.3:0.3];plot" << gp.file1d(plotY) << " with lines title 'Position x/y';"
                            << "plot" << gp.file1d(plotYm) << " with lines title 'Position smoothed x/y';"
                            //<<"set yrange [-10:10];plot" << gp.file1d(plotAccZ) <<  "with lines title 'Accelerometer z';"
                            << endl;
                    if (nbPoints > 1000) {
                        
                        plotAccX.pop_front();
                        plotAccY.pop_front();
                        //plotAccZ.pop_front();

                        plotAccXm.pop_front();
                        plotAccYm.pop_front();

                        plotVX.pop_front();
                        plotVXm.pop_front();
                        plotVY.pop_front();
                        plotVYm.pop_front();
                    }
                    if (nbPointsPosition > 1000) {
                        plotX.pop_front();
                        plotXm.pop_front();
                        plotY.pop_front();
                        plotYm.pop_front();
                    }
                }

            }else if(!plotAccX.empty()){
                plotAccX.clear();
                plotAccY.clear();
                plotAccXm.clear();
                plotAccYm.clear();

                plotVX.clear();
                plotVXm.clear();
                plotVY.clear();
                plotVYm.clear();
                plotAccY.clear();
                //plotX.push_back(std::make_pair(elapsed.count(),integrator->x1));
                //plotXm.push_back(std::make_pair(elapsed.count(),integrator->x1m));
                plotY.clear();
                plotYm.clear();
                integrator->reset();
            }
        }
        
        if (cflieCopter->accZ() != lastZ) {
            /*if(fabs(cflieCopter->pitch())<5&&fabs(cflieCopter->roll())<5){
                double prox = cflieCopter->prox();
                if(fabs(lastProx-prox)>5){//5
                    lastProx = prox;
                }
                if(lastProx-prox>20){//4
                    givenCorrection = 0.35;
                }else if(lastProx-prox>15){//3
                    givenCorrection = 0.25;
                }else if(lastProx-prox>10){//2
                    givenCorrection = 0.15;
                }else if(lastProx-prox>5){//1
                    givenCorrection = 0.10;
                }else if(lastProx < prox){//<
                    givenCorrection = -0.10;
                }else{
                    givenCorrection =0;
                }
            }*/
            
            lastZ = cflieCopter->accZ();
            int correctionOffset = 14000;//15000
            if(hovering){
                corrected = corrector->PID(1,cflieCopter->accZ()-givenCorrection);
            }
            if(plotting){
                nbZ++;
                plotAccZ.push_back(std::make_pair(elapsed.count(), cflieCopter->accZ()));
                plotCAccZ.push_back(std::make_pair(elapsed.count(), correctionOffset*corrected));
                if(nbZ%100==0){
                        gp << "set multiplot layout 2,1;plot" << gp.file1d(plotAccZ) << "with lines title 'Accelerometer z';plot " << gp.file1d(plotCAccZ) << "with lines title 'Corrector';"<<endl;
                }
                if(nbZ>500){
                    plotAccZ.pop_front();
                    plotCAccZ.pop_front();
                }
            }else if(!plotAccZ.empty()){
                plotAccZ.clear();
                plotCAccZ.clear();
            }else if(hovering){
                out<<elapsed.count()<<" "<<cflieCopter->accZ()<<" "<<corrected<<" "<<corrector->avg<<endl;
            }
                
            
            if(hovering){
                setThrust(offsetThrust+correctionOffset*corrected);
            }else{
                //corrector->Old_R = 1;
            }
        }
       // cout<<cflieCopter->prox()<<endl;

        //out<<elapsed.count()<<" "<<cflieCopter->batteryLevel()<<" "<<endl;
        if (i++ % 100 == 0) {
            i = 1;
            FLContainer::pitch->value(cflieCopter->pitch());
            FLContainer::yaw->value(cflieCopter->yaw());
            FLContainer::roll->value(cflieCopter->roll());
            if (oscilating) {
                if (up) {
                    setThrust(offsetThrust + 7200 + oscilThurst);
                } else {
                    setThrust(offsetThrust + 5800 + oscilThurst);
                }
                up = !up;
                cout << up << endl;
            }
        }

        if (toDoList->size() > 0) {
            for (int i = 0; i < toDoList->size(); i++) {
                AsyncState* todo = &toDoList->at(i);
                cout << "yep " << todo->GetTicks() << "-" << todo->GetType() << endl;
                if (todo->GetTicks() == 0) {
                    switch (todo->GetType()) {
                        case Pitch:
                            pulsePitch(todo->GetValue());
                            break;
                        case Roll:
                            pulseRoll(todo->GetValue());
                            break;
                        case Thrust:
                            cout << "thrust - " << pulseThrust(todo->GetValue()) << endl;
                            break;
                        case Yaw:
                            break;
                    }
                    toDoList->erase(toDoList->begin() + i);
                    i--;
                } else {
                    todo->DecreaseTicks();
                }
            }
        }
        if (cflieCopter->batteryLevel() <= 3.1) {
            cout << "Warning low battery !" << endl;
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
    if (yaw > 180) {
        yaw = yaw - 360;
    }
    this->yaw = yaw;
}
