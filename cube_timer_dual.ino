/* cube_timer_dual
 *  
 * Racing cube timers!!!
 */



#include <LiquidCrystal.h>
/*================
 * LCD CONNECTIONS:  (note...we're using 4 bit mode here...)
 *   1 to GND
 *   2 to 5V
 *   3 to the contrast control...I did a hardcoded voltage divider.
 *   4 to Arduino digital pin LCD_REG_SEL
 *   5 to GND
 *   6 to Arduino digital pin LCD_ENABLE
 *   7 (no connection)
 *   8 (no connection)
 *   9 (no connection)
 *   10 (no connection)
 *   11 to Arduino  digital pin LCD_D4
 *   12 to Arduino  digital pin LCD_D5
 *   13 to Arduino  digital pin LCD_D6
 *   14 to Arduino  digital pin LCD_D7
 *   15 to 5V
 *   16 to GND
 *====================*/
 // NEEDS TO BE UPDATED FOR AT LEAST 2, MAYBE 3 LCDS...but for now, all go to serial.
#if 0
#define LCD_D7         4 
#define LCD_D6         5
#define LCD_D5         6
#define LCD_D4         7
#define LCD_ENABLE     8
#define LCD_REG_SEL    9
// Our LCD has 2 rows of 16 characters.
#define LCD_CHARS 16
#define LCD_ROWS 2
LiquidCrystal lcd(LCD_REG_SEL, LCD_ENABLE, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
#endif

#define P1_RH_PIN    22
#define P1_LH_PIN    23
#define P2_RH_PIN    52
#define P2_LH_PIN    53
#define RESET_PIN    12

uint32_t start_time;
uint32_t pre_inspect_start;
#define PRE_INSPECT_MS 3000
uint32_t inspect_start_ms;
uint32_t last_inspect_sec;
#define INSPECT_SEC 15
#define INSPECT_MS (INSPECT_SEC * 1000)
uint32_t handicap_end_ms=0;
uint32_t handicap_ms = 5000;   // Starting with a hardcoded 5 sec handicap for testing.
uint32_t last_handicap_sec;



typedef enum
{
  PLAYER_NONE,
  PLAYER1,
  PLAYER2,
  PLAYER_BOTH  // we're gonna use this for ties...
} player_type;

player_type winner = PLAYER_NONE;

player_type handicapped_player = PLAYER1;  // hardcode for initial testing
player_type non_hc_player = PLAYER2;

boolean p1_began_solve = false;
boolean p2_began_solve = false;

typedef enum
{
  STATE_IDLE,        // waiting for both players to be ready
  STATE_OFFLINE,     // Set handicaps and inspect
  STATE_PRE_INSPECT, // countdown before inspect begins
  STATE_INSPECT,     // both players allowed to inspect cube
  STATE_HC_WFR,      // waiting for hc player to release their buttons
  STATE_RUN_HC_ONLY, // only the handicapped player is allowed to solve
  STATE_NCH_WFR,     // waiting for the non-handicapped player to release their buttons
  STATE_RUN_BOTH,    // both players solving
  STATE_SHOW_WINNER  // Someone has solved!
} state_type;

state_type current_state = STATE_IDLE;

/* State initalization forward declarations */
void init_idle_state( void );
void init_offline_state( void );
void init_pre_inspect_state( void );
void init_inspect_state( void );
void init_hc_wfr_state( void );
void init_run_hc_only_state( void );
void init_nhc_wfr_state( void );
void init_run_both_state( void );
void init_show_winner_state( void );

/* State processing function forward declarations */
state_type process_idle_state( void );
state_type process_offline_state( void );
state_type process_pre_inspect_state( void );
state_type process_inspect_state( void );
state_type process_hc_wfr( void );
state_type process_run_hc_only_state( void );
state_type process_nhc_wfr( void );
state_type process_run_both_state( void );
state_type process_show_winner_state( void );

typedef void (*init_func_type)(void);
typedef state_type (*proc_func_type)(void);

/* init function table */
init_func_type init_func[] = 
{
  init_idle_state,
  init_offline_state,
  init_pre_inspect_state,
  init_inspect_state,
  init_hc_wfr_state,
  init_run_hc_only_state,
  init_nhc_wfr_state,
  init_run_both_state,
  init_show_winner_state
};

/* processing function table */
proc_func_type proc_func[] = 
{
  process_idle_state,
  process_offline_state,
  process_pre_inspect_state,
  process_inspect_state,
  process_hc_wfr_state,
  process_run_hc_only_state,
  process_nhc_wfr_state,
  process_run_both_state,
  process_show_winner_state
};


/*=================================================================
 * init_idle_state
 =================================================================*/
void init_idle_state( void )
{
  Serial.println("Entering Idle");
  
}  /* end of init_idle_state */

/*=================================================================
 * init_offline_state
 =================================================================*/
void init_offline_state( void )
{

  
}  /* end of init_offline_state */

/*=================================================================
 * init_pre_inspect_state
 =================================================================*/
void init_pre_inspect_state( void )
{
  Serial.println("Entering Pre-inspect");
  pre_inspect_start = millis();
  
}  /* end of init_pre_inspect_state */


/*=================================================================
 * init_inspect_state
 =================================================================*/
void init_inspect_state( void )
{
  Serial.println("Entering inspect");
  inspect_start_ms = millis();
  last_inspect_sec = 0;  // this will force a print on the first state processor
  
}  /* end of init_inspect_state */

/*=================================================================
 * init_hc_wfr_state
 =================================================================*/
void init_hc_wfr_state( void )
{
  Serial.println("Entering hc wait-for-release");
}

/*=================================================================
 * init_run_hc_only_state
 =================================================================*/
void init_run_hc_only_state( void )
{
  Serial.println("Starting HC-only countdown");

  // Hmmm...start time should really be broken into a start time per player....and it should 
  // be set in the procesing function rather than the entry function...
  start_time = millis();
  
  // grab a timestamp for when the second player can start
  handicap_end_ms = handicap_ms + start_time;
  
}  /* end of init_run_hc_only_state */

/*=================================================================
 * init_nhc_wfr_state
 =================================================================*/
void init_nhc_wfr_state( void )
{
  Sereial.println("entering nhc wait-for-release");
  
}
/*=================================================================
 * init_run_both_state
 =================================================================*/
void init_run_both_state( void )
{

  
}  /* end of init_run_both_state */

/*=================================================================
 * init_show_winner_state
 =================================================================*/
void init_show_winner_state( void )
{
  Serial.print("WINNER: ");
  if (winner == PLAYER1)
  {
    Serial.println("Player 1");
  }
  else if (winner == PLAYER2)
  {
    Serial.println("Player 2");
  }
  else if (winner = PLAYER_BOTH)
  {
    Serial.println("TIE!!!");
  }
  else
  {
    Serial.println("ERROR");
  }
  
}  /* end of init_show_winner_state */

/*=================================================================
 * process_idle_state
 * 
 * In the idle state, we are looking for two things:
 *  - an indicator to go to offline, where we set various parameters
 *  - an indicator that both players are ready...shown by all player 
 *    buttons being pressed.
 =================================================================*/
state_type process_idle_state( void )
{
  int p1r;
  int p1l;
  int p2r;
  int p2l;

  p1r = digitalRead(P1_RH_PIN);
  p1l = digitalRead(P1_LH_PIN);
  p2r = digitalRead(P2_RH_PIN);
  p2l = digitalRead(P2_LH_PIN);

  if ( (p1r == LOW) && (p1l == LOW) && (p2r == LOW)&& (p2l == LOW) )
  {
    return STATE_PRE_INSPECT;
  }
  else
  {
    return STATE_IDLE;
  }
  
}  /* end of process_idle_state */

/*=================================================================
 * process_offline_state
 * 
 * Currently unimplemented.  We'll eventually use this to set handicaps
 * and inspect times.
 * 
 =================================================================*/
state_type process_offline_state( void )
{
  
}  /* end of process_offline_state */

/*=================================================================
 * process_pre_inspect_state
 * 
 * In the pre-inspect state, we're counting down for inspect to begin.
 * If anyone takes their hands off the buttons early, it's an insta-loss.
 * If the countdown expires, we go to inspect.
 * 
 =================================================================*/
state_type process_pre_inspect_state( void )
{

  int p1r;
  int p1l;
  int p2r;
  int p2l;
  uint32_t current_ms;

  // if anyone takes their hands off a button, it's an insta-win for the other
  p1r = digitalRead(P1_RH_PIN);
  p1l = digitalRead(P1_LH_PIN);
  p2r = digitalRead(P2_RH_PIN);
  p2l = digitalRead(P2_LH_PIN);  

  if (p1r || p1l)
  {
    winner = PLAYER2;
    return STATE_SHOW_WINNER;
  }

  if (p2r || p2l)
  {
    winner = PLAYER1;
    return STATE_SHOW_WINNER;
  }

  // keep counting down 
  current_ms = millis();
  if (current_ms > pre_inspect_start + PRE_INSPECT_MS)
  {
    return STATE_INSPECT;
  }

  // kinda gross right now...show a timestamp.   In future, just make this each second.
  Serial.println(pre_inspect_start + PRE_INSPECT_MS - current_ms);
  return STATE_PRE_INSPECT;
    
}  /* end of process_pre_inspect_state */


/*=================================================================
 * process_inspect_state
 * 
 * In the inspect state, both players are allowed to take their hands
 * off of the buttons and check out the cube.  They'll need to put their
 * hands back on the buttons before inspect is over, but we won't be checking
 * that here.
 * 
 * Our only transition is that if the timer expires, we go to either "run hc only" 
 * (if there is an HC set) or ....HMMMM....NEED TO FIGURE FLOW FOR NO HC!!!
 * 
 =================================================================*/
state_type process_inspect_state( void )
{ 
  uint32_t current_ms;
  uint32_t elapsed_sec;

  current_ms = millis();

  // has our timer run out?
  if (current_ms > inspect_start_ms + INSPECT_MS)
  {
    // if there's a handicap in place, we're going to only run one
    if (handicap_ms)
    { 
      return STATE_HC_WFR;
    }
    
    // if not, we run both
    //  GLENN: RETHINK THIS!!!
    else
    {
      return STATE_RUN_BOTH;
    }
  }

  // if not, we only want to show time deltas on second transitions
  
  // how many seconds have elapsed since inspect began?
  elapsed_sec = (current_ms - inspect_start_ms) / 1000;
  if (elapsed_sec != last_inspect_sec)
  {
    Serial.println(INSPECT_SEC - elapsed_sec);
  }

  return STATE_INSPECT;
  
}  /* end of process_inspect_state */

/*=================================================================
 * process_hc_wfr
 * 
 * In this state, the solve for the HC player has officially started...and we're waiting for them
 * to take their hands off the buttons.
 * 
 * Transitions:
 *   
 * 
 =================================================================*/
state_type process_hc_wfr( void )
{
  
}

/*=================================================================
 * process_run_hc_only_state
 * 
 * In this state, only the un-handicapped player may take their hands off
 * the buttons and solve.  
 * 
 * Transitions:
 *   - if the handicapped player takes their hands off too soon, it's an insta-win
 *   - if the un-handicapped player puts their hands BACK on the buttons, it's a win for them.
 *     (and handicaps probably need to be readjusted...they won without the other player 
 *     getting a chance)
 * 
 =================================================================*/
state_type process_run_hc_only_state( void )
{ 
  int r; // Right button result
  int l; // Left button result
  uint32_t current_ms;
  uint32_t current_handicap_sec;

  // has the non-handicapped player began their solve yet?
  if (non_hc_player == PLAYER1)
  {
    r = digitalRead(P1_RH_PIN);
    l = digitalRead(P1_LH_PIN);
    if ((r==HIGH) && (l==HIGH))
    {
      p1_began_solve = true;
    }
    // did the non-hc player get a solve in?
    else if ((p1_began_solve) && (r == LOW) && (l == LOW))
    {
      Serial.println("Solve!!!");
      winner = non_hc_player;
      return STATE_SHOW_WINNER;
    }
  }
  else if (non_hc_player == PLAYER2)
  {
    r = digitalRead(P2_RH_PIN);
    l = digitalRead(P2_LH_PIN);
    if ((r==HIGH) && (l==HIGH))
    {
      p2_began_solve = true;
    }
    // did the non-hc player get a solve in?
    else if ((p2_began_solve) && (r == LOW) && (l == LOW))
    {
      Serial.println("Solve!!!");
      winner = non_hc_player;
      return STATE_SHOW_WINNER;
    }
  }
  else
  {
    Serial.println("Error...invalid Non-hc player!!!");
    return STATE_IDLE;
  }
  
  // check our time...are we good to transition?
  current_ms = millis();
  if (current_ms > handicap_end_ms)
  {
    return (STATE_RUN_BOTH);
  }
  
  // make sure the handicapped player is still holding both buttons
  if (handicapped_player == PLAYER1)
  {
    r = digitalRead(P1_RH_PIN);
    l = digitalRead(P1_LH_PIN);
  }
  else if (handicapped_player == PLAYER2)
  {
    r = digitalRead(P2_RH_PIN);
    l = digitalRead(P2_LH_PIN);
  }
  else
  {
    Serial.println("Error with HC Player!!!");
    return STATE_IDLE;
  }

  if ((r == HIGH) || (l == HIGH))
  {
    Serial.println("HC player took hands off too early!");
    winner = non_hc_player;
    return STATE_SHOW_WINNER;
  }

  // At this point, we're good to keep going.  Update the times.
  current_handicap_sec = (handicap_end_ms - current_ms) / 1000;
  if (current_handicap_sec != last_handicap_sec)
  {
    Serial.print(current_handicap_sec);
    Serial.println(" seconds left on HC");
    last_handicap_sec = current_handicap_sec;
  }
  return(STATE_RUN_HC_ONLY);
  
  
}  /* end of process_run_hc_only_state */


/*=================================================================
 * process_run_both_state
 * 
 * So now both players are solving.  Just one check...did a player press
 * both buttons?  That's a win. 
 * 
 =================================================================*/
state_type process_run_both_state( void )
{ 
  int p1r;
  int p1l;
  int p2r;
  int p2l;
  uint32_t current_ms;
  uint32_t ms_elapsed;

  // Check for a winner
  p1r = digitalRead(P1_RH_PIN);
  p1l = digitalRead(P1_LH_PIN);
  p2r = digitalRead(P2_RH_PIN);
  p2l = digitalRead(P2_LH_PIN);

  // First case should be very rare.  Do we have a tie?
  if ((p1r == LOW) && (p1l == LOW) && (p2r == LOW) && (p2r == LOW))
  {
    winner = PLAYER_BOTH;
    return(STATE_SHOW_WINNER);
  }
  
  // okay, no tie.  Did P1 win?
  if ((p1r == LOW) && (p1l == LOW))
  {
    winner = PLAYER1;
    return(STATE_SHOW_WINNER);
  }
  
  // What about P2?
  if ((p2r == LOW) && (p2l == LOW))
  {
    winner = PLAYER2;
    return(STATE_SHOW_WINNER);
  }

  // If we get here, no one has won yet.  Update the timers.
  // We're gonna want to change this eventually to reflect the handicaps, but we'll just show 
  // absolute run for now.
  current_ms = millis();
  ms_elapsed = current_ms - start_time;
  Serial.println(ms_elapsed);

  
}  /* end of process_run_both_state */


/*=================================================================
 * process_show_winner_state
 * 
 * Show who won.  Only exit is hitting the reset button, going to idle
 * 
 =================================================================*/
state_type process_show_winner_state( void )
{ 

  // if the reset button has been pressed, we can go to idle
  if (digitalRead(RESET_PIN) == LOW)
  {
    return STATE_IDLE;
  }
  else
  {
    return STATE_SHOW_WINNER;
  }
}  /* end of process_show_winner_state */

void setup( void )
{
  Serial.begin(9600);


  pinMode(P1_RH_PIN, INPUT_PULLUP);
  pinMode(P1_LH_PIN, INPUT_PULLUP);
  pinMode(P2_RH_PIN, INPUT_PULLUP);
  pinMode(P2_LH_PIN, INPUT_PULLUP);
  pinMode(RESET_PIN, INPUT_PULLUP);

  // TODO:  multiple LCDS
  #if 0
  lcd.begin(LCD_CHARS, LCD_ROWS);
  lcd.clear();
  #endif
  
  init_idle_state();
  
}

void loop ( void )
{
  state_type next_state;

  next_state = proc_func[current_state]();
  if (next_state != current_state)
  {
    init_func[next_state]();
    current_state = next_state;
  }
  
}
