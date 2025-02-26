#pragma once
class CMainApp
{
private:
	explicit CMainApp();
public:
	virtual ~CMainApp();

public:
	void	Update();
	void	LateUpdate();
	void	Render();

private:
	HRESULT Initialize();
	void	Release();

public:
	static CMainApp* Create();

private:
	CTimeMgr*		m_pTimeMgr;
	CFrameMgr*		m_pFrameMgr;
	CDeviceMgr*		m_pDeviceMgr;
	CTextureMgr*	m_pTextureMgr;
	CKeyMgr*		m_pKeyMgr;
	CControlMgr*	m_pControlMgr;
	CSceneMgr*		m_pSceneMgr;
};

