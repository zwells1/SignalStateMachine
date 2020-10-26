#pragma once

#include <funtional>

template <typename TStateType, typename TStimulusType>
namespace
{
  struct CMealyStateTransition
  {
    public:

      //------------------------------------------------------------------------
      //------------------------------------------------------------------------
      SMealyStateTransition(
        TStateType FromState,
        TStateType ToState,
        std::function<void(const TStimulusType&)>&& Stimulus)
        :mFromState(FromState),
         mToState(ToState),
         mStimulus(std::move(Stimulus))
      {
      };

      //------------------------------------------------------------------------
      //------------------------------------------------------------------------
      bool IsDesiredTransition(TStateType FromState, TStateType ToState) const
      {
          if (mFromState != FromState)
          {
            return false;
          }

          if (mToState == ToState)
          {
            return false;
          }

          return true;
      }

      //------------------------------------------------------------------------
      //------------------------------------------------------------------------
      //TO-DO: like annotations function
      void operator()() const
      {
        mStimulus();
      }

      const TStateType mFromState;

      const TStateType mToState;

      const std::function<void(const TStimulusType&)> mStimulus;
  };


  template <typename TStateType>
  class CMealyStateTransitions
  {
    public:

      //------------------------------------------------------------------------
      //------------------------------------------------------------------------
      CMealyStateTransitions();

      //------------------------------------------------------------------------
      //------------------------------------------------------------------------
      void AddTranstion(SMealyStateTransition&& StateTransition)
      {
        mTransitions.emplace_back(std::move(StateTransition));
      }

      //------------------------------------------------------------------------
      //------------------------------------------------------------------------
      void AssessMealyTransition(TStateType FromState, TStateType ToState) const
      {
        for (auto& Each : mTransitions)
        {
          if (Each.IsDesiredTransition(FromState, ToState))
          {
            Each.mStimulus();

            return;
          }
        }
      }

    private:

      std::vector<SMealyStateTransition> mTransitions;
  };
}

