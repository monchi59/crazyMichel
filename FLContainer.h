/* 
 * File:   FLContainer.h
 * Author: monchi
 *
 * Created on December 26, 2013, 11:45 AM
 */

#ifndef FLCONTAINER_H
#define	FLCONTAINER_H
#include <FL/Fl_Input.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_Dial.H>

class FLContainer {
public:
    static Fl_Value_Slider* thrustOutput;
    static Fl_Value_Slider * pitch;
    static Fl_Value_Slider * roll;
    static Fl_Value_Slider * yaw;
    static Fl_Value_Slider * offsetPitch;
    static Fl_Value_Slider * offsetRoll;
};


#endif	/* FLCONTAINER_H */

