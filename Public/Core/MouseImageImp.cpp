#include "stdafx.h"
#include "MouseImageImp.h"


CMouseImageImp::CMouseImageImp()
	:m_pDeviceMgr(CDeviceMgr::GetInstance())
	, m_pTextureMgr(CTextureMgr::GetInstance())
{
}


CMouseImageImp::~CMouseImageImp()
{
}
