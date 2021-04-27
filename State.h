/**
 * 
 * State.h
 *
 * The class for defining a state and transitions from that state
 *
 * @version: $Id: State.h,v 1.4 2007/07/31 23:18:09 jeg3600 Exp jeg3600 $
 *
 * @author: John Garnham
 *
 * Revisions:
 *     $Log: State.h,v $
 *     Revision 1.4  2007/07/31 23:18:09  jeg3600
 *     Should be final
 *
 *     Revision 1.3  2007/07/31 22:08:00  jeg3600
 *     First test run
 *
 *     Revision 1.2  2007/07/30 00:11:03  jeg3600
 *     1st
 *
 *     Revision 1.1  2007/07/29 19:01:01  jeg3600
 *     Initial revision
 *
 *
 *
 */

#include <map>
#include <iostream>

typedef std::map<char,char> charMap;

class State {

  // Whether or not it is an accepting state
  bool acceptingState;

  // Transition functions
  charMap transitions;
  
 public:
      
  // Constructor for the state
  State();

  // Does this state accept?
  bool isAcceptingState();
  
  // Add directions on where to go
  void addTransitionFunction(char input, char newState);
  
  // Learn where to go from here
  char getTransition(char input);

  // Learn whether or not it has a transition for the specified input
  bool hasTransition(char input);

  // Set this state to an accepting state
  void setAsAccepting();

  // Print this state's transition functions. Mostly for debugging.
  // std::string printTransitions();

};
