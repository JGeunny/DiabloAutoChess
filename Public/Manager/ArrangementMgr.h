#pragma once

class CObjMgr;
class CControlMgr;
class CArrangementMgr
{
	DECLARE_SINGLETON(CArrangementMgr)
private:
	explicit CArrangementMgr();
	virtual ~CArrangementMgr();

public:
	enum class Mode
	{
		NORMAL, ARRANGE
	};

public:
	HRESULT			Initialize();

public:
	int				Update();
	void			LateUpdate();
	void			Render();
	void			Release();

public:
	CObjMgr*		m_pObjMgr;
	CControlMgr*	m_pControlMgr;
	CKeyMgr*		m_pKeyMgr;

public:
	void			SetMode(Mode _eMode) { m_eMode = _eMode; }

public:
	Mode			GetMode() { return m_eMode; }

public:
	Mode			m_eMode;
};

