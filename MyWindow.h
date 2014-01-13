/* 
 * File:   MyWindow.h
 * Author: monchi
 *
 * Created on December 26, 2013, 12:49 PM
 */

#ifndef MYWINDOW_H
#define	MYWINDOW_H
 
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/fl_ask.H>
#include "CrazyContainer.h"
using namespace std;

class MyWindow:public Fl_Window {
public:
    MyWindow();
    MyWindow(int width, int height);
    virtual ~MyWindow();
    int handle(int e);
    CrazyContainer* getCrazyContainer() const;

    void setCrazyContainer(CrazyContainer* container);

private:
    CrazyContainer* crazyContainer;
};

#endif	/* MYWINDOW_H */