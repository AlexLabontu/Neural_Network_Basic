#===============================================================================
#	Project: Nural_network
#	File: make.makefile
#	Author: Alex Labontu
#	Date: 2/22/2019 11:19:39 AM
#	Desc:	
#	
#	cd C:\Work_Station\Nural_networks\tutorial
#	      
#===============================================================================

flags = -g -ansi -fno-gnu-keywords -pedantic -std=gnu++11
Warnings = -Wall -W -Wfloat-equal -Winline -Wunreachable-code -Wredundant-decls -Wconversion -Wwrite-strings -Wcast-qual -Woverloaded-virtual -Weffc++
Includes =
Libs = 
Bins =
Statics = -static-libgcc -static-libstdc++

main.exe: makefile ofile/main.o ofile/Neural_net.o ofile/Neuron.o

	@echo.
	@echo. 
	
	-mv *.h.gch ofile/
	-mv *\*.h.gch ofile/

	@echo.
	@echo.
	g++ ofile/*.o -omain.exe -Dos=$(os) $(flags) $(Warnings) $(Includes) $(Libs) $(Bins) $(Statics)
	@echo.
	@echo. 

ofile/main.o: main.cpp Neural_net.h Neuron.h

	@echo.
	@echo.
	g++ -c main.cpp Neural_net.h -Dos=$(os) $(flags) $(Warnings) $(Includes) $(Libs) $(Bins) $(Statics)
	@echo.
	@echo.

	-mkdir ofile
	-mv *.o ofile/

ofile/Neural_net.o: Neural_net.cpp Neural_net.h Neuron.h

	@echo.
	@echo.
	g++ -c Neural_net.cpp Neural_net.h -Dos=$(os) $(flags) $(Warnings) $(Includes) $(Libs) $(Bins) $(Statics)
	@echo.
	@echo.

	-mkdir ofile
	-mv *.o ofile/
	
ofile/Neuron.o: Neuron.cpp Neuron.h

	@echo.
	@echo.
	g++ -c Neuron.cpp Neuron.h -Dos=$(os) $(flags) $(Warnings) $(Includes) $(Libs) $(Bins) $(Statics)
	@echo.
	@echo.

	-mkdir ofile
	-mv *.o ofile/

#===============================================================================

training.exe: training.cpp

	@echo.
	@echo.
	g++ training.cpp -otraining.exe -Dos=$(os) $(flags) $(Warnings) $(Includes) $(Libs) $(Bins) $(Statics)
	@echo.
	@echo.
	
train:
	training.exe > temp.txt

clean:
	-rm ofile/*
	-rm *.exe

clear:
	-rm ofile/*
	-rm *.exe

play:
	./main.exe

move:
	-mv src\*.h.gch ofile/
	-mv *.h.gch ofile/
	-mv *.o ofile/

raw:
	g++ main.cpp Neural_net.cpp Neuron.cpp -omain.exe -Dos=$(os) $(flags) $(Warnings) $(Includes) $(Libs) $(Bins) $(Statics)
