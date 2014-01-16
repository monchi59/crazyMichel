/* 
 * File:   Integrator.h
 * Author: antoine
 *
 * Created on 14 janvier 2014, 11:39
 */

#ifndef INTEGRATOR_H
#define	INTEGRATOR_H
#include <cstdio>
#include <malloc.h>
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;


#define PM 4
//#define N 2

class Integrator {
public:
    Integrator();
    Integrator(const Integrator& orig);
    virtual ~Integrator();

    /*void systeme_diff(double q[], double t, double qp[], int n) {
        qp[0] = q[1];
        qp[1] = -q[0];
    }
    void euler(void(*sd)(double*, double, double*, int), double q[], double t, double dt, int n) {
        int i;
        double qp[N];
        sd(q, t, qp, n);
        for (i = 0; i < n; i++) q[i] += dt * qp[i];
    }

    void rk4(void(*sd)(double*, double, double*, int), double q[], double t, double dt, int n) {
        int i, j, k, p;
        double *y[PM + 1], *z[PM];
        static const double a[PM][PM] = {1. / 2, 0, 0, 0, 0, 1. / 2, 0, 0, 0, 0, 1, 0, 1. / 6, 1. / 3, 1. / 3, 1. / 6};
        static const double b[PM] = {0, 1. / 2, 1. / 2, 1};

        for (i = 0; i < PM + 1; i++) y[i] = malloc(n * sizeof (double));
        for (i = 0; i < PM; i++) z[i] = malloc(n * sizeof (double));

        for (i = 0; i < n; i++) y[0][i] = q[i];
        for (p = 1; p <= PM; p++) {
            sd(y[p - 1], t + b[p - 1] * dt, z[p - 1], n);
            for (i = 0; i < n; i++) y[p][i] = q[i];
            for (k = 0; k < p; k++) {
                for (i = 0; i < n; i++) y[p][i] += dt * a[p - 1][k] * z[k][i];
            }
        }
        for (i = 0; i < n; i++) q[i] = y[PM][i];
    }*/
    void integrate(){
        //(y0 + y1)/2 * (x1 - x0) + (y1 + y2)/2 * (x2 - x1)
        int XorY = 1;
        ivalues[0][0] = values[0][0];
        ivalues[0][1] = 0;
        ivalues[0][2] = 0;
        for(int i=1;i<howmany;i++){
            ivalues[i][XorY] = ((values[i-1][XorY]+values[i][XorY])/2)*(values[i][0]-values[i-1][0]) + ivalues[i-1][XorY];
        }
        
        XorY = 2;
        ivalues[0][0] = values[0][0];
        ivalues[0][1] = 0;
        ivalues[0][2] = 0;
        for(int i=1;i<howmany;i++){
            ivalues[i][0] = values[i][0];
            ivalues[i][XorY] = ((values[i-1][XorY]+values[i][XorY])/2)*(values[i][0]-values[i-1][0]) + ivalues[i-1][XorY];
        }
        
        XorY = 1;
        iivalues[0][0] = ivalues[0][0];
        iivalues[0][1] = 0;
        iivalues[0][2] = 0;
        for(int i=1;i<howmany;i++){
            iivalues[i][0] = ivalues[i][0];
            iivalues[i][XorY] = ((ivalues[i-1][XorY]+ivalues[i][XorY])/2)*(ivalues[i][0]-ivalues[i-1][0]) + iivalues[i-1][XorY];
        }
        
        XorY = 2;
        iivalues[0][0] = ivalues[0][0];
        iivalues[0][1] = 0;
        iivalues[0][2] = 0;
        for(int i=1;i<howmany;i++){
            iivalues[i][XorY] = ((ivalues[i-1][XorY]+ivalues[i][XorY])/2)*(ivalues[i][0]-ivalues[i-1][0]) + iivalues[i-1][XorY];
        }
       //return total; 
    }
    int readFile(string filename){
        ifstream fin;
        fin.open(filename); // open a file
        int i=0;
        //this->values = {};
        if (!fin.good()) 
          return 1; // exit if file not found

        // read each line of the file
        double init = 0;
        double last = 0;
        while (!fin.eof())
        {
          // read an entire line into memory
          char buf[255];
          fin.getline(buf, 255);

          // parse the line into blank-delimited tokens
          int n = 0; // a for-loop index

          // array to store memory addresses of the tokens in buf
          const char* token[3] = {}; // initialize to 0

          // parse the line
          token[0] = strtok(buf, " "); // first token
          
          if (token[0]) // zero if line is blank
          {
            for (n = 1; n < 3; n++)
            {
              token[n] = strtok(0, " "); // subsequent tokens
              if (!token[n]) break; // no more tokens
            }
                if(i==0){
                    init = atof(token[0]);
                }
                if(atof(token[1])!=last){
                  this->values[i][0] = (atof(token[0])-init)/1000;
                  this->values[i][1] = atof(token[1])-0.017; 
                  this->values[i][2] = atof(token[2])-0.022;
                  i++;
                  i = i%15000;
                  last = atof(token[1]);
                }
          }
          
          
        }
        howmany = i;
        return i;
    }
     int readFile2(string filename){
        ifstream fin;
        fin.open(filename); // open a file
        int i=0;
        //this->values = {};
        if (!fin.good()) 
          return 1; // exit if file not found

        // read each line of the file
        double init = 0;
        double last = 0;
        while (!fin.eof())
        {
          // read an entire line into memory
          char buf[255];
          fin.getline(buf, 255);

          // parse the line into blank-delimited tokens
          int n = 0; // a for-loop index

          // array to store memory addresses of the tokens in buf
          const char* token[3] = {}; // initialize to 0

          // parse the line
          token[0] = strtok(buf, ","); // first token
          
          if (token[0]) // zero if line is blank
          {
            for (n = 1; n < 3; n++)
            {
              token[n] = strtok(0, ","); // subsequent tokens
              if (!token[n]) break; // no more tokens
            }
                if(i==0){
                    init = atof(token[0]);
                }
                if(atof(token[1])!=last){
                  this->values[i][0] = i*10;
                  this->values[i][1] = atof(token[0])-0.017; 
                  this->values[i][2] = atof(token[1])-0.022;
                  i++;
                  i = i%15000;
                  last = atof(token[1]);
                }
          }
          
          
        }
        howmany = i;
        return i;
    }
    void save(){
        ofstream speed("speed.dat");
        ofstream pos("pos.dat");
        ofstream acc("acc2.dat");
        for(int i =0;i<howmany-1;i++){
            speed<<ivalues[i][0]<<" "<<ivalues[i][1]<<" "<<ivalues[i][2]<<endl;
            pos<<iivalues[i][0]<<" "<<iivalues[i][1]<<" "<<iivalues[i][2]<<endl;
            acc<<values[i][0]<<" "<<values[i][1]<<" "<<values[i][2]<<endl;
        }
        
    }
private:
    double values[15000][3];
    double ivalues[15000][3];
    
    double iivalues[15000][3];
    int howmany ;
};





/*
int main(int argc, char* argv[])
{
        int i,np; //D�clarations
        double q[N],q0[N],t,dt,t0,tfin;
        FILE *fich;

        fich=fopen("EulerSys.dat","w");//Fichier
        t0=0.; q0[0]=1.;q0[1]=0.; np=200; tfin=6.28;//Param�tres

        dt=(tfin-t0)/(np-1);//Pas temps

        for(i=0;i<N;i++) q[i]=q0[i];
        t=t0;//Amorcage
        for(i=1;i<=np;i++)
        {
                fprintf(fich,"%lg %lg %lg\n",t,q[0],q[1]);
                euler(systeme_diff,q,t,dt,N);
                t+=dt;
        }
        fclose(fich);//Fichier
        return;
}*/
//---------------------------------------------------------------------------
#endif	/* INTEGRATOR_H */

