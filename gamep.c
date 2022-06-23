/* Joystick Module */
#include "gamep.h"

/* Variables */
int maxx;
int maxy;
int minx;
int miny;

int calibrate_joy( void )
{
   unsigned pv, hv, lv, d, val, yv, xv;
   int i;

   printf("Center Joystick and press a key.\n");
   getch();

   /* X - value */
   outpw( 0x201, 0 );
   pv = inpw( 0x201 );
   lv = pv;

   val = 0;
   i = 0;

   while( ( i < 1000 ) && ( lv != 0 ) )
   {
      if( lv == 0 )
	 break;

      pv = 0x0f & inpw( 0x201 );
      d = pv ^ lv;
      if( ( d & ( 1 << 0 ) ) == ( 1 << 0 ) )
      {
	 val = i;
      }
      lv = pv;

      i ++;
   }
   xv = val;

   /* Y - value */
   outpw( 0x201, 0 );
   pv = inpw( 0x201 );
   lv = pv;

   val = 0;
   i = 0;

   while( ( i < 1000 ) && ( lv != 0 ) )
   {
      if( lv == 0 )
	 break;

      pv = 0x0f & inpw( 0x201 );
      d = pv ^ lv;
      if( ( d & ( 1 << 1 ) ) == ( 1 << 1 ) )
      {
	 val = i;
      }
      lv = pv;

      i ++;
   }
   yv = val;

   minx = 0;
   miny = 0;
   maxx = 2 * xv;
   maxy = 2 * yv;

   if( ( maxx == 0 ) || ( maxy == 0 ) )
   {
      printf("Error. Press a key.\n");
      getch();
      return( 1 );
   }

   printf("Calibration complete.\n");

   return( 0 );
}

int get_joy( double *x, double *y )
{
   unsigned pv, hv, lv, d, val, xv, yv;
   int i;

   /* X - value */
   outpw( 0x201, 0 );
   pv = inpw( 0x201 );
   lv = pv;

   val = 0;
   i = 0;

   while( ( i < 1000 ) && ( lv != 0 ) )
   {
      if( lv == 0 )
	 break;

      pv = 0x0f & inpw( 0x201 );
      d = pv ^ lv;
      if( ( d & ( 1 << 0 ) ) == ( 1 << 0 ) )
      {
	 val = i;
      }
      lv = pv;

      i ++;
   }
   xv = val;

   /* Y - value */
   outpw( 0x201, 0 );
   pv = inpw( 0x201 );
   lv = pv;

   val = 0;
   i = 0;

   while( ( i < 1000 ) && ( lv != 0 ) )
   {
      if( lv == 0 )
	 break;

      pv = 0x0f & inpw( 0x201 );
      d = pv ^ lv;
      if( ( d & ( 1 << 1 ) ) == ( 1 << 1 ) )
      {
	 val = i;
      }
      lv = pv;

      i ++;
   }
   yv = val;

   *x = 1 - 2. * ( ( 1. * ( xv - minx ) ) / maxx );
   *y = 1 - 2. * ( ( 1. * ( yv - miny ) ) / maxy );

   return( 0x0f & ( ( ~inpw( 0x201 ) ) >> 4 ) );
}

