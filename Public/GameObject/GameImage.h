#pragma once
#include "Observer.h"
class CGameImage
	: public CObserver
{
public:
	explicit CGameImage();
	virtual ~CGameImage();

protected:
	virtual HRESULT		Initialize() PURE;
	virtual HRESULT		LateInit();
	virtual void		Release() PURE;

public:
	virtual int			Update() PURE;
	virtual void		LateUpdate() PURE;
	virtual void		Render() PURE;

public:
	virtual void		Render_Scroll();
	bool				IsRendering();
	virtual void		RenderInfo();

public:
	virtual void		MoveFrame(); //애니 메이션

public:
	void				SetPos(float _fX, float _fY) { m_tDraw.vPos.x = _fX; m_tDraw.vPos.y = _fY; }
	void				SetSize(float _fX, float _fY) { m_tDraw.vSize.x = _fX; m_tDraw.vSize.y = _fY; }
	void				SetPos(D3DXVECTOR3& _vPos) { m_tDraw.vPos = _vPos; }
	void				SetSize(D3DXVECTOR3& _vSize) { m_tDraw.vSize = _vSize; }
	void				SetScale(D3DXVECTOR3& _vScale) { m_tDraw.vScale = _vScale; }
	void				SetAngle(float _fAngle) { m_tDraw.vAngle.z = _fAngle; }
	void				SetFrameKey(TCHAR* _pFrameKey) { lstrcpy(m_szFrameKey, _pFrameKey); }
	void				SetFrame(FRAME& _tFrame) { m_tFrame = _tFrame; }
	void				SetActivate(bool _bActivate) { m_bActivate = _bActivate; }
public:
	D3DXVECTOR3&		GetPos() { return m_tDraw.vPos; }
	D3DXVECTOR3&		GetSize() { return m_tDraw.vSize; }
	D3DXVECTOR3&		GetScale() { return m_tDraw.vScale; }
	RECT				GetRect(){ return m_tDraw.GetRect(); }
	DRAW_INFO&			GetDrawInfo() { return m_tDraw; }
	TCHAR*				GetFrameKey(){ return m_szFrameKey; }
	FRAME&				GetFrame() { return m_tFrame; }
	bool&				GetActivate() { return m_bActivate; }

public:
	void				SetSelect(bool _bSelect) { m_bSelect = _bSelect; }
	void				SetImpossible(bool _bImpossilbe) { m_bImpossible = _bImpossilbe; }
	void				SetVisible(bool _bVisible) { m_bVisible = _bVisible; }

public:
	bool&				GetSelect() { return m_bSelect; }
	bool&				GetImpossible() { return m_bImpossible; }
	bool&				GetVisible() { return m_bVisible; }

protected:
	bool				m_bSelect;
	bool				m_bImpossible;
	bool				m_bVisible;
	bool				m_bInfoRender;

protected:
	bool				m_bIsInit;
	DRAW_INFO			m_tDraw;
	DRAW_INFO			m_tDrawBackGround;
	
protected:
	FRAME				m_tFrame;							//애니메이션
	TCHAR				m_szFrameKey[MAX_STR];

protected:
	CDeviceMgr*			m_pDeviceMgr;
	CTextureMgr*		m_pTextureMgr;
	CKeyMgr*			m_pKeyMgr;
	//CSoundMgr*		m_pSoundMgr;
	CObjMgr*			m_pObjMgr;
	CScrollMgr*			m_pScrollMgr;

protected:
	bool				m_bActivate;
};