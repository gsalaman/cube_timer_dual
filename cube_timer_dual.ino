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
 // NEEDS TO BE UPDATED FOR AT LEAST 2, MAYBE 3 LCDS!
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

// and we need a ton ore pins...
#define RH_PIN    10
#define LH_PIN    11
#define RESET_PIN 12

uint32_t start_time;

typedef enum
{
  STATE_IDLE,        // waiting for both players to be ready
  STATE_OFFLINE,     // Set handicaps and inspect
  STATE_PRE_INSPECT, // countdown before inspect begins
  STATE_INSPECT,     // both players allowed to inspect cube
  STATE_RUN_HC_ONLY, // only the handicapped player is allowed to solve
  STATE_RUN_BOTH,    // both players solving
  STATE_SHOW_WINNER  // Someone has solved!
} state_type;

state_type current_state = STATE_IDLE;

/* State initalization forward declarations */
void init_idle_state( void );
void init_offline_state( void );
void init_pre_inspect_state( void );
void init_inspect_state( void );
void init_run_hc_only_state( void );
void init_run_both_state( void );
void init_show_winner_state( void );

/* State processing function forward declarations */
state_type process_idle_state( void );
state_type process_offline_state( void );
state_type process_pre_inspect_state( void );
state_type process_inspect_state( void );
state_type process_run_hc_only_state( void );
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
  init_run_hc_only_state,
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
  process_run_hc_only_state,
  process_run_both_state,
  process_show_winner_state
};


/*=================================================================
 * init_idle_state
 =================================================================*/
void init_idle_state( void )
{

  
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

  
}  /* end of init_pre_inspect_state */


/*=================================================================
 * init_inspect_state
 =================================================================*/
void init_inspect_state( void )
{

  
}  /* end of init_inspect_state */

/*=================================================================
 * init_run_hc_only_state
 =================================================================*/
void init_run_hc_only_state( void )
{

  
}  /* end of init_run_hc_only_state */

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

  
}  /* end of init_show_winner_state */

/*=================================================================
 * process_idle_state
 * 
 *
 =================================================================*/
state_type process_idle_state( void )
{
  
  
}  /* end of process_idle_state */

/*=================================================================
 * process_offline_state
 * 
 =================================================================*/
state_type process_offline_state( void )
{
  
}  /* end of process_offline_state */

/*=================================================================
 * process_pre_inspect_state
 * 
 =================================================================*/
state_type process_pre_inspect_state( void )
{

  
}  /* end of process_pre_inspect_state */


/*=================================================================
 * process_inspect_state
 * 
 =================================================================*/
state_type process_inspect_state( void )
{ 
  
  
}  /* end of process_inspect_state */


/*=================================================================
 * process_run_hc_only_state
 * 
 =================================================================*/
state_type process_run_hc_only_state( void )
{ 
  
  
}  /* end of process_run_hc_only_state */


/*=================================================================
 * process_run_both_state
 * 
 =================================================================*/
state_type process_run_both_state( void )
{ 
  
  
}  /* end of process_run_both_state */


/*=================================================================
 * process_show_winner_state
 * 
 =================================================================*/
state_type process_show_winner_state( void )
{ 
  
  
}  /* end of process_show_winner_state */

void setup( void )
{
  Serial.begin(9600);

  // TODO:  add pins
  pinMode(RH_PIN, INPUT_PULLUP);
  pinMode(LH_PIN, INPUT_PULLUP);
  pinMode(RESET_PIN, INPUT_PULLUP);

  // TODO:  multiple LCDS
  lcd.begin(LCD_CHARS, LCD_ROWS);
  lcd.clear();
  
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
