/* Shuttle simulation in space (Technical Version) */
#include <graph.h>
#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include <stdlib.h>
#include <dos.h>
#include "sound.c"
#include "gamep.h"

#define dist( dx, dy, dz ) fabs( ( sqrt( dx * dx + dy * dy + dz * dz ) ) )
#define getrandom( min, max ) ((rand() % (int)(((max)+1) - (min))) + (min))

main()
{
   FILE *fp;
   char ch, comm, comm2, comm3, rv = 0, arm = 0;
   /* MAX_OBJ: beyond 100 is unacceptable, even on a 80486 */
   int MAX_OBJ = 20, MAX_M_OBJ = 4;
   int i, i2, i3, i4, *ot, h, m, *nmob;
   int chr, fine, trac=-1, etrac=0, mx, my;
   int *so, vd, vd1, fill=3, *xo, *yo, oside=0, cr=1;
   double tsx=-50.,tsy=-50., acc=0, acc1=1, *ox, *oy, *oz;
   double *dox, *doy, *doz, visd = -1;
   double x, y, z, *os,pit=0,pit1=1,zrot;
   double tvel, rvel, angr, dx, dy, dz, a1, e1, a2, etime, za;
   double dx1, dy1, dz1, dh, dh2, sch, rot, dd2, ha, ha1, tx, ty, tz;
   double tvel1, rvel1, angr1, mia, maa, mie, mae, ia, ta, ta1;
   double MAX_TV=2000, M_TH=.0075, M_MA=0.0125, va, va2, rr=.0873665;
   double xj, yj;
   long sch2;
   struct dostime_t st, et;
   int sou=1;
   long isize;
   char  _huge *ibuffer, strng[20], str[80];

   /*-----initialize------------*/

   /* Object Memory allocation */
   if( (ox = (double *)calloc( MAX_OBJ, sizeof( double ) )) == NULL )
   {
      printf("Not Enough Memory for objects\n");
      return( 1 );
   }
   if( (oy = (double *)calloc( MAX_OBJ, sizeof( double ) )) == NULL )
   {
      printf("Not Enough Memory for objects\n");
      return( 1 );
   }
   if( (oz = (double *)calloc( MAX_OBJ, sizeof( double ) )) == NULL )
   {
      printf("Not Enough Memory for objects\n");
      return( 1 );
   }
   if( (os = (double *)calloc( MAX_OBJ, sizeof( double ) )) == NULL )
   {
      printf("Not Enough Memory for objects\n");
      return( 1 );
   }
   if( (ot = (int *)calloc( MAX_OBJ, sizeof( int ) )) == NULL )
   {
      printf("Not Enough Memory for objects\n");
      return( 1 );
   }
   if( (nmob = (int *)calloc( MAX_M_OBJ, sizeof( int ) )) == NULL )
   {
      printf("Not Enough Memory for objects\n");
      return( 1 );
   }
   if( (xo = (int *)calloc( MAX_OBJ, sizeof( int ) )) == NULL )
   {
      printf("Not Enough Memory for objects\n");
      return( 1 );
   }
   if( (yo = (int *)calloc( MAX_OBJ, sizeof( int ) )) == NULL )
   {
      printf("Not Enough Memory for objects\n");
      return( 1 );
   }
   if( (so = (int *)calloc( MAX_OBJ, sizeof( int ) )) == NULL )
   {
      printf("Not Enough Memory for objects\n");
      return( 1 );
   }
   if( (dox = (double *)calloc( MAX_M_OBJ, sizeof( double ) )) == NULL )
   {
      printf("Not Enough Memory for objects\n");
      return( 1 );
   }
   if( (doy = (double *)calloc( MAX_M_OBJ, sizeof( double ) )) == NULL )
   {
      printf("Not Enough Memory for objects\n");
      return( 1 );
   }
   if( (doz = (double *)calloc( MAX_M_OBJ, sizeof( double ) )) == NULL )
   {
      printf("Not Enough Memory for objects\n");
      return( 1 );
   }

reset:

   calibrate_joy();

   MAX_TV=50;
   x=0, y=0, z=0, tvel=0, rvel=.025, dx=0, dy=0, dz=0;
   angr=1.570796326794896, rot=0, vd=0, chr=0, ha=0, fine=0, ta=0, ta1=1;
   tvel1=1, rvel1=1, angr1=1, ha1=1, vd1=1,zrot = 0;

   if( MAX_M_OBJ > 0 )
      nmob[0] = 1;

   ox[0]=0;
   oy[0]=5;
   oz[0]=0;
   os[0]=1;
   ot[0]=1;

   ox[1]=4;
   oy[1]=5;
   oz[1]=0;
   os[1]=1;
   ot[1]=0;
   if( MAX_M_OBJ > 0 )
   {
      dox[0]=-1;
      doy[0]=-1;
      doz[0]=0;
   }

   i2=1;
   for(i=2; i<MAX_OBJ; i++ )
   {
      os[i]=getrandom(0,20);
      os[i]/=10;
      ot[i]=0;

      reset( &ox[i], &oy[i], &oz[i], MAX_OBJ );

      if( i2 < MAX_M_OBJ )
      {
	 i3=getrandom(5,15);
	 if( i3 < 10 )
	 {
	    nmob[i2]=i;
	    dox[i2]=getrandom(0,2);
	    doy[i2]=getrandom(0,2);
	    doz[i2]=0;

	    if( fabs( dox[i2] ) < 1 )
	    {
	       if( rand() > ( RAND_MAX / 2 ) )
		  dox[i2] = 1.000000;
	       else
		  dox[i2] = 0.0;
	    }
	    if( fabs( doy[i2] ) < 1 )
	    {
	       if( rand() > ( RAND_MAX / 2 ) )
		  doy[i2] = 1.000000;
	       else
		  doy[i2] = 0.0;
	    }

	    if( fabs( dox[i2] ) > 2. )
	    {
	       if( rand() > ( RAND_MAX / 2 ) )
		  dox[i2] = 2.000000;
	       else
		  dox[i2] = 1.0;
	    }
	    if( fabs( doy[i2] ) > 2. )
	    {
	       if( rand() > ( RAND_MAX / 2 ) )
		  doy[i2] = 2.000000;
	       else
		  doy[i2] = 1.0;
	    }

	    if( rand()>( RAND_MAX/2 ) )
	       dox[i2]=-dox[i2];
	    if( rand()>( RAND_MAX/2 ) )
	       doy[i2]=-doy[i2];

	    i2 += 1;
	 }
      }
   }
   if( rv )
      goto redo;

   _setvideomode(_VRES16COLOR);

   _setcolor(8);
   _ellipse(_GFILLINTERIOR,300,140,320,160);
   _ellipse(_GFILLINTERIOR,300,155,320,175);

   _setcolor(0);
   _ellipse(_GBORDER,300,140,320,160);

   _setcolor(7);
   _ellipse(_GFILLINTERIOR,329,160,332,170);

   _setcolor(7);
   _ellipse(_GFILLINTERIOR,310,150,330,170);
   _ellipse(_GFILLINTERIOR,310,165,330,185);

   _setcolor(0);
   _ellipse(_GBORDER,310,150,330,170);
   _ellipse(_GBORDER,299,147,319,177);

   _setcolor(7);
   for( i=5; i>=0; i-- )
      _ellipse(_GBORDER,298-i,147,318-i,177);

   _setcolor(0);
   _ellipse(_GBORDER,293,147,313,177);
   _ellipse(_GBORDER,306,159,310,165);

   _setcolor(7);
   for( i=0; i<8; i++ )
      _ellipse(_GBORDER,305-i,159,309-i,165);

   _setcolor(0);
   _ellipse(_GBORDER,297,159,301,165);

   _moveto(300,158);
   _lineto(308,158);
   _moveto(300,166);
   _lineto(308,166);

   isize = _imagesize(290,140,333,185);
   ibuffer = halloc( isize, 1 );
   _getimage( 290,140,333,185, ibuffer );

   _clearscreen(_GCLEARSCREEN);

   /* Main control panel */
   _setcolor(7);
   _rectangle(_GFILLINTERIOR,0,241,640,480);
   _setcolor(15);
   _moveto(0,241);
   _lineto(640,241);
   /* hole for vector meter */
   _setcolor(0);
   _ellipse(_GFILLINTERIOR,180,260,240,320);

   /* hole for pitch meter */
   _setcolor(0);
   _ellipse(_GFILLINTERIOR,180,340,240,400);

   while(1)
   {
      /*-----update positions------*/

      tvel=dist( dx, dy, dz );

      sch=fabs( ha-angr );
      if( sch > 3.141592654 )
	 tvel=-tvel;

      if( fabs( tvel ) > MAX_TV )
      {
	 _beep(475,10);
      }

      if( fabs( tvel ) < ( rvel / 10 ) )
	 dx=0.,dy=0.,dz=0.,tvel=0.;

      if( pit < 0 )
	 pit += 6.28319;

      if( pit > 6.28319 )
	 pit -= 6.28319;

      if( ( pit > 1.5708 ) && ( pit < 4.7124 ) )
      {
	 zrot = -zrot;
	 angr = angr + 3.1416;
      }

      /*update position */
      _dos_gettime( &et );

      if( st.hsecond < et.hsecond )
	 etime = et.hsecond - st.hsecond;
      else
      {
	 etime = ( et.hsecond + 100 ) - st.hsecond;
      }

      if( ( etime < 1 ) && ( ( et.second - st.second ) <= 1 ) )
      {
	 etime = 1;
      }

      etime = etime / 100;

      run_op( &etime, &angr, &rot, &pit, &zrot, &acc, &dx, &dy, &dz, &x, &y,
	    &z );

      /* move moving objects */
      if( MAX_M_OBJ )
      {
	 for( i=0; i< MAX_M_OBJ; i++ )
	 {
	    i2=nmob[i];
	    if( i2 == -1 )
	       break;
	    ox[i2] += dox[i] * etime;
	    oy[i2] += doy[i] * etime;
	    oz[i2] += doz[i] * etime;
	    if( trac == i2 )
	    {
	       tx=ox[i2];
	       ty=oy[i2];
	       tz=oz[i2];
	    }
	 }
      }
      _dos_gettime( &st );

      /* Calculate actual heading */
      run_xyb( dx, dy, &ha );

      if( ( fabs( angr-ha ) < .1 ) && ( !rot ) && ( !acc ) )
	 angr=ha;

      tvel=dist( dx, dy, dz );

      if( tvel == 0 )
	 ha=angr;

      if( etrac ) /* Execute tracking */
      {
	 /* Calculate intersection angle (x,y axis) */
	    /* Set up relative coords */
	 dx1=tx-x;
	 dy1=ty-y;
	 dz1=tz-z;

	    /* calculate angle to object */
	 i = 0;
	 i = run_xyb( dx1, dy1, &a1 );
	 if( i )
	    a1 = angr;

	 if( a1>angr )
	    rot=.174733;
	 if( a1<angr )
	    rot=-.174733;
	 if( fabs( a1-angr ) < .174733 )
	 {
	    if( a1>angr )
	       rot = fabs( a1 - angr );
	    if( a1<angr )
	       rot = - ( fabs( a1 - angr ) );
	 }
	 if( fabs( a1-angr ) < .0001 )
	    rot=0;
	 if( tvel!=0 )
	    ha=angr;
	 ta=a1;
	 /* calculate elevation to object */
	 if( dy1 > 0 )
	 {
	    za=atan( dz1/dy1 );
	    za = -za;
	    if( za < 0 )
	       za=za+6.28319;
	 }
	 else if( dy1 < 0 )
	 {
	    za=atan( dz1/dy1 );
	    za = -za;
	    if( za > 6.28319 )
	       za=za-6.28319;
	 }
	 else
	 {
	    if( dz1 > 0 )
	       za=1.5708;
	    if( dz1 < 0 )
	       za=4.7124;
	    if( dz1 == 0 )
	       za = 0;
	 }
	 if( fabs( ta-angr ) < .05 )
	 {
	    if( za > 3.1416 )
	       a1 = za - 6.28319;
	    else
	       a1 = za;

	    if( pit > 3.1416 )
	       a2 = pit - 6.28319;
	    else
	       a2 = pit;

	    if( a1>a2 )
	       zrot=.0873665;
	    if( a1<a2 )
	       zrot=-.0873665;
	    if( ( a1 > 1.5708 ) && ( a1 < 4.7124 ) )
	       zrot = 0;
	    if( fabs( a1-a2 ) < .08 )
	    {
	       if( a1>a2 )
		  zrot = fabs( a1 - a2 );
	       if( a1<a2 )
		  zrot = - ( fabs( a1 - a2 ) );
	    }
	    if( fabs( a1-a2 ) < .0001 )
	       zrot=0;
	 }
	 else
	    zrot = 0;
      }

      /* calculate track angle to object */
      if( trac != -1 )
      {
	 /* Set up relative coords */
	 dx1=tx-x;
	 dy1=ty-y;
	 dz1=tz-z;

	 i = run_xyb( dx1, dy1, &a1 );
	 if( i == 1 )
	    a1 = angr;
	 ta=a1;
      }

      for ( i = 0; i < MAX_OBJ; i++ )
      {
	 /* Check if object location is becoming a problem */
	 if( ox[i] > 1e+100 )
	 {
	    ox[i] = -1e+99 ;
	 }
	 if( ox[i] < ( -1e+100 ) )
	 {
	    ox[i] = 1e+99 ;
	 }
	 if( oy[i] > 1e+100 )
	 {
	    oy[i] = -1e+99 ;
	 }
	 if( oy[i] < ( -1e+100 ) )
	 {
	    oy[i] = 1e+99 ;
	 }
	 if( oz[i] > 1e+100 )
	 {
	    oz[i] = -1e+99 ;
	 }
	 if( oz[i] < ( -1e+100 ) )
	 {
	    oz[i] = 1e+99 ;
	 }
      }

      /* Crash Warning */
      if( cr && sou )
      {
	 for( i = 0; i < MAX_OBJ; i++ )
	 {
	    sch = os[i];
	    if( ( fabs( ox[i] - x ) < sch ) &&
		( fabs( oy[i] - y ) < sch ) &&
		( fabs( oz[i] - z ) < sch ) )
	    {
	       /* Warning Issued */
	       if( sou )
	       {
		  _beep( 2000, 5 );
	       }
	       break;
	    }
	 }

      }

      /*-----draw control panel----*/
      _setcliprgn(0,240,640,480);

      /* Position indicator */
      _setcliprgn(0,480,640,464);
      _clearscreen(_GVIEWPORT);

      _settextposition( 30,0 );
      printf("%g,%g,%g",x,y,z);

      _setcolor(7);
      _moveto(0,464);
      _lineto(640,464);
      _setcliprgn(0,240,640,480);

      /* track object display */
      _setcliprgn(0,0,640,15);
      _clearscreen(_GVIEWPORT);
      _settextposition( 0,0 );
      printf("Track ");
      if( trac==-1 )
	 printf("Off");
      else if( trac != -2 )
      {
	 printf("Obj %d: ",trac);
	 printf("%g,%g,%g: %g",tx,ty,tz,os[trac]);
	 for( i=0; i<MAX_M_OBJ; i++ )
	 {
	    if( nmob[i] == trac )
	    {
	       printf(" V: ");
	       if( ( dox[i]*dox[i]+doy[i]*doy[i] ) < 1e+99 )
		  printf("%g",dist( dox[i], doy[i], 0 ) );
	       else
		  printf(". . .");
	    }
	 }
      }
      else
      {
	 printf("Coord: ");
	 printf("%g,%g,%g",tx,ty,tz);
      }

      if( trac != -1 )
      {
	 dx1 = fabs( x - tx );
	 dy1 = fabs( y - ty );
	 dz1 = fabs( z - tz );
	 printf( " D: ");
	 if( ( dx1 * dx1 + dy1 * dy1 + dz1 * dz1 ) < 1e+99 )
	    printf("%g", dist( dx1, dy1, dz1 ) );
	 else
	    printf(". . .");
      }

      _setcolor(7);
      _moveto(0,15);
      _lineto(640,15);
      _setcliprgn(0,240,640,480);

      if( etrac )
	 _setcolor(2);
      else
	 _setcolor(4);
      _rectangle(_GFILLINTERIOR, 93, 310, 108, 315 );
      _setcolor(15);
      _rectangle(_GBORDER, 93, 310, 108, 315 );

      /* Crash Mode Indicator */
      if( cr == 1 )
      {
	 _setcolor( 4 );
	 _ellipse( _GFILLINTERIOR, 500, 320, 510, 330 );
	 _setcolor( 15 );
	 _ellipse( _GBORDER, 500, 320, 510, 330 );
      }
      if( cr == 2 )
      {
	 _setcolor( 1 );
	 _ellipse( _GFILLINTERIOR, 500, 320, 510, 330 );
	 _setcolor( 15 );
	 _ellipse( _GBORDER, 500, 320, 510, 330 );
      }
      if( !cr )
      {
	 _setcolor( 2 );
	 _ellipse( _GFILLINTERIOR, 500, 320, 510, 330 );
	 _setcolor( 15 );
	 _ellipse( _GBORDER, 500, 320, 510, 330 );
      }

      /* Total velocity indicator */
      if( tvel != tvel1 )
      {
	 _setcolor(0);
	 if( tvel>0 )
	    _setcolor(2);
	 if( tvel<0 )
	    _setcolor(4);
	 _rectangle(_GFILLINTERIOR,10,250,25,255);
	 _setcolor(15);
	 _rectangle(_GBORDER,10,250,25,255);

	 _setcliprgn(51,249,149,261);
	 _setcolor(0);
	 _rectangle(_GFILLINTERIOR,50,250,150,260);
	 _setcolor(15);
	 _rectangle(_GBORDER,50,250,150,260);
	 _moveto(100,250);
	 _lineto(100,260);

	 _settextposition( 29, 0 );
	 printf("              ");
	 _settextposition( 29, 0 );
	 if( tvel > .000001 )
	    printf("%g",tvel);
	 else
	    printf("~0");

	 if( tvel == 0 )
	 {
	    _moveto(50,250);
	    _lineto(150,260);
	 }
	 _setcolor(9);
	 sch2=( tvel * 50 )/MAX_TV;
	 i=sch2;
	 _rectangle(_GFILLINTERIOR,100,251,100+i,259);
      }
      _setcliprgn(0,0,640,480);

      /* Thruster strength indicator */
      if( rvel!=rvel1 )
      {
	 _setcolor(0);
	 _rectangle(_GFILLINTERIOR,280,260,290,360);
	 if( rvel > M_TH )
	    rvel=M_TH;
	 if( rvel < 0 )
	    rvel=0;
	 sch2=( rvel * 100 )/M_TH;
	 i=sch2;
	 _setcolor(7);
	 _rectangle(_GFILLINTERIOR,281,360,289,360-i);
	 _setcolor(15);
	 _rectangle(_GBORDER,280,260,290,360);
      }

      /* Acceleration indicator */
      if( acc!=acc1 )
      {
	 _setcolor(0);
	 _rectangle(_GFILLINTERIOR,300,260,310,360);
	 if( acc > M_MA )
	    acc=M_MA;
	 if( acc < -M_MA )
	    acc=-M_MA;
	 sch2=( acc * 100 )/( 2 * M_MA );
	 i=sch2;
	 _setcolor(7);
	 _rectangle(_GFILLINTERIOR,301,310,309,310-i);
	 _setcolor(15);
	 _rectangle(_GBORDER,300,260,310,360);
      }

      /* view display */
      if( vd != vd1 )
      {
	 _setcolor(0);
	 _ellipse(_GFILLINTERIOR,350,360,360,350);
	 _ellipse(_GFILLINTERIOR,320,320,330,310);
	 _ellipse(_GFILLINTERIOR,350,280,360,270);
	 _ellipse(_GFILLINTERIOR,380,320,370,310);

	 _setcolor(0);
	 if( vd1 == 0 )
	    _ellipse(_GFILLINTERIOR,350,270,360,280);
	 if( vd1 == 1 )
	    _ellipse(_GFILLINTERIOR,380,320,370,310);
	 if( vd1 == 2 )
	    _ellipse(_GFILLINTERIOR,360,350,350,360);
	 if( vd1 == 3 )
	    _ellipse(_GFILLINTERIOR,320,320,330,310);

	 _setcolor(15);
	 if( vd == 0 )
	    _ellipse(_GFILLINTERIOR,350,270,360,280);
	 if( vd == 1 )
	    _ellipse(_GFILLINTERIOR,380,320,370,310);
	 if( vd == 2 )
	    _ellipse(_GFILLINTERIOR,360,350,350,360);
	 if( vd == 3 )
	    _ellipse(_GFILLINTERIOR,320,320,330,310);

	 _setcolor(15);
	 _ellipse(_GBORDER,350,360,360,350);
	 _ellipse(_GBORDER,320,320,330,310);
	 _ellipse(_GBORDER,350,280,360,270);
	 _ellipse(_GBORDER,380,320,370,310);
      }

      /* Vector meter (compass) */
      if( ( angr!=angr1 ) || ( ha!=ha1 ) || ( ta!=ta1 ) || ( pit!=pit1 ) ||
	  ( tvel != tvel1 ) )
      {
	 v_m( angr1, angr, pit1, pit, ha1, ha, ta1, ta, tvel1, tvel, trac );
      }

      /* Weapon indicator */
      /* Armed? */
      if( arm )
	 _setcolor( 4 );
      else
	 _setcolor( 2 );
      _rectangle(_GFILLINTERIOR,501,401,599,449);
      _setcolor( 15 );
      _rectangle(_GBORDER,500,400,600,450);

      /* In range? */
      if( trac > -1 )
      {
	 dx1 = fabs( x - ox[trac] );
	 dy1 = fabs( y - oy[trac] );
	 dz1 = fabs( z - oz[trac] );

	 if( ( dist( dx1, dy1, dz1 ) - os[trac] ) < 10 )
	 {
	    _setcolor( 15 );
	    _moveto(550,405);
	    _lineto(550,445);
	    _moveto(505,425);
	    _lineto(595,425);
	 }
      }
      /* Angle of movement */
      for( i=0; i<MAX_M_OBJ; i++ )
      {
	 if( nmob[i] == trac )
	 {
	    if( fabs( dist( dox[i], doy[i], doz[i] ) ) > 0 )
	    {
	       run_xyb( dox[i], doy[i], &sch );
	       _setcolor( 15 );
	       dial( 550, 425, 20, sch );
	    }
	 }
      }

      if( fabs( tvel ) < .001 )
	 dx=0,dy=0,dz=0,tvel = 0;

      _setcliprgn(0,15,640,240);

      /*-------View Screen---------*/
      /* Draw Crosshairs */
      if( chr )
      {
	 dx1 = x + cos( ha1 ) * 10;
	 dy1 = y + sin( ha1 ) * 10;
	 dr_pt3( &i, &i2, dx1, dy1, dz1, x, y, z, angr1, 0 );

	 _setcolor( 0 );
	 _moveto( i - 20, 120 );
	 _lineto( i + 20, 120 );
	 _moveto( i, 100 );
	 _lineto( i, 140 );

	 dx1 = x + cos( ha ) * 10;
	 dy1 = y + sin( ha ) * 10;
	 dr_pt3( &i, &i2, dx1, dy1, dz1, x, y, z, angr, 0 );

	 _setcolor( 1 );
	 _moveto( i - 20, 120 );
	 _lineto( i + 20, 120 );
	 _moveto( i, 100 );
	 _lineto( i, 140 );

	 _setcolor(4);
	 _moveto(300,120);
	 _lineto(340,120);
	 _moveto(320,100);
	 _lineto(320,140);
      }

      /*-----set up check variables-------*/
      tvel1=tvel, rvel1=rvel, angr1=angr, ha1=ha, ta1=ta;
      acc1=acc, vd1=vd, pit1=pit;

      /*_clearscreen(_GVIEWPORT);*/

      /* draw objects */
      if( !oside )
      {
	 va = angr + ( vd * 1.5707 );
	 if( va<0 )
	    va=va+6.28319;
	 if( va>6.28319 )
	    va=va-6.28319;

	 if( vd == 2 )
	    va2 = -pit;
	 else
	    va2 = pit;

	 mia=va-.785398,maa=va+.785398;
	 mie=va2-.785398,mae=va2+.785398;

	 if( va2<0 )
	    va2=va2+6.28319;
	 if( va2>=6.28319 )
	    va2=va2-6.28319;

	 if( mia<0 )
	    mia=mia+6.28319;
	 if( maa>6.28319 )
	    maa=maa-6.28319;
	 if( mie<0 )
	    mie=mie+6.28319;
	 if( mae>6.28319 )
	    mae=mae-6.28319;
      }
      else
      {
	 va=angr+1.5;
	 if( va<0 )
	    va=va+6.28319;
	 if( va>6.28319 )
	    va=va-6.28319;
	 mia=va-.785398,maa=va+.785398;
	 mie=pit-.785398,mae=pit+.785398;
	 if( mia<0 )
	    mia=mia+6.28319;
	 if( maa>6.28319 )
	    maa=maa-6.28319;
	 if( mie<0 )
	    mie=mie+6.28319;
	 if( mae>6.28319 )
	    mae=mae-6.28319;
      }

      _setcolor(15);
      i=tsx;
      i2=tsy;
      _ellipse(_GBORDER,i-10,i2-10,i+10,i2+10);

      for( i=0; i<MAX_OBJ; i++)
      {
	 d_ob1( so, xo, yo, ox, oy, oz, os, ot, x, y, z, visd, va, va2,
		oside, mia, maa, mie, mae, fill, trac, i );
      }

      _setcolor(0);
      i=tsx;
      i2=tsy;
      _ellipse(_GBORDER,i-10,i2-10,i+10,i2+10);

      if( trac==-2 )
      {
	 dr_tc1( &tsx, &tsy, tx, ty, tz, x, y, z, mia, mie, va, va2 );
      }

      /* draw ship */
      if( oside )
      {
	 _putimage(320,120,ibuffer,_GPSET);
      }

      /* Check For Crash */
      if( cr == 2 )
      {
	 for( i = 0; i < MAX_OBJ; i++ )
	 {
	    sch = os[i] / 2;

	    if( ( fabs( ox[i] - x ) < sch ) &&
		( fabs( oy[i] - y ) < sch ) &&
		( fabs( oz[i] - z ) < sch ) )
	    {
	       /* Collision with Object occured */
	       if( ( tvel < .006667 ) &&
		   ( fabs( ox[i] - x ) > ( sch - .125 ) ) &&
		   ( fabs( oy[i] - y ) > ( sch - .125 ) ) &&
		   ( fabs( oz[i] - z ) > ( sch - .125 ) ) )
	       {
		  if( tvel > 0 )
		  {
		     dx = 0, dy = 0, dz = 0;
		     ha = angr;
		     for( i2 = 75; i2 >= 50; i2 = i2 - 5 )
			_beep( i2, 25 );
		  }
		  continue;
	       }

	       _setbkcolor( _RED );
	       if( sou )
	       {
		  for( i2 = 75; i2 >= 20; i2 = i2 - 5 )
		     _beep( i2, 25 );
	       }
	       _setbkcolor( _BLACK );
	       rot = .43668325;
	       zrot = .174733;

	       x=x-os[i]/2;
	       y=x-os[i]/2;

	       i=getrandom(1,3);
	       i--;
	       if( i )
		  dx = -dx;

	       i=getrandom(1,3);
	       i--;
	       if( i )
		  dy = -dy;

	       i=getrandom(1,3);
	       i--;
	       if( i )
		  rot = -rot;

	       i=getrandom(1,3);
	       i--;
	       if( i )
		  zrot = -zrot;
	    }
	 }
      }
      if( cr == 1 )
      {
	 for( i = 0; i < MAX_OBJ; i++ )
	 {
	    sch = os[i] / 2;
	    if( ( fabs( ox[i] - x ) < sch ) &&
		( fabs( oy[i] - y ) < sch ) &&
		( fabs( oz[i] - z ) < sch ) )
	    {
	       /* Collision with Object occured */
	       if( ( tvel < .006667 ) &&
		   ( fabs( ox[i] - x ) > ( sch - .125 ) ) &&
		   ( fabs( oy[i] - y ) > ( sch - .125 ) ) &&
		   ( fabs( oz[i] - z ) > ( sch - .125 ) ) )
	       {
		  if( tvel > 0 )
		  {
		     dx = 0, dy = 0, dz = 0;
		     ha = angr;
		     for( i2 = 75; i2 >= 50; i2 = i2 - 5 )
			_beep( i2, 25 );
		  }
		  continue;
	       }

	       _setbkcolor( _RED );
	       if( sou )
	       {
		  for( i2 = 75; i2 >= 20; i2 = i2 - 5 )
		     _beep( i2, 25 );
	       }
	       getch();
	       _setbkcolor( _BLACK );

	       tvel=0;
	       x=0,y=0,z=0;
	       dx=0,dy=0,dz=0,acc=0,zrot=0,pit=0;
	       angr=1.570796326794896,ha=0,rot=0,angr1=0,ha1=1;
	       break;
	    }
	 }
      }

      /*------Get and interpret commands-----*/
      i2 = get_joy( &xj, &yj );
      if( yj < -1. )
	 yj = -1.;
      if( yj > 1. )
	 yj = 1.;
      if( xj < -1. )
	 xj = -1.;
      if( xj > 1. )
	 xj = 1.;

      xj = -xj;

      if( !i2 )
      {
	 /* Main Panel Commands */
	 dz = dz+( ( sin( pit ) ) * yj * rvel );

	 if( !( ( fabs( pit-1.5708 ) < .001 ) ||
	      ( fabs( pit-4.7124 ) < .001 ) ) )
	 {
	    dx = dx+( ( cos( angr ) ) * yj * rvel );
	    dy = dy+( ( sin( angr ) ) * yj * rvel );
	 }
	 else
	 {
	    sch = pit/1.5708;
	    dx = dx+( ( cos( angr ) ) * yj * sch );
	    dy = dy+( ( sin( angr ) ) * yj * sch );
	 }

	 if( !tvel )
	    ha=angr;

	 /* calculate total velocity in km/sec */
	 tvel=dist( dx, dy, dz );

	 if( !tvel )
	    ha=angr;

	 rot = rot + ( rr * xj );
      }
      else
      {
	 /* Vector Panel Commands */
	 sch = angr + 1.5707;

	 while( sch > 6.28319 )
	    sch = sch - 6.28319;

	 dx = dx+( ( cos( sch ) ) * rvel * xj );
	 dy = dy+( ( sin( sch ) ) * rvel * xj );

	 /* calculate total velocity in km/sec */
	 tvel=dist( dx, dy, dz );

	 if( !tvel )
	    ha=sch;

	 /* calculate total velocity in km/sec */
	 tvel=dist( dx, dy, dz );
      }

      if( kbhit() != 0 )
      {
	 ch=getch();
	 switch(ch)
	 {
	    case 'q': /* quit */
	 kill:
	       hfree( ibuffer );
	       free( ox );
	       free( oy );
	       free( oz );
	       free( os );
	       free( ot );
	       free( nmob );
	       free( xo );
	       free( yo );
	       free( so );
	       free( dox );
	       free( doy );
	       free( doz );

	       _setvideomode(_DEFAULTMODE);
	       printf("Space Craft Simulator Completed\n");
	       return( 0 );
	    case 'd': /* redraw screen */
	       _setcliprgn(0,0,640,240);
	       _clearscreen(_GVIEWPORT);
	       _setcliprgn(0,0,640,480);
	       break;
	    case ']': /* Toggle weapon arming */
	       arm = ! arm;
	       break;
	    case '[': /* Weapon systems */
	       if( arm )
		  wep( angr, pit, os, ox, oy, oz, trac, &tx, &ty, &tz, x,
		       y, z, MAX_OBJ );
	       break;
	    case 'c': /* Rotate Down */
	       if( !fine )
		  zrot=zrot+rr;
	       else
		  zrot=zrot+rr/8;
	       break;
	    case 'e': /* Rotate Up */
	       if( !fine )
		  zrot=zrot-rr;
	       else
		  zrot=zrot-rr/8;
	       break;

	    case 'o': /* toggle outside/ inside view */
	       if( oside )
	       {
		  _setcliprgn(0,0,640,240);
		  _clearscreen(_GVIEWPORT);
		  _setcliprgn(0,0,640,480);
		  oside=0;
	       }
	       else
		  oside=1;
	       break;
	    case 'a': /* decrease acceleration */
	       if( fine )
		  acc-=M_MA/10;
	       else
		  acc-=M_MA/5;
	       break;
	    case 'b': /* Toggle Filling */
	       if( fill == 2 )
		  fill = 3;
	       else
		  fill = 2;
	       break;
	    case 'g': /* increase acceleration */
	       if( fine )
		  acc+=M_MA/10;
	       else
		  acc+=M_MA/5;
	       break;
	    case 'V': /* Editing work */
	       _setvideomode( _DEFAULTMODE );

	       comm = '1';
	       while( comm != '0' )
	       {
		  printf("\nEditing Menu: \n");
		  printf("0) Return to simulation\n");
		  printf("1) Change number of objects\n");
		  printf("2) Change Maximum velocity\n");
		  printf("3) Toggle Sound effects: %s\n", (sou)?"On":"Off" );
		  switch( cr )
		  {
		     case 0:
			strcpy( strng, "Off" );
			break;
		     case 1:
			strcpy( strng, "On" );
			break;
		     case 2:
			strcpy( strng, "Deflect" );
			break;
		  }
		  printf("4) Toggle Crash: %s\n", strng );
		  printf("5) Set Position: %g,%g,%g\n", x, y, z );
		  printf("6) Change positions of objects\n");
		  printf("7) Read spacecraft file\n");
		  printf("8) Create spacecraft file\n");
		  if( visd > 0 )
		     printf("9) Set Visibility: %g km\n",visd );
		  else
		     printf("9) Visibility Disabled\n");
		  printf("a) Set velocities: %g,%g,%g\n",dx,dy,dz);
		  printf("press number of your selection. . .\n");
		  comm = getch();

		  switch( comm )
		  {
		     case '0':
			break;
		     case '1': /* Reallocate memory */
			comm2 = '1';
			while( ( comm2 != '0' ) && ( comm2 != '3' ) )
			{
			   printf("\nNumber of objects menu\n");
			   printf("0) Return to main menu\n");
			   printf("1) Set number of objects: %d\n",MAX_OBJ);
			   printf("2) Set number of moving objects: %d\n",
			      MAX_M_OBJ);
			   printf("3) Allocate memory\n");
			   printf("press number of your selection. . .\n");
			   comm2 = getch();

			   switch( comm2 )
			   {
			      case '1': /* Enter # of objects */
				  printf("Enter number of objects: ");
				  scanf("%d", &MAX_OBJ);
				  break;
			      case '2': /* Enter # of moving objects */
				  do
				  {
				     printf("Enter number of moving objects: ");
				     scanf("%d", &MAX_M_OBJ);

				     if( MAX_M_OBJ > MAX_OBJ )
				       printf("Too many moving objects\n");
				  }while( MAX_M_OBJ > MAX_OBJ );
				  break;
			   }
			}

			if( comm2 == '0' )
			   break;

			if( (ox = (double *)realloc( ox,
			   MAX_OBJ * sizeof( double ) )) == NULL )
			{
			   printf("Not Enough memory for reallocation\n");
			   goto kill;
			}
			if( (oy = (double *)realloc( oy,
			   MAX_OBJ * sizeof( double ) )) == NULL )
			{
			   printf("Not Enough memory for reallocation\n");
			   goto kill;
			}
			if( (oz = (double *)realloc( oz,
			   MAX_OBJ * sizeof( double ) )) == NULL )
			{
			   printf("Not Enough memory for reallocation\n");
			   goto kill;
			}
			if( (os = (double *)realloc( os,
			   MAX_OBJ * sizeof( double ) )) == NULL )
			{
			   printf("Not Enough memory for reallocation\n");
			   goto kill;
			}
			if( (ot = (int *)realloc( ot,
			   MAX_OBJ * sizeof( int ) )) == NULL )
			{
			   printf("Not Enough memory for reallocation\n");
			   goto kill;
			}
			if( ( (nmob = (int *)realloc( nmob,
			   MAX_M_OBJ * sizeof( int ) )) == NULL ) &&
			   MAX_M_OBJ > 0 )
			{
			   printf("Not Enough memory for reallocation\n");
			   goto kill;
			}
			if( (xo = (int *)realloc( xo,
			   MAX_OBJ * sizeof( int ) )) == NULL )
			{
			   printf("Not Enough memory for reallocation\n");
			   goto kill;
			}
			if( (yo = (int *)realloc( yo,
			   MAX_OBJ * sizeof( int ) )) == NULL )
			{
			   printf("Not Enough memory for reallocation\n");
			   goto kill;
			}
			if( (so = (int *)realloc( so,
			   MAX_OBJ * sizeof( int ) )) == NULL )
			{
			   printf("Not Enough memory for reallocation\n");
			   goto kill;
			}
			if( ( (dox = (double *)realloc( dox,
			   MAX_M_OBJ * sizeof( double ) )) == NULL ) &&
			   MAX_M_OBJ > 0 )
			{
			   printf("Not Enough memory for reallocation\n");
			   goto kill;
			}
			if( ( (doy = (double *)realloc( doy,
			   MAX_M_OBJ * sizeof( double ) )) == NULL ) &&
			   MAX_M_OBJ > 0 )
			{
			   printf("Not Enough memory for reallocation\n");
			   goto kill;
			}
			if( ( (doz = (double *)realloc( doz,
			   MAX_M_OBJ * sizeof( double ) )) == NULL ) &&
			   MAX_M_OBJ > 0 )
			{
			   printf("Not Enough memory for reallocation\n");
			   goto kill;
			}
			rv = 1;
			goto reset;
redo:
			rv = 0;

			break;
		     case '2':
			printf("Enter Maximum Velocity: ");
			scanf("%lf",&MAX_TV);
			break;
		     case '3':
			if( sou )
			   sou=0;
			else
			{
			   sou=1;
			   _beep( 100, 2 );
			}
			break;
		     case '4': /* Toggle Crash */
			cr += 1;
			if( cr == 3 )
			   cr=0;
			break;
		     case '5': /* Set Position */
			printf("Enter position (x,y,z): ");
			scanf("%lf,%lf,%lf",&x,&y,&z);
			break;
		     case '6': /* Set Object positions */
			do
			{
			   printf("\nObject Editing Menu:\n");
			   printf("0) Return to main menu\n");
			   printf("1) Load Objects from file\n");
			   comm2 = getch();

			   switch( comm2 )
			   {
			      case '1':
				 printf("Enter Filename to read: ");
				 gets( strng );
				 if( ( fp = fopen( strng, "r" ) ) == NULL )
				 {
				    printf("Error Reading file\n");
				    break;
				 }
				 i=0;
				 while( ( fscanf( fp,"%lf,%lf,%lf,%lf,%d",
				       &ox[i],&oy[i],&oz[i],&os[i],&ot[i]) !=
				       EOF) && ( i <= MAX_OBJ ) )
				    i++;

				 fclose( fp );

				 break;
			      default:
				 break;
			   }
			}while( comm2 != '0' );

			break;
		     case '7':
			printf("Enter Filename to read: ");
			gets( strng );
			if( ( fp = fopen( strng, "r" ) ) == NULL )
			{
			   printf("Error Reading file\n");
			      break;
			}
			i=0;
			while( fgets( str, 80, fp ) != NULL )
			{
			   if( strnicmp( str, "maxvel=", 7 ) == 0 )
			   {
			      i = 0;
			      i2 = 7;
			      while( str[i2] != '\0' )
			      {
				 strng[i] = str[i2];
				 i ++;
				 i2 ++;
			      }
			      sscanf(strng,"%lf",&MAX_TV);
			   }
			   if( strnicmp( str, "maxacc=", 7 ) == 0 )
			   {
			      i = 0;
			      i2 = 7;
			      while( str[i2] != '\0' )
			      {
				 strng[i] = str[i2];
				 i ++;
				 i2 ++;
			      }
			      sscanf(strng,"%lf",&M_MA);
			   }
			   if( strnicmp( str, "maxthr=", 7 ) == 0 )
			   {
			      i = 0;
			      i2 = 7;
			      while( str[i2] != '\0' )
			      {
				 strng[i] = str[i2];
				 i ++;
				 i2 ++;
			      }
			      sscanf(strng,"%lf",&M_TH);
			   }
			   if( strnicmp( str, "rotthr=", 7 ) == 0 )
			   {
			      i = 0;
			      i2 = 7;
			      while( str[i2] != '\0' )
			      {
				 strng[i] = str[i2];
				 i ++;
				 i2 ++;
			      }
			      sscanf(strng,"%lf",&rr);
			   }
			}
			fclose( fp );

			break;
		     case '8':
			strcpy( strng, "a:\\scsim\\t1.sc");
			while(1)
			{
			  printf("0) Return to main Menu\n");
			  printf("1) Save File\n");
			  printf("2) Max Acceleration: %g m/sý\n",M_MA*1000);
			  printf("3) Max Acceleration: %g g\n",( M_MA/9.8 )*1000);
			  printf("4) Max Velocity: %g km/s\n", MAX_TV );
			  printf("5) Max Thrusters: %g m/sý\n", M_TH*1000 );
			  printf("6) Rotational Speed: %g radians/s\n",rr);
			  printf("7) Rotational Speed: %gø/s\n",rr*57.29578);
			  printf("8) Filename: %s\n",strng);
			  printf("Press The number of your choise\n");
			  comm2 = getch();
			  switch( comm2 )
			  {
			   case '0': /* Return */
			      break;
			   case '1': /* Save File */
			      fp = fopen( strng, "w" );
			      fprintf(fp,"MaxVel=%g\n",MAX_TV);
			      fprintf(fp,"MaxAcc=%g\n",M_MA);
			      fprintf(fp,"MaxThr=%g\n",M_TH);
			      fprintf(fp,"RotThr=%g\n",rr);
			      fclose( fp );
			      printf("File Saved\n");
			      break;
			   case '2': /* Set Acceleration */
			      printf("Enter acceleration: ");
			      scanf("%lf",&M_MA);
			      M_MA = M_MA/1000;
			      break;
			   case '3': /* Set acceleration in g's */
			      printf("Enter acceleration (in g's): ");
			      scanf("%lf",&M_MA);
			      M_MA *= 9.8;
			      M_MA = M_MA/1000;
			      break;
			   case '4': /* Set Velocity */
			      printf("Enter Max Velocity: ");
			      scanf("%lf",&MAX_TV);
			      break;
			   case '5': /* Set Thrusters */
			      printf("Enter Max Thruster Acceleration: ");
			      scanf("%lf",&M_TH);
			      M_TH = M_TH/1000;
			      break;
			   case '6': /* Set Rotational Thrusters */
			      printf("Enter Max Rotational Speed (rad/s): ");
			      scanf("%lf",&rr);
			      break;
			   case '7': /* Set Rotational Thrusters */
			      printf("Enter Max Rotational Speed (deg/s): ");
			      scanf("%lf",&rr);
			      rr = rr * .0174533;
			      break;
			   case '8': /* Set Filename */
			      printf("Enter Filename: ");
			      scanf("%s",strng);
			      break;
			  }
			  if( comm2 == '0' )
			     break;
			}
			break;
		     case '9':
			printf("Enter the maximum visibility: ");
			scanf("%lf", &visd );
			break;
		     case 'a':
			printf("Enter velocity (dx,dy,dz): ");
			scanf("%lf,%lf,%lf",&dx, &dy, &dz );
			break;
		     default:
			comm = '1';
			break;
		  }
	       }

	       _setvideomode(_VRES16COLOR);
	       /* Main control panel */
	       _setcolor(7);
	       _rectangle(_GFILLINTERIOR,0,241,640,480);
	       _setcolor(15);
	       _moveto(0,241);
	       _lineto(640,241);

	       /* hole for vector meter */
	       _setcolor(0);
	       _ellipse(_GFILLINTERIOR,180,260,240,320);

	       /* hole for pitch meter */
	       _setcolor(0);
	       _ellipse(_GFILLINTERIOR,180,340,240,400);

	       /* Change check variales to have them redrawn */
	       tvel1=tvel+1, rvel1=rvel+1, angr1=angr+1, ha1=ha+1, ta1=ta+1;
	       acc1=acc+1, vd1=vd+1, pit1=pit+1;

	       _setcliprgn(0,15,640,240);
	       _clearscreen(_GVIEWPORT);
	       _dos_gettime( &st ); /* reset timer */

	       break;
	    case 'v': /* cycle thru views */
	       vd += 1;
	       if( vd >= 4 )
		  vd=0;
	       break;
	    case '5': /* center heading on true direction of travel */
	       if( tvel != 0 )
		  angr=ha;
	       rot=0;
	       break;
	    case 'w': /* increase thruster strength */
	       if( fine )
		  rvel+=M_TH/10;
	       else
		  rvel+=M_TH/5;
	       break;
	    case 'S': /* track coord */
	       _settextposition(2,0);
	       printf("Enter coords (x,y,z): ");
	       scanf("%lf,%lf,%lf",&tx,&ty,&tz);

	       trac=-2;
	       /* Calculate intersection angle (x,y axis) */
		  /* Set up relative coords */
	       dx1=tx-x;
	       dy1=ty-y;
	       dz1=tz-z;

		  /* calculate angle to each object */
	       i = run_xyb( dx1, dy1, &a1 );
	       if( i )
		  break;
	       ta=a1;

	       _setcliprgn(0,15,640,240);
	       _clearscreen(_GVIEWPORT);
	       _dos_gettime( &st ); /* reset timer */

	       break;
	    case 'p': /* pause */
	       _settextposition(15,0);
	       printf("Paused");
	       getch();
	       _setcliprgn(0,15,640,240);
	       _clearscreen(_GVIEWPORT);
	       _dos_gettime( &st ); /* reset timer */
	       break;
	    case 'x': /* decrease thruster strength */
	       if( fine )
		  rvel-=M_TH/10;
	       else
		  rvel-=M_TH/5;
	       break;
	    case 'F': /* toggle fine thruster movements */
	       if( fine )
		  fine=0;
	       else
		  fine=1;
	       break;
	    case 't': /* select track object */
	       _setcolor(0);
	       if( trac == -2 )
	       {
		  i2=tsx, i3=tsy;
		  _ellipse(_GBORDER,i2-10,i3-10,i2+10,i3+10);
		  tsx=-50., tsy=-50.;
	       }
	       else
	       {
		  i2=xo[trac], i3=yo[trac];
		  _ellipse(_GBORDER,i2-10,i3-10,i2+10,i3+10);
	       }
	       if( MAX_OBJ < 30 )
	       {
		  trac=trac+1;
	       }
	       else
	       {
		  _settextposition(2,0);
		  printf("Enter Track object #: ");
		  scanf("%d",&trac);

		  _setcliprgn(0,15,640,240);
		  _clearscreen(_GVIEWPORT);
		  _dos_gettime( &st ); /* reset timer */
	       }
	       if( trac >= MAX_OBJ )
	       {
		  trac=-1;
		  tsx=-50.;
		  tsy=-50.;
		  ta1 = ta + 1;
	       }
	       else
	       {
		  /* Set up track coords */
		  tx=ox[trac];
		  ty=oy[trac];
		  tz=oz[trac];

		  /* Calculate intersection angle (x,y axis) */
		     /* Set up relative coords */
		  dx1=tx-x;
		  dy1=ty-y;
		  dz1=tz-z;
		  if( ( !dx1 ) && ( !dy1 ) )
		     break;

		     /* calculate angle to each object */
		  if( dx1 > 0 )
		  {
		     a1=atan( dy1/dx1 );
		     if( a1 < 0 )
			a1=a1+6.28319;
		  }
		  else if( dx1 < 0 )
		  {
		     a1=atan( dy1/dx1 ) + 3.1415;
		     if( a1 > 6.28319 )
			a1=a1-6.28319;
		  }
		  else
		  {
		     if( dy1 > 0 )
			a1=1.5708;
		     if( dy1 < 0 )
			a1=4.7124;
		     if( dy1 == 0 )
			break;
		  }
		  ta=a1;
	       }
	       break;
	    case 'E': /* toggle track execution */
	       if( etrac )
		  etrac=0;
	       else if( trac != -1 )
	       {
		  etrac=1;

		  /* Calculate intersection angle (x,y axis) */
		     /* Set up relative coords */
		  dx1=tx-x;
		  dy1=ty-y;
		  dz1=tz-z;

		  /* calculate angle to each object */
		  run_xyb( dx1, dy1, &a1 );

		  if( a1>angr )
		     rot=rr;
		  if( a1<angr )
		     rot=-rr;
		  if( fabs( a1-angr ) < .05 )
		     rot=rot-rr-.01;
		  if( fabs( a1-angr ) < .0001 )
		     rot=0;
		  if( dx1 > 0 )
		  {
		     za=atan( dz1/dx1 );
		     if( za < 0 )
			za=za+6.28319;
		  }
		  else if( dx1 < 0 )
		  {
		     za=atan( dz1/dx1 ) + 3.1415;
		     if( za > 6.28319 )
			za=za-6.28319;
		  }
		  else
		  {
		     if( dy1 > 0 )
			za=1.5708;
		     if( dy1 < 0 )
			za=4.7124;
		     if( dz1 == 0 )
		     {
			za=pit;
		     }
		  }
		  if( fabs( ta-angr ) < .01 )
		  {
		     if( za>pit )
			zrot=-.174733;
		     if( za<pit )
			zrot=.174733;
		     if( ( za > 1.5708 ) && ( za < 4.7124 ) )
			zrot = 0;
		     if( fabs( za-pit ) < .01 )
			zrot-=.05;
		     if( fabs( za-pit ) < .0001 )
			zrot=0;
		  }
	       }
	       break;
	    case '7': /* thrusters up */
	       sch = pit - 1.5708;

	       dz = dz+( ( sin( sch ) ) * rvel );

	       sch = cos( sch );
	       dx = dx+( ( cos( angr ) ) * rvel * sch );
	       dy = dy+( ( sin( angr ) ) * rvel * sch );

	       /* calculate total velocity in km/sec */
	       tvel=dist( dx, dy, dz );

	       if( !tvel )
		  ha=angr;

	       /* calculate total velocity in km/sec */
	       tvel=dist( dx, dy, dz );

	       break;
	    case '3': /* thrusters down */
	       sch = pit - 1.5708;

	       dz = dz-( ( sin( sch ) ) * rvel );

	       sch = cos( sch );
	       dx = dx+( ( cos( sch ) ) * rvel * sch );
	       dy = dy+( ( sin( sch ) ) * rvel * sch );

	       /* calculate total velocity in km/sec */
	       tvel=dist( dx, dy, dz );

	       if( !tvel )
		  ha=angr;

	       /* calculate total velocity in km/sec */
	       tvel=dist( dx, dy, dz );

	       break;
	    case 'C': /* Toggle crosshairs */
	       if( chr )
	       {
		  dx1 = x + cos( ha1 ) * 10;
		  dy1 = y + sin( ha1 ) * 10;
		  dr_pt3( &i, &i2, dx1, dy1, dz1, x, y, z, angr, 0 );

		  _setcolor( 0 );
		  _moveto( i - 20, 120 );
		  _lineto( i + 20, 120 );
		  _moveto( i, 100 );
		  _lineto( i, 140 );

		  _moveto(300,120);
		  _lineto(340,120);
		  _moveto(320,100);
		  _lineto(320,140);
		  chr=0;
	       }
	       else
		  chr=1;
	       break;
	    case 'R': /* reset position */
	       goto reset;
	    default:
	       break;
	 }
      }
   }
}
