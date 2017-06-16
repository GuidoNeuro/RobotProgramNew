# RobotProgramNew
We want to control the parallelport form the version of the robot program that Jana and Charlotte are now using

To get the program working in "RobotProgram New.vcxproj" in debug mode, these steps need to happen:
- The changes in trials.cpp presented here
- Add INPOUT32.LIB and INPOUT32.DLL to the folder of the robot program
- Add INPOUT32.LIB to the project library in visual studio
- Add the complete ParallelPort map to the folder of the robot program
- Include CPaPiC.cpp and CPaPiC.h in the project via solution explorer
