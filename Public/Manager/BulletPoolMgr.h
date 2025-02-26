#pragma once
class CBulletPoolMgr
{
	DECLARE_SINGLETON(CBulletPoolMgr)

private:
	CBulletPoolMgr();
	~CBulletPoolMgr();

public:
	enum EBulletType {eArrow, eIceBolt, eLaser, eEnd};

public:
	CGameObject* GetBullet(EBulletType _eBulletType = eArrow);

public:
	void SetObject(EBulletType _eBulletType, CGameObject* pObject);

private:
	void Release();


private:
	std::list<CGameObject*>	m_BulletPool[eEnd]; // 오브젝트 풀
};

