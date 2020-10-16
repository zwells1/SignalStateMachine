#pragma once

#include <function>

namespace
{
  enum class EStateAction
  {
    eEntryAction,
    eInState,
    eExitAction,
  };

  enum class EStateGuard
  {
    eEntryGuard,
    eExitGuard
  };

  using AStateActionMap = std::unordered_map<EStateAction, std::function<void()>>;

  using AStateGuardMap = std::unordered_map<EStateGuard, std::function<void()>>;

  class CState
  {
    public:

      CState(
        const std::string& StateName,
        AStateActionMap&& ActionMap,
        AStateGuardMap&& GuardMap);

      const std::string mStateName;

      const AStateActionMap mStateActionMap;

      const AStateGuardMap mStateGuardMap;
  };
}

