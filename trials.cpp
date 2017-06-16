#include "stdafx.h"
#include <math.h>
#include "Resource.h"
#include "Robot.h"
#include "ForceProgram.h"
#include "Keyboard.h"
#include "ErrorHandler.h"
#include "Trials.h"
#include "Drawings.h"
#include "Text.h"
#include "Target.h"
#include "Cursor.h"
#include "IntentionDisplay.h"
#include "definition.h"
#include "Parameters.h"
#include "KalmanFilter.h"
#include "GlobalStuff.h"
#include <fstream>
#include <sstream>
#include <exception>
#include <vector>
#define M_PI 3.14159265358979323846 /* pi */
using namespace std;

#include "MMsystem.h"	//for playing sounds
#pragma comment( lib, "Winmm.lib" )	//add the necessary .lib file

extern ofstream debuglog;
#define DEBUG(X) debuglog << #X << ": " << X << endl;


Trial::Trial(Robot& robot, Drawings& draw, forceProgram& forces, Keyboard& keyboard, const vector<TwoDoubles>& pointLocations)
	: _robot(robot), _draw(draw), _forces(forces), _keyboard(keyboard), _pointLocations(pointLocations)
{
}

Trial::~Trial()
{}

// Initialize all variables for the Behavior Parameters
double movementSpeedThreshold;
double originRadius;
double originHitRadius;
Drawings::colorType originColor;
Drawings::colorType originColorReach;
double endpointRadius;
Drawings::colorType endpointColor;
double shoulderX;
double shoulderY;
double upperArmLength;
double foreArmLength;
double targetDrawRadius;
double targetHitRadius;
Drawings::colorType targetHoldColor;
Drawings::colorType targetGoColor;
double intentionSpacingDeg;
int intentionFontsize;
Drawings::colorType intentionColor;
double displayCursorDistance;
double displayCursorDistanceTarget;
Drawings::colorType successColor;
Drawings::colorType slowColor;
Drawings::colorType fastColor;
Drawings::colorType missColor;
Drawings::colorType itiColor;
double trialFeedbackTime;
double maxPushToOriginTime;
double showOriginRadius;
double trialTime;
double trialWindow;
double maxTrialTime;
double originHoldTime;
double maxReactionTime;
double dampingTime;
double maxPushbackTime;
double breakThreshold;
double itiThreshold;
int	playSuccessSound;
int	playMissSound;
int	playFastSound;
int	playSlowSound;
string	successSoundFile;
string	missSoundFile;
string	fastSoundFile;
string	slowSoundFile;
Drawings::colorType positionFeedback;
TwoDoubles savePosition;
TwoDoubles correction;

// Load all Behavior Parameters from the .dat file
void Trial::loadBehavioralParameters(const ParameterList& behaviorParams, const ParameterList& blockParams)
{
	movementSpeedThreshold = behaviorParams["MovementSpeedThreshold[cm/ms]"].getValueD();
	originRadius = behaviorParams["OriginRadius[cm]"].getValueD();
	originHitRadius = behaviorParams["OriginHitRadius[cm]"].getValueD();
	originColor = Drawings::char2Color(behaviorParams["OriginColor"].getValueC());
	endpointRadius = behaviorParams["EndpointRadius[cm]"].getValueD();
	endpointColor = Drawings::char2Color(behaviorParams["EndpointColor"].getValueC());
	positionFeedback = Drawings::char2Color(behaviorParams["PositionFeedback"].getValueC());
	shoulderX = behaviorParams["ShoulderX[cm]"].getValueD();
	shoulderY = behaviorParams["ShoulderY[cm]"].getValueD();
	upperArmLength = behaviorParams["UpperArmLength[cm]"].getValueD();
	foreArmLength = behaviorParams["ForeArmLength[cm]"].getValueD();
	targetDrawRadius = behaviorParams["TargetDrawRadius[cm]"].getValueD();
	targetHitRadius = behaviorParams["TargetHitRadius[cm]"].getValueD();
	targetHoldColor = Drawings::char2Color(behaviorParams["TargetHoldColor"].getValueC());
	targetGoColor = Drawings::char2Color(behaviorParams["TargetGoColor"].getValueC());
	intentionSpacingDeg = behaviorParams["IntentionSpacing[deg]"].getValueD();
	intentionFontsize = behaviorParams["IntentionFontsize[pts]"].getValueI();
	intentionColor = Drawings::char2Color(behaviorParams["IntentionColor"].getValueC());
	displayCursorDistance = behaviorParams["DisplayCursorDistance[cm]"].getValueD();
	displayCursorDistanceTarget = behaviorParams["DisplayCursorDistanceTarget[cm]"].getValueD();
	itiColor = Drawings::char2Color(behaviorParams["TargetITIColor"].getValueC());
	trialFeedbackTime = behaviorParams["TrialFeedbackTime[ms]"].getValueD();
	maxPushToOriginTime = behaviorParams["MaxPushToOriginTime[ms]"].getValueD();
	showOriginRadius = behaviorParams["ShowOriginRadius[cm]"].getValueD();
	originHoldTime = behaviorParams["OriginHoldTime[ms]"].getValueD();
	trialTime = behaviorParams["TrialTime[ms]"].getValueD();
	trialWindow = behaviorParams["TrialWindow[ms]"].getValueD();
	maxTrialTime = behaviorParams["MaxTrialTime[ms]"].getValueD();
	maxReactionTime = behaviorParams["MaxReactionTime[ms]"].getValueD();
	dampingTime = behaviorParams["DampingTime[ms]"].getValueD();
	maxPushbackTime = behaviorParams["MaxPushbackTime[ms]"].getValueD();
	breakThreshold = behaviorParams["BreakThreshold[ms]"].getValueD();
	itiThreshold = behaviorParams["ITIThreshold[ms]"].getValueD();
	correction.x = behaviorParams["CorrectionX[cm]"].getValueD();
	correction.y = behaviorParams["CorrectionY[cm]"].getValueD();

	playSuccessSound = behaviorParams["PlaySuccessSound"].getValueI();
	playMissSound = behaviorParams["PlayMissSound"].getValueI();
	playFastSound = behaviorParams["PlayFastSound"].getValueI();
	playSlowSound = behaviorParams["PlaySlowSound"].getValueI();
	successSoundFile = behaviorParams["SuccessSoundFile"].getValueS();
	missSoundFile = behaviorParams["MissSoundFile"].getValueS();
	fastSoundFile = behaviorParams["FastSoundFile"].getValueS();
	slowSoundFile = behaviorParams["SlowSoundFile"].getValueS();

	// Params we get from block inputFiles and not behaviorParams.dat
	successColor = Drawings::char2Color(blockParams["TargetSuccessColor"].getValueC());
	slowColor = Drawings::char2Color(blockParams["TargetSlowColor"].getValueC());
	fastColor = Drawings::char2Color(blockParams["TargetFastColor"].getValueC());
	missColor = Drawings::char2Color(blockParams["TargetMissColor"].getValueC());

}

// Initialize the variables for Trial Parameters
int originPoint;
int visualPerturbationType;
int showCursor;
double rotation;
int targetPoint;
int forceType;
double forceGain;
double ITI;
int nextOriginPoint;
string showBackground;
TwoDoubles originLocation;
TwoDoubles originLocationRobot;
TwoDoubles targetLocation;
TwoDoubles nextOriginLocation;
TwoDoubles nextOriginLocationRobot;
bool cursorUpdate = true;
bool backgroundUpdate = true; 
int getIntention;


// Variables for trial statistics
bool succesfulTrial;
double trialMovementTime;
double reactionTime;
double totalTrialMovementTime;
bool saveData = false;
double trialWindowNext;

// Load the Trial Parameters from input .dat files
void Trial::loadTrialParameters(const ParameterVectorList& trialParams, int trialNum)
{
	originPoint = trialParams(trialNum, "Origin").getValueI();
	visualPerturbationType = trialParams(trialNum, "VisualPerturbationType").getValueI();
	showCursor = trialParams(trialNum, "showCursor").getValueI();
	rotation = trialParams(trialNum, "VisualRotationDeg").getValueD();
	targetPoint = trialParams(trialNum, "Target").getValueI();
	forceType = trialParams(trialNum, "forceType").getValueI();
	forceGain = trialParams(trialNum, "forceGain").getValueD();
	ITI = trialParams(trialNum, "interTrialInterval").getValueD();
	nextOriginPoint = trialParams(trialNum, "NextOrigin").getValueI();  // This trials origin
	showBackground = trialParams(trialNum, "showBackground").getValueS();
	getIntention = trialParams(trialNum, "getIntention").getValueI();

	originLocation = _pointLocations[originPoint-1];
	targetLocation = _pointLocations[targetPoint-1];
	nextOriginLocation = _pointLocations[nextOriginPoint-1];
	nextOriginLocationRobot = nextOriginLocation - correction;
	originLocationRobot = originLocation - correction;
	rotation = (rotation*(M_PI/180));
}

// Sets the output variables for saving data
const int numOutputDataVars = 8;
char *outputDataNames[numOutputDataVars] = {	"Time", "PosX", "PosY",	"VelX",	"VelY",	"ForceX", "ForceY",	"Stage" };
char outputDataTypes[numOutputDataVars] = { 'i', 'd', 'd', 'd', 'd', 'd', 'd', 'i' };

Parameter outputData[numOutputDataVars] = {
	Parameter((int) 0), Parameter((double) 0.0), Parameter((double) 0.0), Parameter((double) 0.0),	Parameter((double) 0.0),
	Parameter((double) 0.0), Parameter((double) 0.0), Parameter((int) 0) };


// Structure for the display of intention
IntentionDisplay intentionTexts; // Used for the display subjects use for intention



/****************************************************************
Start Trial
****************************************************************/
void Trial::startTrial() {
	currentStage = trialStart;

	// Generate a ParameterListVector for storing the data from the trial
	vector<string> dataNames;
	vector<char> dataTypes;
	dataNames.assign(outputDataNames, outputDataNames+numOutputDataVars);
	dataTypes.assign(outputDataTypes, outputDataTypes+numOutputDataVars);
	saveDataTimeStep.createEmpty( dataNames, dataTypes );


	// Generate a 0 time for the data
	//    Actually the 0 time is found when we first start running 
	//    processTrial(), but here we reset it so that it is 'refound
	zeroTime = -1;

	saveDataTrial.clear();

	intentionTexts.init(intentionSpacingDeg, intentionFontsize, intentionColor);


}


// The main routine of the Trial program
void Trial::processTrial(Drawings& draw) {
	static double delayTimer = 0.0;
	static double trialMovementTime = 0.0;
	static double dampTime = 0.0;
	static Target target;
	static Target origin;
	static Cursor cursor;
	static Text testText;
	static TwoDoubles lastCursorPosition;
	static Cursor cursorReturn;



	TwoDoubles robotPosition;
	if (!_robot.getPosition(robotPosition)) {
		return;
	} else {
		robotPosition = robotPosition + correction;
		if (!cursorUpdate) {
			// no update of cursor position
			cursor.setPosition(savePosition);
			cursorReturn.setPosition(robotPosition);
		} else {
			cursor.setPosition(robotPosition);
			cursorReturn.setPosition(robotPosition);
		}
	}
	TwoDoubles robotVelocity;
	if (!_robot.getVelocity(robotVelocity)) {
		return;
	}
	bool robotMoving = robotVelocity.magnitude() >= movementSpeedThreshold;
	TwoDoubles robotForce;
	if (!_robot.getForce(robotForce)) {
		return;
	}

	// We need an 'old time' but we have to make sure it is valid coming from the robot
	static long storedTime = -1;
	if (storedTime <= 0 || zeroTime <= 0) {
		long tempTime;
		if (_robot.getTimeMs(tempTime)) {
			storedTime = tempTime;
			if (zeroTime <= 0) {
				zeroTime = tempTime;
				lastCursorPosition = cursor.getDisplayedPosition(); // Set the last cursor position to current at the beginning of each trial
			}
		}
		return;
	}
	if (!_robot.getTimeMs(robotTime)) {
		return;
	}
	double deltaTime = (double) (robotTime - storedTime);
	storedTime = robotTime;

	// Switch of currentStage that "runs" all trials
	switch(currentStage)
	{
	case trialStart:
		{
			// Save trial characteristics to output file
			saveDataTrial.addParam("OriginX", Parameter(originLocation.x));
			saveDataTrial.addParam("OriginY", Parameter(originLocation.y));
			saveDataTrial.addParam("TargetX", Parameter(targetLocation.x));
			saveDataTrial.addParam("TargetY", Parameter(targetLocation.y));
			saveDataTrial.addParam("visualPerturbationType", Parameter(visualPerturbationType));
			saveDataTrial.addParam("rotation", Parameter(rotation));
			saveDataTrial.addParam("forceType", Parameter(forceType));
			saveDataTrial.addParam("forceGain", Parameter(forceGain));
			saveDataTrial.addParam("ITI", Parameter(ITI));
			saveDataTrial.addParam("showBackground", Parameter(showBackground));
			saveDataTrial.addParam("showCursor", Parameter(showCursor));
			saveDataTrial.addParam("getIntention", Parameter(getIntention));

			// If the input file has no background.bmp, we will call ClearScreen in GlobalStuff
			if (showBackground == "0") {
				// Draw origin and cursor
				origin.setPosition(originLocation);
				origin.setDrawParameters(originRadius, originColor);
				cursor.setDrawParameters(endpointRadius, endpointColor);
				origin.on();
				cursor.on();
				backgroundUpdate = true;
			}
			else {
				// if there is a .bmp in input file we will not clearScreen and keep background static
				origin.off();
				cursor.off();
				backgroundUpdate = false;
			}


			currentStage = outsideOriginMode;
		}
	case outsideOriginMode:
		{
			// Check whether cursor is inside the origin		
			if(origin.checkHit(cursor.getDisplayedPosition()) || backgroundUpdate == false){
				delayTimer = 0.0;
				deltaTime = 0.0;
				succesfulTrial = false;
				_forces.startHold(robotPosition);
				currentStage = insideOriginMode;
				//DEBUG("outsideOriginMode");
				//DEBUG(_forces.isHold());
				//DEBUG(_forces.isPush());
				// position
			} 

			break;
		}
	case insideOriginMode:
		{
			origin.setColor(originColorReach);
			// Let time pass independent of cursor being in the origin
			delayTimer = delayTimer + deltaTime;

			//DEBUG("insideOriginMode");
			//DEBUG(_forces.isHold());
			//DEBUG(_forces.isPush());

			if (showCursor == 0) {
				cursor.off();
			}

			if (delayTimer > ITI){
				origin.setDrawParameters(originRadius, originColor);
				target.setPosition(targetLocation);
				target.setDrawParameters(targetDrawRadius, targetHoldColor);
				target.on();

				PlaySound(NULL, NULL, 0); // Stop any sounds
				_forces.stopPush();
				saveData = true;
				delayTimer = 0.0;
				deltaTime = 0.0;
				currentStage = waitOriginHoldMode;

				if (getIntention) {
					intentionTexts.setPositions(originLocation, targetLocation);
					intentionTexts.on();
					 _keyboard.clearLine();

					currentStage = waitForResponseMode;  
				}

			} // end of ITI if

			break;
		}
	
	
	case waitForResponseMode:
		{
			
			BOOL enterPressed = _keyboard.lineReady(); // trying to skip input mode
			if (enterPressed) {	

				target.setColor(targetGoColor);
				_forces.stopHold();

				currentStage = reactionMode;
				
			}
			break;
		}


	case waitOriginHoldMode:
		{
			delayTimer = delayTimer + deltaTime;

			DEBUG("waitOriginHoldMode");
			DEBUG(_forces.isHold());
			DEBUG(_forces.isPush());

			if (delayTimer > originHoldTime) {
				target.setColor(targetGoColor);
				_forces.stopHold();

				// string naString = "nan";
				// saveDataTrial.addParam("intention", Parameter(naString));

				currentStage = reactionMode;

			}
			break;
		}


	case reactionMode:
		// Reaction = when robotVelocity gets above a certain treshold
		{
			
			delayTimer = delayTimer + deltaTime;

			// When robot moves, or reaction time has passed, or background is not being updated
			if(robotMoving || delayTimer > (maxReactionTime) || backgroundUpdate == false) {
				// Save the time it takes for subject to react to drawing of target
				intentionTexts.off();	// only turn numbers of when robot moves or too much time's passed
				reactionTime = delayTimer;
				saveDataTrial.addParam("reactionTime", Parameter(reactionTime));



				// Generate perturbation after reacion
				// Generate viscousField
				if (forceType == 1) {
					double matVals[] = {0, forceGain, -forceGain, 0};
					_forces.startViscous(Matrix(2,2, matVals));
				}
				// Generate forceChannel
				if (forceType == 2) {
					_forces.startChannel(robotPosition, targetLocation);
					cursor.clampError(robotPosition, targetLocation);
				}
				// Generate visualPerturbation
				if (visualPerturbationType == 1) {
					cursor.rotateDisplay(robotPosition, rotation);
				}
				// Generate visualChannel
				if (visualPerturbationType == 2) {
					cursor.clampError(robotPosition, targetLocation);
				}
				currentStage = targetMode;
			}
			break;
		}
	case targetMode:
		// After reaction from the subject, when he/she is moving towards the target
		{
			delayTimer = delayTimer + deltaTime;
			// Check if the cursor is outside an imaginary circle with radius equal to the distance between the origin and the target
			TwoDoubles radius = origin.getPosition() - target.getPosition();
			double radiusMag = radius.magnitude();
			double radiusMagTest = radiusMag + displayCursorDistanceTarget;

			// Check if we hit the target
			if(target.checkHit(cursor.getDisplayedPosition())) {
				succesfulTrial = true;
			}

			if(!(origin.checkHit(cursor.getDisplayedPosition(), radiusMagTest )) || delayTimer >= (maxTrialTime) || backgroundUpdate == false) 
			{
				// Get trialTime
				trialMovementTime = delayTimer;

				// Turn off forces
				_forces.stopChannel();
				_forces.stopViscous();
				cursor.setDrawParameters(endpointRadius, positionFeedback);

				cursorUpdate = false;
				if (delayTimer < maxTrialTime){
					TwoDoubles differenceVector = robotPosition - origin.getPosition();
					savePosition = 10*((robotPosition-origin.getPosition())/differenceVector.magnitude()) + originLocation;
				} else 
				{
					savePosition = robotPosition;
				}

				// Save the time and success parameters
				saveDataTrial.addParam("trialMovementTime", Parameter(trialMovementTime));
				saveDataTrial.addParam("Success", Parameter(succesfulTrial));

				// Can comment damping out, since this might give proprioceptive feedback on the location of your hand
				_forces.startDamping();
				//cursor.off();
				delayTimer = 0.0;
				deltaTime = 0.0;
				currentStage = setFeedbackMode;
			}
			break;
		}

	case setFeedbackMode:
		{
			delayTimer = delayTimer + deltaTime;
			saveDataTrial.addParam("trialWindow", Parameter(trialWindow));
			// Assume not playing any sound
			bool playSound = true;
			string soundFile = "";

			// Set the color of the target to reflect the success level
			// First check for movement time, then check for target hit

			// Speed OK && Target hit
			if((trialMovementTime >= (trialTime - trialWindow)) && (trialMovementTime <= (trialTime + trialWindow)) && succesfulTrial && backgroundUpdate == true)
			{
				trialWindowNext = (trialWindow * 0.9);
				target.setColor(successColor);
				cursor.setColor(successColor);
				target.on();
				if (playSuccessSound == 1) {
					playSound = true;
					soundFile = successSoundFile;
				}
			}
			// Speed OK && Target miss
			// In my case I don't care if you hit the target or not, just the speed matters (set missColor to be the same in behavParameters.dat)
			else if((trialMovementTime >= (trialTime - trialWindow)) && (trialMovementTime <= (trialTime + trialWindow)) && !succesfulTrial && backgroundUpdate == true)
			{
				trialWindowNext = (trialWindow * 0.9);
				target.setColor(missColor);
				cursor.setColor(missColor);
				target.on();
				if (playMissSound == 1) {
					playSound = true;
					soundFile = missSoundFile;
				}
			}
			// Too slow
			else if(trialMovementTime > (trialTime + trialWindow) && backgroundUpdate == true)
			{
				trialWindowNext = (trialWindow * 1.1);
				target.setColor(slowColor);
				cursor.setColor(slowColor);
				target.on();
				if (playSlowSound == 1) {
					playSound = true;
					soundFile = slowSoundFile;
				}
			}

			// Too fast
			else if(trialMovementTime < (trialTime - trialWindow) && backgroundUpdate == true)
			{
				trialWindowNext = (trialWindow * 1.1);
				target.setColor(fastColor);
				cursor.setColor(fastColor);
				target.on();
				if (playFastSound == 1) {
					playSound = true;
					soundFile = fastSoundFile;
				}
			}

			else
			{
				//do nothing
			}

			if (playSound == true) {
				PlaySound(soundFile.c_str(), NULL, SND_FILENAME | SND_ASYNC);
			}

			currentStage = dampMode;
			break;
		}

	case dampMode:
		{
			saveData = false;
			delayTimer = delayTimer + deltaTime;
			if (delayTimer > dampingTime || backgroundUpdate == false) 
			{
				//Make sure damping forces are off
				_forces.stopDamping();
				delayTimer = 0.0;
				deltaTime = 0.0;
				trialWindow = trialWindowNext;
				_forces.startPush(nextOriginLocationRobot);
				currentStage = pushBackMode;
			}
			break;
		}

	case pushBackMode:
		{
			// Set next origin location
			origin.setDrawParameters(originRadius, originColor);
			origin.setPosition(nextOriginLocation);

			// Wait for reaching next origin
			if(cursorReturn.checkHit(nextOriginLocation, displayCursorDistance) || backgroundUpdate == false) 
			{
				cursorUpdate = true;
				backgroundUpdate = true;
				target.off();
				cursor.off();
				origin.off();
				cursor.setPosition(robotPosition);
				cursorReturn.setPosition(robotPosition);
				cursor.setColor(successColor);

				// Turn off cursor perturbation 
				cursor.rotateOff();
				cursor.clampErrorOff();

				// Turn off all forces

				_forces.stopDamping();
				_forces.stopChannel();
				_forces.stopViscous();
				_forces.stopPush();
				currentStage = trialDone;

			}
			break;
		}


	case trialDone:	
		// The end case of the trial
		{
			break;
		}
	}//switch

	// save Data each timestep we loop over processTrial function
	if (saveData) {
		outputData[0].setValue((robotTime - zeroTime));
		outputData[1].setValue(robotPosition.x);
		outputData[2].setValue(robotPosition.y);
		outputData[3].setValue(robotVelocity.x);
		outputData[4].setValue(robotVelocity.y);
		outputData[5].setValue(robotForce.x);
		outputData[6].setValue(robotForce.y);
		outputData[7].setValue(currentStage);
		saveDataTimeStep.addData(outputData);
	}

	// Draw target, origin and cursor on screen
	target.draw(_draw);
	origin.draw(_draw);
	cursor.draw(_draw);
	intentionTexts.draw(_draw);

	// Update lastCursorPosition to current (so it will be good for next time)
	lastCursorPosition = cursor.getDisplayedPosition();
}




trialList::trialList()
	:
_numberOfTrials(0),
	_blockNumber(0),
	_trialParamsList(1) // Start counting from trial 1
{}


trialList::~trialList()
{}

// Get the location of the behaviorParameters.dat
void trialList::loadBehaviorParameters(const string& fileName)
{
	_behaviorParams.read(fileName);
}

// Get the positions of the different origins/targets.
void trialList::loadPointLocations()	
{
	string fileName = _behaviorParams["PointLocationFile"].getValueS();

	ifstream pointsLocationfile(fileName.c_str());
	if(pointsLocationfile.fail()){
		string message = "Can't open file: ";
		message += fileName;
		handleError(message, "Trials::ReadPointsLocationdFromFile()");
	}
	else
	{
		_pointLocations.clear();
		while(!pointsLocationfile.eof())	//read until the end of the file
		{
			TwoDoubles location;
			pointsLocationfile>>location.x;
			pointsLocationfile>>location.y;
			if(pointsLocationfile.fail())
				handleError("  can't read points location file", "Trials::ReadPointsLocationdFromFile()");
			_pointLocations.push_back(location);
		}
		pointsLocationfile.close();

	}//else
}

// Get the location of the .input files
void trialList::loadTrials(const string& ID, const string& day, int blockNumber)
{
	//generate a string to know from where to read the information
	ostringstream fileName;
	//"XXXXXXX_DayX_BlockX.input"
	static TCHAR szDirectory[1500] = "";
	GetCurrentDirectory(sizeof(szDirectory) - 1, szDirectory); //directory from which the exe runs

	fileName<<szDirectory<<"\\InputFiles\\" << ID << "_Day" << day << "_Block" << blockNumber << ".input";

	string filenameString = fileName.str();

	ifstream input_file(filenameString.c_str(), ios::in);	//parameters will be read from "input file"
	if(input_file.fail()) {	//check if read successfully
		handleError( "file does not exist in the necessary folder","Located in: ParameterList::ReadFromFile()");
	}

	input_file >> _blockInfo;

	_trialParamsList.readFromFile(input_file);

	_numberOfTrials = _trialParamsList.size();
	_blockNumber = blockNumber;
	_subjectID = ID;
	_subjectDay = day;
}//end of getTrials


