#include "tools.h"
#include <iostream>

using Eigen::VectorXd;
using Eigen::MatrixXd;
using std::vector;
using std::cout;

Tools::Tools() {}

Tools::~Tools() {}

VectorXd Tools::CalculateRMSE(const vector<VectorXd> &estimations,
                              const vector<VectorXd> &ground_truth) {
  /**
   * TODO: Calculate the RMSE here.
   */
  VectorXd rmse(4);
  rmse << 0,0,0,0;

  // TODO: YOUR CODE HERE
  // check the validity of the following inputs:
  //  * the estimation vector size should not be zero
  //  * the estimation vector size should equal ground truth vector size
  
  if(estimations.size()==0)
  {
    cout<<"Error: Empty estimation  vector !"; 
    return rmse;
  }
  if(ground_truth.size()!=estimations.size())
  {
    cout<<"Error: estimation vector and ground truth vector sizes aren't the same !"; 
    return rmse;
  }

  // TODO: accumulate squared residuals
  for (unsigned int i=0; i < estimations.size(); ++i) {
      VectorXd temp =estimations[i]-ground_truth[i];
      temp=temp.array()*temp.array();
      rmse+=temp;
       // ... your code here
    
  }

  // TODO: calculate the mean
    rmse/=estimations.size();
  // TODO: calculate the squared root
	rmse=rmse.array().sqrt();
  // return the result
  return rmse;
}

MatrixXd Tools::CalculateJacobian(const VectorXd& x_state) {
  /**
   * TODO:
   * Calculate a Jacobian here.
   */
  MatrixXd Hj(3,4);
  // recover state parameters
  float px = x_state(0);
  float py = x_state(1);
  float vx = x_state(2);
  float vy = x_state(3);

  // TODO: YOUR CODE HERE 

  // check division by zero
  
  if(fabs(px * px + py * py) < .00001) {
      std::cout << "Error - Division by Zero" << std::endl;
      return Hj;
}
  
    float c1 = px*px + py*py;
 	float c2 = sqrt(c1);
	float c3 = (c1*c2);
  
  // compute the Jacobian matrix
  Hj << (px / c2), (py / c2), 0, 0,
       -(py / c1), (px / c1), 0, 0,
  py*(vx*py - vy*px) / c3, px*(px*vy - py*vx) / c3, px / c2, py / c2;
  
  
  return Hj;
}
