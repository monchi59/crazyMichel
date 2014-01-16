/* 
 * File:   main.cpp
 * Author: monchi
 *
 * Created on December 25, 2013, 10:11 PM
 */

#include <cstdlib>
#include "cflie/CCrazyflie.h"
#include "CrazyContainer.h"
#include <iostream>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/fl_ask.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_Dial.H>
#include "FLContainer.h"
#include "Integrator.h"
#include "MyWindow.h"
#include <thread>

using namespace std;


void connect(Fl_Widget *, void * container) {
    CrazyContainer* ncontainer = (CrazyContainer*)container;
    ncontainer->connect();
    
}
void run(Fl_Widget *, void * container) {
    cout<<"Run"<<endl;
    ((CrazyContainer*)container)->setThrust(11000);
}
void runCustomThrust(Fl_Widget *, void * container) {
    cout<<"Go2"<<endl;
    ((CrazyContainer*)container)->setThrust(FLContainer::thrustOutput->value());
}
void stop(Fl_Widget *, void * container) {
    cout<<"Stop"<<endl;
    
    ((CrazyContainer*)container)->setThrust(0);
    
}
void save(Fl_Widget *, void * container) {
    cout<<"save"<<endl;
     Integrator* test = new Integrator();
    cout<<test->readFile2("acccfc.dat")<<endl;
    test->integrate();
    test->save();
    //((CrazyContainer*)container)->saveXML();
    
}
void load(Fl_Widget *, void * container) {
    cout<<"load"<<endl;
    Integrator* test = new Integrator();
    cout<<test->readFile("acc.dat")<<endl;
    test->integrate();
    test->save();
    //((CrazyContainer*)container)->loadXML();
    
}
void killnstop(Fl_Widget *, void * container) {
    cout<<"Killnstop"<<endl;
    
    delete (CrazyContainer*)container;
    exit(0);
}
void kill(Fl_Widget *, void * container) {
    cout<<"Kill"<<endl;
    
    ((CrazyContainer*)container)->kill();
    exit(0);
}
void setOffsetRoll(Fl_Widget *, void * container){
    cout<<"callback roll"<<endl;
    ((CrazyContainer*)container)->setOffsetRoll(FLContainer::offsetRoll->value());
}
void setOffsetPitch(Fl_Widget *, void * container){
    ((CrazyContainer*)container)->setOffsetPitch(FLContainer::offsetPitch->value());
}
Fl_Value_Slider* FLContainer::thrustOutput;
Fl_Value_Slider * FLContainer::pitch;
Fl_Value_Slider * FLContainer::roll;
Fl_Value_Slider * FLContainer::yaw;
Fl_Value_Slider * FLContainer::offsetPitch;
Fl_Value_Slider * FLContainer::offsetRoll;
/*
 * 
 */ 

int main(int argc, char** argv) {
    
    
    CrazyContainer *container = new CrazyContainer();
    container->loadXML();
    MyWindow *window = new MyWindow();
    window->setCrazyContainer(container);
        
    Fl_Button *b1 = new Fl_Button(20, 20, 80, 25, "Connect");
    b1->callback(connect,(void *)container);
    
    Fl_Button *b2 = new Fl_Button(100, 20, 80, 25, "Go 11000");
    b2->callback(run,(void *)container);
    FLContainer::thrustOutput = new Fl_Value_Slider(100,50,250,25,"Thrust meter");
    FLContainer::thrustOutput->type(FL_HOR_FILL_SLIDER);
    FLContainer::thrustOutput->scrollvalue(5000, 100, 5000, 100000);
    FLContainer::thrustOutput->callback(runCustomThrust,(void *)container); 
    
    FLContainer::pitch = new Fl_Value_Slider(100,100,250,25,"Pitch");
    FLContainer::pitch->type(FL_HORIZONTAL);
    FLContainer::pitch->scrollvalue(0,10,-180,370);
    FLContainer::pitch->precision(2);
    FLContainer::roll = new Fl_Value_Slider(100,140,250,25,"Roll");
    FLContainer::roll->type(FL_HORIZONTAL);
    FLContainer::roll->scrollvalue(0,10,-180,370);
    FLContainer::roll->precision(2);
    FLContainer::yaw = new Fl_Value_Slider(100,180,250,25,"Yaw");
    FLContainer::yaw->type(FL_HORIZONTAL);
    FLContainer::yaw->scrollvalue(0,10,-180,370);
    FLContainer::yaw->precision(2);
    FLContainer::offsetPitch = new Fl_Value_Slider(100,220,250,25,"Offset Pitch");
    FLContainer::offsetPitch->type(FL_HORIZONTAL);
    FLContainer::offsetPitch->scrollvalue(container->getOffsetPitch(),10,-20,50);
    FLContainer::offsetPitch->precision(2);
    FLContainer::offsetPitch->callback(setOffsetPitch,(void *)container);
    FLContainer::offsetRoll = new Fl_Value_Slider(100,260,250,25,"Offset Roll");
    FLContainer::offsetRoll->type(FL_HORIZONTAL);
    FLContainer::offsetRoll->scrollvalue(container->getOffsetRoll(),10,-20,50);
    FLContainer::offsetRoll->precision(2);
    FLContainer::offsetRoll->callback(setOffsetRoll,(void *)container);
    
     Fl_Button *b3 = new Fl_Button(200, 20, 80, 25, "Stop");
    b3->callback(stop,(void *)container);
    
    Fl_Button *bfocus = new Fl_Button(20, 45, 80, 25, "Focus");
    
     Fl_Button *b5 = new Fl_Button(400, 20, 80, 25, "Kill n' Exit");
    b5->callback(killnstop,(void *)container);
    
    Fl_Button *bsave = new Fl_Button(500, 20, 80, 25, "Save");
    bsave->callback(save,(void *)container);
    
    Fl_Button *bload = new Fl_Button(500, 50, 80, 25, "Load");
    bload->callback(load,(void *)container);
    
    
    window->end();
    window->show(argc,argv);
    return Fl::run();
}
