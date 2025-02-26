#include "stdafx.h"
#include "BulletPoolMgr.h"
#include "GameObject.h"

IMPLEMENT_SINGLETON(CBulletPoolMgr)
CBulletPoolMgr::CBulletPoolMgr()
{
}


CBulletPoolMgr::~CBulletPoolMgr()
{
	Release();
}

CGameObject * CBulletPoolMgr::GetBullet(EBulletType _eBulletType)
{
	if (m_BulletPool[_eBulletType].empty())
	{
		return nullptr;
	}
	else
	{
		// 풀에 재활용 가능한 오브젝트가 존재한다면 재활용!
		CGameObject* pObject = m_BulletPool[_eBulletType].front();
		m_BulletPool[_eBulletType].pop_front();
		pObject->InitData();
		return pObject;
	}
}

void CBulletPoolMgr::SetObject(EBulletType _eBulletType, CGameObject * pObject)
{
	if (pObject)
	{
		pObject->GetStatusInfo().FnRecovery();
		// 사용을 마친 오브젝트는 풀에 담는다.
		m_BulletPool[_eBulletType].push_back(pObject);
	}
}

void CBulletPoolMgr::Release()
{
	for (auto& lstBulletPool : m_BulletPool)
	{
		for_each(lstBulletPool.begin(), lstBulletPool.end(), SafeDelete<CGameObject*>);
		lstBulletPool.clear();
	}
}
