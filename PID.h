#ifndef PID_H
#define PID_H

#define STEP 100

class PID {
public:
  // the number of twiddling it did
  int iter;
  // ftwd = 1 when finished twiddling
  bool ntwd;
  // step for twiddle
  int step;
  // coefficient for p,d,i
  double *Kpid;
  // error for p,i,d
  double Epid[3];
  // increments for Kp,Kd,Ki
  double *Dpid;
  // index for Dpid
  int i;
  // sum of squared cte (for twiddle)
  double se;
  // best se so far (for twiddle)
  double bse;
  // whether is the second update
  bool snd;  
  /*
  * Constructor
  */
  PID();

  /*
  * Destructor.
  */
  virtual ~PID();

  /*
  * Initialize PID.
  */
  void Init(double *Kpid);
  
  /*
  * twiddle
  */
  void Twiddle();
  
  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateError(double cte);

  /*
  * Calculate the total PID error.
  */
  double TotalError();
};

#endif /* PID_H */
