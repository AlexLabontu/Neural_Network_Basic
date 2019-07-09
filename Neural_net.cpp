//==============================================================================
//    Project: Neural_network
//    File: Neural_net.cpp
//    Author: Alex Labontu
//    Date: 2/22/2019 11:01:19 AM
//==============================================================================

#include <iostream> 	/* cout */
#include <fstream> 	/* cout */
#include <cmath>
#include <vector>
#include <cassert>

#include "Neural_net.h"

/*
	code
*/

Net::Net(void):m_layers(0),m_error(0.0),m_propCount(0){
}

Net::Net(const std::vector<unsigned> & topology):m_layers(0),m_error(0.0),m_propCount(0){
	unsigned numLayers = topology.size();
	for (unsigned layerNum = 0; layerNum < numLayers; ++ layerNum){
		m_layers.push_back(Layer());
		unsigned numOutputs = layerNum == topology.size() - 1 ? 0 : topology[layerNum +1];
		
		//we have a new l;ayer, now fill it with neurons, and
		//add a bias Neuron to the layer:
		for (unsigned neuronNum = 0; neuronNum <= topology[layerNum];++neuronNum){
			m_layers.back().push_back(Neuron(numOutputs,neuronNum));
		}
		
		//force bies neuron
		m_layers.back().back().setOutputVal(1.0);
	}
}

bool Net::read_from_binary(void){
	return read_from_binary("Neuron/neuron.nur");
}

bool Net::read_from_binary(char * name){
    std::ifstream InFile(name,std::ios::in | std::ios::binary);
    if(InFile){
		//std::cerr << "this: " << this << std::endl;
		
		for (unsigned c = 0; c < m_layers.size(); ++c){
			m_layers[c].clear();
		}
		m_layers.clear();
		
		unsigned temp,temp2;
        InFile.read(reinterpret_cast<char *>(&temp2),sizeof(temp2));
		//std::cerr << "temp: " << temp << std::endl;
		
		std::vector<unsigned> topology;
		for (unsigned c = 0; c < temp2; ++c){
			InFile.read(reinterpret_cast<char *>(&temp),sizeof(temp));
			//std::cerr << "topo" << c << ": " << temp << std::endl;
			topology.push_back(temp);
		}
		
		//delete this;
		//*this = Net(topology);
        InFile.read(reinterpret_cast<char *>(&m_error),sizeof(m_error));
        InFile.read(reinterpret_cast<char *>(&m_propCount),sizeof(m_propCount));
		//std::cerr << "m_error: " << m_error << std::endl;
		
		//read m_layers
        for (unsigned c = 0; c < temp2; ++c){
			
			unsigned numOutputs = c == topology.size() - 1 ? 0 : topology[c + 1];
			m_layers.push_back(Layer());
			
            for (unsigned g = 0; g < topology[c]; ++g){
				
				m_layers[c].push_back(Neuron(numOutputs,g));
				
				InFile.read(reinterpret_cast<char *>(&m_layers[c][g]),sizeof(Neuron)-sizeof(Connections));
				//std::cerr << "m_layers[" << c << "][" << g << "] values " << &m_layers[c][g] << std::endl;
				InFile.read(reinterpret_cast<char *>(&temp),sizeof(temp));
				//std::cerr << "temp_length: " << temp << " " << (sizeof(Neuron)-sizeof(Connections)) << std::endl;
					
				m_layers[c][g].getOutputWeights().clear();
				for(unsigned j = 0; j < temp; ++j){
					double d_temp_1,d_temp_2;
					InFile.read(reinterpret_cast<char *>(&d_temp_1),sizeof(d_temp_1));
					InFile.read(reinterpret_cast<char *>(&d_temp_2),sizeof(d_temp_2));
					Connections cons(d_temp_1,d_temp_2);
					//std::cerr << "cons[" << j << "] W " << cons.weight << " D " << cons.deltaWeight << std::endl;
					m_layers[c][g].getOutputWeights().push_back(cons);
					
				}
            }
        }
		std::cout << "Loaded" << std::endl;
		InFile.close();
		InFile.clear();
		return true;
    }
	std::cout << "Load failed" << std::endl;
    InFile.close();
    InFile.clear();
    return false;
}

bool Net::save_to_binary(void){
	return save_to_binary("Neuron/neuron.nur");
}

bool Net::save_to_binary(char * name){
    std::ofstream OutFile(name ,std::ios::out | std::ios::binary);
    if(OutFile){
		//std::cerr << "this: " << this << std::endl;
        
		unsigned temp,temp2 = m_layers.size();
        OutFile.write((char *)&temp2,sizeof(temp2));
		//std::cerr << "temp: " << temp << std::endl;
		
		std::vector<unsigned> topology;
		for (unsigned c = 0; c < temp2; ++c){
			temp = m_layers[c].size();
			OutFile.write((char *)&temp,sizeof(temp));
			//std::cerr << "topo" << c << ": " << temp << std::endl;
			topology.push_back(temp);
		}
		
        
		
		OutFile.write((char *)&m_error,sizeof(m_error));
		OutFile.write((char *)&m_propCount,sizeof(m_propCount));
		//std::cerr << "m_error: " << m_error << std::endl;
		
        
		for (unsigned c = 0; c < temp2; ++c){
            
			
			
			
			
			for (unsigned g = 0; g < topology[c]; ++g){
				
				std::vector<Connections> & cons = m_layers[c][g].getOutputWeights();
				temp = cons.size();
				
                
				
				OutFile.write((char *)&m_layers[c][g],sizeof(Neuron)-sizeof(Connections));
				//std::cerr << "m_layers[" << c << "][" << g << "] values " << &m_layers[c][g] << std::endl;
				OutFile.write((char *)&temp,sizeof(temp));
				//std::cerr << "temp_length: " << temp << " " << (sizeof(Neuron)-sizeof(Connections)) << std::endl;
				
				
				
				for(unsigned j = 0; j < temp; ++j){
					OutFile.write((char *)&cons[j],sizeof(cons[j]));
					//std::cerr << "cons[" << j << "] W " << cons[j].weight << " D " << cons[j].deltaWeight << std::endl;
					//std::cout << "\teta " << cons[j].eta << std::endl
					//std::cout << "\talpha " << cons[j].alpha << std::endl
				}
            }
        }
		std::cout << "Saved" << std::endl;
		OutFile.close();
		return true;
    }
	std::cout << "Save Failed" << std::endl;
    OutFile.close();
    return true;
}

void Net::feedForward(const std::vector<double> &inputVals){
		
	assert(inputVals.size() == m_layers[0].size() - 1);
	
	//assign (latch) the input values into the input neurons
	for (unsigned i = 0; i < inputVals.size(); ++i) {
		m_layers[0][i].setOutputVal(inputVals[i]);
		//m_layers[0][i].setOutputVal(tanh(inputVals[i]));
	}
	
	//forward propagate
	for (unsigned layerNum = 1; layerNum < m_layers.size(); ++layerNum){
		Layer &prevLayer = m_layers[layerNum -1];
		for(unsigned n = 0; n < m_layers[layerNum].size() - 1; ++n){
			m_layers[layerNum][n].feedForward(prevLayer);
		}
	}
	
}

void Net::backProp(const std::vector<double> &targetVals){
	//calculate overall net error
	Layer &outputLayer = m_layers.back();
	m_error = 0.0;
	for (unsigned n = 0; n < outputLayer.size() -1; ++n){
		double delta = targetVals[n] - outputLayer[n].getOutputVal();
		//double delta = tanh(targetVals[n]) - outputLayer[n].getOutputVal();
		m_error += delta * delta;
	}
	m_error /= outputLayer.size() - 1;	//get average error squared
	m_error = sqrt(m_error);	//RMS
	
	//calculate output layer gradients
	
	for (unsigned n = 0; n < outputLayer.size() -1; ++n){
		outputLayer[n].calcOutputGradients(targetVals[n]);
		//outputLayer[n].calcOutputGradients(tanh(targetVals[n]));
		
	}
	
	//calculate gradients on hidden layers
	
	for (unsigned layerNum = m_layers.size() - 2; layerNum > 0; --layerNum){
		Layer &hiddenLayer = m_layers[layerNum];
		Layer &nextLayer = m_layers[layerNum+1];
		
		for (unsigned n = 0; n < hiddenLayer.size(); ++n){
			hiddenLayer[n].calcHiddenGradients(nextLayer);
		}
	}
	
	//for all layers from ooutputs to first hidden layer,
	//update connection weights
	for (unsigned layerNum = m_layers.size() -1; layerNum > 0; --layerNum){
		Layer &layer = m_layers[layerNum];
		Layer &prevLayer = m_layers[layerNum - 1];
		
		for (unsigned n = 0; n < layer.size() - 1; ++ n){
			layer[n].updateInputWeights(prevLayer);
		}
	}
	++m_propCount;
}

void Net::getResults(std::vector<double> &resultVals) const{
	resultVals.clear();
	for (unsigned n = 0; n <m_layers.back().size()-1;++n){
		resultVals.push_back(m_layers.back()[n].getOutputVal());
		//resultVals.push_back(atanh(m_layers.back()[n].getOutputVal()));
	}
}
