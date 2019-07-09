//==============================================================================
//    Project: Neural_network
//    File: Neural_net.h
//    Author: Alex Labontu
//    Date: 2/22/2019 11:14:26 AM
/*    Desc:    
*/
//==============================================================================

#ifndef Neural_network_Neural_net_HEADER_INCLUDE
#define Neural_network_Neural_net_HEADER_INCLUDE

/*
	code
*/

#include <vector>

#include "Neuron.h"

typedef std::vector<Neuron> Layer;

class Net{
	public:
		Net(void);
		Net(const std::vector<unsigned> & topology);
		
		double getErrorConfidince(void) const {return m_error;}
		
		bool save_to_binary(void);
		bool save_to_binary(char * name);
		bool read_from_binary(void);
		bool read_from_binary(char * name);
		
		void feedForward(const std::vector<double> &inputVals);
		void backProp(const std::vector<double> &targetVals);
		void getResults(std::vector<double> &resultVals) const;
		
		unsigned getBackPropCount(void) const {return m_propCount;}
		
	private:
		std::vector<Layer> m_layers;		//m_layers[layerNum][neuronNum]
		double m_error;
		unsigned m_propCount;
};

#endif
