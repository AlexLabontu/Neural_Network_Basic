//==============================================================================
//    Project: Neural_network
//    File: Neuron.cpp
//    Author: Alex Labontu
//    Date: 2/22/2019 12:15:33 PM
//==============================================================================

#include <iostream> 	/* cout */
#include <cmath>		/* tanh */
#include <vector>		/* tanh */

#include "Neuron.h"

/*
	code
*/



Neuron::Neuron(unsigned numOutputs, unsigned myIndex):m_outputVal(0),m_myIndex(-1),m_outputWeights(0),m_gradient(0){
	for (unsigned c = 0; c < numOutputs; ++c){
		m_outputWeights.push_back(Connections());
		m_outputWeights.back().weight = randomWeight();
	}
	m_myIndex = myIndex;
}

void Neuron::feedForward(const Layer &prevLayer){
	double sum = 0.0;
	
	//sum the prev layer outputs
	//including bias node
	
	for (unsigned n = 0; n < prevLayer.size(); ++n){
		sum += prevLayer[n].getOutputVal() *
				prevLayer[n].m_outputWeights[m_myIndex].weight;
	}
	
	m_outputVal = Neuron::transferFunction(sum);
}

void Neuron::calcOutputGradients(double targetVal){
	double delta = targetVal - m_outputVal;
	m_gradient = delta * Neuron::transferFunctionDerivative(m_outputVal);
}

void Neuron::calcHiddenGradients(const Layer &nextLayer){
	double dow = sumDOW(nextLayer);
	m_gradient = dow * Neuron::transferFunctionDerivative(m_outputVal);
	
}

void Neuron::updateInputWeights(Layer &prevLayer){
	for (unsigned n = 0; n < prevLayer.size(); ++n){
		
		Neuron &neuron = prevLayer[n];
		double oldDeltaWeight = neuron.m_outputWeights[m_myIndex].deltaWeight;
		
		double newDeltaWeight = 
			//Indibidual Input, magnified by the gradient and train rate:
			eta
			* neuron.getOutputVal()
			* m_gradient
			//also add momentum
			+ alpha
			* oldDeltaWeight;
		
		neuron.m_outputWeights[m_myIndex].deltaWeight = newDeltaWeight;
		neuron.m_outputWeights[m_myIndex].weight += newDeltaWeight;
	}
}

double Neuron::transferFunction(double x){
	// tanh - output range [-1.0 -> 1.0]
	return tanh(x);
}

double Neuron::transferFunctionDerivative(double x){
	// tanh Darivative
	return 1.0 - tanh(x)*tanh(x);
}

double Neuron::sumDOW(const Layer &nextLayer){
	double sum = 0.0;
	
	for (unsigned n = 0; n < nextLayer.size() - 1; ++n){
		sum += m_outputWeights[n].weight * nextLayer[n].m_gradient;
	}
	return sum;
}
