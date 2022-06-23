/*SOUND.C: module for sound.h*/
#include "sound.h"
#include <conio.h>

/* Sounds the speaker for a time specified in milliseconds by duration
 * at a pitch specified in hertz by frequency.
 */
void _beep( short frequency, short duration )
{
    int control;

    /* If frequency is 0, Beep doesn't try to make a sound. It
     * just sleeps for the duration.
     */
    if( frequency )
    {

	/* Prepare timer by sending 10111100 to port 43. */
	outp( 0x43, 0xb6 );

	/* Divide input frequency by timer ticks per second and
	 * write (byte by byte) to timer.
	 */
	frequency = (unsigned)(1193180L / frequency);
	outp( 0x42, (char)frequency );
	outp( 0x42, (char)(frequency >> 8) );

	/* Save speaker control byte. */
	control = inp( 0x61 );

	/* Turn on the speaker (with bits 0 and 1). */
	outp( 0x61, control | 0x3 );
    }

    sleep( (clock_t)duration );

    /* Turn speaker back on if necessary. */
    if( frequency )
	outp( 0x61, control );

}

/* Pauses for a specified number of milliconds. */
void sleep( clock_t wait )
{
    clock_t goal;

    goal = wait + clock();
    while( goal > clock() )
	;
}

/* Pauses for a specified number of milliconds. Returns 1 if
 * aborted by keypress
 */
int sleep_k( clock_t wait )
{
    clock_t goal;

    goal = wait + clock();
    while( goal > clock() )
	if( kbhit() )
	   return( 1 );

    return( 0 );
}


/*Does the star trek door signal*/
void sttrek1()
{
	_beep(1955,10);
	_beep(0,10);
	_beep(1955,10);
	_beep(0,10);
	_beep(1400,10);
	_beep(0,10);
	_beep(1400,10);
}
