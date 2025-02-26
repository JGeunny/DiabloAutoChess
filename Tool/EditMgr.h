#pragma once

//Main
class CMainFrame;
//Left
class CMiniView;
class CObjView;
class CObjFormView;
//Right
class CToolView;
class CEditFormView;
//Data
class CTerrain;

class CEditMgr
{
	DECLARE_SINGLETON(CEditMgr)
private:
	explicit		CEditMgr();
	virtual			~CEditMgr();

public:
	enum class EditState {MAPTOOL, UNITTOOL, MIXTOOL, END};
public:
	HRESULT			Initialize();
	void			Release();

	void			Update();
	void			Render(bool _bMiniView = false);
	void			ChangeEditState();
	
public:
	void			SetMainFrame(CMainFrame* _pMainFrame) { m_pMainFrame = _pMainFrame; }

	void			SetMiniView(CMiniView* _pMiniView) { m_pMiniView = _pMiniView; }
	void			SetObjView(CObjView* _pObjView) { m_pObjView = _pObjView; }
	void			SetObjFormView(CObjFormView* _pObjFormView) { m_pObjFormView = _pObjFormView; }

	void			SetToolView(CToolView* _pToolView) { m_pToolView = _pToolView; }
	void			SetEditFormView(CEditFormView* _pEditFormView) { m_pEditFormView = _pEditFormView; }

	void			SetEditState(EditState _eEditState) { m_eNextEditState = _eEditState; }
	
public:
	CMainFrame*		GetMainFrame() { return m_pMainFrame; }

	CMiniView*		GetMiniView() { return m_pMiniView; }
	CObjView*		GetObjView() { return m_pObjView; }
	CObjFormView*	GetObjFormView() { return m_pObjFormView; }

	CToolView*		GetToolView() { return m_pToolView; }
	CEditFormView*	GetEditFormView() { return m_pEditFormView; }

	CTerrain*		GetTerrain() { return m_pTerrain; }

	EditState&		GetEditState() { return m_eNextEditState; }

private:
	CMainFrame*		m_pMainFrame;

	CMiniView*		m_pMiniView;
	CObjView*		m_pObjView;
	CObjFormView*	m_pObjFormView;

	CToolView*		m_pToolView;
	CEditFormView*	m_pEditFormView;

	CObjMgr*		m_pObjMgr;

private:
	CTerrain*		m_pTerrain;

	EditState		m_eCurEditState;
	EditState		m_eNextEditState;

};

