/**
 * 
 * FiniteAuomata.cpp
 *
 * The class for constructing and testing finite auomatas
 *
 * @version: $Id: FiniteAutomata.cpp,v 1.5 2007/07/31 23:18:20 jeg3600 Exp jeg3600 $
 *
 * @author: John Garnham
 *
 * Revisions:
 *     $Log: FiniteAutomata.cpp,v $
 *     Revision 1.5  2007/07/31 23:18:20  jeg3600
 *     Should be final
 *
 *     Revision 1.4  2007/07/31 22:34:09  jeg3600
 *     Properly handles lambdas
 *
 *     Revision 1.3  2007/07/31 22:07:50  jeg3600
 *     First test run
 *
 *     Revision 1.2  2007/07/31 20:51:27  jeg3600
 *     Fixed printing issue
 *
 *     Revision 1.1  2007/07/31 19:54:35  jeg3600
 *     Initial revision
 *
 *
 *
 */

#include "FiniteAutomata.h"
#include <set>
#include <map>

typedef std::map<char, State> stateMap;

FiniteAutomata::FiniteAutomata() {
  // Set the default start state to ' ' (No start state)
  startState = ' ';
}

std::set<char> FiniteAutomata::getAlphabet() {
  return alphabet;
}

void FiniteAutomata::addInputSymbol(char newLetter) {
  alphabet.insert(newLetter);
}

void FiniteAutomata::addState(char newLetter) {
  State newState;
  states.insert(stateMap::value_type(newLetter, newState));
}

bool FiniteAutomata::hasInputSymbol(char letter ) {

  // Try to find the letter
  std::set<char>::iterator iter = alphabet.find(letter);
   if (iter == alphabet.end()) {
     return false;
   } else {
     return true;
   }

}

bool FiniteAutomata::hasState(char letter) {
  
  bool found = false;

  // Try to find the state
  stateMap::iterator iter;
  for(iter = states.begin(); iter != states.end(); ++iter) {
    if ((*iter).first == letter) {
      found = true;
    }
  }

  return found;

}

bool FiniteAutomata::hasStartState() {
  return (startState != ' ');
}

void FiniteAutomata::setStartState(char state) {

  // Make sure that the start state hasn't already been defined
  if (startState != ' ') {
    throw "Start state already defined.";
  } else {
    startState = state;
  }

}

char FiniteAutomata::getCurrentState() {
  return currentState;
}

bool FiniteAutomata::process(char letter) {

  // Make sure that it is a valid input symbol. If not, always rejected.
  if (! hasInputSymbol(letter)) {
    return false;
  }

  // Update the current state by transitioning on the input
  currentState = states[currentState].getTransition(letter);
  
  // Return whether or not in accepting state
  return states[currentState].isAcceptingState();

}

bool FiniteAutomata::process(std::string testString) {

  // Handle lambda
  if (testString.length() == 0) {
    return states[currentState].isAcceptingState();
  }

  // Go through the string letter by letter
  for(int i = 0; i < testString.length(); ++i) {

    // Get the current letter
    char current = testString.at(i);
    
    // Make sure that it is a valid input symbol. If not, always rejected.
    if (! hasInputSymbol(current)) {
      return false;
    }
    
    // Process that letter
    process(current);

  }

  // Return whether or not in accepting state
  return FiniteAutomata::states[currentState].isAcceptingState();

}

State* FiniteAutomata::getState(char letter) {
  // Return a reference to the state
  return &states[letter];
}

/**
void FiniteAutomata::print() {

  // Not run in actual program. Mostly for debugging.

  std::string returns;
  std::cout << "Alphabet: ";

  // Print out the alphabet
  std::set<char>::iterator iter;
  for(iter = alphabet.begin(); iter != alphabet.end(); ++iter) {
    std::cout << (*iter);
  }

  std::cout << "\n" << states.size() << " states:\n";

  // Print out the states and transitions

  stateMap::iterator iter2;
  for(iter2 = states.begin(); iter2 != states.end(); ++iter2) {

    if ((*iter2).second.isAcceptingState()) { 
      std::cout << "Accepting: ";
    } else if ((*iter2).first == startState) {
      std::cout << "Start: ";
    }
    std::cout << (*iter2).first << "\n";
    
    std::set<char>::iterator iter3;
    for(iter3 = alphabet.begin(); iter3 != alphabet.end(); ++iter3) {
      std::cout <<  "(" << (*iter2).first << "," << (*iter3) << ")";
          // Print out the alphabet
      std::cout << " -> " << (*iter2).second.getTransition((*iter3));
      std::cout << std::endl;
    }
      
  }

}
*/

void FiniteAutomata::validate() {

  std::string message;

  // Make sure that automata has a start state
  if (! hasStartState() ) {
    message = "No start state.";
    throw message;
  }

  // Make sure that all of the transitions are complete
  stateMap::iterator iter;
  for(iter = states.begin(); iter != states.end(); ++iter) {

    std::set<char>::iterator iter2;
    for(iter2 = alphabet.begin(); iter2 != alphabet.end(); ++iter2) {
      
      if (! (*iter).second.hasTransition((*iter2))) {
	message = "Incomplete transition functions.";
	throw message;
      }

    }

  }

}

void FiniteAutomata::reset() {
  
  // Make the current state the start state
  currentState = startState;

}
