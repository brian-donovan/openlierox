/////////////////////////////////////////
//
//             OpenLieroX
//
// code under LGPL, based on JasonBs work,
// enhanced by Dark Charlie and Albert Zeyer
//
//
/////////////////////////////////////////


// Client class - Sending routines
// Created 22/7/02
// Jason Boettcher


#include "LieroX.h"
#include "CClient.h"
#include "Protocol.h"
#include "CWorm.h"


///////////////////
// Send the worm details
void CClient::SendWormDetails(void)
{
	// Don't flood packets so often
	if ((tLX->fCurTime - fLastUpdateSent) <= tLXOptions->fUpdatePeriod)
		if (tGameInfo.iGameType != GME_LOCAL)  {
			fLastUpdateSent = tLX->fCurTime;
			return;
		}

	CBytestream bs;
	CWorm *w;
	uint i;

	// If all me worms are not alive, don't send
	bool Alive = false;
	for(i=0;i<iNumWorms;i++) {
		if(cLocalWorms[i]->getAlive()) {
			Alive = true;
			break;		
		}
	}

	if(!Alive)
		return;


	// Check if we need to write the state update
	bool update = false;
	w = cLocalWorms[0];
	for(i = 0; i < iNumWorms; i++, w++)
		if (w->checkPacketNeeded())  {
			update = true;
			break;
		}
	// No update, just quit
	if (!update)
		return;

	// Write the update
	bs.writeByte(C2S_UPDATE);
	
	w = cLocalWorms[0];
	for(i = 0; i < iNumWorms; i++, w++)
		w->writePacket(&bs);

	bsUnreliable.Append(&bs);
}


///////////////////
// Send a death
void CClient::SendDeath(int victim, int killer)
{
	CBytestream *bs = cNetChan.getMessageBS();

	bs->writeByte(C2S_DEATH);
	bs->writeInt(victim,1);
	bs->writeInt(killer,1);
}


///////////////////
// Send a string of text
void CClient::SendText(const std::string& sText)
{
	CBytestream *bs = cNetChan.getMessageBS();

	bs->writeByte(C2S_CHATTEXT);
	bs->writeString(sText);
}
