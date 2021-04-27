/**
 *
 * FiniteAutomata.h
 *
 * The class for constructing and running a finite automata.
 *
 * @version: $Id: FiniteAutomata.h,v 1.5 2007/07/31 23:18:14 jeg3600 Exp jeg3600 $
 * @author: John Garnham
 *
 * Revisions:
 *     $Log: FiniteAutomata.h,v $
 *     Revision 1.5  2007/07/31 23:18:14  jeg3600
 *     Should be final
 *
 *     Revision 1.4  2007/07/31 22:34:17  jeg3600
 *     Properly handles lambdas
 *
 *     Revision 1.3  2007/07/31 22:07:55  jeg3600
 *     First test run
 *
 *     Revision 1.2  2007/07/31 20:51:37  jeg3600
 *     Fixed printing issue
 *
 *     Revision 1.1  2007/07/29 18:53:09  jeg3600
 *     Initial revision
 *
 *
 */

#include <iostream>
#include <set>
#include <map>
#include "State.h"

typedef std::map<char, State> stateMap;

class FiniteAutomata {

 private:

  // The alphabet
  std::set<char> alphabet;

  // The states
  stateMap states;

  // Key to the start state
  char startState;

  // Key to the current state
  char currentState;

 public:

  FiniteAutomata();

  // Returns the alphabet
  std::set<char> getAlphabet();
  
  // Add an input symbol to the automata
  void addInputSymbol(char newLetter);

  // Add a state to the automata
  void addState(char newLetter);

  // Whether or not the letter is in the alphabet
  bool hasInputSymbol(char letter);

  // Whether or not it has the specified state
  bool hasState(char letter);

  // Whether or not it has a start state
  bool hasStartState();

  // Sets the start state
  void setStartState(char letter);

  // Return what the current state is
  char getCurrentState();

  // Run the letter
  bool process(char letter);

  // Run the string
  bool process(std::string testString);

  // Get the state symbolized by the letter
  State* getState(char letter);

  // Print the finite automata. Mostly for debugging purposes.
  // void print();

  // Test whether or not it is a valid automata
  void validate();

  // Reset the finite automata
  void reset();

};
