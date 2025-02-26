#pragma once

namespace KEY {
	const DWORD UP = 0x00000001;	// 0000 0000 0000 0000 0000 0000 0000 0001
	const DWORD DOWN = 0x00000002;	// 0000 0000 0000 0000 0000 0000 0000 0010
	const DWORD LEFT = 0x00000004;	// 0000 0000 0000 0000 0000 0000 0000 0100
	const DWORD RIGHT = 0x00000008;	// 0000 0000 0000 0000 0000 0000 0000 1000
	const DWORD RETURN = 0x00000010;	// 0000 0000 0000 0000 0000 0000 0001 0000
	const DWORD SPACE = 0x00000020;	// 0000 0000 0000 0000 0000 0000 0010 0000
	const DWORD LBUTTON = 0x00000040;	// 0000 0000 0000 0000 0000 0000 0100 0000
	const DWORD RBUTTON = 0x00000080;	// 0000 0000 0000 0000 0000 0000 1000 0000
	const DWORD Q = 0x00000100;
	const DWORD TAB = 0x00000200;
	const DWORD Y = 0x00000400;
}
enum class KeyChannel {BASE, UI, UI2, END};
class CKeyMgr
{
	DECLARE_SINGLETON(CKeyMgr)

private:
	explicit CKeyMgr();
	virtual ~CKeyMgr();

public:
	int Update();
	bool KeyDown(DWORD dwKey, KeyChannel _eChannel = KeyChannel::BASE);
	bool KeyUp(DWORD dwKey, KeyChannel _eChannel = KeyChannel::BASE);
	bool KeyPressing(DWORD dwKey, KeyChannel _eChannel = KeyChannel::BASE);
	//bool KeyCombined(DWORD dwFirst, DWORD dwSecond);

private:
	DWORD m_dwKey[(int)KeyChannel::END];
	DWORD m_dwKeyDown[(int)KeyChannel::END];
	DWORD m_dwKeyPressed[(int)KeyChannel::END];
};

