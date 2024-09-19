#include <vector>
#include <string>
#include <pair>

class Percept() {
  
}

class Action() {
  private:
    std::string actionName;
    std::vector<Percept> percepts; // chain of percepts that are formed while agent is in progress of completing a task
  // public: attributes to be implemented
}

// TODO: Implement hash table that contains all the actions with percepts being vectors

// pre-defined sequence of percepts
Action tableDrivenAgent(Percept percept) {
  Action flag;
  
  std::vector<Percepts> percepts;
  std::vector<Action> actions; // should rather be a hash table, right now just implementing something

  // append percept to the end of percepts;
  // action = Lookup(percepts, table);
  return action;
}


// Computationally expensive because of the requirement to remember all the previous percepts.
// Gives an idea of why theory of complexity of algorithms is important when extrapolating these solutions to a larger
// more complex robotic task


// -----------------------------------------------------------------------------------------------------------------

std::vector<Action> actionLookupTable;

void suckDirt() {
}

void moveRight() {
}

void moveLeft() {
}

void reflexVacuumAgent(std::pair<int, std::string> stateEstimate) {
  // Corresponds to which square on the grid needs to be cleaned -- or relative position marking
  if (stateEstimate.second == "dirty") { return suckDirt() }
  else if (stateEstimate.first == "1") { return moveRight() }
  else if (stateEstimate.first == "2") { return moveLeft() }
}






