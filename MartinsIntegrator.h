/* 
 * File:   MartinsIntegrator.h
 * Author: antoine
 *
 * Created on 16 janvier 2014, 16:49
 */

#ifndef MARTINSINTEGRATOR_H
#define	MARTINSINTEGRATOR_H

#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <string.h>
#include<fstream>

#define PM 4
#define GNUPLOT_PATH "/usr/bin/gnuplot"  //Chemin pour l'execution de GnuPlot
#define DAT_PATH "/home/isen"
#define BUFFER_LENGTH 10


using namespace std;

class MartinsIntegrator {
public:
    MartinsIntegrator();
    MartinsIntegrator(const MartinsIntegrator& orig);
    virtual ~MartinsIntegrator();
    double t, ax, ay, t1, ax1, ay1, x, y, x1, y1, vx, vx1, vy, vy1, dt, axoffset, toffset, ayoffset, axm, ax1m, aym, ay1m, vxm, vym, xm, ym, vx1m, vy1m, x1m, y1m;
    double* xbuffer;
    double* ybuffer;
    int numberOfMeasures;

    void reset() {
        t = 0;
        ax = 0;
        ay = 0;
        axm = 0;
        aym = 0;
        vym = 0;
        vxm = 0;
        xm = 0;
        ym = 0;
        x = 0;
        y = 0;
        vx = 0;
        vy = 0;
        xbuffer = new double[BUFFER_LENGTH];
        ybuffer = new double[BUFFER_LENGTH];
        numberOfMeasures = 1;
    }

    void append(double* array, double newValue) {
        int i;
        for (i = 0; i < BUFFER_LENGTH - 1; i++) {
            array[i] = array[i + 1];
        }
        array[BUFFER_LENGTH - 1] = newValue;

    }

    double average(double* array) {
        double sum = 0;
        for (int i = 0; i < BUFFER_LENGTH; i++) {
            sum += array[i];
        }
        return sum / BUFFER_LENGTH;

    }

    void integrate(double ax1, double ay1, double t1) {


        //t1= t+ 0.01;





        if (fabs(ax1) < 0.03) {
            ax1 = 0;
        }
        if (fabs(ay1)<(0.05)) {

            ay1 = 0;

        }


        append(xbuffer, ax1);
        append(ybuffer, ay1);
        ax1m = average(xbuffer);
        ay1m = average(ybuffer);

        dt = t1 - t;

        //            {
        //                    cout<<"ay1= "<<ay<<endl;
        //            }


        vx1 = vx + ax1*dt;
        vy1 = vy + ay1*dt;

        vx1m = vxm + ax1m*dt;
        vy1m = vym + ay1m*dt;

                    
                    if(ax1==0 and ax==0)
                    {
                        vx1=vx1*0.7;
                    }
                    if(ay1==0 and ay==0)
                    {
                        vy1=vy1*0.7;
                    }

          if(ax1m==0 and axm==0)
                    {
                        vx1m=vx1m*0.7;
                    }
                    if(ay1m==0 and aym==0)
                    {
                        vy1m=vy1m*0.7;
                    }


        x1 = vx1 * dt + x;
        y1 = vy1 * dt + y;



        x1m = vx1m * dt + xm;
        y1m = vy1m * dt + ym;

        x = x1;
        y = y1;
        t = t1;
        ax = ax1;
        ay = ay1;
        vx = vx1;
        vy = vy1;


        xm = x1m;
        ym = y1m;
        t = t1;
        axm = ax1m;
        aym = ay1m;
        vxm = vx1m;
        vym = vy1m;

        //out  <<t<<" "<< x << " " << y << endl;


        // out <<t<<" "<<ax<<" "<<vx<<" "<<x<<" "<<ay<<" "<<vy<<" " <<y<<endl;
        //outm <<t<<" "<<axm<<" "<<vxm<<" "<<xm<<" "<<aym<<" "<<vym<<" " <<ym<<endl;
        //           nomotion<<ax<<endl;
        //out<<t<<" "<<x<<" "<<xm<<endl;   

        //double returned [] = {axm,aym,vx,vy,vxm,vym,x,y,xm,ym};
        numberOfMeasures++;

        //return returned;
    }
private:

};

#endif	/* MARTINSINTEGRATOR_H */

