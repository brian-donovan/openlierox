/////////////////////////////////////////
//
//             OpenLieroX
//
// code under LGPL, based on JasonBs work,
// enhanced by Dark Charlie and Albert Zeyer
//
//
/////////////////////////////////////////


// Projectile class
// Created 26/6/02
// Jason Boettcher


#ifndef __CPROJECTILE_H__
#define __CPROJECTILE_H__

#include "Sounds.h"
#include "GfxPrimitives.h"

#define		MAX_PROJECTILES	3000

#define		COL_TOP		    0x01
#define		COL_RIGHT	    0x02
#define		COL_BOTTOM	    0x04
#define		COL_LEFT	    0x08


// Projectile collisions
#define     PJC_NONE        0x00
#define     PJC_TERRAIN     0x01
#define     PJC_WORM        0x02
#define     PJC_EXPLODE     0x04
#define     PJC_TOUCH       0x08




// Projectile structure
class proj_t { public:
	std::string	filename;		// Compiler use (was 64b before)
	int		id;					// File ref use

	int		Type;
	int		Trail;
	int		NumColours;
	int		Colour1[3];
	int		Colour2[3];
	std::string	ImgFilename; // (was 64b before)
	int		Rotating;
	int		RotIncrement;
	int		RotSpeed;
	int		UseAngle;
	int		UseSpecAngle;
	int		AngleImages;
	int		UseCustomGravity;
	int		Gravity;
	int		Animating;
	float	AnimRate;
	int		AnimType;
	float   Dampening;

	// Timer (When the timer is finished)
	int		Timer_Type;
	float	Timer_Time;
	float	Timer_TimeVar;
	int		Timer_Damage;
	int		Timer_Projectiles;
	int		Timer_Shake;
	
	// Hit (When hitting the terrain)
	int		Hit_Type;
	int		Hit_Damage;
	int		Hit_Projectiles;
	int		Hit_UseSound;
	int		Hit_Shake;
	std::string	Hit_SndFilename; // (was 64b before)
	float	Hit_BounceCoeff;
	int		Hit_BounceExplode;

    // OnExplode (When something near has exploded)
    int		Exp_Type;
	int		Exp_Damage;
	int		Exp_Projectiles;
	int		Exp_UseSound;
    std::string	Exp_SndFilename; // (was 64b before)
	int		Exp_Shake;


    // Touch (When another projectile has touched this projectile)
    int		Tch_Type;
	int		Tch_Damage;
	int		Tch_Projectiles;
	int		Tch_UseSound;
    std::string	Tch_SndFilename; // (was 64b before)
	int		Tch_Shake;


	// Player hit
	int		PlyHit_Type;
	int		PlyHit_Damage;
	int		PlyHit_Projectiles;
	float	PlyHit_BounceCoeff;

	int		ProjUseangle;
	int		ProjAngle;
	int		ProjSpeed;
	float	ProjSpeedVar;
	float	ProjSpread;	
	int		ProjAmount;
	proj_t	*Projectile;


	// Projectile trail
	int		PrjTrl_UsePrjVelocity;
	float	PrjTrl_Delay;
	int		PrjTrl_Amount;
	int		PrjTrl_Speed;
	float	PrjTrl_SpeedVar;
	float	PrjTrl_Spread;
	proj_t	*PrjTrl_Proj;



#ifndef _CONSOLE
	SDL_Surface*	bmpImage;
	SoundSample*	smpSample;
#endif


};

class CProjectile {
public:
	// Constructor
	CProjectile() {
        iID = 0;
		fSpeed = 0;
		bUsed = false;
		fLife = 0;
		tProjInfo = NULL;
		fLastTrailProj = 0;
		iSpawnPrjTrl = false;
		iColour = 0;
		iRandom = 0;
		iRemote = false;
        nExplode = false;
        nTouched = false;
        fRotation = 0;
	}


private:
	// Attributes

    int         iID;
	bool		bUsed;
	int			iType;
	float		fLife;
	float		fExtra;
	int			iOwner;
	float		fSpeed;
	Uint32		iColour;

	// Projectile trail
	float		fLastTrailProj;
	int			iSpawnPrjTrl;
    float       fTimeVarRandom;

	proj_t		*tProjInfo;

	CVec		vOldPos;
	CVec		vPosition;
	CVec		vVelocity;
	float		fRotation;
	int			CollisionSide;

	// Network
	int			iRandom;
	int			iRemote;
	float		fRemoteFrameTime;

	// Animation
	int			iFrameDelta;
	float		fFrame;
    int         iFrameX;

	// Beam info
	CVec		vStart, vEnd;
	int			iWidth;

    // Queued events
    int         nExplode;
    float       fExplodeTime;
    int         nTouched;

	// Debug info
	int			firstbounce;



public:
	// Methods
	

	void	Spawn(proj_t *_proj, CVec _pos, CVec _vel, int _rot, int _owner, int _random, int _remote, float _remoteframe);	
	int		Simulate(float dt, CMap *map, CWorm *worms, int *wormid);
	int		Collision(uchar pf);

    void	Draw(SDL_Surface *bmpDest, CViewport *view);
    void	DrawShadow(SDL_Surface *bmpDest, CViewport *view, CMap *map);

	int		CheckWormCollision(CWorm *worms);
	int		ProjWormColl(CVec pos, CWorm *worms);
	int		CheckCollision(float dt, CMap *map, CWorm* worms, float* enddt);
	static int	CheckCollision(proj_t* tProjInfo, float dt, CMap *map, CVec pos, CVec vel);

	void	Bounce(float fCoeff);

	bool	isUsed(void)			{ return bUsed; }
	void	setUsed(bool u)			{ bUsed = u; }

	float	getLife(void)			{ return fLife; }

	int		getSpawnPrjTrl(void)	{ return iSpawnPrjTrl; }
	void	setSpawnPrjTrl(int p)	{ iSpawnPrjTrl = p; }

	CVec	GetPosition(void)		{ return vPosition; }
	CVec	GetVelocity(void)		{ return vVelocity; }
	proj_t	*GetProjInfo(void)		{ return tProjInfo; }
	int		GetOwner(void)			{ return iOwner; }

    float   getTimeVarRandom(void)  { return fTimeVarRandom; }

	float	getRandomFloat(void);
	int		getRandomIndex(void)	{ return iRandom; }

    void    setID(int id)           { iID = id; }
    int     getID(void)             { return iID; }

    void    setExplode(float t, int _e)     { fExplodeTime = t; nExplode = _e; }
    void    setTouched(int _t)      { nTouched = _t; }


};


#endif  //  __CPROJECTILE_H__
