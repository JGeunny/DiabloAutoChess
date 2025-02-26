#include "stdafx.h"
//#include "../../Client/stdafx.h"
#include "KeyMgr.h"

IMPLEMENT_SINGLETON(CKeyMgr)
CKeyMgr::CKeyMgr()
{
	ZeroMemory(m_dwKey, sizeof(m_dwKey));
	ZeroMemory(m_dwKeyDown, sizeof(m_dwKeyDown));
	ZeroMemory(m_dwKeyPressed, sizeof(m_dwKeyPressed));
}

CKeyMgr::~CKeyMgr()
{
}

int CKeyMgr::Update()
{
	for(auto& dwKey: m_dwKey)
		dwKey = 0;

	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		for (auto& dwKey : m_dwKey)
			dwKey |= KEY::UP;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		for (auto& dwKey : m_dwKey)
			dwKey |= KEY::DOWN;
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		for (auto& dwKey : m_dwKey)
			dwKey |= KEY::LEFT;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		for (auto& dwKey : m_dwKey)
			dwKey |= KEY::RIGHT;
	}
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		for (auto& dwKey : m_dwKey)
			dwKey |= KEY::RETURN;
	}
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		for (auto& dwKey : m_dwKey)
			dwKey |= KEY::SPACE;
	}
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		for (auto& dwKey : m_dwKey)
			dwKey |= KEY::LBUTTON;
	}
	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
	{
		for (auto& dwKey : m_dwKey)
			dwKey |= KEY::RBUTTON;
	}
	if (GetAsyncKeyState('Q') & 0x8000)
	{
		for (auto& dwKey : m_dwKey)
			dwKey |= KEY::Q;
	}
	if (GetAsyncKeyState(VK_TAB) & 0x8000)
	{
		for (auto& dwKey : m_dwKey)
			dwKey |= KEY::TAB;
	}
	if (GetAsyncKeyState('Y') & 0x8000)
	{
		for (auto& dwKey : m_dwKey)
			dwKey |= KEY::Y;
	}
	return 0;
}

bool CKeyMgr::KeyDown(DWORD dwKey, KeyChannel _eChannel)
{
	// 이 전에 누른적 없고 현재 눌렸으면 TRUE
	if (!(m_dwKeyDown[(int)_eChannel] & dwKey) && (m_dwKey[(int)_eChannel] & dwKey))
	{
		m_dwKeyDown[(int)_eChannel] |= dwKey;
		return true;
	}

	// 이전에 누른적 있고 현재 누르지 않았으면 FALSE
	if ((m_dwKeyDown[(int)_eChannel] & dwKey) && !(m_dwKey[(int)_eChannel] & dwKey))
	{
		m_dwKeyDown[(int)_eChannel] ^= dwKey;
		return false;
	}

	return false;
}

bool CKeyMgr::KeyUp(DWORD dwKey, KeyChannel _eChannel)
{
	// 이전에 누른적 있고 현재 누르지 않았다면 TRUE
	if ((m_dwKeyPressed[(int)_eChannel] & dwKey) && !(m_dwKey[(int)_eChannel] & dwKey))
	{
		m_dwKeyPressed[(int)_eChannel] ^= dwKey;
		return true;
	}

	// 이전에 누른적 없고 현재 눌렀다면 FALSE
	if (!(m_dwKeyPressed[(int)_eChannel] & dwKey) && (m_dwKey[(int)_eChannel] & dwKey))
	{
		m_dwKeyPressed[(int)_eChannel] |= dwKey;
		return false;
	}

	return false;
}

bool CKeyMgr::KeyPressing(DWORD dwKey, KeyChannel _eChannel)
{
	if (m_dwKey[(int)_eChannel] & dwKey)
		return true;

	return false;
}

//bool CKeyMgr::KeyCombined(DWORD dwFirst, DWORD dwSecond)
//{
//	if (KeyDown(dwSecond) && KeyPressing(dwFirst))
//		return true;
//
//	return false;
//}