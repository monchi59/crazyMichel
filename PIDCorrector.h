/* 
 * File:   PIDCorrector.h
 * Author: antoine
 *
 * Created on 17 janvier 2014, 14:51
 */
/**
 *PID : fonction qui effectue un asservissement PID
 *Remarque:
 * Il faut commencer par definir les constantes Kp, Ki, Kd dans le programme principal
 */

#ifndef PIDCORRECTOR_H
#define	PIDCORRECTOR_H

#include <cmath>
#define Kp 1.1
#define Ki 0.16
#define Kd 0.08
#define Lissage 2 //min 1

class PIDCorrector {
public:

    PIDCorrector() {
        this->zeroing();
    }
    void zeroing(){
        e = 0;
        FR = 0;
        I = 0;
        for(int i=0;i<Lissage;i++){
            previousVals[i] = 0;
        }
    }
    double filter(float R, float Ci){//Simplement plafonner l'acceleration pour éviter les coups de folies
        double avg =0;
        for(int i=0;i<Lissage;i++){
            avg += previousVals[i];
        }
        avg = (2*R + avg)/(Lissage+2); //Lissage pondéré
        
        /*if(R>2.5){
            return 2.5;
        }else if(R<-1.5){
            return -1.5;
        }*/
        this->avg = avg;
        return avg;
    }
    PIDCorrector(const PIDCorrector& orig);
    virtual ~PIDCorrector();
    double PID(float Ci, float R) {
        long P, D;
        double C;
        if(fabs(R-Ci)<0.1){
            return Ci;
        }
        e = Ci - R;
        FR=filter(R,Ci);//On filtre le retour
        P = e; //Terme Proportionnel
        I = I + e; //Terme Integral
        D = FR - previousVals[0]; //Terme D�riv�
        C = Kp * P + Ki * I + Kd*D; // oops on a fini
        
        for(int i=Lissage-2;i>=1;i--){
            previousVals[i] = previousVals[i-1];
        }
        previousVals[0] = FR; //On sauvegarde

        return C;
    }
    double e, FR, I,avg;
    double previousVals[Lissage] ;
private:
    


};

#endif	/* PIDCORRECTOR_H */

