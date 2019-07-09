//==============================================================================
//    Project: Neural_network
//    File: neuron.h
//    Author: Alex Labontu
//    Date: 2/22/2019 12:15:40 PM
/*    Desc:    
*/
//==============================================================================

#ifndef Neural_network_neuron_HEADER_INCLUDE
#define Neural_network_neuron_HEADER_INCLUDE

/*
	code
*/

#include <vector>
#include <cstdlib>

class Neuron;
typedef std::vector<Neuron> Layer;

struct Connections{
	Connections():weight(0.0),deltaWeight(0.0){}
	Connections(double x, double y):weight(x),deltaWeight(y){}
	double weight;
	double deltaWeight;
};
		
extern double eta;	// [0.0->1.0]	overall net training rate
extern double alpha;// [0.0->n]		multiplier of last weight change (momentum)

class Neuron{
	public:
		Neuron(unsigned numOutputs, unsigned myIndex);
		
		void setOutputVal(double val) {m_outputVal = val;}
		
		double getOutputVal(void) const {return m_outputVal;}
		std::vector<Connections> & getOutputWeights(void) {return m_outputWeights;}
		
		void feedForward(const Layer &prevLayer);
		void calcOutputGradients(double targetVal);
		void calcHiddenGradients(const Layer &nextLayer);
		void updateInputWeights(Layer &prevLayer);
		
		
	private:
		static double transferFunction(double x);
		static double transferFunctionDerivative(double x);
		static double randomWeight(void) {return rand()/double(RAND_MAX);}
		
		double m_outputVal;
		unsigned m_myIndex;
		double m_gradient;
		double sumDOW(const Layer &nextLayer);
		std::vector<Connections> m_outputWeights;
};

#endif
