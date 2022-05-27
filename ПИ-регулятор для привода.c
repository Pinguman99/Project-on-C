#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
#include <AsDefault.h>
#endif

// amount of memory to be allocated for heap storage must be specified for every ANSI C++ program with the bur_heap_size variable
unsigned long bur_heap_size = 0xFFFF; 

void _INIT ProgramInit(void)
{
	fb_motor.dt=0.01;
	fb_motor.ke=16;
	fb_motor.Tm=0.04;
	

	fb_motor2.dt=0.01;
	fb_motor2.ke=16;
	fb_motor2.Tm=0.04;
	
	
	fb_regulator.dt=0.01;
	fb_regulator.k_p=0.64;
	fb_regulator.k_i=16;
	fb_regulator.max_abs_value=24;
	
	enable=1;
	count=0;
	speed = 0;

}

void _CYCLIC ProgramCyclic(void)
{
	if(enable)
	{
		count+=10;
		if(count<=2500)
		{
			speed=0;
		}
			
		else
		{
			speed=6;
			if(count>=5000)
			{
				count=0;
			}
		}
	}
	fb_regulator.e = speed - fb_motor.w;
	FB_Regulator(&(fb_regulator));
	fb_motor.u = fb_regulator.u*fb_motor.ke;
	fb_motor2.u = speed*fb_motor2.ke;
	FB_Motor(&(fb_motor));
	FB_Motor(&(fb_motor2));

}

void _EXIT ProgramExit(void)
{
	// Insert code here 

}