//==============================================================================
//    Project: Neural_network
//    File: main.cpp
//    Author: Alex Labontu
//    Date: 2/22/2019 11:00:50 AM

//https://www.youtube.com/watch?v=KkwX7FkLfug

//==============================================================================

#include <iostream> 	/* cout */
#include <vector>
#include <cassert>
#include <iomanip>

#include "Neural_net.h"
#include "Neuron.h"

/*
	code
*/

double eta = 0.15;	//good between 0.1 and 0.2
double alpha = 0.5;	//multiplier of last weight change (momentum)

int main(){
	std::vector<unsigned> topology;
	topology.push_back(2);
	topology.push_back(4);
	topology.push_back(1);
	Net myNet(topology);
	
	std::vector<double> inputVals,targetVals,resultVals;
	
	std::cout << std::endl;
	std::cout << "==========================" << std::endl;
	std::cout << "====== XOR trainer! ======" << std::endl;
	std::cout << "======  1 ^ 1  = 0  ======" << std::endl;
	std::cout << "======  0 ^ 0  = 0  ======" << std::endl;
	std::cout << "======  1 ^ 0  = 1  ======" << std::endl;
	std::cout << "======  0 ^ 1  = 1  ======" << std::endl;
	std::cout << "==========================" << std::endl;
	
	unsigned loops,runs = 0;
			std::cout << std::endl;
		std::cout << "How many trials? " << std::fixed << std::setprecision(4);
		std::cin >> loops;
		int in1,in2;
		double TGoutput;
	
	if (loops == -1){
		myNet.read_from_binary();
		std::cout << "How many trials? ";
		std::cin >> loops;
	}
	
	do{
		for (unsigned c = loops; c > 0; --c) {
			
			std::cout << std::endl;
			inputVals.clear();
			targetVals.clear();
			
			in1 = 
			(int)(2.0 * rand()/double(RAND_MAX));
			in2 = 
			(int)(2.0 * rand()/double(RAND_MAX));
			inputVals.push_back(in1);
			inputVals.push_back(in2);
			myNet.feedForward(inputVals);
			
			myNet.getResults(resultVals);
			
			TGoutput = in1 ^ in2;
			targetVals.push_back(TGoutput);
			assert(targetVals.size() == topology.back());
			myNet.backProp(targetVals);
			
			if(c < 11){
				std::cout << "Run #" << ++runs << std::endl;
				std::cout << '\t' << "Inputs: " << in1 << ".0 , " << in2 << ".0" << std::endl;
				std::cout << '\t' << "Output: " << (resultVals[0]) << std::endl;
				std::cout << '\t' << "target: " << (TGoutput) << std::endl;
				std::cout << '\t' << "Root Mean square Error: "
						<< myNet.getErrorConfidince() 
						<< std::endl;
			}
			else{
				std::cout << "Run #" << ++runs << " RMS Error: "
						<< myNet.getErrorConfidince() 
						<< std::endl;
			}
		}
		
			std::cout << std::endl;
		
		std::cout << "How many trials? ";
		std::cin >> loops;
		
		if (loops == -1){
			myNet.save_to_binary();
			loops = 0;
		}
		
		std::cout << std::endl;
	}while(loops>0);
	
	std::cout << "done" <<std::endl;
}

//windows	====================================================================
#if os == 0

//Unix	========================================================================
#elif os == 1
    
#endif	//======================================================================
