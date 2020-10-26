#include <functional>

#pragma once

namespace
{

  //TO-DO: use type ID-ing to get type checking
  template <typename TStateType, typename TExitConditionType>
  class CExitCondition
  {
    public:

      //------------------------------------------------------------------------
      //------------------------------------------------------------------------
      CExitCondition(
        const std::function<bool(TExitConditionType)>& ExitCondition,
        TStateType ExitStateId,
        Type Stimulus)
        :mExitCondition(std::move(ExitCondition)),
        mExitStateId(ExitStateId),
        mStimulus(Stimulus)
      {
      };

      //------------------------------------------------------------------------
      //------------------------------------------------------------------------
      TStateType GetExitStateId() const
      {
        return mExitState;
      };

      //------------------------------------------------------------------------
      //------------------------------------------------------------------------
      bool operator()() const
      {
        return mExitCondition(mStimulus);
      };

    private:

      std::function<bool(Type)> mExitCondition;

      TStateType mExitStateId;

      Type& mStimulus;
  };
}

