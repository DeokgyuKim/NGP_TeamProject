#pragma once
class CScene;
class CSceneMgr
{
public:
	enum SCENEID{SCENE_LOGO, SCENE_INTRO, SCENE_MENU, SCENE_EDIT, SCENE_STAGE, SCENE_BOSS, SCENE_ENDING, SCENE_END};
private:
	CScene*				m_pScene;
	SCENEID				m_eCurScene;
	SCENEID				m_eNextScene;
public:
	SCENEID	Get_SceneID() { return m_eCurScene; }
	void	Update();
	void	LateUpdate();
	void	Render(HDC hDC);
	void	Release();
public:
	void	SceneChange(SCENEID eNextScene);
private:
	static CSceneMgr*	m_pInstance;
public:
	static CSceneMgr*	Get_Instance() {
		if (nullptr == m_pInstance)
			m_pInstance = new CSceneMgr;
		return m_pInstance;
	}
	static void			Destory_Instace() {
		if (m_pInstance)
			delete m_pInstance;
		m_pInstance = nullptr;
	}
private:
	CSceneMgr();
	CSceneMgr(const CSceneMgr& _rVal) {}
	void operator=(const CSceneMgr& rVal) {}
	~CSceneMgr();
};

