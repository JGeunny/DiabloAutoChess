#pragma once
#include "GameImage.h"
class CGameObject :
	public CGameImage
{
public:
	explicit			CGameObject();
	virtual				~CGameObject();

protected:
	virtual HRESULT		Initialize() PURE;
	virtual HRESULT		LateInit();
	virtual void		Release() PURE;

public:
	virtual int			Update() PURE;
	virtual void		LateUpdate() PURE;
	virtual void		Render() PURE;

public:
	virtual void		RenderInfo();

public:
	virtual void		FSM();// ���� ���� ���(�⺻���� �ΰ�����)


public:
	bool				ReceiveAttack(int _iAtt = 0);	//hp�� 0�̵Ǹ� true ��ȯ
public:
	bool				IsHit(CGameObject * pObj); //�ǰ��� �ߴ��� üũ
	bool				IsTeam(ENUM::Team _eTeam) { return (m_tStatus.eTeam == _eTeam); }
	bool				IsRecogDist(float _fRecogDist) { return (_fRecogDist <= m_tStatus.fRecogDist); }
	bool				IsRecogDist(CGameObject* _pObj);
	

public:
	void				SetTeam(ENUM::Team _eTeam) { m_tStatus.eTeam = _eTeam; }
	void				SetRecogDist(float _fRecogDist) { m_tStatus.fRecogDist = _fRecogDist; }
	void				SetControlFucus(bool _bControlFocus) { m_bControlFocus = _bControlFocus; }
	void				SetState(ENUM::State _eState) { m_eNextState = _eState; }
	void				SetCollisionLand(bool _bCollisionLand){ m_bCollisionLand = _bCollisionLand; }
	void				SetStun(bool _bStun) { m_bStun = _bStun; }
	void				SetBuff(bool _bBuff) { m_bBuff = _bBuff; }

	void				SetLeadershipKey(CGameObject* _pKey) { m_pLeadershipKey = _pKey; }
	void				SetBeOnTheLand(bool _bBeOnTheLand) { m_bBeOnTheLand = _bBeOnTheLand; }
	void				SetLandPos(D3DXVECTOR3 _vLandPos) { m_vLandPos = _vLandPos; }
public:
	ENUM::Team&			GetTeam() { return  m_tStatus.eTeam; }
	float&				GetRecogDist() { return m_tStatus.fRecogDist; }
	STATUS_INFO&		GetStatusInfo() { return m_tStatus; }
	ENUM::State&		GetState() { return m_eNextState; }
	bool&				GetControlFucus() { return m_bControlFocus; }
	int					GetClassId() { return m_tStatus.iClassID; }
	bool				GetCollisionLand(){ return m_bCollisionLand; }
	bool				GetStun() { return m_bStun; }
	bool				GetBuff() { return m_bBuff; }

	CGameObject*		GetLeadershipKey() { return m_pLeadershipKey; }
	bool				GetBeOnTheLand() { return m_bBeOnTheLand; }
	D3DXVECTOR3&		GetLandPos() { return m_vLandPos; }
public:
	//���� �� Ÿ���� ��� �����־� �������� �������� ���� ��츦 �����ϱ� ���� ����
	std::unordered_map<CGameObject*, UINT>	m_mapAttackTime;	//���� ������ ������ �ð��� ����
	UINT									m_uValidityTime; 	//m_mapUnitAttackTime �� ���� �ð� �̽ð��� ������ ���� ���ٲ���

protected:
	STATUS_INFO			m_tStatus;
	ENUM::State			m_eCurState;
	ENUM::State			m_eNextState;

protected:
	bool				m_bControlFocus;
	D3DXVECTOR3			m_vMoveCheckPos;
	int					m_iCheckHp;
	bool				m_bCollisionLand;
	bool				m_bReStartAstar;

	bool				m_bStun;
	bool				m_bBuff;

protected:
	CGameObject*		m_pLeadershipKey;
	bool				m_bBeOnTheLand;
	D3DXVECTOR3			m_vLandPos;
};

