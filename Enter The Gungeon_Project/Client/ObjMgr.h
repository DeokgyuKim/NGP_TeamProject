#pragma once
class CObj; 
class CObjMgr
{
public:
	static CObjMgr* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CObjMgr; 

		return m_pInstance; 
	}
	static void Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance; 
			m_pInstance = nullptr; 
		}
	}
private:
	CObjMgr();
	~CObjMgr();
	CObjMgr(CObjMgr& rObj) {}
	void operator=(CObjMgr& rObj) {}
public:
	void			Push_Object(CObj* pObj, OBJ::ID eID);
	void			Clear_Object(OBJ::ID eID);
	void			Wheel_Up_N_Down(int zDelta);
	CObj*			Get_Player() { return m_lstObject[OBJ::PLAYER].front();  }
	CObj*			Get_Mouse() { return m_lstObject[OBJ::MOUSE].front(); }
	CObj*			Get_Target(CObj* pSourceObj, OBJ::ID eID);
	CObj*			Get_Boss();
	list<CObj*>*	Get_M_LstBullet() { return &m_lstObject[OBJ::M_BULLET]; }
	list<CObj*>*	Get_P_LstBullet() { return &m_lstObject[OBJ::P_BULLET]; }
	list<CObj*>*	Get_Monster() { return &m_lstObject[OBJ::MONSTER]; }
	list<CObj*>*	Get_Razer() { return &m_lstObject[OBJ::RAZER]; }
	list<CObj*>*	Get_Teleport() { return &m_lstObject[OBJ::TELEPORT]; }
public:
	void Update(); 
	void LateUpdate(); 
	void Render(HDC hDC);
	void Release(); 
private:
	static CObjMgr* m_pInstance; 
	list<CObj*> m_lstObject[OBJ::END];
};

