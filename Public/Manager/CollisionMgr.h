#pragma once

//class CGameObject;
class CCollisionMgr
{
private:
	explicit CCollisionMgr();
	virtual ~CCollisionMgr();

public:
	static void TargetUnit(std::list<CGameObject*>& rSrc, float _fRecogDist = 250);
	static bool CollisionGoToBattleField(std::list<CGameObject*>& rSrc);//����ʿ��� ��Ʋ�ʵ�� ������ ���� �ڵ�
	static void CollisionRect(std::list<CGameObject*>& rDst, std::list<CGameObject*>& rSrc);
	static void CollisionRectEx(std::list<CGameObject*>& rDst, std::list<CGameObject*>& rSrc);
	static void CollisionRectEx(CGameObject* pDest, CGameObject* pSrc);
	static void CollisionSphereEx(CGameObject* pDst, CGameObject* pSrc);
	static bool CheckSphere(CGameObject * pDst, CGameObject * pSrc);
	//template<class Object1, class Object2>
	//static void CollisionSphere(std::list<Object1*>& rDst, std::list<Object2*>& rSrc);

public:
	//template<class Object1, class Object2>
	//static bool CheckSphere(Object1* pDst, Object2* pSrc);

public:
	//template<class Object1, class Object2>
	//static void ObjOnMouse(std::list<CObj*>& rObj, CObj * rMouse);
	//static void TargetEnemy(std::list<CObj*>& rDst, std::list<CObj*>& rSrc);
};
