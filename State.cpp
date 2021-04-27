/**
 *
 * State.cpp
 *
 * The class for defining a state and transitions from that state
 *
 * @version: $Id: State.cpp,v 1.4 2007/07/31 23:18:02 jeg3600 Exp jeg3600 $
 *
 * @author: John Garnham
 *
 * Revisions:
 *     $Log: State.cpp,v $
 *     Revision 1.4  2007/07/31 23:18:02  jeg3600
 *     Should be final
 *
 *     Revision 1.3  2007/07/31 22:08:06  jeg3600
 *     First test run
 *
 *     Revision 1.2  2007/07/30 00:11:15  jeg3600
 *     1st
 *
 *     Revision 1.1  2007/07/29 23:52:40  jeg3600
 *     Initial revision
 *
 *
 *
 */

#include "State.h"
#include <iostream>
#include <map>

typedef std::map<char,char> charMap;

// Constructor for state
State::State() {
  acceptingState = false;
}

bool State::isAcceptingState() {
  return acceptingState;
}

void State::addTransitionFunction(char input, char newState) {

  transitions[input] = newState;

}

char State::getTransition(char input) {
  return transitions[input];
}

bool State::hasTransition(char input) {
  bool found = false;

  // Try to find the input symbol
  charMap::iterator iter;
  for(iter = transitions.begin(); iter != transitions.end(); ++iter) {
    if ((*iter).first == input) {
      found = true;
    }
  }

  return found;
}

void State::setAsAccepting() {
  acceptingState = true;
}

/**
std::string State::printTransitions() {
  
  // Mostly for debugging
  std::cout << transitions.size() << " transitions." << std::endl;
  std::string returns = "";

  charMap::iterator iter;
  for(iter = transitions.begin(); iter != transitions.end(); ++iter) {
    returns = returns + (*iter).first + " -> ";
    returns = returns + (*iter).second + "\n";
  }

  return returns;

}
*/
