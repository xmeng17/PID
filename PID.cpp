#include "PID.h"
#include <limits>
#include <iostream>

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double *Kpid) {
  iter = 0;
  ntwd = 0;
  step = 0;
  this->Kpid = Kpid;
  Dpid = (double*) malloc(3*sizeof(double));
  Dpid[0] = 0.005;
  Dpid[1] = 0.5;
  Dpid[2] = 0.00002; 
  for (int j=0;j<3;j++) {
    Epid[j] = 0.0;
  }
  i = 0;
  se = 0.0;
  bse = std::numeric_limits<double>::max();
  snd = 0;
}

void PID::Twiddle(){
  if(step == 2*STEP){
    if ((Dpid[0] + Dpid[1] + Dpid[2]) > 0.001) {
      if (se < bse) {
        //update bse 
        bse = se;
        //enlarge current Dpid
        Dpid[i] *= 1.1;
      } else {
        if (!snd) {
          //subtract current Dpid from the previous Kpid
          Kpid[i] -= 2*Dpid[i];
          //mark is second update
          snd = 1;
          step = 0;
          se = 0;
          return;
        } else {
          //restore previous Kpid
          Kpid[i] += Dpid[i]; 
          //shrink current Dpid
          Dpid[i] *= 0.9;
          }
      }
      i = (i + 1) % 3;
      snd = 0;
      step = 0;
      se = 0;
      iter++;
      //change Kpid for next round
      Kpid[i] += Dpid[i];
    } else {
      ntwd = 1;
    }
  }
}

void PID::UpdateError(double cte) {
  //Ei = Scte
  Epid[1] = cte - Epid[0];
  //Ep = cte
  Epid[0] = cte;
  //Ed = Dcte
  Epid[2] += cte;
  //update only after enough steps
  if (!ntwd && step>=STEP && step<2*STEP) se += cte*cte;
  step ++;
}

double PID::TotalError() {
  return  -Kpid[0]*Epid[0] - Kpid[1]*Epid[1] - Kpid[2]*Epid[2];
}

