#include "Statemachine.hpp"

using ::Statemachine;

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
CStatemachine::CStatemachine()
{
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
CStatemachine::Start()
{
  CheckStates();

  StartService();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
CStatemachine::StartService()
{
  //TO-DO: set up slot to connect to each Transition
  for (auto& State: mStates)
  {
    State.mSignalTransitionFromTo.connect[](TStateType FromState, TStateType ToState)
    {
      //TO-DO: call mealy state transition and see if any are set
      if (moMealyTransition)
      {
        moMealyTransition->AssessMealyTransition(FromState, ToState);
      }
    }
  }
}

