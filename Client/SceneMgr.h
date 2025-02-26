#pragma once

class CScene;
class CSceneMgr
{
	DECLARE_SINGLETON(CSceneMgr)
private:
	explicit CSceneMgr();
	virtual ~CSceneMgr();

public:
	bool Initialize();
	void Update();
	void LateUpdate();
	void Render();
	void Release();

public:
	void SceneChange(ENUM::Scene _eScene);

private:
	HRESULT ExecuteSceneChange();

protected:
	CScrollMgr* m_pScrollMgr;

protected:
	CScene*		m_pScene;
	ENUM::Scene m_eCurScene;
	ENUM::Scene m_eNextScene;
};