#include <MKL46Z4.h>

#define FRDIVMIN			32
#define FRDIVMAX			1536

#define PRDIVMIN			1
#define PRDIVMAX			24

#define MCGERFLL_MIN 		31.25
#define MCGERFLL_MAX 		39.0625
#define MCGERFLL_MID 		32.768

#define MCGERPLL_MIN 		2
#define MCGERPLL_MAX 		4

//#define 

enum eMCGMODE 
{
	emcgmFEI, emcgmFBI, emcgmFBE, emcgmBLPI, emcgmPBE, emcgmPEE, emcgmFEE, emcgmBLPE
};

#define FRDIV_MASK			(0x0007)
#define FRDIV_SHIFT			0
#define DMX32_MASK			(0x0008)
#define DMX32_SHIFT			3
#define DRST_DRS_MASK		(0x0030)
#define DRST_DRS_SHIFT		4
#define PRDIV0_MASK			(0x07C0)
#define PRDIV0_SHIFT		6
#define VDIV0_MASK			(0xF800)
#define VDIV0_SHIFT			11
#define MCGVALEN_MASK		(0x1)
#define MCGVALEN_SHIFT		(0)
#define C2SETEN_MASK		(0x2)
#define C2SETEN_SHIFT		1

int initMCG(int crystal_val, unsigned char drst_drs, unsigned char dmx32, 
		signed char frdiv_val, unsigned char lp_mode, unsigned char clks);
int getMCGMode();
int setMCGMode(int mode, int crysVal, unsigned short mcgVal, unsigned char c2Set, unsigned char argEnable);

