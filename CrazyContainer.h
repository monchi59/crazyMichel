/* 
 * File:   CrazyContainer.h
 * Author: monchi
 *
 * Created on December 25, 2013, 11:54 PM
 */


#ifndef CRAZYCONTAINER_H
#define	CRAZYCONTAINER_H

#include <cstdlib>
#include "cflie/CCrazyflie.h"
#include "AsyncState.h"
#include <iostream>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/fl_ask.H>
#include <thread>
#include <vector>
using namespace std;

class CrazyContainer {
public:
    CrazyContainer();
    CrazyContainer(CCrazyRadio *crRadio,CCrazyflie *cflieCopter);
    virtual ~CrazyContainer();
    
    void connect();
    void kill();
    void setThrust(double thrust);
    void setYaw(double yaw);
    void setYawVar(double yaw);
    void setPitch(double pitch);
    void setRoll(double roll);
    CCrazyflie* getCflieCopter() const;

    void setCflieCopter(CCrazyflie* cflieCopter);

    bool isConnected() const;
    void setConnected(bool connected);

    CCrazyRadio* getCrRadio() const;

    void setCrRadio(CCrazyRadio* crRadio) ;
    void loop();
    double pulsePitch(double val);
    double backPitch();
    double pulseRoll(double val);
    double pulseThrust(double thrust);
    void backThrust();
    
    double stopThrust();
    
    double backRoll();
    double getHighThrust() const;
    void setHighThrust(double highThrust) ;
    thread* getLoopthread() const;
    void setLoopthread(thread* loopthread);
    double getLowThrust() const ;
    void setLowThrust(double lowThrust) ;
    double getOffsetPitch() const ;
    void setOffsetPitch(double offsetPitch);
    void addOffsetPitch(double offsetPitch);

    double getOffsetRoll() const ;
    void setOffsetRoll(double offsetRoll) ;
    void addOffsetRoll(double offsetRoll) ;
    double getOffsetThrust() const ;

    void setOffsetThrust(double offsetThrust);
    void loadXML();
    void saveXML();
    vector<AsyncState> * getToDoList() const;
    void setToDoList(vector<AsyncState>* toDoList);
    void addToDoList(AsyncState* waiting);
    bool isKeepYaw() const;

    void setKeepYaw(bool keepYaw);

    bool isOscilating() const {
        return oscilating;
    }

    void setOscilating(bool oscilating) {
        this->oscilating = oscilating;
    }
    bool isUp() const {
        return up;
    }

    void setUp(bool up) {
        this->up = up;
    }
    int getOscilThurst() const {
        return oscilThurst;
    }

    void setOscilThurst(int oscilThurst) {
        this->oscilThurst = oscilThurst;
    }

    bool isPlotting() const {
        return plotting;
    }

    void setPlotting(bool plotting) {
        this->plotting = plotting;
    }

    bool isHovering() const {
        return hovering;
    }

    void setHovering(bool hovering) {
        this->hovering = hovering;
    }

    double getGivenCorrection() const {
        return givenCorrection;
    }

    void setGivenCorrection(double givenCorrection) {
        this->givenCorrection = givenCorrection;
    }

private:
    thread* loopthread;
    CCrazyRadio *crRadio;
    CCrazyflie *cflieCopter;
    bool connected;
    void nloop();
    
    double offsetPitch;
    double offsetRoll;
    double yaw;
    double offsetThrust;
    double lowThrust;
    double highThrust;
    vector<AsyncState> *toDoList;
    bool keepYaw;
    
    bool oscilating;
    bool up;
    
    bool plotting;
    bool hovering;
    int oscilThurst;
    
    double givenCorrection;
};

#endif	/* CRAZYCONTAINER_H */

