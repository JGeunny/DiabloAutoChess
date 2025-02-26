#include "stdafx.h"
//#include "../../Client/stdafx.h"
#include "TextureMgr.h"
#include "SingleTexture.h"
#include "MultiTexture.h"

IMPLEMENT_SINGLETON(CTextureMgr)
CTextureMgr::CTextureMgr()
{
}

CTextureMgr::~CTextureMgr()
{
	Release();
}

const TEXTURE_INFO * CTextureMgr::GetTexInfo(const std::wstring & _wstrImageKey,  const int & _iIndex)
{
	auto& iter = m_mapImage.find(_wstrImageKey);
	if (m_mapImage.end() == iter)
	{
		return nullptr;
	}
	return iter->second->GetTexInfo(_iIndex);
}

HRESULT CTextureMgr::LoadTexture(const std::wstring & _wstrImageKey,
	const std::wstring & _wstrFilePath, const int & _iCount,
	const int & _iCountX, const int & _iCountY, const D3DCOLOR& _dwColor)
{
	auto& iter = m_mapImage.find(_wstrImageKey);
	if (iter != m_mapImage.end()) // 존재 하는 그림
	{
		iter->second->LoadTexture(_wstrFilePath, _iCount, _iCountX, _iCountY, _dwColor);
	}
	else
	{
		CTexture* pTexture = nullptr;
		if(_iCount == -1)
			pTexture = new CSingleTexture;
		else
			pTexture = new CMultiTexture;
		pTexture->LoadTexture(_wstrFilePath, _iCount, _iCountX, _iCountY, _dwColor);
		m_mapImage.emplace(_wstrImageKey, pTexture);

		SetImageVec(_wstrImageKey, pTexture);
	}
	return S_OK;
}

const int CTextureMgr::GetSize(const std::wstring & _wstrImageKey)
{
	auto& iter = m_mapImage.find(_wstrImageKey);
	if (m_mapImage.end() == iter)
	{
		return 0;
	}
	return iter->second->GetSize();
}

CTexture * CTextureMgr::GetTexture(const std::wstring & _wstrImageKey)
{
	auto& iter = m_mapImage.find(_wstrImageKey);
	if (m_mapImage.end() == iter)
		return nullptr;
	return iter->second;
}

void CTextureMgr::Release()
{
	for (auto& pair : m_mapImage)
	{
		SafeDelete(pair.second);
	}
	m_mapImage.clear();
	for (auto& vecImage : m_vecImage) {
		vecImage.clear();
		vecImage.shrink_to_fit();
	}
}

const TEXTURE_INFO * CTextureMgr::GetTexInfo(RZIMAGE::ID _eID, int _iKey, int _iIndex)
{
	return m_vecImage[_eID][_iKey]->GetTexInfo(_iIndex);
}

void CTextureMgr::SetImageVec(std::wstring _strImageKey, CTexture* _pTexture)
{
	int i = 0;
	RZIMAGE::ID eID = RZIMAGE::BASE;
	if ((i = _strImageKey.find(L"|", 0)) != std::wstring::npos)
		_strImageKey = _strImageKey.substr(0, i);
	if (!lstrcmp(_strImageKey.c_str(), L"Background")) {
		eID = RZIMAGE::BACKGROUND;
	}
	if (!lstrcmp(_strImageKey.c_str(), L"Map")) {
		eID = RZIMAGE::MAP;
	}
	if (!lstrcmp(_strImageKey.c_str(), L"Tile")) {
		eID = RZIMAGE::TILE;
	}
	if (!lstrcmp(_strImageKey.c_str(), L"Amazon")) {
		eID = RZIMAGE::AMAZONE;
	}
	if (!lstrcmp(_strImageKey.c_str(), L"Duriel")) {
		eID = RZIMAGE::DURIEL;
	}
	if (!lstrcmp(_strImageKey.c_str(), L"Bavarian")) {
		eID = RZIMAGE::BAVARIAN;
	}
	if (!lstrcmp(_strImageKey.c_str(), L"Andariel")) {
		eID = RZIMAGE::ANDARIEL;
	}
	if (!lstrcmp(_strImageKey.c_str(), L"Dia")) {
		eID = RZIMAGE::DIA;
	}
	if (!lstrcmp(_strImageKey.c_str(), L"Izual")) {
		eID = RZIMAGE::IZUAL;
	}
	if (!lstrcmp(_strImageKey.c_str(), L"Barlog")) {
		eID = RZIMAGE::BARLOG;
	}
	if (!lstrcmp(_strImageKey.c_str(), L"Cow")) {
		eID = RZIMAGE::COW;
	}
	if (!lstrcmp(_strImageKey.c_str(), L"Skill")) {
		eID = RZIMAGE::SKILL;
	}
	if (!lstrcmp(_strImageKey.c_str(), L"IceBolt")) {
		eID = RZIMAGE::ICEBOLT;
	}
	if (!lstrcmp(_strImageKey.c_str(), L"Laser")) {
		eID = RZIMAGE::LASER;
	}
	if (!lstrcmp(_strImageKey.c_str(), L"Bone")) {
		eID = RZIMAGE::BONE;
	}
	if (!lstrcmp(_strImageKey.c_str(), L"Stun")) {
		eID = RZIMAGE::STUN;
	}
	if (!lstrcmp(_strImageKey.c_str(), L"TraitBuff")) {
		eID = RZIMAGE::TRAITBUFF;
	}
	if (!lstrcmp(_strImageKey.c_str(), L"BaseButton")) {
		eID = RZIMAGE::BASEBUTTON;
	}
	if (!lstrcmp(_strImageKey.c_str(), L"BaseMouse")) {
		eID = RZIMAGE::BASEMOUSE;
	}
	m_vecImage[eID].emplace_back(_pTexture);
}
