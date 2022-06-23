/*SOUND.H: sound function prototypes*/
/* Prototypes */
#include <time.h>
void _beep( short frequency, short duration );
void sleep( clock_t wait );
void sttrek1();
/* Pauses for a specified number of milliconds. Returns 1 if
 * aborted by keypress
 */
int sleep_k( clock_t wait );

/* Notes and frequencies: */
#define C0  262
#define D0  296
#define E0  330
#define F0  349
#define G0  392
#define A0  440
#define B0  494
#define C1  523
#define D1  587
#define E1  659
#define F1  698
#define G1  784
#define A1  880
#define B1  988
#define REST  0

/*Durations: */
#define EIGHTH  125
#define QUARTER  250
#define HALF  500
#define WHOLE  1000
#define END  0

