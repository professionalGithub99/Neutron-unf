#include <TMath.h>
Eigen::VectorXf standardDeviation(Eigen::MatrixXf matrix){
  Eigen::VectorXf stdVectors;
  for (int i=0;i<matrix.cols();i++) {
    float sd=0;
    float mean=matrix.col(i).mean();
    for (int j=0;j<matrix.rows();j++){
      sd+=TMath::Power((matrix(j,i)-mean),2);
  }
  sd=sqrt(sd/matrix.rows());
  stdVectors(i)=sd;
}
return stdVectors;
}
