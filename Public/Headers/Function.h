#pragma once

class CGameObject;
template<class T> DWORD SafeRelease(T& _pComponent)
{
	DWORD dwErr = _pComponent->Release();
	if (0 == dwErr)
	{
		_pComponent = nullptr;
	}
	return dwErr;
}
template<class T> void SafeDelete(T& _pObj)
{
	if (_pObj)
	{
		delete _pObj;
		_pObj = nullptr;
	}
}
template<class T> void SafeDelete_Array(T& _pObj)
{
	if (_pObj)
	{
		delete[] _pObj;
		_pObj = nullptr;
	}
}
template<class T> void SafeDelete_Array2(T& _ppObj, int _iRow)
{	
	if (_ppObj)
	{
		for (int i = 0; i < _iRow; ++i) {
			delete[] _ppObj[i];
			_ppObj[i] = nullptr;
		}
		delete[] _ppObj;
		_ppObj = nullptr;
	}
}

class FUNC{
public:
	class CHECK {
	public:
		static bool PosInRect(RECT _rtCrash, D3DXVECTOR3 _vPos)
		{
			return 0 != PtInRect(&_rtCrash, POINT() = { (LONG)_vPos.x, (LONG)_vPos.y});
		}
		template<class T>
		static bool CheckSphere(T * pDst, T * pSrc)
		{
			DRAW_INFO& tDst = pDst->GetDrawInfo();
			DRAW_INFO& tSrc = pSrc->GetDrawInfo();
			float fRadiusSum = ((tDst.GetSizeLand().x) * 0.4f) + ((tSrc.GetSizeLand().x) * 0.4f);

			float fDist = FUNC::MATH::Dist(tDst.vPos, tSrc.vPos);
			return fRadiusSum > fDist;
		}
	};
	class SORT {
	public:
		template<class T>
		static void ObjectVec(std::vector<T>& _vecObj, ENUM::OrderBy _eOrderBy = ENUM::OrderBy::ASC)
		{
			sort(_vecObj.begin(), _vecObj.end(), [&](auto& obj1, auto& obj2) {
				if (_eOrderBy == ENUM::OrderBy::ASC)
					return obj1->GetPos().y < obj2->GetPos().y;
				else
					return obj1->GetPos().y > obj2->GetPos().y;
			});
		}
		template<class T>
		static void ObjectList(std::list<T>& _lstObj, ENUM::OrderBy _eOrderBy = ENUM::OrderBy::ASC)
		{
			_lstObj.sort([&](auto& obj1, auto& obj2) {
				if (_eOrderBy == ENUM::OrderBy::ASC)
					return obj1->GetPos().y < obj2->GetPos().y;
				else
					return obj1->GetPos().y > obj2->GetPos().y;
			});
		}
		template<class T>
		static void RandomList(std::list<T>& _lstObj)
		{
			for (auto& pObj : _lstObj)
				pObj->GetPos().z = float(std::rand()*1000 % 7);
			_lstObj.sort([&](auto& obj1, auto& obj2) {
				return obj1->GetPos().z > obj2->GetPos().z;
			});
			for (auto& pObj : _lstObj)
				pObj->GetPos().z = 0.f;
		}
	};

	class CONVERT {
	public:
		static RZIMAGE::ID GetImageId(LPWSTR _pImageName)
		{
			RZIMAGE::ID eImageId = RZIMAGE::END;
			if (!lstrcmp(_pImageName, L"NONE"))
				eImageId = RZIMAGE::END;
			if (!lstrcmp(_pImageName, L"Amazon"))
				eImageId = RZIMAGE::AMAZONE;
			if (!lstrcmp(_pImageName, L"Duriel"))
				eImageId = RZIMAGE::DURIEL;
			if (!lstrcmp(_pImageName, L"Bavarian"))
				eImageId = RZIMAGE::BAVARIAN;
			if (!lstrcmp(_pImageName, L"Andariel"))
				eImageId = RZIMAGE::ANDARIEL;
			if (!lstrcmp(_pImageName, L"Dia"))
				eImageId = RZIMAGE::DIA;
			if (!lstrcmp(_pImageName, L"Izual"))
				eImageId = RZIMAGE::IZUAL;
			if (!lstrcmp(_pImageName, L"Barlog"))
				eImageId = RZIMAGE::BARLOG;
			return eImageId;
		}
		static LPWSTR GetImageName(RZIMAGE::ID _eImageId)
		{
			LPWSTR pImageName = L"NONE";
			switch (_eImageId)
			{
			case RZIMAGE::BASE:
				break;
			case RZIMAGE::BACKGROUND:
				break;
			case RZIMAGE::MAP:
				break;
			case RZIMAGE::TILE:
				break;
			case RZIMAGE::AMAZONE:
				pImageName = L"Amazon";
				break;
			case RZIMAGE::DURIEL:
				pImageName = L"Duriel";
				break;
			case RZIMAGE::BAVARIAN:
				pImageName = L"Bavarian";
				break;
			case RZIMAGE::ANDARIEL:
				pImageName = L"Andariel";
				break;
			case RZIMAGE::DIA:
				pImageName = L"Dia";
				break;
			case RZIMAGE::IZUAL:
				pImageName = L"Izual";
				break;
			case RZIMAGE::BARLOG:
				pImageName = L"Barlog";
				break;
			case RZIMAGE::SKILL:
				break;
			case RZIMAGE::BASEBUTTON:
				break;
			case RZIMAGE::END:
				break;
			default:
				break;
			}
			return pImageName;
		}
	};
	class STR {
	public:
		static int Replace(std::wstring& _strData, LPCWSTR _pszOld, LPCWSTR _pszNew) {
			int i = 0, iCount = 0, iSize = lstrlen(_pszOld);
			while((i = _strData.find(_pszOld, 0)) != std::wstring::npos){
				_strData.replace(i, iSize, _pszNew);
				++iCount;
			}
			return iCount;
		}
		static int Split(std::vector<std::wstring>& _vecData, std::wstring _strData, LPCWSTR _pszSep) {
			int i = 0, iCount = 0, iSize = lstrlen(_pszSep);
			_vecData.clear();
			while ((i = _strData.find(_pszSep, 0)) != std::wstring::npos) {
				_vecData.emplace_back(_strData.substr(0, i));
				_strData = _strData.substr(i + iSize, _strData.size());
				++iCount;
			}
			if (_vecData.size() > 0){
				_vecData.emplace_back(_strData);
				++iCount;
			}
			return iCount;
		}
	};
	class GET {
	public:
		template<class T>
		static void CombinationList(std::list<T>& _lstResultObjs, std::list<T>* _lstObjArray, int _iSize)
		{
			_lstResultObjs.clear();
			for (int i = 0; i < _iSize; ++i)
			{
				for (auto& pObj : _lstObjArray[i])
				{
					_lstResultObjs.emplace_back(pObj);
				}
			}
		};
		template<class T>
		static int UBound(T& _array)
		{
			return int(sizeof(_array) / sizeof(_array[0]));
		}
		static D3DXVECTOR3 D3DXVec3Multiply(D3DXVECTOR3& _vData1, D3DXVECTOR3& _vData2) {
			return D3DXVECTOR3(_vData1.x*_vData2.x, _vData1.y*_vData2.y, _vData1.z*_vData2.z);
		}
		static RECT Rect(D3DXVECTOR3& _vPos, D3DXVECTOR3& _vSize, float _fBorder = 0.f) {
			return RECT() = { LONG(_vPos.x - _vSize.x*0.5f + _fBorder)
				, LONG(_vPos.y - _vSize.y*0.5f + _fBorder)
				, LONG(_vPos.x + _vSize.x*0.5f - _fBorder)
				, LONG(_vPos.y + _vSize.y*0.5f - _fBorder) };
		}
		static RECT RectSprite(D3DXVECTOR3& _vPos, D3DXVECTOR3& _vSize, float _fBorder = 0.f) {
			return RECT() = { LONG(_vPos.x * _vSize.x + _fBorder)
				, LONG(_vPos.y * _vSize.y + _fBorder)
				, LONG((_vPos.x + 1) * _vSize.x - _fBorder)
				, LONG((_vPos.y + 1) * _vSize.y - _fBorder) };
		}
		static D3DXVECTOR3* Rhombus(D3DXVECTOR3 _vRhombus[4], D3DXVECTOR3& _vPos, D3DXVECTOR3& _vSize, float _fBorder = 0.f)
		{
			_vRhombus[0] = { _vPos.x, _vPos.y - _vSize.y*0.5f + _fBorder, 0.f }; //»ó
			_vRhombus[1] = { _vPos.x + _vSize.x*0.5f - _fBorder, _vPos.y, 0.f }; //¿ì
			_vRhombus[2] = { _vPos.x, _vPos.y + _vSize.y*0.5f - _fBorder, 0.f }; //ÇÏ 
			_vRhombus[3] = { _vPos.x - _vSize.x*0.5f + _fBorder, _vPos.y, 0.f }; //ÁÂ
			return _vRhombus;
		}
		static D3DXVECTOR3* Hexagon(D3DXVECTOR3 _vHexagon[6], D3DXVECTOR3& _vPos, D3DXVECTOR3& _vSize, float _fBorder = 0.f)
		{	
			_vHexagon[0] = { _vPos.x, _vPos.y + _vSize.y*(-0.5f) + _fBorder, 0.f }; //»ó
			_vHexagon[1] = { _vPos.x + _vSize.x*(0.5f) - _fBorder, _vPos.y + _vSize.y*(-0.25f) + _fBorder, 0.f }; //¿ì»ó
			_vHexagon[2] = { _vPos.x + _vSize.x*(0.5f) - _fBorder, _vPos.y + _vSize.y*(+0.25f) - _fBorder, 0.f }; //¿ìÇÏ

			_vHexagon[3] = { _vPos.x, _vPos.y + _vSize.y*(+0.5f) - _fBorder, 0.f }; //ÇÏ
			_vHexagon[4] = { _vPos.x + _vSize.x*(-0.5f) + _fBorder, _vPos.y + _vSize.y*(+0.25f) - _fBorder, 0.f }; //ÁÂÇÏ
			_vHexagon[5] = { _vPos.x + _vSize.x*(-0.5f) + _fBorder, _vPos.y + _vSize.y*(-0.25f) + _fBorder, 0.f }; //ÁÂ»ó
	
			/*_vHexagon[0] = { _vPos.x + _vSize.x*(-0.25f) + _fBorder, _vPos.y + _vSize.y*(-0.5f) + _fBorder, 0.f }; //ÁÂ»ó
			_vHexagon[1] = { _vPos.x + _vSize.x*(0.25f) - _fBorder, _vPos.y + _vSize.y*(-0.5f) + _fBorder, 0.f }; //¿ì»ó
			_vHexagon[2] = { _vPos.x + _vSize.x*(0.5f) - _fBorder, _vPos.y, 0.f }; //¿ì
			_vHexagon[3] = { _vPos.x + _vSize.x*(0.25f) - _fBorder, _vPos.y + _vSize.y*(0.5f) - _fBorder, 0.f }; //¿ìÇÏ 
			_vHexagon[4] = { _vPos.x + _vSize.x*(-0.25f) + _fBorder, _vPos.y + _vSize.y*(0.5f) - _fBorder, 0.f }; //ÁÂÇÏ
			_vHexagon[5] = { _vPos.x + _vSize.x*(-0.5f) + _fBorder, _vPos.y, 0.f }; //ÁÂ*/
			return _vHexagon;
		}
		static D3DXVECTOR3 Angle(D3DXVECTOR3& _vPosDst, D3DXVECTOR3& _vPosSrc, D3DXVECTOR3& _vLook) {
			return D3DXToDegree(Radian(_vPosDst, _vPosSrc, _vLook));
		}
		static D3DXVECTOR3 Radian(D3DXVECTOR3& _vPosDst, D3DXVECTOR3& _vPosSrc, D3DXVECTOR3& _vLook) {
			D3DXVECTOR3 vRadian = { 0.f, 0.f, 0.f };
			D3DXVECTOR3 vDir = D3DXVECTOR3(floor(_vPosDst.x), floor(_vPosDst.y), floor(_vPosDst.z)) 
				- D3DXVECTOR3(floor(_vPosSrc.x), floor(_vPosSrc.y), floor(_vPosSrc.z));
			D3DXVec3Normalize(&vDir, &vDir);
			vRadian.z = acosf(D3DXVec3Dot(&_vLook, &vDir));
			if (_vPosDst.y > _vPosSrc.y)
				vRadian.z = 2 * PI - vRadian.z;
			return vRadian;
		}
		static const D3DXVECTOR3 Dir(D3DXVECTOR3& _vAngle, D3DXVECTOR3 _vLook = {1.f, 0.f, 0.f}) {
			D3DXVECTOR3 vDir = { 0.f, 0.f, 0.f };
			D3DXVec3TransformNormal(&vDir, &_vLook, &MATRIX::MatrixRotation(_vAngle));
			return vDir;
		}
	};
	class MATH {
	public:
		static float Dist(D3DXVECTOR3& _vPosDst, D3DXVECTOR3& _vPosSrc)
		{
			return D3DXVec3Length(&(_vPosDst - _vPosSrc));
		}
		static float Roundf(float _fX, int _iDigit = 0)
		{
			return roundf(_fX* powf(float(10), (float)_iDigit)) / powf(float(10), (float)_iDigit);
		}
		static float RoundUpf(float _fX, int _iDigit = 0)
		{
			return ceilf(_fX* powf(float(10), (float)_iDigit)) / powf(float(10), (float)_iDigit);
		}
		static float RoundDownf(float _fX, int _iDigit = 0)
		{
			return floorf(_fX* powf(float(10), (float)_iDigit)) / powf(float(10), (float)_iDigit);
		}
	};
	class MATRIX {
	public:
		static D3DXMATRIX MatrixInit()
		{
			D3DXMATRIX matrix;
			D3DXMatrixIdentity(&matrix);
			return matrix;
		}
		static D3DXMATRIX MatrixScaling(D3DXVECTOR3& _vScale)
		{
			D3DXMATRIX& matrix = MatrixInit();
			D3DXMatrixScaling(&matrix, _vScale.x, _vScale.y, _vScale.z);
			return matrix;
		}
		static D3DXMATRIX MatrixRotation(D3DXVECTOR3& _vAngle)
		{
			D3DXMATRIX& matrix = MatrixInit();
			D3DXMatrixRotationZ(&matrix, D3DXToRadian(-_vAngle.z));
			return matrix;
		}
		static D3DXMATRIX MatrixTranslation(D3DXVECTOR3& _vPos)
		{
			D3DXMATRIX& matrix = MatrixInit();
			D3DXMatrixTranslation(&matrix, _vPos.x, _vPos.y, _vPos.z);
			return matrix;
		}
	};
};