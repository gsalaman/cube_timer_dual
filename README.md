# cube_timer_dual

So now that I have one timer working, it's time (heh) to think about the racing setup.  
Here are some loose requirements/operational description:

* Each person will have a setup in front of them that has 2 buttons (L & R), and probably a personal LCD screen.
* In the middle, we'll have a main control panel.
* Prior to starting, you'll be able to set handicap (seconds), and inspect (seconds)
* The initial state is waiting for both players to press both of their buttons.
* This then starts the inspect time (if set).
* Players may release their buttons in this time period, but the must be dual pressed before inspect ends.
* At this point, we start the timer for the person without the handicap.  They are now allowed to release.  I'll call this mode "handicapped running".
* Once the handicap timer runs out, that person is allowed to release.  This is "dual running"
* In "dual running", if someone solves (indicated by both their buttons pressed), they're declared the winner.  
* Note this can also happen if they solve in "handicapped running"....but it should be rare...and is the result of too great a handicap.
* Once someone has solved, we'll show the winner time...and wait for a reset button (in center console) to be pressed.
* Once reset is pressed, we go back to the "waiting" state...where we can again set handicaps.

## State Machine Breakout

So I've been proceeding on the notion that I have one big state machine driving this whole process...but this AMs brainchild is that I should instead be going with MULTIPLE state machines:

* One that drives the game itself and sends commands to the "players"
* ...and then one each per player

Nice things about this:
* it scales!   One player, fine.  Ten players, fine.
* I'm planning on starting with one main proc driving everything (ribbon cables to player consoles)...but with this model, it's easier to port to some sort of a distributed solution.  3 processors, one for the two players, one for the controller?  No prob.  Talk Serial?  Good.  MQTT?  Sure.  BLE?  Yup.

So now, how to proceed?  If I go single proc, I'll need to tweak the SM driver to support multiple state machines.  Kinda curious if one of the Tiny's can support the player console.  Abstracting the interface layer between the contoller and console is probably a good thing as well...same upper IF, but then the internals can be serial/MQTT/BLE/whatever.

Okay, so next steps:
* Overall system arch diagram showing Controller/Console layouts...and high-level interface description.
* Controller State Machine
* Console State Machine
* Start with hardwired signals...can I use ATTINY?
