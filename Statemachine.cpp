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
