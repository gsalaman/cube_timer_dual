# System Architecture

## Overview
Controller:  responsible for overall control of the game.  Displays current state and any timers.
Consoles:  One per player.  Two buttons for R & L hands.  Responsible for:
* Determining when a player is ready
* Flagging early starts
* Telling the controller once a player has solved.

We'll start with the assumpting that "inspect" is hardcoded at 15s.  Next version we'll be able to configure that.

Inspects happen at the same time.  Any handicpaped player has to wait after this point for their timer to start before beginning the solve.

## Sample Flow (2 players)
Controller sets handicap....we'll arbitrarily say P1 starts 10s before P2.

Controller waits for "ready" from both players.

Each player waits for both buttons to be pressed before sending a ready back to the controller.  If buttons are releaseed, "not ready" is sent back.

Controller sends "start inspect" to both consoles.

Each console then starts their 15s timer.  At then end of this time, we start making sure both buttons are pressed again.

Controller sends "start" to console for P1.

P1 console then starts it's internal timer, and waits for release.

Once buttons are released, we're looking for "solved" (by buttons being pressed again).  In this case, we're going to assume we solve *after* P2 starts.

So, 10s pass, and the controller sends "start" to the console for P2.

P2 console starts it's internal timer, and waits for release...and then it's looking for "solved" (just like P1).

Whoever solves first sends a "solved" to the controller.

Controller goes to "solved" state...we wait for a "reset" (starting by having that on the controller) before we go to "waiting for ready".

we could have a "stop" command here...but I'm gonna start by trying without it

## Messages
* Ready: from console to controller, indicating both buttons pressed.  
* Start Inspect:  from controller to console, indicating inspect time has started.  Controller button state doesn't matter here.
* Stop Inspect:  from controller to console, indicating we're waiting for solves.  All buttons must be pressed.
* Start Solve:  from controller to console, indicating it's okay to lift buttons and start your solve.
* Fault:  from console to controller.  We released early.  :(
* Done:  from console to controller.  We're done!

## Ladder diagrams needed
* 10s HC, standard solve
* one player's inspect took too long
* BOTH player's inspect took too long
* 10s HC, early release
* 10s HC, solve before HC timer starts

## Design considerations:
* If someone solves, the other player keeps going until done...they can either choose to solve (which will give the delta time), or hit both buttons to give a done signal (but one that counts as DNF)
* 





