/* Shuttle simulation in space (Technical Version) */
#include <graph.h>
#include <malloc.h>
#include <math.h>
#include <conio.h>
#include <stdlib.h>
#include <dos.h>
#include "sound.c"

#define MAX_OBJ 11
#define MAX_M_OBJ 4
#define c (double) 299793 /* speed of light in km/sec */

#define getrandom( min, max ) ((rand() % (int)(((max)+1) - (min))) + (min))

main()
{
   char ch;
   int i, i2, i3, ot[MAX_OBJ], doc, nx1, ny1, nx2, ny2, h, m, nmob[MAX_M_OBJ];
   int chr, fine, trac=-1, etrac=0, xo[MAX_OBJ], yo[MAX_OBJ], oside=0, cr=1;
   int so[MAX_OBJ], osw, vd, vd1, fill=3;
   double tsx=-50.,tsy=-50., acc=0, acc1=1, ox[MAX_OBJ], oy[MAX_OBJ], oz[MAX_OBJ];
   double dox[MAX_M_OBJ], doy[MAX_M_OBJ], doz[MAX_M_OBJ];
   double x, y, z, os[MAX_OBJ],pit=0,pit1=1,zrot;
   double tvel, rvel, angr, dx, dy, dz, a1, e1, a2, etime, ts;
   double dx1, dy1, dz1, dh, dd, dh2, ds, sch, rot, dd2, ha, ha1, tx, ty, tz;
   double tvel1, rvel1, angr1, mia, maa, mie, mae, ia, ta, ta1,schs;
   double MAX_TV=2000, M_TH=.0125, M_MA=0.075, va, va2;
   long ox1[MAX_OBJ], oy1[MAX_OBJ], oz1[MAX_OBJ], sch2;
   struct dostime_t st, et;
   int sou=1;
   long isize;
   char  _huge *ibuffer;

   /*-----initialize------------*/
   _setvideomode(_VRES16COLOR);
   MAX_TV=50;
   x=0, y=0, z=0, tvel=0, rvel=.025, doc=0, dx=0, dy=0, dz=0;
   angr=1.570796326794896, rot=0, vd=0, chr=0, ha=0, fine=0, ta=0, ta1=1;
   tvel1=1, rvel1=1, angr1=1, ha1=1, nmob[0]=1, vd1=1,zrot = 0;

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
   dox[0]=-1;
   doy[0]=-1;
   doz[0]=0;

   i2=1;
   for(i=2; i<MAX_OBJ; i=i+1 )
   {
      os[i]=1;
      ot[i]=0;
      oz[i]=getrandom(0,2);
      ox[i]=getrandom(0,100);
      oy[i]=getrandom(0,100);

      while( ( !ox[i] ) && ( !oy[i] ) && ( !oz[i] ) )
      {
	 oz[i]=getrandom(0,2);
	 ox[i]=getrandom(0,100);
	 oy[i]=getrandom(0,100);
      }

      if( ox[i] > 100. )
	 ox[i] = 100.;
      if( oy[i] > 100. )
	 oy[i] = 100.;
      if( oz[i] > 100. )
	 oz[i] = 100.;

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
      if( rand()>( RAND_MAX/2 ) )
	 ox[i]=-ox[i];
      if( rand()>( RAND_MAX/2 ) )
	 oy[i]=-oy[i];
      if( rand()>( RAND_MAX/2 ) )
	 oz[i]=-oz[i];
   }

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
   for( i=5; i>=0; i=i-1 )
      _ellipse(_GBORDER,298-i,147,318-i,177);

   _setcolor(0);
   _ellipse(_GBORDER,293,147,313,177);
   _ellipse(_GBORDER,306,159,310,165);

   _setcolor(7);
   for( i=0; i<8; i=i+1 )
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

      /* round off velocities */
      if( fabs( dx ) <.001 )
	 dx=0;
      if( fabs( dy ) <.001 )
	 dy=0;

      tvel=sqrt( dx*dx + dy*dy + dz*dz );

      sch=fabs( ha-angr );
      if( sch > 3.141592654 )
	 tvel=-tvel;

      if( fabs( tvel ) > MAX_TV )
      {
	 _beep(475,10);
      }

      if( fabs( tvel ) < .001 )
	 dx=0,dy=0,dz=0;

      if( pit < 0 )
	 pit += 6.28319;

      if( pit > 6.28319 )
	 pit -= 6.28319;

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

      /* if ship is spinning, spin it */
      angr=angr+( rot*etime );
      if( angr<0 )
      {
	 angr=angr+6.283185307179585;
      }
      if( angr>6.283185307179585 )
      {
	 angr=angr-6.283185307179585;
      }

      pit = pit + ( zrot*etime );
      if( pit<0 )
      {
	 pit=pit+6.283185307179585;
      }
      if( pit>6.283185307179585 )
      {
	 pit=pit-6.283185307179585;
      }

      /* if ship is accelerating, push up delta values */
      if( acc != 0 )
      {
	 dx = dx+( ( cos( angr ) ) * ( acc * etime ) );
	 dy = dy+( ( sin( angr ) ) * ( acc * etime ) );
      }

      /*Calculate new x,y,z locations */
      x=x+dx*etime;
      y=y+dy*etime;
      z=z+( dz * etime );

      /* move moving objects */
      if( MAX_M_OBJ )
      {
	 for( i=0; i< MAX_M_OBJ; i=i+1 )
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
      if( dx > 0 )
      {
	 ha=atan( dy/dx );
	 if( ha < 0 )
	    ha=ha+6.28319;
      }
      else if( dx < 0 )
      {
	 ha=atan( dy/dx ) + 3.1415;
	 if( ha < 0 )
	    ha=ha+6.28319;
      }
      else
      {
	 if( dy > 0 )
	    ha=1.5708;
	 if( dy <= 0 )
	    ha=4.7124;
      }
      if( ( fabs( angr-ha ) < .1 ) && ( !rot ) && ( !acc ) )
	 angr=ha;

      if( tvel == 0 )
	 ha=angr;

      if( etrac ) /* Execute tracking */
      {
	 /* Calculate z axis thruster power */
	 if( tz>z )
	    dz=.25;
	 if( tz<z )
	    dz=-.25;
	 if( fabs( tz-z ) < .05 )
	    dz=dz-.24;
	 if( fabs( tz-z ) < .0001 )
	    dz=0;

	 /* Calculate intersection angle (x,y axis) */
	    /* Set up relative coords */
	 dx1=tx-x;
	 dy1=ty-y;
	 dz1=tz-z;

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
	    {
	       a1=angr;
	    }
	 }
	 if( a1>angr )
	    rot=.174733;
	 if( a1<angr )
	    rot=-.174733;
	 if( fabs( a1-angr ) < .01 )
	    rot=rot-.173733;
	 if( fabs( a1-angr ) < .0001 )
	    rot=0;
	 if( tvel!=0 )
	    ha=angr;
	 ta=a1;
      }

      /* calculate track angle to object */
      if( trac != -1 )
      {
	 /* Set up relative coords */
	 dx1=tx-x;
	 dy1=ty-y;
	 dz1=tz-z;

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
	    {
	       a1=angr;
	    }
	 }
	 ta=a1;
      }

      for ( i = 0; i < MAX_OBJ; i = i + 1 )
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


      /* Check For Crash */
      if( cr == 2 )
      {
	 for( i = 0; i < MAX_OBJ; i = i + 1 )
	 {
	    sch = os[i] / 2;

	    if( ( fabs( ox[i] - x ) < sch ) &&
		( fabs( oy[i] - y ) < sch ) &&
		( fabs( oz[i] - z ) < sch ) )
	    {
	       /* Collision with Object occured */
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
	       i = i - 1;
	       if( i )
		  dx = -dx;

	       i=getrandom(1,3);
	       i = i - 1;
	       if( i )
		  dy = -dy;

	       i=getrandom(1,3);
	       i = i - 1;
	       if( i )
		  rot = -rot;

	       i=getrandom(1,3);
	       i = i - 1;
	       if( i )
		  zrot = -zrot;
	    }
	 }
      }
      if( cr == 1 )
      {
	 for( i = 0; i < MAX_OBJ; i = i + 1 )
	 {
	    sch = os[i] / 2;
	    if( ( fabs( ox[i] - x ) < sch ) &&
		( fabs( oy[i] - y ) < sch ) &&
		( fabs( oz[i] - z ) < sch ) )
	    {
	       /* Collision with Object occured */
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
	       dx=0,dy=0,dz=0;
	       angr=1.570796326794896,ha=0,rot=0,angr1=0,ha1=1;
	       break;
	    }
	 }
      }

      /* Crash Warning */
      if( cr && sou )
      {
	 for( i = 0; i < MAX_OBJ; i = i + 1 )
	 {
	    sch = 1;
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
	 for( i=0; i<MAX_M_OBJ; i=i+1 )
	 {
	    if( nmob[i] == trac )
	    {
	       printf(" V: ");
	       if( ( dox[i]*dox[i]+doy[i]*doy[i] ) < 1e+99 )
		  printf("%g",sqrt(dox[i]*dox[i]+doy[i]*doy[i]) );
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
	    printf("%g", sqrt( dx1 * dx1 + dy1 * dy1 + dz1 * dz1 ) );
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
	 printf("%g",tvel);

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
	 if( acc > .075 )
	    acc=M_MA;
	 if( acc < 0 )
	    acc=0;
	 sch2=( acc * 100 )/M_MA;
	 i=sch2;
	 _setcolor(7);
	 _rectangle(_GFILLINTERIOR,301,360,309,360-i);
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
      if( ( angr!=angr1 ) || ( ha!=ha1 ) || ( ta!=ta1 ) || ( pit!=pit1 ) )
      {
	 /* draw hole for vector meter */
	 _setcolor(0);
	 _ellipse(_GFILLINTERIOR,180,260,240,320);

	 sch=cos(angr1)*28;
	 i=210-sch;
	 sch=sin(angr1)*28;
	 i2=290-sch;
	 _moveto(210,290);
	 _lineto(i,i2);

	 sch=cos(pit1)*28;
	 i=210-sch;
	 sch=sin(pit1)*28;
	 i2=370-sch;
	 _moveto(210,370);
	 _lineto(i,i2);


	 if( tvel1 > 0 )
	 {
	    _setcolor(0);
	    sch=cos(ha1)*28;
	    i=210-sch;
	    sch=sin(ha1)*28;
	    i2=290-sch;
	    _moveto(210,290);
	    _lineto(i,i2);
	 }

	 sch=cos(ta1)*28;
	 i=210-sch;
	 sch=sin(ta1)*28;
	 i2=290-sch;
	 sch=cos(ta1)*25;
	 i3=210-sch;
	 sch=sin(ta1)*25;
	 h=290-sch;
	 _moveto(i,i2);
	 _lineto(i3,h);

	 _setcolor(15);
	 _ellipse(_GBORDER,180,260,240,320);
	 sch=cos(angr)*28;
	 i=210-sch;
	 sch=sin(angr)*28;
	 i2=290-sch;
	 _moveto(210,290);
	 _lineto(i,i2);

	 _ellipse(_GBORDER,180,340,240,400);
	 sch=cos(pit)*28;
	 i=210-sch;
	 sch=sin(pit)*28;
	 i2=370-sch;
	 _moveto(210,370);
	 _lineto(i,i2);

	 if( trac!=-1 )
	 {
	    sch=cos(ta)*28;
	    i=210-sch;
	    sch=sin(ta)*28;
	    i2=290-sch;
	    sch=cos(ta)*25;
	    i3=210-sch;
	    sch=sin(ta)*25;
	    h=290-sch;
	    _moveto(i,i2);
	    _lineto(i3,h);
	 }

	 if( tvel > 0 )
	 {
	    if( ha == angr )
	    {
	       _setcolor(2);
	       _rectangle(_GFILLINTERIOR,200,330,220,335);
	       _setcolor(15);
	       _rectangle(_GBORDER,200,330,220,335);
	    }
	    else
	    {
	       _setcolor(4);
	       _rectangle(_GFILLINTERIOR,200,330,220,335);
	       _setcolor(15);
	       _rectangle(_GBORDER,200,330,220,335);
	    }
	    _setcolor(10);
	    sch=cos(ha)*28;
	    i=210-sch;
	    sch=sin(ha)*28;
	    i2=290-sch;
	    _moveto(210,290);
	    _lineto(i,i2);
	 }
	 else
	 {
	    _setcolor(2);
	    _rectangle(_GFILLINTERIOR,200,330,220,335);
	    _setcolor(15);
	    _rectangle(_GBORDER,200,330,220,335);
	 }

      }

      /*-----set up check variables-------*/
      tvel1=tvel, rvel1=rvel, angr1=angr, ha1=ha, ta1=ta;
      acc1=acc, vd1=vd, pit1=pit;

      /*-------View Screen---------*/
      _setcliprgn(0,15,640,240);
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

      for( i=0; i<MAX_OBJ; i=i+1)
      {
	 /* Erase old object */
	 if( trac==i )
	 {
	    _setcolor(15);
	    i2=xo[i], i3=yo[i];
	    _ellipse(_GBORDER,i2-10,i3-10,i2+10,i3+10);
	 }
	 i2=xo[i]-so[i], i3=yo[i]-so[i];
	 h=xo[i]+so[i], m=yo[i]+so[i];
	 _setcolor(0);
	 if( ot[i] == 0 )
	    _ellipse(_GFILLINTERIOR,i2,i3,h,m);
	 if( ot[i] == 1 )
	    _rectangle(_GFILLINTERIOR,i2,i3,h,m);
	 if( trac==i )
	 {
	    _setcolor(0);
	    i2=xo[i], i3=yo[i];
	    _ellipse(_GBORDER,i2-10,i3-10,i2+10,i3+10);
	 }

	 /* set up variables */
	 so[i]=0, xo[i]=-50, yo[i]=-50;

	 /* Set up relative coords */
	 dx1=ox[i]-x;
	 dy1=oy[i]-y;
	 dz1=oz[i]-z;

	 if( oside )
	 {
	    dx1 += cos( va );
	    dy1 += sin( va );
	 }

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
	       a1=mia-.785398;
	 }

	 /* is object outside field of view? */
	 if( maa<mia )
	 {
	    if( ( a1 < mia ) && ( a1 > maa ) )
	       continue; /* Object not on screen */
	 }
	 else if( ( a1<mia ) || ( a1>maa ) )
	    continue; /* then do not put on screen */

	 /* Calculate angle to object relative to view angle */
	 a2=a1-va;

	 if( fabs( a2 ) > 3.1415 )
	 {
	    a2=a2-6.28319;
	 }
	 if( fabs( a2 ) < .00001 )
	    a2=0;

	 /* calculate elevation to object */
	 if( dy1 > 0 )
	 {
	    e1=atan( dz1/dy1 );
	    if( e1 < 0 )
	       e1=e1+6.28319;
	 }
	 else if( dy1 < 0 )
	 {
	    e1=atan( dz1/dy1 );
	    if( e1 > 6.28319 )
	       e1=e1-6.28319;
	 }
	 else
	 {
	    if( dz1 > 0 )
	       e1=1.5708;
	    if( dz1 < 0 )
	       e1=4.7124;
	    if( dz1 == 0 )
	       e1=mie-.785398;
	 }

	 e1=e1+va2;

	 if( fabs( e1 ) > 6.28319 )
	 {
	    e1=e1-6.28319;
	 }
	 if( fabs( e1 ) < .00001 )
	    e1=0;

	 /* is object outside field of view? */
	 if( mae<mie )
	 {
	    if( ( e1 > mie ) && ( e1 < mae ) )
	       continue; /* Object not on screen */
	 }
	 else if( ( e1<mie ) || ( e1>mae ) )
	    continue; /* then do not put on screen */

	 /* Calculate relative distance to object */
	 dd=sqrt( dx1*dx1+dy1*dy1+dz1*dz1 );

	 /* Translate distance to field of view size */
	 dd *= 2;

	 /* Calculate apparent size of object */
	 if( dd != 0 )
	    ds=os[i]/dd; /* physical size / field of view */
	 else
	    ds=100;

	 /* Calculate radius in pixels */
	 ds *= 400;
	 so[i]=ds;

	 /* Calculate x,y on screen (dh=x, dh2=y) */
	 dh=320 + ( 320 * ( a2/.785398 ) );
	 /*if( ( a2 < 4.7124 ) && ( a2 > 1.5708 ) )
	 {

	    if( e1 > 3.1415 )
	       dh2=120 - ( 120 * ( ( e1 - 6.28319 )/.785398 ) );
	    else
	       dh2=120 - ( 120 * ( e1/.785398 ) );
	 }
	 else
	 {  */
	    if( e1 > 3.1415 )
	       dh2=120 + ( 120 * ( ( e1 - 6.28319 )/.785398 ) );
	    else
	       dh2=120 + ( 120 * ( e1/.785398 ) );
	 /*}*/

	 /*translate doubles to ints */
	 xo[i]=dh;
	 yo[i]=dh2;

	 i2=xo[i]-so[i], i3=yo[i]-so[i];
	 h=xo[i]+so[i], m=yo[i]+so[i];

	 /* draw object */
	 _setcolor(15);
	 if( ot[i] == 0 )
	    _ellipse(fill,i2,i3,h,m);
	 if( ot[i] == 1 )
	    _rectangle(fill,i2,i3,h,m);
	 if( trac==i )
	 {
	    i2=xo[i], i3=yo[i];
	    if( so[i]<10 )
	       _setcolor(14);
	    else
	       _setcolor(2);
	    _ellipse(_GBORDER,i2-10,i3-10,i2+10,i3+10);
	 }
      }
      _setcolor(0);
      i=tsx;
      i2=tsy;
      _ellipse(_GBORDER,i-10,i2-10,i+10,i2+10);

      if( trac==-2 )
      {

	 /* set up variables */
	 tsx=-50., tsy=-50.;

	 /* Set up relative coords */
	 dx1=tx-x;
	 dy1=ty-y;
	 dz1=tz-z;

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
	       a1=mia-.785398;
	 }

	 /* Calculate angle to object relative to view angle */
	 a2=a1-va;

	 if( fabs( a2 ) > 3.1415 )
	 {
	    a2=a2-6.28319;
	 }
	 if( fabs( a2 ) < .00001 )
	    a2=0;

	 /* calculate elevation to object */
	 if( dy1 > 0 )
	 {
	    e1=atan( dz1/dy1 );
	    if( e1 < 0 )
	       e1=e1+3.1415;
	 }
	 else if( dy1 < 0 )
	 {
	    e1=atan( dz1/dy1 );
	    if( e1 > 3.1415 )
	       e1=e1-3.1415;
	 }
	 else
	 {
	    if( dz1 > 0 )
	       e1=1.5708;
	    if( dz1 < 0 )
	       e1=4.7124;
	    if( dz1 == 0 )
	       e1=mie-.785398;
	 }

	 e1=e1+va2;

	 if( fabs( e1 ) > 3.1415 )
	 {
	    e1=e1-6.28319;
	 }
	 if( fabs( e1 ) < .00001 )
	    e1=0;

	 /* Calculate x,y on screen (dh=x, dh2=y) */
	 dh=320 + ( 320 * ( a2/.785398 ) );
	 if( ( a2 < 4.7124 ) && ( a2 > 1.5708 ) )
	    dh2=120 - ( 120 * ( e1/.785398 ) );
	 else
	    dh2=120 + ( 120 * ( e1/.785398 ) );

	 /* save positions */
	 tsx=dh;
	 tsy=dh2;

	 /*translate doubles to ints */
	 i=tsx;
	 i2=tsy;

	 _setcolor(14);
	 _ellipse(_GBORDER,i-10,i2-10,i+10,i2+10);
      }

      /* draw ship */
      if( oside )
      {
	 _putimage(320,120,ibuffer,_GPSET);
      }

      /* Draw Crosshairs */
      if( chr )
      {
	 _setcolor(4);
	 _moveto(300,120);
	 _lineto(340,120);
	 _moveto(320,100);
	 _lineto(320,140);
      }

      /*------Get and interpret commands-----*/
      if( kbhit() != 0 )
      {
	 ch=getch();
	 switch(ch)
	 {
	    case 'q': /* quit */
	       hfree( ibuffer );
	       goto end;
	    case 'd': /* redraw screen */
	       _setcliprgn(0,0,640,240);
	       _clearscreen(_GVIEWPORT);
	       _setcliprgn(0,0,640,480);
	       break;
	    case 'M': /* Adjust Maximum Velocity */
	       _settextposition(2,0);
	       printf("Enter Maximum Velocity: ");
	       scanf("%lf",&MAX_TV);

	       _setcliprgn(0,15,640,240);
	       _clearscreen(_GVIEWPORT);
	       _dos_gettime( &st ); /* reset timer */

	       break;

	       break;
	    case '8': /* thrusters forward */
	       dz = dz+( ( sin( pit ) ) * rvel );

	       if( !( ( fabs( pit-1.5708 ) < .001 ) ||
		   ( fabs( pit-4.7124 ) < .001 ) ) )
	       {
		  dx = dx+( ( cos( angr ) ) * rvel );
		  dy = dy+( ( sin( angr ) ) * rvel );
	       }
	       else
	       {
		  sch = pit/1.5708;
		  dx = dx+( ( cos( angr ) ) * rvel * sch );
		  dy = dy+( ( sin( angr ) ) * rvel * sch );
	       }

	       if( !tvel )
		  ha=angr;

	       /* round off velocities */
	       if( fabs( dx ) <.001 )
		  dx=0;
	       if( fabs( dy ) <.001 )
		  dy=0;

	       /* calculate total velocity in km/sec */
	       tvel=sqrt( dx*dx + dy*dy + dz*dz );

	       break;
	    case '2': /* thrusters reverse */
	       if( fabs( angr-ha ) < .1 )
		  angr=ha;

	       dz = dz-( ( sin( pit ) ) * rvel );

	       if( !( ( fabs( pit-1.5708 ) < .001 ) ||
		   ( fabs( pit-4.7124 ) < .001 ) ) )
	       {
		  dx = dx-( ( cos( angr ) ) * rvel );
		  dy = dy-( ( sin( angr ) ) * rvel );
	       }
	       else
	       {
		  sch = pit/1.5708;
		  dx = dx-( ( cos( angr ) ) * rvel * sch );
		  dy = dy-( ( sin( angr ) ) * rvel * sch );
	       }

	       if( !tvel )
	       {
		  ha=angr-3.1415;
		  if( ha < 0 )
		     ha=ha+6.28;
	       }

	       /* round off velocities */
	       if( fabs( dx ) <.001 )
		  dx=0;
	       if( fabs( dy ) <.001 )
		  dy=0;

	       /* Calculate total apparent velocity */
	       tvel=sqrt( dx*dx + dy*dy + dz*dz );

	       break;
	    case 'c': /* Rotate Down */
	       if( !fine )
		  zrot=zrot-.0873665;
	       else
		  zrot=zrot-.01;
	       break;
	    case 'e': /* Rotate Up */
	       if( !fine )
		  zrot=zrot+.0873665;
	       else
		  zrot=zrot+.01;
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
	    case 'n': /* Toggle Sound effects */
	       if( sou )
		  sou=0;
	       else
	       {
		  sou=1;
		  _beep( 100, 2 );
	       }
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
	       trac=trac+1;
	       if( trac >= MAX_OBJ )
	       {
		  trac=-1;
		  tsx=-50.;
		  tsy=-50.;
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
	    case 's': /* Slide left */
	       sch = angr - 1.5707;

	       while( sch < 0 )
		  sch = sch + 6.28319;

	       dx = dx+( ( cos( sch ) ) * rvel );
	       dy = dy+( ( sin( sch ) ) * rvel );

	       if( !tvel )
		  ha=sch;

	       /* round off velocities */
	       if( fabs( dx ) <.001 )
		  dx=0;
	       if( fabs( dy ) <.001 )
		  dy=0;

	       /* calculate total velocity in km/sec */
	       tvel=sqrt( dx*dx + dy*dy + dz*dz );

	       break;
	    case 'f': /* Slide Right */
	       sch = angr + 1.5707;

	       while( sch > 6.28319 )
		  sch = sch - 6.28319;

	       dx = dx+( ( cos( sch ) ) * rvel );
	       dy = dy+( ( sin( sch ) ) * rvel );

	       if( !tvel )
		  ha=sch;

	       /* round off velocities */
	       if( fabs( dx ) <.001 )
		  dx=0;
	       if( fabs( dy ) <.001 )
		  dy=0;

	       /* calculate total velocity in km/sec */
	       tvel=sqrt( dx*dx + dy*dy + dz*dz );

	       break;

	       break;
	    case 'E': /* toggle track execution */
	       if( etrac )
		  etrac=0;
	       else if( trac != -1 )
	       {
		  etrac=1;

		  /* Calculate z axis thruster power */
		  if( tz>z )
		     dz=.25;
		  if( tz<z )
		     dz=-.25;
		  if( fabs( tz-z ) < .05 )
		     dz=dz-.24;
		  if( fabs( tz-z ) < .0001 )
		     dz=0;

		  /* Calculate intersection angle (x,y axis) */
		     /* Set up relative coords */
		  dx1=tx-x;
		  dy1=ty-y;
		  dz1=tz-z;

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
		  if( a1>angr )
		     rot=.0873665;
		  if( a1<angr )
		     rot=-.0873665;
		  if( fabs( a1-angr ) < .05 )
		     dz=dz-.0773665;
		  if( fabs( a1-angr ) < .0001 )
		     dz=0;
	       }
	       break;
	    case '7': /* thrusters up */
	       schs = pit - 1.5708;

	       dz = dz+( ( sin( schs ) ) * rvel );

	       sch = cos( schs );
	       dx = dx+( ( cos( angr ) ) * rvel * sch );
	       dy = dy+( ( sin( angr ) ) * rvel * sch );

	       if( !tvel )
		  ha=angr;

	       /* round off velocities */
	       if( fabs( dx ) <.001 )
		  dx=0;
	       if( fabs( dy ) <.001 )
		  dy=0;

	       /* calculate total velocity in km/sec */
	       tvel=sqrt( dx*dx + dy*dy + dz*dz );

	       break;
	    case '3': /* thrusters down */
	       schs = pit - 1.5708;

	       dz = dz-( ( sin( schs ) ) * rvel );

	       sch = cos( schs );
	       dx = dx+( ( cos( schs ) ) * rvel * sch );
	       dy = dy+( ( sin( schs ) ) * rvel * sch );

	       if( !tvel )
		  ha=angr;

	       /* round off velocities */
	       if( fabs( dx ) <.001 )
		  dx=0;
	       if( fabs( dy ) <.001 )
		  dy=0;

	       /* calculate total velocity in km/sec */
	       tvel=sqrt( dx*dx + dy*dy + dz*dz );

	       break;
	    case '4': /* thrusters spin left */
	       if( !fine )
		  rot=rot-.0873665;
	       else
		  rot=rot-.01;
	       break;
	    case '6': /* thrusters spin right */
	       if( !fine )
		  rot=rot+.0873665;
	       else
		  rot=rot+.01;
	       break;
	    case 'z': /* Toggle Crash */
	       cr += 1;
	       if( cr == 3 )
		  cr=0;
	       break;
	    case 'C': /* Toggle crosshairs */
	       if( chr )
	       {
		  _setcolor(0);
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
	       _clearscreen(_GCLEARSCREEN);
	       _setcliprgn(0,0,640,480);

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

	       tvel=0, tvel1=1;
	       x=0, y=0, z=0, vd=0, vd1=1, zrot=0, pit=0,pit1=1;
	       dx=0, dy=0, dz=0, acc=0, acc1=1, rvel=M_TH, rvel1=-1;
	       angr=1.570796326794896,ha=0,rot=0,angr1=0,ha1=1;

	       break;
	    default:
	       break;
	 }
      }
   }
end:
   _setvideomode(_DEFAULTMODE);
   printf("SC2 Simulator Completed\n");
}
