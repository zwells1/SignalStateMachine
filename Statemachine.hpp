#pragma once

#include "StateTable.hpp"

namespace
{
  class CStateMachine
  {
    public:

      CStateMachine();

      SetStatesAndTable(const CStateTable);

      GetStateTable();

      GetCurrentState();

      //Need something to drive this machine from state to state
      //needs to be compatible with the state transitions
      Heartbeat();

      Start();

    private:

      CheckStates();

  };
}

