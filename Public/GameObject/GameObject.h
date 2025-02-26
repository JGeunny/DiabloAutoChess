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
	virtual void		FSM();// 유한 상태 기계(기본적인 인공지능)


public:
	bool				ReceiveAttack(int _iAtt = 0);	//hp가 0이되면 true 반환
public:
	bool				IsHit(CGameObject * pObj); //또공격 했는지 체크
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
	//공격 한 타겟이 계속 겹쳐있어 연속으로 데미지가 들어가는 경우를 방지하기 위한 변수
	std::unordered_map<CGameObject*, UINT>	m_mapAttackTime;	//최초 공격한 유닛의 시간을 저장
	UINT									m_uValidityTime; 	//m_mapUnitAttackTime 의 유지 시간 이시간이 지나면 삭제 해줄꺼임

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

