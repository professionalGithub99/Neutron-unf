namespace UNFOLD;
class MCMC{
private:
public:
  MCMC(Eigen::VectorXf startingGuess,Eigen::MatrixXf responseMatrix,int sampleCount );
  Eigen::VectorXf currentGuess;
  Eigen::VectorXf generateNewSample();// find a method for generating new sample of neutron guesses
  void acceptOrReject();// use likelihood algorithm to campare curent guess with new sample
  void secondChance();//Metropolis -hastings algorithm decide whether to accept or reject


}
