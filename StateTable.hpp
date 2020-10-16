#pragma once

namespace
{
  //TO-DO: transitation are strings now but can be changed to anything
  struct STransition
  {
    STransition(
      const std::string& FromState,
      const std::string& ToState);

    const std::string mFromState;

    const std::string mToState;
  }


  class CStateTable
  {
    public:

      CStateTable();

      SetStateTransitions();

    private:

      //checks for superflous states that have no connections or sates that will trap the machine
      CheckStateTransitions();

      const std::vector<STransition> mTransitions;
  };
}

