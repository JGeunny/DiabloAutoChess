#include "stdafx.h"
#include "ButtonImageImp.h"

CButtonImageImp::CButtonImageImp()
	:m_pDeviceMgr(CDeviceMgr::GetInstance())
	, m_pTextureMgr(CTextureMgr::GetInstance())
{
}


CButtonImageImp::~CButtonImageImp()
{
}

