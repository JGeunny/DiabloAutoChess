#pragma once

class CArrangementMgr;
class CTerrain;
class CGameImage;
class CTile;
class CObjMgr
{
	DECLARE_SINGLETON(CObjMgr)

private:
	explicit CObjMgr();
	virtual ~CObjMgr();

public:
	HRESULT		 Initialize();

public:
	int			Update();
	void		LateUpdate();
	void		Render();
	void		Release();

public:
	HRESULT		AddObject(ENUM::MapType _eMapType, CGameImage* pObj);
	HRESULT		AddObject(ENUM::ObjType _eObjType, CGameObject* pObj);
	HRESULT		AddObject(ENUM::UIType _eUIType, CGameImage* pObj);

public:
	//void	GetObjListOrderBy(list<CObj*>& _lstObj, OBJ::ID _eBegin, OBJ::ID _eEnd, int _iOrderBy = 0);	//y 정렬을 위한 함수

public:
	void		DeleteID(ENUM::MapType _eMapType);
	void		DeleteID(ENUM::ObjType _eObjType);
	void		DeleteID(ENUM::UIType _eUIType);

private:
	void		DeleteBufferID(ENUM::MapType _eMapType);
	void		DeleteBufferID(ENUM::ObjType _eObjType);
	void		DeleteBufferID(ENUM::UIType _eUIType);

public:
	void		SelectedObjectFollowToPos(CTile* _pTile);
	void		DeselectObjectList();

public:
	CGameObject*	GetUnit(D3DXVECTOR3 _vPos);
	bool			CollisionExUnit(CGameObject* _pUnit);

public:
	std::list<CGameImage*>&		GetObjectList(ENUM::MapType _eMapType);
	std::list<CGameObject*>&	GetObjectList(ENUM::ObjType _eObjType);
	std::list<CGameImage*>&		GetObjectList(ENUM::UIType _eUIType);

public:
	CGameObject* GetObjectInList(D3DXVECTOR3 _vMousePos);
	CTerrain*	 GetTerrain();

public:
	void		InitNextScene();
	void		LoadUnitInfo();

public:
	void		BackupList();
	void		LoadList();

public:
	CGameObject* CreateObject(RZIMAGE::ID _eImageId);

private:
	std::list<CGameImage*> m_lstMap[(int)ENUM::MapType::END];
	std::list<CGameObject*> m_lstObject[(int)ENUM::ObjType::END];
	std::list<CGameImage*> m_lstUI[(int)ENUM::UIType::END];

private:
	std::list<CGameImage*> m_lstMapBuffer[(int)ENUM::MapType::END];
	std::list<CGameObject*> m_lstObjectBuffer[(int)ENUM::ObjType::END];
	std::list<CGameImage*> m_lstUIBuffer[(int)ENUM::UIType::END];

public:
	CArrangementMgr* m_pArrangementMgr;
};