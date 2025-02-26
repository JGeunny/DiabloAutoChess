#pragma once

//#include "RotatePos.h"

//Texture.h=====================================================================================
typedef struct tagTextureInfo
{
	LPDIRECT3DTEXTURE9	pTexture;	//�ҷ��� �ؽ�ó
	D3DXIMAGE_INFO		tImgInfo;	//�ҷ��� �̹��� ����
	int					iCountX;	//��������Ʈ �׸��� ���� ����
	int					iCountY;	//��������Ʈ �׸��� ���� ����
}TEXTURE_INFO;
//Texture.h//=====================================================================================

//CObj.h=======================================================================================
//�ִϸ��̼�
typedef struct tagFrame
{
	tagFrame()
		:iFrameKey(0)
		, iFrameStart(0)
		, iFrameEnd(0)
		, iFrameScene(0)
		, iFrameSceneEnd(0)
		, uFrameSpeed(0)
		, uFrameTime(0)
		, pListSceneOrder(nullptr)
	{}
	int		iFrameKey;		// �̹��� ����
	int		iFrameStart;	// �̹��� ������
	int		iFrameEnd;		// �̹��� ����
	int		iFrameScene;	// �̹��� �ൿ
	int		iFrameSceneEnd;	// �̹��� �ൿ
	UINT	uFrameSpeed;	// ��� �ӵ�
	UINT	uFrameTime;		// ��� �ð�

	std::vector<int>* pListSceneOrder; //���⿡ ���� �׸�(Scene) ����

public:
	void SetScene(float _fAngle) {
		_fAngle = (float)((int)_fAngle % 360);
		if (_fAngle < 0)
			_fAngle = 360.f - _fAngle;
		
		iFrameScene = int((iFrameSceneEnd + 2) * _fAngle / 360.f);

		if (pListSceneOrder)
		{	
			if (iFrameScene >= (int)pListSceneOrder->size() || iFrameScene < 0)
			{
				iFrameScene = 0;
			}
			iFrameScene = (*pListSceneOrder)[iFrameScene];			
		}
	}
}FRAME;


typedef struct tagDrawData
{
public:
	tagDrawData() :fSpeed(0.f)
	{
		vPos = { 0.f, 0.f, 0.f };
		vPosFit = { 0.f, 0.f, 0.f };
		vSize = { 0.f, 0.f, 0.f };
		vDir = { 0.f, 0.f, 0.f };
		vLook = { 1.f, 0.f, 0.f };
		vAngle = { 0.f, 0.f, 0.f };
		vScale = { 1.f, 1.f, 1.f };
		vScaleFit = { 1.f, 1.f, 1.f };
		D3DXMatrixIdentity(&matCurrent);
		color = INIT_COLOR;
		vSizeCollision = {-1.f, -1.f, -1.f};
		vSizeLand = { -1.f, -1.f, -1.f };
	}
	void SetData(tagDrawData& _tData) {
		*this = _tData;
	}
public:
	D3DXVECTOR3 vPos;	//��ġ����	// X, Y, Z �� ������ �ֵ�
	D3DXVECTOR3 vPosFit;		//vPosFit��ŭ ���� ��ġ���� �̹����� �׷��� 
	D3DXVECTOR3 vSize;	//ũ��
	D3DXVECTOR3 vLook;	//�ʱ� �ٶ� ���� ����
	D3DXVECTOR3 vDir;	//����(����)����(�� ��ǥ�� ũ�Ⱑ 1�� ����) ���⿡ �ӷ¸� �����ָ� �ӵ��� �ȴ� // Dir�ΰ��� ����(x*x+y*y+z*z)�ϸ� �ڽ��� ��Ÿ�� �ȴ�.
	D3DXVECTOR3 vAngle;
	D3DXVECTOR3 vScale;	//ũ�� ���� ����
	float		fSpeed;

public:
	D3DXVECTOR3 vSizeCollision;//�浹 ũ��
	D3DXVECTOR3 vSizeLand;//���� �������� �ִ� ũ��

protected:
	D3DXVECTOR3 vScaleFit;	//�̹��� ũ�⸦ ����� ������
	
public:
	D3DXMATRIX	matCurrent;	//SetTransform ���� ����Ҳ���
	D3DCOLOR	color;		//�׸� �׸��� ���� ���� �Ҳ���
}DRAW_DATA;

// ������Ʈ Ŭ������ ���� �׸� �׸��� ���� ����ü
typedef struct tagDrawInfo 
	: public tagDrawData
{
public:
	tagDrawInfo() :pTexInfo(nullptr)
	{
		ZeroMemory(vPolygon, sizeof(vPolygon));
	}
public:
	void SetData(tagDrawData& _tData) {
		tagDrawData::SetData(_tData);
	}

private:
	const TEXTURE_INFO*	pTexInfo;	// �׋��׶� �޾Ƽ� ����Ҳ��� Delete ����
	D3DXVECTOR3 vPolygon[6];		// �ٰ���

public:
	const LPDIRECT3DTEXTURE9 GetTexture()
	{
		return pTexInfo->pTexture;
	}
	const TEXTURE_INFO* GetTextureInfo()
	{
		return pTexInfo;
	}
	void SetTexInfo(const TEXTURE_INFO* _pTexInfo)
	{
		if (!_pTexInfo) return;
		pTexInfo = _pTexInfo;
		vScaleFit = { 1.f, 1.f, 1.f};
		//vScaleFit.x = vSize.x / (pTexInfo->tImgInfo.Width / pTexInfo->iCountX);
		//vScaleFit.y = vSize.y / (pTexInfo->tImgInfo.Height / pTexInfo->iCountY);
		vScaleFit.x = vSize.x * pTexInfo->iCountX / pTexInfo->tImgInfo.Width;
		vScaleFit.y = vSize.y * pTexInfo->iCountY / pTexInfo->tImgInfo.Height;
	}
	void SetAngle(D3DXVECTOR3 _vPos)
	{
		vAngle = FUNC::GET::Angle(_vPos, vPos, vLook);
	}
	float GetDist(D3DXVECTOR3 _vPos)
	{
		return FUNC::MATH::Dist(_vPos, vPos);
	}
	void FnMove(float _fDelTime = 0.f)
	{
		vPos += GetSpeed() * _fDelTime;
	}
public:
	D3DXVECTOR3 GetPos()
	{
		return vPos;
	}
	D3DXVECTOR3 GetSizeLand()
	{
		D3DXVECTOR3 vSizeTemp = vSize;
		if (vSizeLand.x != -1)
			vSizeTemp = vSizeLand;
		return vSizeTemp;
	}
	D3DXVECTOR3 GetSizeCollision()
	{
		D3DXVECTOR3 vSizeTemp = vSize;
		if (vSizeCollision.x != -1)
			vSizeTemp = vSizeCollision;
		return vSizeTemp;
	}
	D3DXVECTOR3 GetImagePos()
	{
		return vPos + FUNC::GET::D3DXVec3Multiply(vPosFit, vScale);
	}
	D3DXVECTOR3 GetCenter()
	{
		return D3DXVECTOR3((pTexInfo->tImgInfo.Width / pTexInfo->iCountX) *0.5f , (pTexInfo->tImgInfo.Height / pTexInfo->iCountY) *0.5f, 0.f *0.5f);
	}
	D3DXVECTOR3 GetSpeed()
	{
		return fSpeed * FUNC::GET::Dir(vAngle, vLook);
	}
	RECT GetRect(float _fBorder = 0.f, bool _bScale = true, ENUM::DrawRect _eType = ENUM::DrawRect::COLLISION)
	{
		D3DXVECTOR3 vCurPos = {};
		D3DXVECTOR3 vCurSize = {};
		switch (_eType)
		{
		case ENUM::DrawRect::IMAGE:
			vCurPos = vPos + FUNC::GET::D3DXVec3Multiply(vPosFit, vScale);
			vCurSize = vSize;
			break;
		case ENUM::DrawRect::COLLISION:
			vCurPos = vPos + FUNC::GET::D3DXVec3Multiply(vPosFit, vScale);
			vCurSize = (vSizeCollision.x == -1.f) ? vSize : vSizeCollision;
			break;
		case ENUM::DrawRect::LAND:
			vCurPos = vPos;
			vCurSize = (vSizeLand.x == -1.f) ? vSize : vSizeLand;
			break;
		}
		if (_bScale)
			return FUNC::GET::Rect(vCurPos, FUNC::GET::D3DXVec3Multiply(vCurSize, vScale), _fBorder);
		return FUNC::GET::Rect(vCurPos, vCurSize, _fBorder);
	}
	D3DXVECTOR3* GetRhombus(float _fBorder = 0.f, bool _bScale = true, ENUM::DrawRect _eType = ENUM::DrawRect::COLLISION)
	{
		D3DXVECTOR3 vCurPos = {};
		D3DXVECTOR3 vCurSize = {};
		switch (_eType)
		{
		case ENUM::DrawRect::IMAGE:
			vCurPos = vPos + FUNC::GET::D3DXVec3Multiply(vPosFit, vScale);
			vCurSize = vSize;
			break;
		case ENUM::DrawRect::COLLISION:
			vCurPos = vPos + FUNC::GET::D3DXVec3Multiply(vPosFit, vScale);
			vCurSize = (vSizeCollision.x == -1.f) ? vSize : vSizeCollision;
			break;
		case ENUM::DrawRect::LAND:
			vCurPos = vPos;
			vCurSize = (vSizeLand.x == -1.f) ? vSize : vSizeLand;
			break;
		}
		if (_bScale)
			return FUNC::GET::Rhombus(vPolygon, vCurPos, FUNC::GET::D3DXVec3Multiply(vCurSize, vScale), _fBorder);
		return FUNC::GET::Rhombus(vPolygon, vCurPos, vCurSize, _fBorder);
	}
	D3DXVECTOR3* GetHexagon(float _fBorder = 0.f, bool _bScale = true, ENUM::DrawRect _eType = ENUM::DrawRect::COLLISION)
	{
		D3DXVECTOR3 vCurPos = {};
		D3DXVECTOR3 vCurSize = {};
		switch (_eType)
		{
		case ENUM::DrawRect::IMAGE:
			vCurPos = vPos + FUNC::GET::D3DXVec3Multiply(vPosFit, vScale);
			vCurSize = vSize;
			break;
		case ENUM::DrawRect::COLLISION:
			vCurPos = vPos + FUNC::GET::D3DXVec3Multiply(vPosFit, vScale);
			vCurSize = (vSizeCollision.x == -1.f) ? vSize : vSizeCollision;
			break;
		case ENUM::DrawRect::LAND:
			vCurPos = vPos;
			vCurSize = (vSizeLand.x == -1.f) ? vSize : vSizeLand;
			break;
		}
		if (_bScale)
			return FUNC::GET::Hexagon(vPolygon, vCurPos, FUNC::GET::D3DXVec3Multiply(vCurSize, vScale), _fBorder);
		return FUNC::GET::Hexagon(vPolygon, vCurPos, vCurSize, _fBorder);
	}
	RECT GetRectSprite(int _iX, int _iY)
	{
		D3DXVECTOR3 vSpriteSize = {
			FUNC::MATH::RoundUpf(pTexInfo->tImgInfo.Width / float(pTexInfo->iCountX)),
			FUNC::MATH::RoundUpf(pTexInfo->tImgInfo.Height / float(pTexInfo->iCountY)),
			0.f};
		return FUNC::GET::RectSprite(D3DXVECTOR3((float)_iX, (float)_iY, 0.f), vSpriteSize);
	}
	RECT GetRectSprite(int _iX, int _iY, D3DXVECTOR3 _vSize)
	{
		return FUNC::GET::RectSprite(D3DXVECTOR3((float)_iX, (float)_iY, 0.f), _vSize);
	}

public:	//���̷�Ʈ ��� ��� ���
	D3DXMATRIX GetMatrixInit()
	{
		return FUNC::MATRIX::MatrixInit();
	}
	D3DXMATRIX GetMatrixScaling()
	{
		return FUNC::MATRIX::MatrixScaling(vScaleFit)* FUNC::MATRIX::MatrixScaling(vScale);
	}
	D3DXMATRIX GetMatrixRotation()
	{
		return FUNC::MATRIX::MatrixRotation(vAngle);
	}
	D3DXMATRIX GetMatrixTranslation()
	{
		return FUNC::MATRIX::MatrixTranslation(vPos + FUNC::GET::D3DXVec3Multiply(vPosFit, vScale));
	}
	D3DXMATRIX GetMatrixWorld(int _iCombineMatrix = MATRIX::ALL, D3DXMATRIX* _mtxParent = nullptr )
	{
		D3DXMATRIX matrix = GetMatrixInit();
		//�����̰���: ������, ����, �̵�, ����, �θ����
		if (_iCombineMatrix & MATRIX::SCALE)
			matrix *= GetMatrixScaling();
		if (_iCombineMatrix & MATRIX::ROTATE)
			matrix *= GetMatrixRotation();
		if (_iCombineMatrix & MATRIX::TRANS)
			matrix *= GetMatrixTranslation();
		if (_mtxParent)
		{
			if (_iCombineMatrix & MATRIX::REVOLVE)
				matrix *= FUNC::MATRIX::MatrixRotation(-vAngle);
			if (_iCombineMatrix & MATRIX::PARENT)
				matrix *= *_mtxParent;
		}
		return matrix;
	}

}DRAW_INFO;

// ���� Ŭ������ ���� ������ �̸�, ü��, �������� ���� ����ü
typedef struct tagStatusData
{
public:
	tagStatusData() {
		FnInitialize();
	}
	//szName�� ���� ���縦 �ϱ� ���� ���� ������ �����ε�
	tagStatusData& operator=(const tagStatusData& _tData)
	{
		iClassID = _tData.iClassID;
		FnSetName(_tData.szName);
		iAtt = _tData.iAtt;
		iMaxHp = _tData.iMaxHp;
		iHp = _tData.iHp;
		iMaxMp = _tData.iMaxMp;
		iMp = _tData.iMp;

		iMaxExp = _tData.iMaxExp;
		iExp = _tData.iExp;
		iLevel = _tData.iLevel;

		iGold = _tData.iGold;
		iCritical = _tData.iCritical;
		iLeaderShip = _tData.iLeaderShip;
		eTeam = _tData.eTeam;
		fRecogDist = _tData.fRecogDist;
		eJob = _tData.eJob;
		return *this;
	}
	void SetData(tagStatusData& _tData) {
		*this = _tData;
	}
	void FnInitialize()
	{
		iClassID = 0;
		ZeroMemory(szName, sizeof(szName));
		iAtt = 0;

		iMaxHp = 0;
		iHp = iMaxHp;
		iMaxMp = 0;
		iMp = iMaxMp;

		iMaxExp = 100;
		iExp = 0;
		iLevel = 0;

		iGold = 10;
		iCritical = 0;	//ũ��Ƽ�� �ִ밪 1000 �̸� ������ ũ��
		iLeaderShip = 0; //��ַ� ������ ������ ���� ���� �Ҽ�����
		eTeam = ENUM::Team::NONE;
		fRecogDist = 0.f;
		eJob = ENUM::Job::NONE;
	}
	void FnSetName(const LPCWSTR _pName)
	{
		swprintf_s(szName, L"%s", _pName);
	}
public:
	int			iClassID;
	TCHAR		szName[100];

	int			iAtt;
	int			iMaxHp;
	int			iHp;
	int			iMaxMp;
	int			iMp;

	int			iExp;
	int			iMaxExp;
	int			iLevel;

	int			iGold;

	int			iCritical;

	int			iLeaderShip;//��ַ�
	ENUM::Team	eTeam;		//��
	float		fRecogDist;	//��ȿ �Ÿ�

	ENUM::Job	eJob;		//����(������ ���� �ɷ� ��ȭ)
}STATUS_DATA;

typedef struct tagStatusInfo
	:public tagStatusData
{

public:
	tagStatusInfo() {
		//FnInitialize();
	}
	tagStatusInfo(const LPCWSTR _pName, int _iAtt = 100, int _iMaxHp = 100, int _iMaxMp = 0
		, int _iLevel = 1, int _iGold = 0) {
		FnInitialize();
		FnSetName(_pName);
		iAtt = _iAtt;
		iMaxHp = _iMaxHp;
		iMaxMp = _iMaxMp;
		iLevel = _iLevel;
		iGold = _iGold;
		FnRecovery();
	}
	//szName�� ���� ���縦 �ϱ� ���� ���� ������ �����ε�
	tagStatusInfo& operator=(const tagStatusInfo& _tData)
	{
		iClassID = _tData.iClassID;
		FnSetName(_tData.szName);
		iAtt = _tData.iAtt;
		iMaxHp = _tData.iMaxHp;
		iHp = _tData.iHp;
		iMaxMp = _tData.iMaxMp;
		iMp = _tData.iMp;

		iMaxExp = _tData.iMaxExp;
		iExp = _tData.iExp;
		iLevel = _tData.iLevel;

		iGold = _tData.iGold;
		iCritical = _tData.iCritical;
		iLeaderShip = _tData.iLeaderShip;
		eTeam = _tData.eTeam;
		fRecogDist = _tData.fRecogDist;
		eJob = _tData.eJob;
		return *this;
	}
	void SetData(tagStatusData& _tData) {
		tagStatusData::SetData(_tData);
	}
public:
	void FnRecoveryHp()
	{
		iHp = iMaxHp;
	}
	void FnRecoveryMp()
	{
		iMp = iMaxMp;
	}
	void FnRecovery()
	{
		FnRecoveryHp();
		FnRecoveryMp();
	}
	bool FnLevelUp()
	{
		if (iExp >= iMaxExp)
		{
			iExp -= iMaxExp;
			return true;
		}
		return false;
	}
	void FnGain(tagStatusInfo& _tUnit)
	{
		iHp += 20;
		iGold += _tUnit.iGold;
		iExp += _tUnit.iMaxExp;
		if (iHp > iMaxHp)
			iHp = iMaxHp;
	}

}STATUS_INFO;
//CObj.h//=======================================================================================

//CTile.h=======================================================================================
typedef struct tagTileInfo
{
	ENUM::Tile  eTileID;
	int			iImageID;
	DWORD	    color;
	int		    iIndex;
	int		    iParentIndex;
	tagTileInfo()
		:eTileID(ENUM::Tile::BLANK)
		, iImageID(-1)
		, color(D3DCOLOR_ARGB(255, 0, 0, 0))
		, iIndex(0)
		, iParentIndex(0)
	{
	}
}TILE_INFO;
//CTile.h//=======================================================================================

//ObjData=======================================================================================
typedef struct tagObjInfo		//Ŭ������ �������� �ʰ� ������ ���� �� ���
{
	DRAW_DATA	tDraw;
	STATUS_DATA tStatus;
	TCHAR       szFrameKey[MIN_STR];	
}OBJ_INFO;
//ObjData//=======================================================================================
//
////Crafting=======================================================================================
//typedef struct tagSourceInfo {
//	ENUM::Craft		eType;
//	TCHAR			szName[MIN_STR];
//	int				iCount;
//}SOURCE_INFO;
//
//typedef struct tagCraftInfo		//Ŭ������ �������� �ʰ� ������ ���� �� ���
//{
//	ENUM::Craft			eType;
//	TCHAR				szName[MIN_STR];
//	SOURCE_INFO			tSource[3];
//	int					iCount;
//	SOURCE_INFO			tResult;
//}CRAFT_INFO;
////Crafting//=======================================================================================
//
//
////Astar.h=======================================================================================
//struct POINTFLOAT3
//{
//	FLOAT x;
//	FLOAT y;
//	FLOAT z;
//
//public:
//	POINTFLOAT3() { x = 0, y = 0, z = 0; }
//	POINTFLOAT3(FLOAT _x, FLOAT _y, FLOAT _z)
//		:x(_x), y(_y), z(_z) {}
//
//	// assignment operators
//	POINTFLOAT3& operator += (CONST POINTFLOAT3& _pt) {
//		x += _pt.x, y += _pt.y, z += _pt.z;
//		return *this;
//	}
//	POINTFLOAT3& operator -= (CONST POINTFLOAT3& _pt) {
//		x -= _pt.x, y -= _pt.y, z -= _pt.z;
//		return *this;
//	}
//	POINTFLOAT3& operator *= (FLOAT _f) {
//		x *= _f, y *= _f, z *= _f;
//		return *this;
//	}
//	POINTFLOAT3& operator /= (FLOAT _f) {
//		x /= _f, y /= _f, z /= _f;
//		return *this;
//	}
//
//	// binary operators
//	POINTFLOAT3 operator + (CONST POINTFLOAT3& _pt) const {
//		POINTFLOAT3 ptThis = *this;
//		ptThis.x += _pt.x, ptThis.y += _pt.y, ptThis.z += _pt.z;
//		return ptThis;
//	}
//	POINTFLOAT3 operator - (CONST POINTFLOAT3& _pt) const {
//		POINTFLOAT3 ptThis = *this;
//		ptThis.x -= _pt.x, ptThis.y -= _pt.y, ptThis.z -= _pt.z;
//		return ptThis;
//	}
//	POINTFLOAT3 operator * (FLOAT _f) const {
//		POINTFLOAT3 ptThis = *this;
//		ptThis.x *= _f, ptThis.y *= _f, ptThis.z *= _f;
//		return ptThis;
//	}
//	POINTFLOAT3 operator / (FLOAT _f) const {
//		POINTFLOAT3 ptThis = *this;
//		ptThis.x /= _f, ptThis.y /= _f, ptThis.z /= _f;
//		return ptThis;
//	}
//
//	BOOL operator == (CONST POINTFLOAT3& _pt) const {
//		return (x == _pt.x) && (y == _pt.y) && (z == _pt.z);
//	}
//	BOOL operator != (CONST POINTFLOAT3& _pt) const {
//		return !((x == _pt.x) && (y == _pt.y) && (z == _pt.z));
//	}
//};
//
//typedef struct tagNode
//{
//	POINTFLOAT3 ptBegin;
//	POINTFLOAT3 ptEnd;
//	int iF, iG, iH;		// F = ���(G + H) , G = ���� �Ÿ�, H = ���� �Ÿ�
//	tagNode* pParent;
//	tagNode() :pParent(nullptr), ptBegin(0.f, 0.f, 0.f), ptEnd(0.f, 0.f, 0.f), iF(0), iG(0), iH(0) {}
//	tagNode(POINTFLOAT3 _ptStartPoint, POINTFLOAT3 _ptEndPoint, tagNode* _pParent)
//		:pParent(nullptr), ptBegin(0.f, 0.f, 0.f), ptEnd(0.f, 0.f, 0.f), iF(0), iG(0), iH(0)
//	{
//		float x = 0, y = 0;	// ��� ��ǥ ��(�θ� ��ǥ-�ڽ� ��ǥ)
//		if (nullptr == pParent)	// �θ� ���� ���
//			iG = 0;
//		else
//		{
//			POINTFLOAT3& ptPoint = ptBegin - pParent->ptBegin;// ��� ��ǥ ��(�θ� ��ǥ-�ڽ� ��ǥ)
//			if (0 == ptPoint.x || 0 == ptPoint.y)	// ������ ���
//				iG = pParent->iG + 10;
//			else if (0 != ptPoint.x && 0 != ptPoint.y)	// �밢 ���� ���
//				iG = pParent->iG + 14;
//			else // ����(�θ�� ��ǥ�� ���� ���)(0 == x && 0 == y)
//			{
//				iF = -100000;  iH = -100000; iG = -100000;
//			}
//		}
//		iH = int((abs(ptEnd.x - ptBegin.x) + abs(ptEnd.y - ptBegin.y)) * 10);
//		iF = iG + 10;
//	}
//}NODE;
//Astar.h//=======================================================================================