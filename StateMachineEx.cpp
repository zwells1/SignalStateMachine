
enum EAllStates
{
  eStateA,
  eStateB,
  eStateC,
  eStateD
};


//no signal
CTransition T1(
  {eStateA, eStateB},
  eStateC,
  {});

CTransition T2(
  {eStateC},
  eStateD,
  [](){cout  std::cout << "transition from State C to D" <<  << std::endl;});


auto ExitConditionStateA = [heartbeat](){
  if (heartbeat == 4)
  {
    return true;
  }
  return false
};


//three constructors
//1 with just a state name, and exit transition
// constructor 2 state name, exit transition, Exit condition
// constructor 2 state name, exit transition, Exit condition

//    leaning towdard this one vvvvvvv
// or just 1 constructor with a state name and exit transition
// then dot operator like with tgl EarthIcons in sgfFrame.bold().color().closed()

CState::State StateA(
  EAllStates::eStateA,
  CExitCondition(ExitConditionStateA), //can add more if desired
  )

StateA.AddWhileInStateAction()


//Micro Class that checks all states, ensures they were all set
// checks for no duplicate states
mAllState.push_back(StateA);

//

