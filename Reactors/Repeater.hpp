#pragma once

#include <boost/signals2/signal.hpp>

#include <chrono>
#include <condition_variable>
#include <mutex>
#include <optional>
#include <thread>

namespace
{
  enum class EUpdateStyle
  {
    eAllowAsynchronousUpdate,
    eConsistentBroadcast
  };

  template <typename ARepeatType>
  class CRepeater
  {
    public:
      //------------------------------------------------------------------------
      //------------------------------------------------------------------------
      static std::unique_ptr<CRepeater> Instance(
        EUpdateStyle UpdateStyle,
        std::chrono::milliseconds TimePeriod)
      {
        return std::unique_ptr<CRepeater>(
          new CRepeater<ARepeatType>(
            UpdateStyle,
            TimePeriod));
      }

      //------------------------------------------------------------------------
      //------------------------------------------------------------------------
      ~CRepeater()
      {
        maRun = false;

        mSleep.notify_all();

        std::unique_lock<std::mutex> Lock (mSleepMutex);

        if (mpThread)
        {
          mpThread->join();
        }
      }

      //------------------------------------------------------------------------
      //------------------------------------------------------------------------
      void Update(const ARepeatType Value)
      {
        if (!maRun)
        {
          return;
        }

        std::unique_lock<std::mutex> Lock(mDataMutex);

        bool HadDataThereforeAlreadyInitialized = moData.has_value();

        moData.emplace(Value);

        Lock.unlock();

        if (!HadDataThereforeAlreadyInitialized)
        {
          Initialize();

          mSignalData(Value);
        }
        else if (mUpdateStyle == EUpdateStyle::eAllowAsynchronousUpdate)
        {
          mSignalData(Value);
        }
      }

    private:

      //------------------------------------------------------------------------
      //------------------------------------------------------------------------
      CRepeater(
        EUpdateStyle UpdateStyle,
        std::chrono::milliseconds TimePeriod)
        : maRun(true),
        mUpdateStyle(UpdateStyle),
        mTimePeriod(TimePeriod),
        mpThread(nullptr)
      {
      }

      //------------------------------------------------------------------------
      //------------------------------------------------------------------------
      void Initialize()
      {
        mpThread.reset(
          new std::thread([this]
            {
              while (true)
              {
                if (!maRun)
                {
                  return;
                }

                std::unique_lock<std::mutex> SleepLock (mSleepMutex);

                mSleep.wait_for(SleepLock, mTimePeriod);

                //release data need data lock
                std::lock_guard<std::mutex> DataLock (mDataMutex);

                mSignalData(moData.value());
              }
            }));
      }

    public:

      boost::signals2::signal<void(const ARepeatType&)> mSignalData;

    private:

      std::atomic<bool> maRun;

      const EUpdateStyle mUpdateStyle;

      const std::chrono::milliseconds mTimePeriod;

      std::optional<ARepeatType> moData;

      std::condition_variable mSleep;

      std::mutex mDataMutex;

      std::mutex mSleepMutex;

      std::unique_ptr<std::thread> mpThread;
  };
}

