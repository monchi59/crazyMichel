/* 
 * File:   MartinsIntegrator.cpp
 * Author: antoine
 * 
 * Created on 16 janvier 2014, 16:49
 */



#include "MartinsIntegrator.h"

MartinsIntegrator::MartinsIntegrator() {
    this->reset();
    
}

MartinsIntegrator::MartinsIntegrator(const MartinsIntegrator& orig) {
}

MartinsIntegrator::~MartinsIntegrator() {
}



/*
 * File:   Satallite.c
 * Author: isen
 *
 * Created on 7 décembre 2010, 17:36
 *


/*
 *
 */







/*

int main() {

    cout << "Run" << endl;
    FILE *fich;

    fich = fopen("/home/isen/Téléchargements/cfclient-2013.4.2/bin/stop.dat", "r"); //Fichier
    ofstream out("/home/isen/Téléchargements/cfclient-2013.4.2/bin/out.dat");
    ofstream outm("/home/isen/Téléchargements/cfclient-2013.4.2/bin/outm.dat");
   

    char* datas = new char[1000];
    double* xbuffer = new double[BUFFER_LENGTH];
    double* ybuffer = new double[BUFFER_LENGTH];
    int numberOfMeasures = 1;
    string s;
    double t, ax, ay, t1, ax1, ay1, x, y,x1,y1,vx,vx1,vy,vy1,dt,axoffset,toffset,ayoffset,axm,ax1m,aym,ay1m,vxm,vym,xm,ym,vx1m,vy1m,x1m,y1m;

    cout<<fich<<endl;
    fgets(datas, 100, fich);
    fgets(datas, 100, fich);
    s = (string) datas;
    cout<<"st"<<endl;
    
    axoffset = atof(strtok(datas, ","));
    ayoffset = atof(strtok(NULL, ","));
    
    cout<<"yoffset= "<<ayoffset<<endl;
    cout<<xbuffer[1]<<endl;
    
    t=0;
    ax=0;
    ay=0;
    axm=0;   
    aym = 0;  
    vym=0;
    vxm=0;
    xm=0;ym=0;
    x=0;
    y=0;
    vx=0;
    vy=0;
   
    
    do {
      
        fgets(datas, 100, fich);
        s = (string) datas;
        //    
        if (datas !=NULL and feof(fich) == 0) {
          
            
            ax1 = atof(strtok(datas, ","));//-axoffset;
            ay1 = atof(strtok(NULL, ","));//-ayoffset;
            
            t1= t+ 0.01;
            
            
            
            append(xbuffer,ax1);
            append(ybuffer,ay1);
            ax1m = average(xbuffer);
            ay1m = average(ybuffer);
            
            dt=0.01;
            //    
//            if(fabs(ax1)<0.03)
//            {
//                ax1=0;
//            }
//            if(fabs(ay1)<(0.05))
//            {
//            
//                ay1=0;
//            
//            }
//            else
//            {
//                    cout<<"ay1= "<<ay<<endl;
//            }
                
            
            vx1 = vx + ax1*dt;
            vy1 = vy+ ay1*dt;
            
            vx1m=vxm + ax1m*dt;
            vy1m = vym + ay1m*dt;
            
//            
//            if(ax1==0 and ax==0)
//            {
//                vx1=vx1*0.7;
//            }
//            if(ay1==0 and ay==0)
//            {
//                vy1=vy1*0.7;
//            }
            
            
            
            x1 = vx1*dt + x;
            y1 = vy1*dt + y;
            
            
                    
            x1m = vx1m*dt + xm;
            y1m = vy1m*dt + ym;
            
            x=x1;
            y=y1;
            t = t1;
            ax = ax1;
            ay = ay1;
            vx=vx1;
            vy=vy1;
            
            
             xm=x1m;
            ym=y1m;
            t = t1;
            axm = ax1m;
            aym = ay1m;
            vxm=vx1m;
            vym=vy1m;

            //out  <<t<<" "<< x << " " << y << endl;
            
            
            out <<t<<" "<<ax<<" "<<vx<<" "<<x<<" "<<ay<<" "<<vy<<" " <<y<<endl;
           outm <<t<<" "<<axm<<" "<<vxm<<" "<<xm<<" "<<aym<<" "<<vym<<" " <<ym<<endl;
//           nomotion<<ax<<endl;
         //out<<t<<" "<<x<<" "<<xm<<endl;   
            
            
           

            numberOfMeasures++;
        }
      


    } while (feof(fich) == 0);

    fclose(fich); //Fichier
    //        getchar();
    FILE *gp;
    gp = popen(GNUPLOT_PATH, "w");

    if (gp == NULL) {
        fprintf(stderr, "Oops, I can't find %s.", GNUPLOT_PATH);
        return EXIT_FAILURE;
    } else {
        printf("file opened \n");
    }

//    //  fprintf(gp, "set autoscale y\n"); //Extension de l'axe x auto
//    fprintf(gp, //"load '/home/isen/Téléchargements/cfclient-2013.4.2/bin/Drone.gnu' \n");
//    fprintf(gp, //"plot '/home/isen/Téléchargements/cfclient-2013.4.2/bin/speed.dat' using 2:3 with line \n");
//    fflush(gp); /* On oublie pas le buffer. */

   // getchar();
/*
    pclose(gp);


    return (EXIT_SUCCESS);
}*/