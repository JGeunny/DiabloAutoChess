#pragma once

//전체 화면
//#define WINCX					1600
//#define WINCY					900
#define WINCX					1280
#define WINCY					720
//#define WINCX					1152
//#define WINCY					864
//#define WINCX					1024
//#define WINCY					768

#define TILEX					18
#define TILEY					22
//#define TILEX					18
//#define TILEY					18

#define TILECX					96
#define TILECY					96

#define BUILDINGCX				180
#define BUILDINGCY				180

#define UNITCX					140
#define UNITCY					140

#define ITEMCX					50
#define ITEMCY					50

#define MIN_STR					64
#define MID_STR					128
#define MAX_STR					256

#define PI						3.1415926536f

// 플래그 연산
#define OPTION_NONE				0x0
#define OPTION_1				0x1
#define OPTION_2				0x2
#define OPTION_3				0x4
#define OPTION_4				0x8
#define OPTION_5				0x10

//방향 정의
#define DIR_NONE				OPTION_NONE
#define DIR_LEFT				OPTION_1
#define DIR_UP					OPTION_2
#define DIR_RIGHT				OPTION_3
#define DIR_DOWN				OPTION_4

//초기 속도
#define INIT_SPEED				300.f
#define INIT_SPEED_SLOW			200.f
#define INIT_SPEED_FAST			800.f
#define INIT_SPEED_FASTEST		1600.f

//초기 색깔
#define INIT_COLOR				D3DCOLOR_ARGB(255, 255, 255, 255)
#define INIT_COLOR_BLACK		D3DCOLOR_ARGB(255, 0, 0, 0)
#define INIT_COLOR_MAGENTA		D3DCOLOR_ARGB(255, 255, 0, 255)
#define INIT_COLOR_RED			D3DCOLOR_ARGB(255, 255, 0, 0)
#define INIT_COLOR_GREEN		D3DCOLOR_ARGB(255, 0, 255, 0)
#define INIT_COLOR_BLUE			D3DCOLOR_ARGB(255, 0, 0, 255)
#define INIT_COLOR_IVORY		D3DCOLOR_ARGB(255, 0xff, 0xf6, 0xd5)
#define INIT_COLOR_GREY			D3DCOLOR_ARGB(255, 170, 170, 170)
#define INIT_COLOR_YELLOW		D3DCOLOR_ARGB(255, 255, 255, 0)
#define INIT_COLOR_OPACITY		D3DCOLOR_ARGB(155, 255, 255, 255)

#define INIT_COLOR_PNG			0

//#define INIT_COLOR_SCREEN		INIT_COLOR_GREY
#define INIT_COLOR_SCREEN		INIT_COLOR_BLACK
#define INIT_COLOR_DEL			INIT_COLOR_MAGENTA
#define INIT_COLOR_SELECT		D3DCOLOR_ARGB(155, 100, 100, 255)
#define INIT_COLOR_IMPOSSIBLE	D3DCOLOR_ARGB(155, 255, 100, 100)

#define INIT_COLOR_TILE			INIT_COLOR_IVORY

//직업 버프 최대 치
#define TRAIT_KNIGHT_MAX				4
#define TRAIT_SCOUT_MAX					2
#define TRAIT_WIZARD_MAX				3
#define TRAIT_ASSASSIN_MAX				2

//클래스 아이디
#define CLASSID_TYPE_BULLET		1000
#define CLASSID_ARROW			CLASSID_TYPE_BULLET + 0
#define CLASSID_ICEBOLT			CLASSID_TYPE_BULLET + 1
#define CLASSID_LASER			CLASSID_TYPE_BULLET + 2

static D3DCOLOR INIT_COLOR_RECT_COLLITION = INIT_COLOR_RED;
static D3DCOLOR INIT_COLOR_RECT_IMAGE = INIT_COLOR_BLUE;
static D3DCOLOR INIT_COLOR_RECT_LAND = INIT_COLOR_GREEN;
static D3DCOLOR INIT_COLOR_RECT_RECOGDIST = INIT_COLOR;


#define NO_COPY(ClassName)				\
private:								\
	ClassName(const ClassName& obj);	\
	ClassName& operator=(const ClassName& obj);

#define DECLARE_SINGLETON(ClassName)	\
		NO_COPY(ClassName)				\
public:									\
	static ClassName* GetInstance();	\
	void DestroyInstance();				\
private:								\
	static ClassName* m_pInstance;

#define IMPLEMENT_SINGLETON(ClassName)			\
ClassName* ClassName::m_pInstance = nullptr;	\
ClassName* ClassName::GetInstance()				\
{												\
	if(nullptr == m_pInstance)					\
		m_pInstance = new ClassName;			\
	return m_pInstance;							\
}												\
void ClassName::DestroyInstance()				\
{												\
	if(m_pInstance)								\
	{											\
		delete m_pInstance;						\
		m_pInstance = nullptr;					\
	}											\
}

#ifdef CLIENT
	#define ERR_MSG(msg)	\
	MessageBox(g_hWnd, msg, L"Error", MB_OK)
#else
	#define ERR_MSG(msg)	\
	AfxMessageBox(msg)
#endif

#define NULL_CHECK(ptr) \
if(nullptr == (ptr))	\
	return;

#define NULL_CHECK_MSG(ptr, msg)	\
if(nullptr == (ptr))				\
{									\
	ERR_MSG(msg);					\
	return;							\
}

#define NULL_CHECK_RETURN(ptr, returnVal)	\
if(nullptr == (ptr))						\
	return returnVal;

#define NULL_CHECK_MSG_RETURN(ptr, msg, returnVal)	\
if(nullptr == (ptr))								\
{													\
	ERR_MSG(msg);									\
	return returnVal;								\
}

#define FAILED_CHECK(hr)\
if(FAILED(hr))			\
	return;

#define FAILED_CHECK_MSG(hr, msg)	\
if(FAILED(hr))						\
{									\
	ERR_MSG(msg);					\
	return;							\
}

#define FAILED_CHECK_RETURN(hr, returnVal)	\
if(FAILED(hr))								\
	return returnVal;

#define FAILED_CHECK_MSG_RETURN(hr, msg, returnVal)	\
if(FAILED(hr))										\
{													\
	ERR_MSG(msg);									\
	return returnVal;								\
}

#define FAILED_CHECK_MSG_CONTINUE(hr, msg, returnVal)\
if(FAILED(hr))										\
{													\
	ERR_MSG(msg);									\
	continue;										\
}

#define FAILED_CHECK_MSG_BREAK(hr, msg, returnVal)	\
if(FAILED(hr))										\
{													\
	ERR_MSG(msg);									\
	break;											\
}

#define DECLARE_CREATE_BASE(ClassName)				\
protected:											\
	explicit ClassName();							\
public:												\
	virtual ~ClassName();							\
public:												\
	static ClassName* Create();						

#define IMPLEMENT_CREATE_BASE(ClassName)			\
ClassName * ClassName::Create()						\
{													\
	ClassName* pInstance = new ClassName;			\
	if(FAILED(pInstance->Initialize())){			\
		SafeDelete(pInstance);						\
		return nullptr;								\
	}												\
	return pInstance;								\
}

#define DECLARE_CREATE(ClassName)					\
protected:											\
	explicit ClassName();							\
public:												\
	virtual ~ClassName();							\
public:												\
	static ClassName* Create();						\
	static ClassName* Create(float _fX,				\
		float _fY);									\
	static ClassName* Create(float _fX, 			\
		float _fY, float _fAngle);


#define IMPLEMENT_CREATE(ClassName)					\
ClassName * ClassName::Create()						\
{													\
	ClassName* pInstance = new ClassName;			\
	if(FAILED(pInstance->Initialize())){			\
		SafeDelete(pInstance);						\
		return nullptr;								\
	}												\
	return pInstance;								\
}													\
ClassName * ClassName::Create(						\
	float _fX, float _fY)							\
{													\
	ClassName* pInstance = ClassName::Create();		\
	if (!pInstance) 								\
		return nullptr;								\
	pInstance->SetPos(_fX, _fY);					\
	return pInstance;								\
}													\
ClassName * ClassName::Create(						\
	float _fX, float _fY, float _fAngle)			\
{													\
	ClassName* pInstance = 							\
		ClassName::Create(_fX, _fY);				\
	if (!pInstance)									\
		return nullptr;								\
	pInstance->SetAngle(_fAngle);					\
	return pInstance;								\
}

#define DECLARE_CREATE_COMPONENT(ClassName)			\
protected:											\
	explicit ClassName();							\
public:												\
	virtual ~ClassName();							\
public:												\
	static ClassName* Create();						\
	static ClassName* Create(float _fX,				\
		float _fY, float _fCX, float _fCY);			\
	static ClassName* Create(float _fX, 			\
		float _fY, float _fCX, float _fCY			\
		, LPCWSTR _pName);							\
	static ClassName* Create(float _fX,				\
		float _fY, float _fCX, float _fCY			\
		, LPCWSTR _pName, D3DCOLOR _dwColor);


#define IMPLEMENT_CREATE_COMPONENT(ClassName)		\
ClassName * ClassName::Create()						\
{													\
	ClassName* pInstance = new ClassName;			\
	if(FAILED(pInstance->Initialize())){			\
		SafeDelete(pInstance);						\
		return nullptr;								\
	}												\
	return pInstance;								\
}													\
ClassName * ClassName::Create(						\
	float _fX, float _fY, float _fCX, float _fCY)	\
{													\
	ClassName* pInstance = ClassName::Create();		\
	if (!pInstance) 								\
		return nullptr;								\
	pInstance->SetPos(_fX, _fY);					\
	pInstance->SetSize(_fCX, _fCY);					\
	return pInstance;								\
}													\
ClassName * ClassName::Create(						\
	float _fX, float _fY, float _fCX, float _fCY	\
	, LPCWSTR _pName)								\
{													\
	ClassName* pInstance = 							\
		ClassName::Create(_fX, _fY, _fCX, _fCY);	\
	if (!pInstance)									\
		return nullptr;								\
	pInstance->SetName(_pName);						\
	return pInstance;								\
}													\
ClassName * ClassName::Create(						\
	float _fX, float _fY, float _fCX, float _fCY	\
	, LPCWSTR _pName, D3DCOLOR _dwColor)			\
{													\
	ClassName* pInstance =							\
	ClassName::Create(_fX, _fY, _fCX, _fCY			\
					, _pName);						\
	if (!pInstance)									\
		return nullptr;								\
	pInstance->SetColor(_dwColor);					\
	return pInstance;								\
}


