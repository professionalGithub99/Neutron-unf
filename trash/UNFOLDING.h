//
#ifndef _UNFOLD_H_
#define _UNFOLD_H_
//ROOT classes
// Eigen
#include <Eigen/Core>
#include <Eigen/Dense>
//c++ classes
#include <vector>
#include <fstream>
#include <string>
#include <TGraph.h>
//my classes
#include <FILEIO.h>

namespace UNFOLDING{

class UNFOLDING
{
  private:
    Eigen::MatrixXf a, b, x, x_1, catr, ax, ansIndex;
    Eigen::ArrayXf a_norm;
    FILEIO *m_fio;
    // a - response matrix
    // b - LO spectrum to unfold
    // x - guess
    // x_1 - updated guess
    // catr - normalization matrix
    // ax - forward projection
    // ansInex - corresponding energy for a position in x or x_1
    std::vector<double> rss2Vals; // rss values as a function of iteration
  public:
    UNFOLDING();
};
}

#endif
