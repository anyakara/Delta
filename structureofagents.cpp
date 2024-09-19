#include <vector>
#include <string>

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
