#include "define.h"
#include "Tile.h"


CTile::CTile()
{
}


CTile::~CTile()
{
	Release();
}

void CTile::Initialize()
{
	m_tInfo.iCX = TILECX;
	m_tInfo.iCY = TILECY;
	m_iDrawID = 0;
	m_iOption = 1;
}

int CTile::Update()
{
	return 0;
}

void CTile::LateUpdate()
{
}

void CTile::Release()
{
}
