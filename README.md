Motivation:

The focus on a large, scalable state machines using modern c++ concepts. I wanted a signal/slots design. That inherently removed main event loops/while loops as part of the reactor.

I have also left it up to the software designer to add event queues to the control paths if they so desire.


Experience has shown that countless hours can be sunk into debugging only semi-complex state machines when a bug exists. The goal is to fix this.


Creating scalable state machines that move away from template nightmares is the goal.

Single threaded FSMs with Multithreaded HSM.


Rules I adhere to in this library:
- The State has an optional exit guard
- State cannot have an entry guard (this could result in a no-man's state)
- Transitions can have a signal (mealy) action.
 -- This update action will complete before the next state is entered.
- While in a state a signal can occur (optionally each cycle or only on transition into the state)
- While in a state all exit conditions are checked in order they were uploaded.
The first exit condtion that is satisified will trigger a transition to occur.
 -- If no exit condition is satisified, the while in-state signal will be fired (optionally)
- States must utilize minimum of 1 stimulus to move it to another state. More than 1 stimulus can be used.
  -- All states exit conditions are tied to the state's stimulus
- States must have an exit transition hooked up.

-Signals are allowed to change the outside world. If it afffects the state machine it will lock up.
 -- No circular dependency is allowed.

- Transistions can have n# of entry states. But only 1 exit state.
 -- No entry state == to the exit state. Initial check will ensure this


 inspiration for this library came from afsm and TinyFsm

Like the licensing, suggestions, dontations section of TinyFsm
