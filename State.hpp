#pragma once

#include "ExitCondition.hpp"
#include <vector>

#include <boost/signals2/signal.hpp>

namespace
{
//TO-DO: maybe
enum class EStateAction
  {
    eEntryAction,
    eInState,
    eExitAction,
  };

  template <typename TStateType>
  class CState
  {
    public:

      //------------------------------------------------------------------------
      //------------------------------------------------------------------------
      //TO-DO: add while in state option
      CState(
        const TStateType& StateIdentifier,
        std::vector<CExitCondition>&& ExitConditions)
        :mStateIdenitifier(StateIdentifier),
         mExitConditions(std::move(ExitConditions))
      {
      };

      //------------------------------------------------------------------------
      //------------------------------------------------------------------------
      void HeartBeat() const
      {
        //TO-DO: consider mutex lock here since accessing ref values
        for (const auto& Each : mExitConditions)
        {
          if (Each())
          {
            mSignalTransitionFromTo(mStateName, Each.GetExitStateId())
          }
        }
      }

      boost::signals2::signal<void(TStateType, TStateType)> mSignalTransitionFromTo;

      //TO-DO: eventually if while in state
      //boost::signals2::signal<void(const ARepeatType&)> mInStateSignal;

      const TStateType mStateName;

      const std::vector<CExitCondition> mExitConditions;
  };
}

