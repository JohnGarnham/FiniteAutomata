/**
 *
 * TestString.cpp
 *
 * The main executable for testing a string on a finite auomata
 *
 * @version: $Id: TestString.cpp,v 1.7 2007/07/31 23:26:18 jeg3600 Exp jeg3600 $
 *
 * @author: John Garnham
 *
 * Revisions:
 *     $Log: TestString.cpp,v $
 *     Revision 1.7  2007/07/31 23:26:18  jeg3600
 *     Now accepts empty lines in state definitions
 *
 *     Revision 1.6  2007/07/31 23:17:51  jeg3600
 *     Should be final
 *
 *     Revision 1.5  2007/07/31 22:34:26  jeg3600
 *     Properly handles lambas
 *
 *     Revision 1.4  2007/07/31 22:08:26  jeg3600
 *     First test run
 *
 *     Revision 1.3  2007/07/29 21:53:06  jeg3600
 *     Deals with comments now
 *
 *     Revision 1.2  2007/07/29 20:39:41  jeg3600
 *     Correctly accepts alphabet
 *
 *     Revision 1.1  2007/07/29 19:37:40  jeg3600
 *     Initial revision
 *
 *
 *
 */

#include <iostream>
#include <set>
#include "FiniteAutomata.h"

using namespace std;

int main(int argc, char* argv[]) {


  // Temp value for user input
  string input = "";

  // The automata
  FiniteAutomata automata;
  
  // Used for indexing and parsing
  int index = 0;
  
  // Grab the line defining the alphabet
  do {
    
    getline(cin, input);
    
    if (input.length() != 0) {
    
      // Get rid of initial comments
      if ((index = input.find_first_not_of(' ')) != string::npos) {
	input = input.substr(index);
      }
	
    }
    
  } while (input.length() != 0 && input.at(0) == '/');

  // Parse through the line
  while ((index = input.find_first_not_of(' ')) != string::npos) {
    
    // Trim leading white space
    input = input.substr(index);
    
    // Grab the next letter
    char newLetter = input.at(0);
    
    // Make sure the "letter" is only single-charactered
    if (input.length() > 1 && input.at(1) != ' ') {
      cerr << "Alphabet may only contain single characters.\n";
      exit(0);
    } 
    
    // Check if the alphabet already has that letter
    if (automata.hasInputSymbol(newLetter)) {
      cerr << "Duplicate alphabet character specified.\n";
      exit(0);
    } else { 
      automata.addInputSymbol(newLetter);
    } 
  
    // Go on to the rest of it
    input = input.substr(1);
  
  }

  // Make sure there actually is an alphabet
  if (automata.getAlphabet().size() == 0) {
    cerr << "No alphabet defined.\n";
    exit(0);
  }
  
  // Grab the states that you need
  getline(cin, input);
  
  // Get rid of white space
  if ((index = input.find_first_not_of(' ')) != string::npos) {
    input = input.substr(index);
  }  

  // Parse the input
  while(input.compare("#") != 0) {

    if (input.length() != 0) {

      //  Ignore comments
      if(input.at(0) != '/') {
      
	// Set start state
	if (input.at(0) == '>') {
	  
	  // Make sure that there is only one start state
	  if (automata.hasStartState()) {
	    cerr << "You may only have one start state" << endl;
	    exit(0);
	  }
	  
	std::string rest = input.substr(1);
	
	// Get rid of white space
	if ((index = rest.find_first_not_of(' ')) != string::npos) {
	  rest = rest.substr(index);
	} else {
	  cerr << "No start state specified after >." << endl;
	  exit(0);
	}
	
	char state = rest.at(0);
	
	if (! automata.hasState(state)) {
	  automata.addState(state);
	}
	
	automata.setStartState(state);
	
	// Set accepting state
	} else if (input.at(0) == '<') {
	  
	  std::string rest = input.substr(1);
	  
	  // Get rid of white space
	  if ((index = rest.find_first_not_of(' ')) != string::npos) {
	    rest = rest.substr(index);
	  } else {
	    cerr << "No accepting state specified after <." << endl;
	    exit(0);
	  }

	  char state = rest.at(0);
	  
	  // If the state does not already exist, then add it
	  if (! automata.hasState(state)) {
	    automata.addState(state);
	  }
	  
	  // Set that state as an accepting state
	  automata.getState(state)->setAsAccepting();

	  // Otherwise it a transition definition 
	} else {
	  
	  // Grab the state
	  
	  std::string rest = input.substr(0);
	  
	  // Get rid of white space
	  if ((index = rest.find_first_not_of(' ')) != string::npos) {
	    rest = rest.substr(index);
	  } else {
	    cerr << "Invalid machine definition" << endl;
	    exit(0);
	  }
	  
	  char state = rest.at(0);

	  // If the state does not already exist, then add it
	  if (! automata.hasState(state)) {
	    automata.addState(state);
	  }
	  
	  // Grab the input symbol
	  
	  rest = rest.substr(1);

	  // Get rid of white space
	  if ((index = rest.find_first_not_of(' ')) != string::npos) {
	    rest = rest.substr(index);
	  } else {
	    cerr << "Incomplete transition function." << endl;
	    exit(0);
	  }
	  
	  char inputsym = rest.at(0);
	  
	  // Make sure that the input symbol is in the alphabet
	  if (! automata.hasInputSymbol(inputsym)) {
	    cerr << "Invalid input symbol." << endl;
	    exit(0);
	  } 
	  
	  // Grab where to go
	  rest = rest.substr(1);
	  
	  // Get rid of white space
	  if ((index = rest.find_first_not_of(' ')) != string::npos) {
	  rest = rest.substr(index);
	  } else {
	    cerr << "Incomplete transition function." << endl;
	    exit(0);
	  }
	  
	  char to = rest.at(0);
	  
	  // If the state doesn't already exist, then add it
	  if (! automata.hasState(to)) {
	    automata.addState(to);
	  }	
	  
	  // Make sure a previous transition function isn't being rewritten
	  if (! automata.getState(state)->hasTransition(inputsym)) {
	    // Add the transition function
	    automata.getState(state)->addTransitionFunction(inputsym, to);
	  } else {
	    cerr << "The finite automata must be deterministic." << endl;
	  exit(0);
	  }
	  
	}
	
	index = input.find(" ", 0);
	while(input.at(index + 1) == ' ') {
	  index = input.find(" ", index + 1);
	}
	
      }

    }

    getline(cin, input);

    // Get rid of white space
    if ((index = input.find_first_not_of(' ')) != string::npos) {
      input = input.substr(index);
    }  
    
  }


  // Make sure that all of the transitions are defined
  try {
    automata.validate();
  } catch(string message) {
    cerr << message << endl;
    exit(0);
  } catch (...) {
    cerr << "Incomplete machine definition." << endl;
    exit(0);
  }
  
  // Print the automata. Mostly for debugging.
  // automata.print();

  // Grab the strings to test
  getline(cin, input);

  while(! cin.eof() ) {
    
    // Ignore comments
    if(input.length() == 0 || input.at(0) != '/') {

      automata.reset();

      if (automata.process(input)) {
	cout << "accepted\n";
      } else {
	cout << "rejected\n";
      }

    }
    
    getline(cin, input);
    
  }

}



