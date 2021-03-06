//
// Created by Sergey Kostyuk (http://git.io/vBvMH) on 26.12.15.
//

/*****************************************************************************/

#ifndef _MESSAGES_HPP_
#define _MESSAGES_HPP_

/*****************************************************************************/

namespace Messages {

	const char * const WrongPortName = "Port name can't be empty";

	const char * const WrongPointerToElement = "Unable to use nullptr as a pointer to element";
	const char * const WrongPointerToPort = "Unable to use nullptr as a pointer to port";

	const char * const ChangesInFinalizedCircuit = "Unable to change structute of the finalized circuit";
	const char * const CircuitAlreadyFinalized = "Unable to finalize circuit twice";
	const char * const CircuitWithoutElements = "Unable to create circuit without elements";
	const char * const CircuitWithoutPorts = "Unable to create circuit without ports";

	const char * const NonExistentPort = "Circuit hasn't port with such name";

	const char * const NonInputPort = "Unable to process this operation for non-input port";

	const char * const UnknownOperation = "Unknown operation was declared";
	const char * const UnspecifiedPort = "Port was not specified";
	const char * const UnspecifiedValue = "Value to set on port was not specified";
	const char * const InvalidValue = "Value to set on port is invalid";
	const char * const UnexpectedTextInLine = "There is unexpected text in the end of line";

}

/*****************************************************************************/

#endif //_MESSAGES_HPP_
