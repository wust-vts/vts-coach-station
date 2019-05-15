// YimaEnc.h : 由 Microsoft Visual C++ 创建的 ActiveX 控件包装类的声明

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CYimaEnc

class CYimaEnc : public CWnd
{
protected:
	DECLARE_DYNCREATE(CYimaEnc)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x18468C02, 0xCE97, 0x4311, { 0xB4, 0xED, 0x97, 0x76, 0xC8, 0xAA, 0x5F, 0xA1 } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle,
						const RECT& rect, CWnd* pParentWnd, UINT nID, 
						CCreateContext* pContext = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); 
	}

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, 
				UINT nID, CFile* pPersist = NULL, BOOL bStorage = FALSE,
				BSTR bstrLicKey = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); 
	}

// 属性
public:

// 操作
public:

	BOOL GetLibMapInfo(long iLibMapPos, BSTR * retStrMapType, BSTR * retStrMapName, float * retOriginalScale, long * retLeftMost, long * retRightMost, long * retUpMost, long * retDownMost, long * retEditionNum, long * retUpdateNum, long * retAgencyNum, long * retHdat, long * retVdat, long * retSdat, BSTR * retStrMapFileName)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_PBSTR VTS_PBSTR VTS_PR4 VTS_PI4 VTS_PI4 VTS_PI4 VTS_PI4 VTS_PI4 VTS_PI4 VTS_PI4 VTS_PI4 VTS_PI4 VTS_PI4 VTS_PBSTR ;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, iLibMapPos, retStrMapType, retStrMapName, retOriginalScale, retLeftMost, retRightMost, retUpMost, retDownMost, retEditionNum, retUpdateNum, retAgencyNum, retHdat, retVdat, retSdat, retStrMapFileName);
		return result;
	}
	void GetScrnPoFromGeoPo(long geoPoX, long geoPoY, long * retScrnPoX, long * retScrnPoY)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_PI4 VTS_PI4 ;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, parms, geoPoX, geoPoY, retScrnPoX, retScrnPoY);
	}
	void GetGeoPoFromScrnPo(long scrnPoX, long scrnPoY, long * retGeoPoX, long * retGeoPoY)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_PI4 VTS_PI4 ;
		InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, parms, scrnPoX, scrnPoY, retGeoPoX, retGeoPoY);
	}
	void SetUseSmpSymbolOrNot(BOOL bUseOrNot)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bUseOrNot);
	}
	BOOL GetUsePlainBndryOrNot()
	{
		BOOL result;
		InvokeHelper(0x5, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	BOOL GetUseSmpSymbolOrNot()
	{
		BOOL result;
		InvokeHelper(0x6, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	long AddMapToLib(LPCTSTR pStrMapPath)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x7, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pStrMapPath);
		return result;
	}
	BOOL DrawMapsInScreen(long hdc)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x8, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, hdc);
		return result;
	}
	void CenterMap(long centerPoGeoCoorX, long centerPoGeoCoorY)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, NULL, parms, centerPoGeoCoorX, centerPoGeoCoorY);
	}
	void SetCurrentScale(float scale)
	{
		static BYTE parms[] = VTS_R4 ;
		InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, parms, scale);
	}
	void SetMapOffset(long scrnOffsetX, long scrnOffsetY)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, parms, scrnOffsetX, scrnOffsetY);
	}
	void SetMapMoreOffset(long scrnMoreOffsetX, long scrnMoreOffsetY)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0xc, DISPATCH_METHOD, VT_EMPTY, NULL, parms, scrnMoreOffsetX, scrnMoreOffsetY);
	}
	BOOL UnloadMapFromMemory(short memMapPos)
	{
		BOOL result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0xd, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, memMapPos);
		return result;
	}
	void SetDisplayCategory(short dspCtgry)
	{
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0xe, DISPATCH_METHOD, VT_EMPTY, NULL, parms, dspCtgry);
	}
	BOOL Init(LPCTSTR pStrWorkDirectory)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xf, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, pStrWorkDirectory);
		return result;
	}
	float GetSafetyDepth()
	{
		float result;
		InvokeHelper(0x10, DISPATCH_METHOD, VT_R4, (void*)&result, NULL);
		return result;
	}
	void SetSafetyDepth(float depth)
	{
		static BYTE parms[] = VTS_R4 ;
		InvokeHelper(0x11, DISPATCH_METHOD, VT_EMPTY, NULL, parms, depth);
	}
	float GetCurrentScale()
	{
		float result;
		InvokeHelper(0x12, DISPATCH_METHOD, VT_R4, (void*)&result, NULL);
		return result;
	}
	BOOL GetLanguage()
	{
		BOOL result;
		InvokeHelper(0x13, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void SetLanguage(BOOL bEnglishOrNational)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x14, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bEnglishOrNational);
	}
	short GetDisplayCategory()
	{
		short result;
		InvokeHelper(0x15, DISPATCH_METHOD, VT_I2, (void*)&result, NULL);
		return result;
	}
	void SetColorModel(short colorGroupNum)
	{
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x16, DISPATCH_METHOD, VT_EMPTY, NULL, parms, colorGroupNum);
	}
	short GetColorModel()
	{
		short result;
		InvokeHelper(0x17, DISPATCH_METHOD, VT_I2, (void*)&result, NULL);
		return result;
	}
	void DeleteLibMap(long libMapPos)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x18, DISPATCH_METHOD, VT_EMPTY, NULL, parms, libMapPos);
	}
	BOOL IsMapInCurrentScrn(long libMapPos)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x19, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, libMapPos);
		return result;
	}
	BOOL LoadMapToMemory(long libMapPos)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1a, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, libMapPos);
		return result;
	}
	BOOL MoveMapPos(long oldMemMapPos, long newMemMapPos)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x1b, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, oldMemMapPos, newMemMapPos);
		return result;
	}
	BOOL InterChangeTwoMapPos(long firstMemMapPos, long secondMemMapPos)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x1c, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, firstMemMapPos, secondMemMapPos);
		return result;
	}
	float GetGeoLenFromScrnLen(long scrnLen)
	{
		float result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1d, DISPATCH_METHOD, VT_R4, (void*)&result, parms, scrnLen);
		return result;
	}
	float GetScrnLenFromGeoLen(float geoLenByMm)
	{
		float result;
		static BYTE parms[] = VTS_R4 ;
		InvokeHelper(0x1e, DISPATCH_METHOD, VT_R4, (void*)&result, parms, geoLenByMm);
		return result;
	}
	long GetLibMapCount()
	{
		long result;
		InvokeHelper(0x1f, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long GetMemMapCount()
	{
		long result;
		InvokeHelper(0x20, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long GetGeoCoorMultiFactor()
	{
		long result;
		InvokeHelper(0x21, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long GetDrawerHWnd()
	{
		long result;
		InvokeHelper(0x22, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long GetDrawerHDC()
	{
		long result;
		InvokeHelper(0x23, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long GetDrawerScreenWidth()
	{
		long result;
		InvokeHelper(0x24, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long GetDrawerScreenHeight()
	{
		long result;
		InvokeHelper(0x25, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	BOOL SaveScrnToBmpFile(long saveBmpScrnLeft, long saveBmpScrnTop, long saveBmpScrnWidth, long saveBmpScrnHeight, LPCTSTR pStrFileName)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_BSTR ;
		InvokeHelper(0x26, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, saveBmpScrnLeft, saveBmpScrnTop, saveBmpScrnWidth, saveBmpScrnHeight, pStrFileName);
		return result;
	}
	long GetLayerCount(long mapPos)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x27, DISPATCH_METHOD, VT_I4, (void*)&result, parms, mapPos);
		return result;
	}
	BOOL GetLayerInfo(long mapPos, long layerPos, BSTR * retLayerName, BSTR * retLayerNameToken, long * retAttrCount)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_PBSTR VTS_PBSTR VTS_PI4 ;
		InvokeHelper(0x28, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, mapPos, layerPos, retLayerName, retLayerNameToken, retAttrCount);
		return result;
	}
	long GetLayerPosByToken(long mapPos, LPCTSTR strLayerToken)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_BSTR ;
		InvokeHelper(0x29, DISPATCH_METHOD, VT_I4, (void*)&result, parms, mapPos, strLayerToken);
		return result;
	}
	BOOL GetLayerObjectAttrInfo(long mapPos, long layerPos, long attrPos, long * retDataTypeID, BSTR * retAttrName, BSTR * retAttrToken)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_PI4 VTS_PBSTR VTS_PBSTR ;
		InvokeHelper(0x2a, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, mapPos, layerPos, attrPos, retDataTypeID, retAttrName, retAttrToken);
		return result;
	}
	BOOL GetObjectAttrValueInt(BSTR * pObjectPos, long attrPos, long * retIntVal, BOOL * retIfFieldValFilled)
	{
		BOOL result;
		static BYTE parms[] = VTS_PBSTR VTS_I4 VTS_PI4 VTS_PBOOL ;
		InvokeHelper(0x2b, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, pObjectPos, attrPos, retIntVal, retIfFieldValFilled);
		return result;
	}
	BOOL GetObjectAttrString(BSTR * pObjectPos, long attrPos, BSTR * retAttrString)
	{
		BOOL result;
		static BYTE parms[] = VTS_PBSTR VTS_I4 VTS_PBSTR ;
		InvokeHelper(0x2c, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, pObjectPos, attrPos, retAttrString);
		return result;
	}
	long GetLayerObjectCountOfMap(long memMapPos, long layerPos)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x2d, DISPATCH_METHOD, VT_I4, (void*)&result, parms, memMapPos, layerPos);
		return result;
	}
	long SelectObjectsByScrnPoint(BSTR * retSelectedObjectPositions, long scrnPoX, long scrnPoY)
	{
		long result;
		static BYTE parms[] = VTS_PBSTR VTS_I4 VTS_I4 ;
		InvokeHelper(0x2e, DISPATCH_METHOD, VT_I4, (void*)&result, parms, retSelectedObjectPositions, scrnPoX, scrnPoY);
		return result;
	}
	BOOL HighLightSelectedObject(BSTR * pStrObjPos, long pointColor, long lineColor, long lineWidth, long areaColor, long transparency, BOOL ifCenterTheObject, BOOL bEditing, long iEditingLinePoint)
	{
		BOOL result;
		static BYTE parms[] = VTS_PBSTR VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_BOOL VTS_BOOL VTS_I4 ;
		InvokeHelper(0x2f, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, pStrObjPos, pointColor, lineColor, lineWidth, areaColor, transparency, ifCenterTheObject, bEditing, iEditingLinePoint);
		return result;
	}
	BOOL RefreshDrawer(long hwnd, long scrnWidth, long scrnHeight, long scrnOrgOffsetPoX, long scrnOrgOffsetPoY)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x30, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, hwnd, scrnWidth, scrnHeight, scrnOrgOffsetPoX, scrnOrgOffsetPoY);
		return result;
	}
	long GetMemMapPosInLib(long memMapPos)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x31, DISPATCH_METHOD, VT_I4, (void*)&result, parms, memMapPos);
		return result;
	}
	long GetObjectGeoType(BSTR * pObjectPos)
	{
		long result;
		static BYTE parms[] = VTS_PBSTR ;
		InvokeHelper(0x32, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pObjectPos);
		return result;
	}
	void SetUsePlainBndryOrNot(BOOL bUseOrNot)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x33, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bUseOrNot);
	}
	BOOL OverViewLibMap(long libMapPos)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x34, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, libMapPos);
		return result;
	}
	BOOL FocusLibMap(long libMapPos)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x35, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, libMapPos);
		return result;
	}
	void DrawDragingMap(long destHDc, long curDragMousePoX, long curDragMousePoY, long dragStartPoX, long dragStartPoY)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x36, DISPATCH_METHOD, VT_EMPTY, NULL, parms, destHDc, curDragMousePoX, curDragMousePoY, dragStartPoX, dragStartPoY);
	}
	void SetLayerDrawOrNot(long mapPos, long layerPos, BOOL bDrawOrNot)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_BOOL ;
		InvokeHelper(0x37, DISPATCH_METHOD, VT_EMPTY, NULL, parms, mapPos, layerPos, bDrawOrNot);
	}
	BOOL GetLayerDrawOrNot(long mapPos, long layerPos)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x38, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, mapPos, layerPos);
		return result;
	}
	void SetAllLayerDrawOrNot(long mapPos, BOOL bDrawOrNot)
	{
		static BYTE parms[] = VTS_I4 VTS_BOOL ;
		InvokeHelper(0x39, DISPATCH_METHOD, VT_EMPTY, NULL, parms, mapPos, bDrawOrNot);
	}
	void RotateMapByScrnCenter(float fRotateAngleByDegree)
	{
		static BYTE parms[] = VTS_R4 ;
		InvokeHelper(0x3a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, fRotateAngleByDegree);
	}
	float GetMapRoatedAngle()
	{
		float result;
		InvokeHelper(0x3b, DISPATCH_METHOD, VT_R4, (void*)&result, NULL);
		return result;
	}
	BOOL GetPointObjectCoor(BSTR * pObjectPos, long * pPointCoorX, long * pPointCoorY)
	{
		BOOL result;
		static BYTE parms[] = VTS_PBSTR VTS_PI4 VTS_PI4 ;
		InvokeHelper(0x3c, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, pObjectPos, pPointCoorX, pPointCoorY);
		return result;
	}
	long GetLineObjectCoorCount(BSTR * pObjectPos)
	{
		long result;
		static BYTE parms[] = VTS_PBSTR ;
		InvokeHelper(0x3d, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pObjectPos);
		return result;
	}
	long GetLineObjectCoors(BSTR * pObjectPos, BSTR * retGeoPoints)
	{
		long result;
		static BYTE parms[] = VTS_PBSTR VTS_PBSTR ;
		InvokeHelper(0x3e, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pObjectPos, retGeoPoints);
		return result;
	}
	long GetFaceOutBndryCoorCount(BSTR * pObjectPos)
	{
		long result;
		static BYTE parms[] = VTS_PBSTR ;
		InvokeHelper(0x3f, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pObjectPos);
		return result;
	}
	long GetFaceOutBndryCoors(BSTR * pObjectPos, BSTR * retGeoPoints)
	{
		long result;
		static BYTE parms[] = VTS_PBSTR VTS_PBSTR ;
		InvokeHelper(0x40, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pObjectPos, retGeoPoints);
		return result;
	}
	long GetFaceInnerBndryCount(BSTR * pObjectPos)
	{
		long result;
		static BYTE parms[] = VTS_PBSTR ;
		InvokeHelper(0x41, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pObjectPos);
		return result;
	}
	long GetFaceInnerBndryCoorCount(BSTR * pObjectPos, long innerBoundryPos)
	{
		long result;
		static BYTE parms[] = VTS_PBSTR VTS_I4 ;
		InvokeHelper(0x42, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pObjectPos, innerBoundryPos);
		return result;
	}
	long GetFaceInnerBndryCoors(BSTR * pObjectPos, long innerBndryPos, BSTR * retGeoPoints)
	{
		long result;
		static BYTE parms[] = VTS_PBSTR VTS_I4 VTS_PBSTR ;
		InvokeHelper(0x43, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pObjectPos, innerBndryPos, retGeoPoints);
		return result;
	}
	void SetOwnShipBasicInfo(float shipLength, float shipBreath, LPCTSTR strShipName, LPCTSTR strMmsi)
	{
		static BYTE parms[] = VTS_R4 VTS_R4 VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x44, DISPATCH_METHOD, VT_EMPTY, NULL, parms, shipLength, shipBreath, strShipName, strMmsi);
	}
	void GetOwnShipBasicInfo(float * retShipLength, float * retShipBreath, BSTR * retStrShipName, BSTR * retStrMmsi)
	{
		static BYTE parms[] = VTS_PR4 VTS_PR4 VTS_PBSTR VTS_PBSTR ;
		InvokeHelper(0x45, DISPATCH_METHOD, VT_EMPTY, NULL, parms, retShipLength, retShipBreath, retStrShipName, retStrMmsi);
	}
	void SetOwnShipCurrentInfo(long currentGeoPoX, long currentGeoPoY, float heading, float courseOverGround, float courseThrghWater, float speedOverGround, float speedThrghWater)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_R4 VTS_R4 VTS_R4 VTS_R4 VTS_R4 ;
		InvokeHelper(0x46, DISPATCH_METHOD, VT_EMPTY, NULL, parms, currentGeoPoX, currentGeoPoY, heading, courseOverGround, courseThrghWater, speedOverGround, speedThrghWater);
	}
	void GetOwnShipCurrentInfo(long * pCurrentGeoPoX, long * pCurrentGeoPoY, float * pHeading, float * pCourseOverGround, float * pCourseThrghWater, float * pSpeedOverGround, float * pSpeedThrghWater)
	{
		static BYTE parms[] = VTS_PI4 VTS_PI4 VTS_PR4 VTS_PR4 VTS_PR4 VTS_PR4 VTS_PR4 ;
		InvokeHelper(0x47, DISPATCH_METHOD, VT_EMPTY, NULL, parms, pCurrentGeoPoX, pCurrentGeoPoY, pHeading, pCourseOverGround, pCourseThrghWater, pSpeedOverGround, pSpeedThrghWater);
	}
	long GetOtherVesselCount()
	{
		long result;
		InvokeHelper(0x48, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long AddOtherVessel(BOOL bArpaOrAisTarget, long currentGeoPoX, long currentGeoPoY, float heading, float courseOverGround, float courseThrghWater, float speedOverGround, float speedThrghWater)
	{
		long result;
		static BYTE parms[] = VTS_BOOL VTS_I4 VTS_I4 VTS_R4 VTS_R4 VTS_R4 VTS_R4 VTS_R4 ;
		InvokeHelper(0x49, DISPATCH_METHOD, VT_I4, (void*)&result, parms, bArpaOrAisTarget, currentGeoPoX, currentGeoPoY, heading, courseOverGround, courseThrghWater, speedOverGround, speedThrghWater);
		return result;
	}
	BOOL SetOtherVesselBasicInfo(long otherVesselPos, float shipLength, float shipBreath, LPCTSTR strShipName, long mmsi, BSTR * pExtAttrs, long extAttrLen)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_R4 VTS_R4 VTS_BSTR VTS_I4 VTS_PBSTR VTS_I4 ;
		InvokeHelper(0x4a, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, otherVesselPos, shipLength, shipBreath, strShipName, mmsi, pExtAttrs, extAttrLen);
		return result;
	}
	BOOL GetOtherVesselBasicInfo(long otherVesselPos, float * retShipLength, float * retShipBreath, BSTR * retStrShipName, long * retMmsi, BSTR * pExtAttrs)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_PR4 VTS_PR4 VTS_PBSTR VTS_PI4 VTS_PBSTR ;
		InvokeHelper(0x4b, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, otherVesselPos, retShipLength, retShipBreath, retStrShipName, retMmsi, pExtAttrs);
		return result;
	}
	void SetDrawShipOptions(BOOL bSetOwnshipOrOtherVessel, BOOL bShowCourseAndSpeedVector, BOOL bShowTimeMarksOnVector, BOOL bShowHeadingLine, long vectorLenTimePeriod, BOOL bVectorStableToGroundOrWater, long vectorTimeMarkIntvl, long memStoreTrackPointsLength, long showTrackPointsLength, long memTrackTimeLenByMin)
	{
		static BYTE parms[] = VTS_BOOL VTS_BOOL VTS_BOOL VTS_BOOL VTS_I4 VTS_BOOL VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x4c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bSetOwnshipOrOtherVessel, bShowCourseAndSpeedVector, bShowTimeMarksOnVector, bShowHeadingLine, vectorLenTimePeriod, bVectorStableToGroundOrWater, vectorTimeMarkIntvl, memStoreTrackPointsLength, showTrackPointsLength, memTrackTimeLenByMin);
	}
	void SetDrawOwnShipSpecialOptions(BOOL bDrawOwnShipSymbolOrOutline, BOOL bShowBeamBearingLine, long bSetColor, long newColor)
	{
		static BYTE parms[] = VTS_BOOL VTS_BOOL VTS_I4 VTS_I4 ;
		InvokeHelper(0x4d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bDrawOwnShipSymbolOrOutline, bShowBeamBearingLine, bSetColor, newColor);
	}
	BOOL SetShipTrackShowOrNot(BOOL bSetOwnshipOrOtherVessel, BOOL bSetAllOtherVessel, long otherVesselID, BOOL bShowOrNot)
	{
		BOOL result;
		static BYTE parms[] = VTS_BOOL VTS_BOOL VTS_I4 VTS_BOOL ;
		InvokeHelper(0x4e, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, bSetOwnshipOrOtherVessel, bSetAllOtherVessel, otherVesselID, bShowOrNot);
		return result;
	}
	BOOL ClearShipMemTrackPoints(BOOL bSetOwnshipOrOtherVessel, BOOL bSetAllOtherVessel, long otherVesselID)
	{
		BOOL result;
		static BYTE parms[] = VTS_BOOL VTS_BOOL VTS_I4 ;
		InvokeHelper(0x4f, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, bSetOwnshipOrOtherVessel, bSetAllOtherVessel, otherVesselID);
		return result;
	}
	void ClearOtherVessels()
	{
		InvokeHelper(0x50, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	double GetDistBetwTwoPoint(long startPoGeoX, long startPoGeoY, long endPoGeoX, long endPoGeoY)
	{
		double result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x51, DISPATCH_METHOD, VT_R8, (void*)&result, parms, startPoGeoX, startPoGeoY, endPoGeoX, endPoGeoY);
		return result;
	}
	double GetBearingBetwTwoPoint(long startGeoPoX, long startGeoPoY, long endGeoPoX, long endGeoPoY)
	{
		double result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x52, DISPATCH_METHOD, VT_R8, (void*)&result, parms, startGeoPoX, startGeoPoY, endGeoPoX, endGeoPoY);
		return result;
	}
	void GetDesPointOfCrsAndDist(long startGeoPoX, long startGeoPoY, double distance, double course, long * retDesGeoPoX, long * retDesGeoPoY)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_R8 VTS_R8 VTS_PI4 VTS_PI4 ;
		InvokeHelper(0x53, DISPATCH_METHOD, VT_EMPTY, NULL, parms, startGeoPoX, startGeoPoY, distance, course, retDesGeoPoX, retDesGeoPoY);
	}
	BOOL tmOpenMapDataFile(LPCTSTR strFilePathName)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x54, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, strFilePathName);
		return result;
	}
	BOOL tmSaveToMapDataFile(LPCTSTR strFilePathName)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x55, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, strFilePathName);
		return result;
	}
	long tmGetLayerCount()
	{
		long result;
		InvokeHelper(0x56, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	BOOL tmGetLayerName(long layerPos, BSTR * retLayerName)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_PBSTR ;
		InvokeHelper(0x57, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, layerPos, retLayerName);
		return result;
	}
	short tmGetLayerGeoType(long layerPos)
	{
		short result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x58, DISPATCH_METHOD, VT_I2, (void*)&result, parms, layerPos);
		return result;
	}
	long tmGetLayerObjectCount(long layerPos)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x59, DISPATCH_METHOD, VT_I4, (void*)&result, parms, layerPos);
		return result;
	}
	BOOL tmAppendObjectInLayer(long layerPos, long objGeoType)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x5a, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, layerPos, objGeoType);
		return result;
	}
	BOOL tmSetPointObjectCoor(long layerPos, long innerLayerObjPos, long geoPoX, long geoPoY)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x5b, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, layerPos, innerLayerObjPos, geoPoX, geoPoY);
		return result;
	}
	BOOL tmSetLineObjectCoors(long layerPos, long innerLayerObjPos, long geoPoCount, BSTR * pGeoPoints)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_PBSTR ;
		InvokeHelper(0x5c, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, layerPos, innerLayerObjPos, geoPoCount, pGeoPoints);
		return result;
	}
	BOOL tmSetFaceObjectCoors(long layerPos, long innerLayerObjPos, long geoPoCount, BSTR * pGeoPoints)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_PBSTR ;
		InvokeHelper(0x5d, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, layerPos, innerLayerObjPos, geoPoCount, pGeoPoints);
		return result;
	}
	BOOL tmDeleteGeoObject(long layerPos, long innerLayerObjPos)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x5e, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, layerPos, innerLayerObjPos);
		return result;
	}
	long tmSelectObjectsByScrnPo(long scrnPointX, long scrnPointY, BSTR * retObjPoses)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_PBSTR ;
		InvokeHelper(0x5f, DISPATCH_METHOD, VT_I4, (void*)&result, parms, scrnPointX, scrnPointY, retObjPoses);
		return result;
	}
	BOOL tmGetPointObjectCoor(long layerPos, long innerLayerObjPos, long * retGeoPointX, long * retGeoPointY)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_PI4 VTS_PI4 ;
		InvokeHelper(0x60, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, layerPos, innerLayerObjPos, retGeoPointX, retGeoPointY);
		return result;
	}
	long tmGetLineObjectCoorCount(long layerPos, long innerLayerObjPos)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x61, DISPATCH_METHOD, VT_I4, (void*)&result, parms, layerPos, innerLayerObjPos);
		return result;
	}
	long tmGetLineObjectCoors(long layerPos, long innerLayerObjPos, BSTR * retGeoPoints)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_PBSTR ;
		InvokeHelper(0x62, DISPATCH_METHOD, VT_I4, (void*)&result, parms, layerPos, innerLayerObjPos, retGeoPoints);
		return result;
	}
	long tmGetFaceObjectCoorCount(long layerPos, long innerLayerObjPos)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x63, DISPATCH_METHOD, VT_I4, (void*)&result, parms, layerPos, innerLayerObjPos);
		return result;
	}
	long tmGetFaceObjectCoors(long layerPos, long innerLayerObjPos, BSTR * retGeoPoints)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_PBSTR ;
		InvokeHelper(0x64, DISPATCH_METHOD, VT_I4, (void*)&result, parms, layerPos, innerLayerObjPos, retGeoPoints);
		return result;
	}
	long tmGetLayerObjectAttrCount(long layerPos)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x65, DISPATCH_METHOD, VT_I4, (void*)&result, parms, layerPos);
		return result;
	}
	long tmGetLayerObjectAttrType(long layerPos, long attrPos)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x66, DISPATCH_METHOD, VT_I4, (void*)&result, parms, layerPos, attrPos);
		return result;
	}
	BOOL tmGetLayerObjectAttrName(long layerPos, long attrPos, BSTR * retAttrName)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_PBSTR ;
		InvokeHelper(0x67, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, layerPos, attrPos, retAttrName);
		return result;
	}
	BOOL tmGetObjectAttrValueString(long layerPos, long innerLayerObjPos, long attrPos, BSTR * retAttrValString)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_PBSTR ;
		InvokeHelper(0x68, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, layerPos, innerLayerObjPos, attrPos, retAttrValString);
		return result;
	}
	BOOL tmSetObjectAttrValueString(long layerPos, long innerLayerObjPos, long attrPos, LPCTSTR srcAttrValString)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_BSTR ;
		InvokeHelper(0x69, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, layerPos, innerLayerObjPos, attrPos, srcAttrValString);
		return result;
	}
	void SetDrawRadarOrNot(BOOL bDrawRadarOrNot)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x6a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bDrawRadarOrNot);
	}
	BOOL GetDrawRadarOrNot()
	{
		BOOL result;
		InvokeHelper(0x6b, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	BOOL RemoveOtherVessel(long vesselPos)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x6c, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, vesselPos);
		return result;
	}
	BOOL SetOtherVesselDrawOrNot(long otherVesselPos, BOOL bDrawOrNot)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_BOOL ;
		InvokeHelper(0x6d, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, otherVesselPos, bDrawOrNot);
		return result;
	}
	long GetOtherVesselID(long vesselPos)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x6e, DISPATCH_METHOD, VT_I4, (void*)&result, parms, vesselPos);
		return result;
	}
	long GetOtherVesselPosOfID(long vesselID)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x6f, DISPATCH_METHOD, VT_I4, (void*)&result, parms, vesselID);
		return result;
	}
	BOOL HighlightOtherVessel(long otherVesselPos)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x70, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, otherVesselPos);
		return result;
	}
	long SelectOtherVesselByScrnPoint(long scrnPoX, long scrnPoY)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x71, DISPATCH_METHOD, VT_I4, (void*)&result, parms, scrnPoX, scrnPoY);
		return result;
	}
	long AddWayPoint(long geoPoX, long geoPoY, LPCTSTR strUsage)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_BSTR ;
		InvokeHelper(0x72, DISPATCH_METHOD, VT_I4, (void*)&result, parms, geoPoX, geoPoY, strUsage);
		return result;
	}
	long GetWayPointsCount()
	{
		long result;
		InvokeHelper(0x73, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long GetWayPointIDFromPos(long globalWpPos)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x74, DISPATCH_METHOD, VT_I4, (void*)&result, parms, globalWpPos);
		return result;
	}
	long GetWayPointPosFromID(long wpID)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x75, DISPATCH_METHOD, VT_I4, (void*)&result, parms, wpID);
		return result;
	}
	BOOL SetWayPointCoor(long wpID, long geoPoX, long geoPoY)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x76, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, wpID, geoPoX, geoPoY);
		return result;
	}
	BOOL GetWayPointCoor(long wpID, long * retGeoPoX, long * retGeoPoY)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_PI4 VTS_PI4 ;
		InvokeHelper(0x77, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, wpID, retGeoPoX, retGeoPoY);
		return result;
	}
	BOOL GetWayPointUsageString(long wpID, BSTR * retStrUsage)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_PBSTR ;
		InvokeHelper(0x78, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, wpID, retStrUsage);
		return result;
	}
	BOOL DeleteWayPoint(long wpID)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x79, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, wpID);
		return result;
	}
	long AddRoute(BSTR * wpIDs, LPCTSTR strRouteName, long wpCount, BOOL bPlanedRouteOrAlterated)
	{
		long result;
		static BYTE parms[] = VTS_PBSTR VTS_BSTR VTS_I4 VTS_BOOL ;
		InvokeHelper(0x7a, DISPATCH_METHOD, VT_I4, (void*)&result, parms, wpIDs, strRouteName, wpCount, bPlanedRouteOrAlterated);
		return result;
	}
	BOOL DeleteRoute(long delRouteID)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x7b, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, delRouteID);
		return result;
	}
	long GetRoutesCount()
	{
		long result;
		InvokeHelper(0x7c, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long GetRouteIDFromPos(long globalRoutePos)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x7d, DISPATCH_METHOD, VT_I4, (void*)&result, parms, globalRoutePos);
		return result;
	}
	long GetRoutePosFromID(long routeID)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x7e, DISPATCH_METHOD, VT_I4, (void*)&result, parms, routeID);
		return result;
	}
	BOOL GetRouteName(long routeID, BSTR * retRouteName)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_PBSTR ;
		InvokeHelper(0x7f, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, routeID, retRouteName);
		return result;
	}
	long GetRouteWayPointsCount(long routeID)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x80, DISPATCH_METHOD, VT_I4, (void*)&result, parms, routeID);
		return result;
	}
	BOOL AddRouteWayPoint(long routeID, long addWpPos, BSTR * addWpIDs, long addWpCount)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_PBSTR VTS_I4 ;
		InvokeHelper(0x81, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, routeID, addWpPos, addWpIDs, addWpCount);
		return result;
	}
	BOOL DeleteRouteWayPoint(long routeID, long delWpPos, long delWpCount)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x82, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, routeID, delWpPos, delWpCount);
		return result;
	}
	long GetRouteWayPointsID(long routeID, BSTR * retWayPointIDs)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_PBSTR ;
		InvokeHelper(0x83, DISPATCH_METHOD, VT_I4, (void*)&result, parms, routeID, retWayPointIDs);
		return result;
	}
	long GetRouteWayPointsCoor(long routeID, BSTR * wpPoints)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_PBSTR ;
		InvokeHelper(0x84, DISPATCH_METHOD, VT_I4, (void*)&result, parms, routeID, wpPoints);
		return result;
	}
	BOOL SetRouteBePlannedOrAlternated(long routeID, BOOL bPlanedRouteOrAlterated, BOOL bAlongOrBack)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_BOOL VTS_BOOL ;
		InvokeHelper(0x85, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, routeID, bPlanedRouteOrAlterated, bAlongOrBack);
		return result;
	}
	BOOL GetRouteBePlannedOrAlternated(long routeID, BOOL * retBePlanedRouteOrAlterated, BOOL * bAlongOrBack)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_PBOOL VTS_PBOOL ;
		InvokeHelper(0x86, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, routeID, retBePlanedRouteOrAlterated, bAlongOrBack);
		return result;
	}
	BOOL SetRouteShowOrNot(BOOL bSetAllRoutes, long routeID, BOOL bShowOrNot, BOOL bSetNewColor, long color)
	{
		BOOL result;
		static BYTE parms[] = VTS_BOOL VTS_I4 VTS_BOOL VTS_BOOL VTS_I4 ;
		InvokeHelper(0x87, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, bSetAllRoutes, routeID, bShowOrNot, bSetNewColor, color);
		return result;
	}
	BOOL SetWayPointShowOrNot(BOOL bSetAllWayPoints, long wayPointID, BOOL bShowOrNot, BOOL bShowNameOrNot)
	{
		BOOL result;
		static BYTE parms[] = VTS_BOOL VTS_I4 VTS_BOOL VTS_BOOL ;
		InvokeHelper(0x88, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, bSetAllWayPoints, wayPointID, bShowOrNot, bShowNameOrNot);
		return result;
	}
	BOOL SaveRoutesToFile(LPCTSTR routeFileName)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x89, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, routeFileName);
		return result;
	}
	BOOL AddRoutesFromFile(LPCTSTR routeFileName)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x8a, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, routeFileName);
		return result;
	}
	BOOL IsShipApproachingIsolatedDanger(long ownShipPointX, long ownShipPointY, float toDangerDistLimitByMeter, long * pRetObjMemMapPos, long * pRetObjLayerPos, long * pRetObjInnerLayerPos)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_R4 VTS_PI4 VTS_PI4 VTS_PI4 ;
		InvokeHelper(0x8b, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, ownShipPointX, ownShipPointY, toDangerDistLimitByMeter, pRetObjMemMapPos, pRetObjLayerPos, pRetObjInnerLayerPos);
		return result;
	}
	BOOL IsShipCrossingSafetyContour(long ownShipPointX, long ownShipPointY, float shipVectorCourse, float vectorDistLimitByMeter)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_R4 VTS_R4 ;
		InvokeHelper(0x8c, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, ownShipPointX, ownShipPointY, shipVectorCourse, vectorDistLimitByMeter);
		return result;
	}
	BOOL IsShipOffRoute(long ownShipPointX, long ownShipPointY, long routeID, float offRouteDistLimitByMeter)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_R4 ;
		InvokeHelper(0x8d, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, ownShipPointX, ownShipPointY, routeID, offRouteDistLimitByMeter);
		return result;
	}
	BOOL IsGeoLineSelectByScrnPoint(long scrnPointX, long scrnPointY, BSTR * geoLinePoints, long linePoCount, long selectDistVal)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_PBSTR VTS_I4 VTS_I4 ;
		InvokeHelper(0x8e, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, scrnPointX, scrnPointY, geoLinePoints, linePoCount, selectDistVal);
		return result;
	}
	BOOL IsGeoPointSelectByScrnPoint(long scrnPointX, long scrnPointY, long geoPointX, long geoPointY, long selectDistVal)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x8f, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, scrnPointX, scrnPointY, geoPointX, geoPointY, selectDistVal);
		return result;
	}
	BOOL IsGeoFaceSelectByScrnPoint(long scrnPoX, long scrnPoY, BSTR * faceGeoPoints, long facePoCount)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_PBSTR VTS_I4 ;
		InvokeHelper(0x90, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, scrnPoX, scrnPoY, faceGeoPoints, facePoCount);
		return result;
	}
	BOOL AddHighLightPoint(long geoPointX, long geoPointY)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x91, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, geoPointX, geoPointY);
		return result;
	}
	BOOL AddHighLightLine(BSTR * linePoints, long linePoCount)
	{
		BOOL result;
		static BYTE parms[] = VTS_PBSTR VTS_I4 ;
		InvokeHelper(0x92, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, linePoints, linePoCount);
		return result;
	}
	BOOL AddHighLightFace(BSTR * pFacePoints, long facePoCount)
	{
		BOOL result;
		static BYTE parms[] = VTS_PBSTR VTS_I4 ;
		InvokeHelper(0x93, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, pFacePoints, facePoCount);
		return result;
	}
	void ClearHighLightPoints()
	{
		InvokeHelper(0x94, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void ClearHighLightLines()
	{
		InvokeHelper(0x95, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void ClearHighLightFaces()
	{
		InvokeHelper(0x96, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	BOOL IsGeoObjectSelectedByArea(short objectMemMapPos, short objectLayPos, long objectInnerLayerPos, long areaCenterPointX, long areaCenterPointY, long areaRadius)
	{
		BOOL result;
		static BYTE parms[] = VTS_I2 VTS_I2 VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x97, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, objectMemMapPos, objectLayPos, objectInnerLayerPos, areaCenterPointX, areaCenterPointY, areaRadius);
		return result;
	}
	void SetIfShowWorldMap(BOOL bShowOrNot)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x98, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bShowOrNot);
	}
	BOOL GetIfShowWorldMap()
	{
		BOOL result;
		InvokeHelper(0x99, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	long GetLibMapPosOfName(LPCTSTR mapName)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x9a, DISPATCH_METHOD, VT_I4, (void*)&result, parms, mapName);
		return result;
	}
	long GetKeyNumber()
	{
		long result;
		InvokeHelper(0x9b, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	BOOL DrawUserMapLayerStyleAtPoint(long destHDc, long layerPos, long layerStylePos, long scrnPointX, long scrnPointY, LPCTSTR strExampleText, long drawScopeWidth, long backgroundColor)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_BSTR VTS_I4 VTS_I4 ;
		InvokeHelper(0x9c, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, destHDc, layerPos, layerStylePos, scrnPointX, scrnPointY, strExampleText, drawScopeWidth, backgroundColor);
		return result;
	}
	BOOL SetWayPointName(long wpID, LPCTSTR wpName)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_BSTR ;
		InvokeHelper(0x9d, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, wpID, wpName);
		return result;
	}
	BOOL SetWayPointCircle(long wpID, float radiusByMeter, long radiusColor, float radiusByMeter2, long radiusColor2)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_R4 VTS_I4 VTS_R4 VTS_I4 ;
		InvokeHelper(0x9e, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, wpID, radiusByMeter, radiusColor, radiusByMeter2, radiusColor2);
		return result;
	}
	BOOL GetWayPointCircleRadius(long wpID, float * retRadius, float * retRadius2)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_PR4 VTS_PR4 ;
		InvokeHelper(0x9f, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, wpID, retRadius, retRadius2);
		return result;
	}
	BOOL SetWayPointAsAimPoint(long wpID, BOOL bAimPoint, float directionByDeg, float offsetByMeter)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_BOOL VTS_R4 VTS_R4 ;
		InvokeHelper(0xa0, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, wpID, bAimPoint, directionByDeg, offsetByMeter);
		return result;
	}
	void SetGridLines(short lineCountPerScreen, long gridLineColor, long latTextColor, long lonTextColor, long textFontSize)
	{
		static BYTE parms[] = VTS_I2 VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0xa1, DISPATCH_METHOD, VT_EMPTY, NULL, parms, lineCountPerScreen, gridLineColor, latTextColor, lonTextColor, textFontSize);
	}
	void SetBackgroundColor(long backColor)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xa2, DISPATCH_METHOD, VT_EMPTY, NULL, parms, backColor);
	}
	BOOL GetWayPointName(long wpID, BSTR * retWpName)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_PBSTR ;
		InvokeHelper(0xa3, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, wpID, retWpName);
		return result;
	}
	void SetGridLinesShowOrNot(BOOL bShowOrNot)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0xa4, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bShowOrNot);
	}
	BOOL SetWayPointUsage(long wpID, LPCTSTR strUsage)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_BSTR ;
		InvokeHelper(0xa5, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, wpID, strUsage);
		return result;
	}
	BOOL GetWayPointShowOrNot(long wpID, BOOL * retBeWayPointShowOrNot, BOOL * retBeWayPointNameOrNot)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_PBOOL VTS_PBOOL ;
		InvokeHelper(0xa6, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, wpID, retBeWayPointShowOrNot, retBeWayPointNameOrNot);
		return result;
	}
	BOOL GetRouteShowOrNot(long routeID, BOOL * retBeShowOrNot)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_PBOOL ;
		InvokeHelper(0xa7, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, routeID, retBeShowOrNot);
		return result;
	}
	BOOL SetWayPointRadialLine(long wpID, float radialAngleByDeg, long radialLineColor, float radialAngleByDeg2, long radialLineColor2)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_R4 VTS_I4 VTS_R4 VTS_I4 ;
		InvokeHelper(0xa8, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, wpID, radialAngleByDeg, radialLineColor, radialAngleByDeg2, radialLineColor2);
		return result;
	}
	BOOL GetWayPointRadialLineAngle(long wpID, float * retRadialAngle1, float * retRadialAngle2)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_PR4 VTS_PR4 ;
		InvokeHelper(0xa9, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, wpID, retRadialAngle1, retRadialAngle2);
		return result;
	}
	BOOL ZoomInByScreenRect(long leftTopScrnPoX, long leftTopScrnPoY, long rightDownScrnPoX, long rightDownScrnPoY)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0xaa, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, leftTopScrnPoX, leftTopScrnPoY, rightDownScrnPoX, rightDownScrnPoY);
		return result;
	}
	BOOL SetCurrentPen(long penWidth, long penColor)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0xab, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, penWidth, penColor);
		return result;
	}
	BOOL SetCurrentBrush(long brushColor)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xac, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, brushColor);
		return result;
	}
	BOOL SetCurrentFont(LPCTSTR strFontName, long fontHeight, long fontColor, long bIsBold, long bIsItalic)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0xad, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, strFontName, fontHeight, fontColor, bIsBold, bIsItalic);
		return result;
	}
	void DrawLine(long startPointX, long startPointY, long endPointX, long endPointY)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0xae, DISPATCH_METHOD, VT_EMPTY, NULL, parms, startPointX, startPointY, endPointX, endPointY);
	}
	BOOL DrawPolyline(BSTR * pPoints, long poCount)
	{
		BOOL result;
		static BYTE parms[] = VTS_PBSTR VTS_I4 ;
		InvokeHelper(0xaf, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, pPoints, poCount);
		return result;
	}
	BOOL FillPolygon(BSTR * pPoints, long poCount, BOOL bDrawEdges, long transparency)
	{
		BOOL result;
		static BYTE parms[] = VTS_PBSTR VTS_I4 VTS_BOOL VTS_I4 ;
		InvokeHelper(0xb0, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, pPoints, poCount, bDrawEdges, transparency);
		return result;
	}
	BOOL PasteBitmap(long hBmp, long hBmpMask, long destPointX, long destPointY)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0xb1, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, hBmp, hBmpMask, destPointX, destPointY);
		return result;
	}
	BOOL TextOutAtPoint(LPCTSTR strText, long poX, long poY)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR VTS_I4 VTS_I4 ;
		InvokeHelper(0xb2, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, strText, poX, poY);
		return result;
	}
	BOOL DrawEllipse(long centerPoX, long centerPoY, long width, long height, BOOL bFill, BOOL bDrawEdge)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_BOOL VTS_BOOL ;
		InvokeHelper(0xb3, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, centerPoX, centerPoY, width, height, bFill, bDrawEdge);
		return result;
	}
	BOOL DrawCircle(long centerPoX, long centerPoY, long radius, BOOL bFill, BOOL bDrawEdge)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_BOOL VTS_BOOL ;
		InvokeHelper(0xb4, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, centerPoX, centerPoY, radius, bFill, bDrawEdge);
		return result;
	}
	BOOL DrawArc(long centerPoX, long centerPoY, long radius, double startArc, double endArc, long edgeLineWidth, BOOL bFill, BOOL bClockWise, long transparency)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_R8 VTS_R8 VTS_I4 VTS_BOOL VTS_BOOL VTS_I4 ;
		InvokeHelper(0xb5, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, centerPoX, centerPoY, radius, startArc, endArc, edgeLineWidth, bFill, bClockWise, transparency);
		return result;
	}
	BOOL tmUpdateUserMapFromLayersCfgFile(LPCTSTR strLayersCfgFileName, BOOL bIfKeepOldMapData)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR VTS_BOOL ;
		InvokeHelper(0xb6, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, strLayersCfgFileName, bIfKeepOldMapData);
		return result;
	}
	long AddAisType(LPCTSTR pStrTypeName)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xb7, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pStrTypeName);
		return result;
	}
	BOOL SetAisTargetType(long otherVesslePos, long typeID)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0xb8, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, otherVesslePos, typeID);
		return result;
	}
	long GetAisTargetType(long otherVesselPos)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xb9, DISPATCH_METHOD, VT_I4, (void*)&result, parms, otherVesselPos);
		return result;
	}
	void SetStandardAisTargetLen(float standardLengthByMeter, float standardWidthByMeter)
	{
		static BYTE parms[] = VTS_R4 VTS_R4 ;
		InvokeHelper(0xba, DISPATCH_METHOD, VT_EMPTY, NULL, parms, standardLengthByMeter, standardWidthByMeter);
	}
	void SetDrawerPastingByMemScrn(BOOL bPasteFromMemScrnOrNot)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0xbb, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bPasteFromMemScrnOrNot);
	}
	BOOL tmSetPointObjectStyle(long layerPos, long innerLayerPos, long symbolID, BOOL bSetTrueTypeSymbolColor, long trueTypeSymbolColor, long trueTypeSymbolSize, BOOL bTakeText, LPCTSTR strText, LPCTSTR pStrFontName, long fontHeight, long fontColor, BOOL bIsBold, BOOL bIsItalic, long offsetX, long offsetY, long textOffsetX, long textOffsetY, float symbolRotateAngleByDeg)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_BOOL VTS_I4 VTS_I4 VTS_BOOL VTS_BSTR VTS_BSTR VTS_I4 VTS_I4 VTS_BOOL VTS_BOOL VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_R4 ;
		InvokeHelper(0xbc, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, layerPos, innerLayerPos, symbolID, bSetTrueTypeSymbolColor, trueTypeSymbolColor, trueTypeSymbolSize, bTakeText, strText, pStrFontName, fontHeight, fontColor, bIsBold, bIsItalic, offsetX, offsetY, textOffsetX, textOffsetY, symbolRotateAngleByDeg);
		return result;
	}
	BOOL tmSetLineObjectStyle(long layerPos, long innerLayerObjPos, BOOL bSetBasicLnStyle, BOOL bSolidOrDash, long dashCycle, long dashLen, long lineWidth, long lineColor, long cycleSymbolID, long cycleSymbolLen, LPCTSTR pStrText, LPCTSTR pStrFontName, long fontHeight, long fontColor, BOOL bIsBold, BOOL bIsItalic, long textOffsetX, long textOffsetY, BOOL bTextAlongWithLine)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_BOOL VTS_BOOL VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_BSTR VTS_BSTR VTS_I4 VTS_I4 VTS_BOOL VTS_BOOL VTS_I4 VTS_I4 VTS_BOOL ;
		InvokeHelper(0xbd, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, layerPos, innerLayerObjPos, bSetBasicLnStyle, bSolidOrDash, dashCycle, dashLen, lineWidth, lineColor, cycleSymbolID, cycleSymbolLen, pStrText, pStrFontName, fontHeight, fontColor, bIsBold, bIsItalic, textOffsetX, textOffsetY, bTextAlongWithLine);
		return result;
	}
	BOOL tmSetFaceObjectStyle(long layerPos, long innerLayerObjPos, BOOL bFillColor, long fillColor, long fillTransparency, long patternSymbolID, long patternSymbolSpaceWidth, long patternSymbolSpaceHeight, LPCTSTR pStrText, LPCTSTR pStrFontName, long fontHeight, long fontColor, BOOL bIsBold, BOOL bIsItalic, BOOL bAtCenterOrBottom, long textOffsetX, long textOffsetY)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_BOOL VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_BSTR VTS_BSTR VTS_I4 VTS_I4 VTS_BOOL VTS_BOOL VTS_BOOL VTS_I4 VTS_I4 ;
		InvokeHelper(0xbe, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, layerPos, innerLayerObjPos, bFillColor, fillColor, fillTransparency, patternSymbolID, patternSymbolSpaceWidth, patternSymbolSpaceHeight, pStrText, pStrFontName, fontHeight, fontColor, bIsBold, bIsItalic, bAtCenterOrBottom, textOffsetX, textOffsetY);
		return result;
	}
	void GetDepthShadesMode(BOOL * pBeTwoShadesOrFourShades, float * pShallowDepth, float * pSafetyDepth, float * pDeepDepth)
	{
		static BYTE parms[] = VTS_PBOOL VTS_PR4 VTS_PR4 VTS_PR4 ;
		InvokeHelper(0xbf, DISPATCH_METHOD, VT_EMPTY, NULL, parms, pBeTwoShadesOrFourShades, pShallowDepth, pSafetyDepth, pDeepDepth);
	}
	void SetDepthShadesMode(BOOL bTwoShadesOrFourShades, float shallowDepth, float safetyDepth, float deepDepth)
	{
		static BYTE parms[] = VTS_BOOL VTS_R4 VTS_R4 VTS_R4 ;
		InvokeHelper(0xc0, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bTwoShadesOrFourShades, shallowDepth, safetyDepth, deepDepth);
	}
	long QueryObjectsByKeyWordsString(BSTR * retSelectedObjectPositions, LPCTSTR keyWordsString)
	{
		long result;
		static BYTE parms[] = VTS_PBSTR VTS_BSTR ;
		InvokeHelper(0xc1, DISPATCH_METHOD, VT_I4, (void*)&result, parms, retSelectedObjectPositions, keyWordsString);
		return result;
	}
	BOOL GetObjectGeoExtent(BSTR * pObjectPos, long * pRetLeft, long * pRetRight, long * pRetTop, long * pRetBottom)
	{
		BOOL result;
		static BYTE parms[] = VTS_PBSTR VTS_PI4 VTS_PI4 VTS_PI4 VTS_PI4 ;
		InvokeHelper(0xc2, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, pObjectPos, pRetLeft, pRetRight, pRetTop, pRetBottom);
		return result;
	}
	long AddAnEmptySymbol()
	{
		long result;
		InvokeHelper(0xc3, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long GetSymbolCount()
	{
		long result;
		InvokeHelper(0xc4, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	BOOL SetSymbolAsTrueTypeSymbol(long symbolID, LPCTSTR pStrFontName, short charCode, long offsetX, long offsetY)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_BSTR VTS_I2 VTS_I4 VTS_I4 ;
		InvokeHelper(0xc5, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, symbolID, pStrFontName, charCode, offsetX, offsetY);
		return result;
	}
	void SaveSymbolsToFile()
	{
		InvokeHelper(0xc6, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	BOOL tmClearLayer(long layerPos)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xc7, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, layerPos);
		return result;
	}
	long GetSymbolIDFromPos(long symbolPos)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xc8, DISPATCH_METHOD, VT_I4, (void*)&result, parms, symbolPos);
		return result;
	}
	long GetSymbolPosOfID(long symbolID)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xc9, DISPATCH_METHOD, VT_I4, (void*)&result, parms, symbolID);
		return result;
	}
	BOOL DeleteSymbol(long symbolID)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xca, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, symbolID);
		return result;
	}
	BOOL RefreshDrawerForDirectDrawDC(long hdc, long scrnWidth, long scrnHeight, long scrnOrgOffsetX, long scrnOrgOffsetY, long bDirectDraw, double mmToPixelMapFactor)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_R8 ;
		InvokeHelper(0xcb, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, hdc, scrnWidth, scrnHeight, scrnOrgOffsetX, scrnOrgOffsetY, bDirectDraw, mmToPixelMapFactor);
		return result;
	}
	void GetMemMapInfo(long iMemMapPos, BSTR * retStrMapType, BSTR * retStrMapName, float * retOriginalScale, long * retLeftMost, long * retRightMost, long * retUpMost, long * retDownMost, long * retEditionNum, long * retUpdateNum)
	{
		static BYTE parms[] = VTS_I4 VTS_PBSTR VTS_PBSTR VTS_PR4 VTS_PI4 VTS_PI4 VTS_PI4 VTS_PI4 VTS_PI4 VTS_PI4 ;
		InvokeHelper(0xcc, DISPATCH_METHOD, VT_EMPTY, NULL, parms, iMemMapPos, retStrMapType, retStrMapName, retOriginalScale, retLeftMost, retRightMost, retUpMost, retDownMost, retEditionNum, retUpdateNum);
	}
	void SetIfUseScaleMin(BOOL bUseOrNot)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0xcd, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bUseOrNot);
	}
	BOOL GetIfUseScaleMin()
	{
		BOOL result;
		InvokeHelper(0xce, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void SetIfShowText(BOOL bIfShow)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0xcf, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bIfShow);
	}
	BOOL GetIfShowText()
	{
		BOOL result;
		InvokeHelper(0xd0, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	long tmSelectOnePointOfLineObject(long scrnPointX, long scrnPointY, long layerPos, long innerLayerObjPos)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0xd1, DISPATCH_METHOD, VT_I4, (void*)&result, parms, scrnPointX, scrnPointY, layerPos, innerLayerObjPos);
		return result;
	}
	BOOL tmMoveOnePointOfLineObject(long lineObjLayerPos, long lineObjInnerLayerPos, long pointPosInLine, long newGeoPositionX, long newGeoPositionY)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0xd2, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, lineObjLayerPos, lineObjInnerLayerPos, pointPosInLine, newGeoPositionX, newGeoPositionY);
		return result;
	}
	BOOL tmAddOnePointToLineOrFaceObject(long lineObjLayerPos, long lineObjInnerLayerPos, long addPointPosInLine, long newGeoPointX, long newGeoPointY)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0xd3, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, lineObjLayerPos, lineObjInnerLayerPos, addPointPosInLine, newGeoPointX, newGeoPointY);
		return result;
	}
	BOOL tmDeleteOnePointOfLineObject(long lineObjLayerPos, long lineObjInnerLayerPos, long pointPosInLine)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0xd4, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, lineObjLayerPos, lineObjInnerLayerPos, pointPosInLine);
		return result;
	}
	BOOL VerifyUserLicense()
	{
		BOOL result;
		InvokeHelper(0xd5, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void SetIfShowSounding(BOOL bShowOrNot)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0xd6, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bShowOrNot);
	}
	BOOL GetIfShowSounding()
	{
		BOOL result;
		InvokeHelper(0xd7, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	BOOL SetYimapEncFileExtension(LPCTSTR ymcExtension, LPCTSTR ympExtension)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0xd8, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, ymcExtension, ympExtension);
		return result;
	}
	BOOL GetYimapEncFileExtension(BSTR * retYmcFileExtension, BSTR * retYmpFileExtension)
	{
		BOOL result;
		static BYTE parms[] = VTS_PBSTR VTS_PBSTR ;
		InvokeHelper(0xd9, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, retYmcFileExtension, retYmpFileExtension);
		return result;
	}
	BOOL SetOtherVesselShowColor(long otherVesselNum, BOOL bUseDefaultColor, long vslColor, BOOL bUseDefualtVectorColor, long vectorColor)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_BOOL VTS_I4 VTS_BOOL VTS_I4 ;
		InvokeHelper(0xda, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, otherVesselNum, bUseDefaultColor, vslColor, bUseDefualtVectorColor, vectorColor);
		return result;
	}
	BOOL tmSetLineObjectStyleRefLib(long layerPos, long innerLayerPos, long libLineStyleID, BOOL bSetColor, long lineColor, BOOL bSetWidth, long lineWidth)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_BOOL VTS_I4 VTS_BOOL VTS_I4 ;
		InvokeHelper(0xdb, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, layerPos, innerLayerPos, libLineStyleID, bSetColor, lineColor, bSetWidth, lineWidth);
		return result;
	}
	long SelectObjectsByScrnRect(BSTR * retSelectedObjectPositions, long rectLeft, long rectTop, long rectRight, long rectDown)
	{
		long result;
		static BYTE parms[] = VTS_PBSTR VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0xdc, DISPATCH_METHOD, VT_I4, (void*)&result, parms, retSelectedObjectPositions, rectLeft, rectTop, rectRight, rectDown);
		return result;
	}
	BOOL GetLibMapEditionIssueDate(long libMapPos, long iUpdateEditionNumber, BSTR * retStrDate)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_PBSTR ;
		InvokeHelper(0xdd, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, libMapPos, iUpdateEditionNumber, retStrDate);
		return result;
	}
	void GetLinePointNearestToPoint(long geoPointX, long geoPointY, long geoLineStartPointX, long geoLineStartPointY, long geoLineEndPointX, long geoLineEndPointY, long * retPointX, long * retPointY, float * retDistByNm, BOOL bRetPointOnLineSection)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_PI4 VTS_PI4 VTS_PR4 VTS_BOOL ;
		InvokeHelper(0xde, DISPATCH_METHOD, VT_EMPTY, NULL, parms, geoPointX, geoPointY, geoLineStartPointX, geoLineStartPointY, geoLineEndPointX, geoLineEndPointY, retPointX, retPointY, retDistByNm, bRetPointOnLineSection);
	}
	BOOL tmSetFaceObjectStyleRefLib(long layerPos, long innerLayerPos, long libFaceStyleID, BOOL bSetFillColor, long fillColor, long bSetFillTransparency, long transparency, BOOL bSetPatternColor, long patternColor)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_BOOL VTS_I4 VTS_I4 VTS_I4 VTS_BOOL VTS_I4 ;
		InvokeHelper(0xdf, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, layerPos, innerLayerPos, libFaceStyleID, bSetFillColor, fillColor, bSetFillTransparency, transparency, bSetPatternColor, patternColor);
		return result;
	}
	BOOL DrawLineWithLibLineStyle(long libLineStyleID, BSTR * linePoints, long linePoCount, BOOL bSetColor, long lineColor, BOOL bSetWidth, long lineWidth)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_PBSTR VTS_I4 VTS_BOOL VTS_I4 VTS_BOOL VTS_I4 ;
		InvokeHelper(0xe0, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, libLineStyleID, linePoints, linePoCount, bSetColor, lineColor, bSetWidth, lineWidth);
		return result;
	}
	BOOL DrawFaceWithLibFaceStyle(long libFaceStyleID, BSTR * facePoints, long facePoCount, BOOL bSetFillColor, long fillColor, BOOL bSetPatternColor, long patternColor)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_PBSTR VTS_I4 VTS_BOOL VTS_I4 VTS_BOOL VTS_I4 ;
		InvokeHelper(0xe1, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, libFaceStyleID, facePoints, facePoCount, bSetFillColor, fillColor, bSetPatternColor, patternColor);
		return result;
	}
	long GetLibLineStyleCount()
	{
		long result;
		InvokeHelper(0xe2, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long GetLibLineStyleIDFromPos(long pos)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xe3, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pos);
		return result;
	}
	long GetLibLineStylePosOfID(long id)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xe4, DISPATCH_METHOD, VT_I4, (void*)&result, parms, id);
		return result;
	}
	long GetLibFaceStyleCount()
	{
		long result;
		InvokeHelper(0xe5, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long GetLibFaceStyleIDFromPos(long pos)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xe6, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pos);
		return result;
	}
	long GetLibFaceStylePosOfID(long id)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xe7, DISPATCH_METHOD, VT_I4, (void*)&result, parms, id);
		return result;
	}
	BOOL DrawPointWithLibSymbol(long symbolID, long pointX, long pointY, BOOL bSetColor, long color, float zoomScale, float rotateAngle)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_BOOL VTS_I4 VTS_R4 VTS_R4 ;
		InvokeHelper(0xe8, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, symbolID, pointX, pointY, bSetColor, color, zoomScale, rotateAngle);
		return result;
	}
	void SetIfShowMapFrame(BOOL bIfShow)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0xe9, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bIfShow);
	}
	BOOL GetIfShowMapFrame()
	{
		BOOL result;
		InvokeHelper(0xea, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	BOOL tmSetPointObjectStyleRefLib(long layerPos, long innerLayerObjPos, long symbolID, BOOL bSetColor, long color, float zoomScale, float symbloRotateAngleByDeg)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_BOOL VTS_I4 VTS_R4 VTS_R4 ;
		InvokeHelper(0xeb, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, layerPos, innerLayerObjPos, symbolID, bSetColor, color, zoomScale, symbloRotateAngleByDeg);
		return result;
	}
	long tmGetGeoObjectType(long layerPos, long innerLayerObjPos)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0xec, DISPATCH_METHOD, VT_I4, (void*)&result, parms, layerPos, innerLayerObjPos);
		return result;
	}
	BOOL tmSetObjectAsSpecialType(long layerPos, long innerLayerObjPos, long specialType)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0xed, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, layerPos, innerLayerObjPos, specialType);
		return result;
	}
	void SetPointSelectJudgeDist(long pointHitPointDist, long pointHitLineDist)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0xee, DISPATCH_METHOD, VT_EMPTY, NULL, parms, pointHitPointDist, pointHitLineDist);
	}
	BOOL tmMoveObjectInScrn(long objLayerPos, long objInnerLayerPos, long scrnOffsetX, long scrnOffsetY)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0xef, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, objLayerPos, objInnerLayerPos, scrnOffsetX, scrnOffsetY);
		return result;
	}
	BOOL tmSetSectorTypeLineObjectParams(long layerPos, long innerLayerPos, BOOL bSetCenterPoint, long centerPointX, long centerPointY, BOOL bSetInnerRadius, float innerRadiusByMeter, BOOL bSetOutterRadius, float outterRadiusByMeter, BOOL bSetStartAngle, float startAngleByDeg, BOOL bSetEndAngle, float endAngleByDeg)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_BOOL VTS_I4 VTS_I4 VTS_BOOL VTS_R4 VTS_BOOL VTS_R4 VTS_BOOL VTS_R4 VTS_BOOL VTS_R4 ;
		InvokeHelper(0xf0, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, layerPos, innerLayerPos, bSetCenterPoint, centerPointX, centerPointY, bSetInnerRadius, innerRadiusByMeter, bSetOutterRadius, outterRadiusByMeter, bSetStartAngle, startAngleByDeg, bSetEndAngle, endAngleByDeg);
		return result;
	}
	BOOL tmSetArcTypeLineObjectParams(long layerPos, long innerLayerPos, BOOL bSetCenterPoint, long centerPointX, long centerPointY, BOOL bSetRadius, float newRadiusByMeter, BOOL bSetStartAngle, float startAngleByDeg, BOOL bSetEndAngle, float endAngleByDeg)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_BOOL VTS_I4 VTS_I4 VTS_BOOL VTS_R4 VTS_BOOL VTS_R4 VTS_BOOL VTS_R4 ;
		InvokeHelper(0xf1, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, layerPos, innerLayerPos, bSetCenterPoint, centerPointX, centerPointY, bSetRadius, newRadiusByMeter, bSetStartAngle, startAngleByDeg, bSetEndAngle, endAngleByDeg);
		return result;
	}
	BOOL tmGetArcTypeLineObjectParams(long layerPos, long innerLayerObjPos, long * pRetCenterPointX, long * pRetCenterPointY, float * pRetRadiusByMeter, float * pRetStartAngleByDeg, float * pRetEndAngleByDeg)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_PI4 VTS_PI4 VTS_PR4 VTS_PR4 VTS_PR4 ;
		InvokeHelper(0xf2, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, layerPos, innerLayerObjPos, pRetCenterPointX, pRetCenterPointY, pRetRadiusByMeter, pRetStartAngleByDeg, pRetEndAngleByDeg);
		return result;
	}
	BOOL tmGetSectorTypeLineObjectParams(long layerPos, long innerLayerObjPos, long * pRetCenterPointX, long * pRetCenterPointY, float * pRetInnerRadiusByMeter, float * pRetOutterRadiusByMeter, float * pRetStartAngleByDeg, float * pRetEndAngleByDeg)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_PI4 VTS_PI4 VTS_PR4 VTS_PR4 VTS_PR4 VTS_PR4 ;
		InvokeHelper(0xf3, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, layerPos, innerLayerObjPos, pRetCenterPointX, pRetCenterPointY, pRetInnerRadiusByMeter, pRetOutterRadiusByMeter, pRetStartAngleByDeg, pRetEndAngleByDeg);
		return result;
	}
	void SetIfUseGDIPlus(BOOL bUseGDIPlus)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0xf4, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bUseGDIPlus);
	}
	BOOL GetIfUseGDIPlus()
	{
		BOOL result;
		InvokeHelper(0xf5, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void SetIfShowOwnship(BOOL bShowOrNot)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0xf6, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bShowOrNot);
	}
	void ZoomS52SymbolOrFontSize(float zoomSymbolSizeRatio, float zoomFontSizeRatio)
	{
		static BYTE parms[] = VTS_R4 VTS_R4 ;
		InvokeHelper(0xf7, DISPATCH_METHOD, VT_EMPTY, NULL, parms, zoomSymbolSizeRatio, zoomFontSizeRatio);
	}
	void SetIfShowGrid(BOOL bShowOrNot)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0xf8, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bShowOrNot);
	}
	BOOL GetIfShowGrid()
	{
		BOOL result;
		InvokeHelper(0xf9, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	BOOL tmSetLayerDrawOrNot(long nLayerPos, BOOL bDrawOrNot)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_BOOL ;
		InvokeHelper(0xfa, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, nLayerPos, bDrawOrNot);
		return result;
	}
	BOOL tmGetLayerDrawOrNot(long nLayerPos, BOOL * pRetDrawOrNot)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_PBOOL ;
		InvokeHelper(0xfb, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, nLayerPos, pRetDrawOrNot);
		return result;
	}
	long GetOtherVesselPosOfMMSI(long mmsi)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xfc, DISPATCH_METHOD, VT_I4, (void*)&result, parms, mmsi);
		return result;
	}
	BOOL SetCurrentTextAlign(long horiJust, long vertJust)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0xfd, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, horiJust, vertJust);
		return result;
	}
	void GetDrawerOrgOffset(long * pRetoffsetX, long * pRetoffsetY)
	{
		static BYTE parms[] = VTS_PI4 VTS_PI4 ;
		InvokeHelper(0xfe, DISPATCH_METHOD, VT_EMPTY, NULL, parms, pRetoffsetX, pRetoffsetY);
	}
	BOOL tmPushInStackUndoOperation(short undoOprtnType, long layerPos, long innerLayerObjPos)
	{
		BOOL result;
		static BYTE parms[] = VTS_I2 VTS_I4 VTS_I4 ;
		InvokeHelper(0xff, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, undoOprtnType, layerPos, innerLayerObjPos);
		return result;
	}
	void tmUndo()
	{
		InvokeHelper(0x100, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void tmRedo()
	{
		InvokeHelper(0x101, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void tmSetTargetForRedoOperation()
	{
		InvokeHelper(0x102, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	BOOL tmRotateLineObjectInScrn(long layerPos, long innerLayerObjPos, long centerGeoPointX, long centerGeoPointY, double rotateAngleByDegree)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_R8 ;
		InvokeHelper(0x103, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, layerPos, innerLayerObjPos, centerGeoPointX, centerGeoPointY, rotateAngleByDegree);
		return result;
	}
	void SetHaloTextBakColor(long color)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x104, DISPATCH_METHOD, VT_EMPTY, NULL, parms, color);
	}
	BOOL GetIfShowScaleBar()
	{
		BOOL result;
		InvokeHelper(0x105, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void SetIfShowScaleBar(BOOL bShow)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x106, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bShow);
	}
	void SetIfShowNorthArrow(BOOL bShowOrNot)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x107, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bShowOrNot);
	}
	BOOL GetIfShowNorthArrow()
	{
		BOOL result;
		InvokeHelper(0x108, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void Exit(BOOL bFastExit)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x109, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bFastExit);
	}
	BOOL tmGetObjectIDFromPos(long layerPos, long innerLayerObjPos, long * retLayerID, long * retInnerLayerObjID)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_PI4 VTS_PI4 ;
		InvokeHelper(0x10a, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, layerPos, innerLayerObjPos, retLayerID, retInnerLayerObjID);
		return result;
	}
	BOOL tmGetObjectPosFromID(long layerID, long innerLayerObjID, long * retLayerPos, long * retInnerLayerObjPos)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_PI4 VTS_PI4 ;
		InvokeHelper(0x10b, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, layerID, innerLayerObjID, retLayerPos, retInnerLayerObjPos);
		return result;
	}
	long AddS63MapLib(LPCTSTR S63CellFilePath, LPCTSTR S63PermitFilePath, BOOL bLeaveS57File)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BOOL ;
		InvokeHelper(0x10c, DISPATCH_METHOD, VT_I4, (void*)&result, parms, S63CellFilePath, S63PermitFilePath, bLeaveS57File);
		return result;
	}
	void SetNationalLanguageCountry(long countryEnum)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x10d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, countryEnum);
	}
	long GetNationalLanguageCountry()
	{
		long result;
		InvokeHelper(0x10e, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void SetLoadMapScaleFactor(float scaleFactor)
	{
		static BYTE parms[] = VTS_R4 ;
		InvokeHelper(0x10f, DISPATCH_METHOD, VT_EMPTY, NULL, parms, scaleFactor);
	}
	float GetLoadMapScaleFactor()
	{
		float result;
		InvokeHelper(0x110, DISPATCH_METHOD, VT_R4, (void*)&result, NULL);
		return result;
	}
	BOOL SetLibMapLoadScale(long libMapPos, float minScaleToLoadAndShow)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_R4 ;
		InvokeHelper(0x111, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, libMapPos, minScaleToLoadAndShow);
		return result;
	}
	float GetLibMapLoadScale(long libMapPos)
	{
		float result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x112, DISPATCH_METHOD, VT_R4, (void*)&result, parms, libMapPos);
		return result;
	}
	BOOL SetOtherVesselShowText(long otherVslPos, BOOL bSetText, LPCTSTR strText, BOOL bSetFontSize, long fontSize, BOOL bSetColor, long fontColor)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_BOOL VTS_BSTR VTS_BOOL VTS_I4 VTS_BOOL VTS_I4 ;
		InvokeHelper(0x113, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, otherVslPos, bSetText, strText, bSetFontSize, fontSize, bSetColor, fontColor);
		return result;
	}
	void SetRadarSwitchForDrawMap(long radarSwitch)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x114, DISPATCH_METHOD, VT_EMPTY, NULL, parms, radarSwitch);
	}
	BOOL IsPointInFaceGeoObject(long pointX, long pointY, long objMemMapPos, long objLayerPos, long objInnerLayerPos, BOOL bGeoCoorOrScrnCoor)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_BOOL ;
		InvokeHelper(0x115, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, pointX, pointY, objMemMapPos, objLayerPos, objInnerLayerPos, bGeoCoorOrScrnCoor);
		return result;
	}
	BOOL DeleteGeoObject(long mapPos, long layerPos, long innerLayerObjPos)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x116, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, mapPos, layerPos, innerLayerObjPos);
		return result;
	}
	BOOL SetGeoObjectScaleMin(long memMapPos, long layerPos, long innerLayerObjPos, float scaleMin)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_R4 ;
		InvokeHelper(0x117, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, memMapPos, layerPos, innerLayerObjPos, scaleMin);
		return result;
	}
	BOOL SaveS57MemMapToFile(long memMapPos, LPCTSTR strFilePathName, BOOL bOnlySaveLayersToDraw)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_BSTR VTS_BOOL ;
		InvokeHelper(0x118, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, memMapPos, strFilePathName, bOnlySaveLayersToDraw);
		return result;
	}
	void SaveMapLibBasicInfo()
	{
		InvokeHelper(0x119, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	long GetYMCFileEncryptKey()
	{
		long result;
		InvokeHelper(0x11a, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void SetYMCFileEncryptKey(long keyNumber)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x11b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, keyNumber);
	}
	void SetIfYmcFileNeedEncrypt(BOOL bEncryptOrNot)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x11c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bEncryptOrNot);
	}
	void SetIfOnDrawRadarMode(BOOL bOnDrawRadarMode)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x11d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bOnDrawRadarMode);
	}
	long GetSoundingSetPointCount(long memMapPos, long layerPos, long innerLayerObjPos)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x11e, DISPATCH_METHOD, VT_I4, (void*)&result, parms, memMapPos, layerPos, innerLayerObjPos);
		return result;
	}
	BOOL GetSoundingSetPointDepth(long memMapPos, long layerPos, long innerLayerObjPos, long pointPosInSoundingSet, float * pRetDepth, long * retSoundCoorX, long * retSoundCoorY)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_PR4 VTS_PI4 VTS_PI4 ;
		InvokeHelper(0x11f, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, memMapPos, layerPos, innerLayerObjPos, pointPosInSoundingSet, pRetDepth, retSoundCoorX, retSoundCoorY);
		return result;
	}
	BOOL GetSoundPointSelectByGeoPoint(long sphereGeoPoX, long sphereGeoPoY, long maxDistByMmToSounding, float * retSoundingDepth, BSTR * pRetBstrSoundingObjPos, long * pRetSoundingInObjPos)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_PR4 VTS_PBSTR VTS_PI4 ;
		InvokeHelper(0x120, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, sphereGeoPoX, sphereGeoPoY, maxDistByMmToSounding, retSoundingDepth, pRetBstrSoundingObjPos, pRetSoundingInObjPos);
		return result;
	}
	long GetLayerGeoType(long nLayerPos)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x121, DISPATCH_METHOD, VT_I4, (void*)&result, parms, nLayerPos);
		return result;
	}
	BOOL ReInitMapMan(LPCTSTR nowS57CfgFileDir)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x122, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, nowS57CfgFileDir);
		return result;
	}
	BOOL SetAisTypeInfo(long typeID, LPCTSTR strTypeName, BOOL bUseStandardS52Symbol, long symbolID, float zoomSybmolRatio, BOOL bSetColor, long symbolColor, long tinySymbolID, float showTinySymbolScale, BOOL bShowRealSize, BOOL bZoomWithScale, float zoomBaseScale, BOOL bRotateSymbolWithCourse)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_BSTR VTS_BOOL VTS_I4 VTS_R4 VTS_BOOL VTS_I4 VTS_I4 VTS_R4 VTS_BOOL VTS_BOOL VTS_R4 VTS_BOOL ;
		InvokeHelper(0x123, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, typeID, strTypeName, bUseStandardS52Symbol, symbolID, zoomSybmolRatio, bSetColor, symbolColor, tinySymbolID, showTinySymbolScale, bShowRealSize, bZoomWithScale, zoomBaseScale, bRotateSymbolWithCourse);
		return result;
	}
	BOOL SetWorkDirectory(LPCTSTR strCfgFileLibDir, LPCTSTR strMapLibDir)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x124, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, strCfgFileLibDir, strMapLibDir);
		return result;
	}
	void SetDrawShipHeadingLineLen(long ownShipHeadLineLenByMm, long otherShipHeadLineLenByMm)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x125, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ownShipHeadLineLenByMm, otherShipHeadLineLenByMm);
	}
	BOOL SelectGeoObjectByLineSection(long memMapPos, long layerPos, long innerLayerPos, long lineSectionStartGeoPoX, long lineSectionStartGeoPoY, long lineSectionEndGeoPoX, long lineSectionEndGeoPoY, float selDistByMeter, BOOL * pbRetResult)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_R4 VTS_PBOOL ;
		InvokeHelper(0x126, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, memMapPos, layerPos, innerLayerPos, lineSectionStartGeoPoX, lineSectionStartGeoPoY, lineSectionEndGeoPoX, lineSectionEndGeoPoY, selDistByMeter, pbRetResult);
		return result;
	}
	long QueryInMapLayerByFieldCondtion(long memMapPos, long layerPos, long conditionFieldPos, long conditionType, LPCTSTR conditionVal, BSTR * pRetResultObjectPoses)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_BSTR VTS_PBSTR ;
		InvokeHelper(0x127, DISPATCH_METHOD, VT_I4, (void*)&result, parms, memMapPos, layerPos, conditionFieldPos, conditionType, conditionVal, pRetResultObjectPoses);
		return result;
	}
	void SetScaleBarPosition(BOOL bUseDefaultPosition, long setPositionX, long setPositionY)
	{
		static BYTE parms[] = VTS_BOOL VTS_I4 VTS_I4 ;
		InvokeHelper(0x128, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bUseDefaultPosition, setPositionX, setPositionY);
	}
	void SetIfOnAutoLoadMapMode(BOOL bSetOnAutoLoadMapMode)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x129, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bSetOnAutoLoadMapMode);
	}
	BOOL SetRouteName(long routeID, LPCTSTR routeName)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_BSTR ;
		InvokeHelper(0x12a, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, routeID, routeName);
		return result;
	}
	BOOL SetWayPointShowText(long wpPos, BOOL bSetText, LPCTSTR strText, BOOL bSetFontSize, long fontSize, BOOL bSetColor, long fontColor)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_BOOL VTS_BSTR VTS_BOOL VTS_I4 VTS_BOOL VTS_I4 ;
		InvokeHelper(0x12b, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, wpPos, bSetText, strText, bSetFontSize, fontSize, bSetColor, fontColor);
		return result;
	}
	BOOL IsGeoObjectNearPoint(long memMapPos, long layerPos, long innerLayerPos, long destPointGeoX, long destPointGeoY, long nearJudgeDistByMeter, BOOL * pRetIfNear)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_PBOOL ;
		InvokeHelper(0x12c, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, memMapPos, layerPos, innerLayerPos, destPointGeoX, destPointGeoY, nearJudgeDistByMeter, pRetIfNear);
		return result;
	}
	void SetDeviceID(long deviceID)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x12d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, deviceID);
	}
	BOOL IsLineSectionCrossPolygon(long lineSectionStartPoX, long lineSectionStartPoY, long lineSectionEndPoX, long lineSectionEndPoY, BSTR * pPolygonPoints, long polygonPoCount, BOOL bInputGeoOrScrnCoor, BOOL * pRetResult)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_PBSTR VTS_I4 VTS_BOOL VTS_PBOOL ;
		InvokeHelper(0x12e, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, lineSectionStartPoX, lineSectionStartPoY, lineSectionEndPoX, lineSectionEndPoY, pPolygonPoints, polygonPoCount, bInputGeoOrScrnCoor, pRetResult);
		return result;
	}
	BOOL OverViewGeoRect(long leftDownGeoPoX, long leftDownGeoPoY, long rightUpGeoPoX, long rightUpGeoPoY)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x12f, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, leftDownGeoPoX, leftDownGeoPoY, rightUpGeoPoX, rightUpGeoPoY);
		return result;
	}
	BOOL RefreshDynamicDrawerForScrnDC(long scrnHdc, long scrnWidth, long scrnHeight)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x130, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, scrnHdc, scrnWidth, scrnHeight);
		return result;
	}
	void SetActiveDrawer(BOOL bSetMainOrDynamicDrawerActive)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x131, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bSetMainOrDynamicDrawerActive);
	}
	BOOL tmDrawGeoObject(long layerPos, long innerLayerObjPos)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x132, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, layerPos, innerLayerObjPos);
		return result;
	}
	long GetLibMapPosInMem(long libMapPos)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x133, DISPATCH_METHOD, VT_I4, (void*)&result, parms, libMapPos);
		return result;
	}
	BOOL IsLibMapLoaded(long libMapPos, BOOL * pbRetResult)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_PBOOL ;
		InvokeHelper(0x134, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, libMapPos, pbRetResult);
		return result;
	}
	BOOL tmCopyObject(long layerPos, long innerLayerPos, long dstLayerPos)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x135, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, layerPos, innerLayerPos, dstLayerPos);
		return result;
	}
	BOOL tmSetObjectAsSymbolLineObject(long layerPos, long innerLayerObjPos, BOOL bSetToBeSymbolObjectOrNot)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_BOOL ;
		InvokeHelper(0x136, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, layerPos, innerLayerObjPos, bSetToBeSymbolObjectOrNot);
		return result;
	}
	BOOL tmSetObjectShowOrNot(long layerPos, long innerLayerObjPos, BOOL bShowOrNot)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_BOOL ;
		InvokeHelper(0x137, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, layerPos, innerLayerObjPos, bShowOrNot);
		return result;
	}
	BOOL tmGetObjectIsSymbolLineObject(long layerPos, long innerLayerObjPos, BOOL * pbSymbolLineObject)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_PBOOL ;
		InvokeHelper(0x138, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, layerPos, innerLayerObjPos, pbSymbolLineObject);
		return result;
	}
	BOOL tmGetLineObjectSpecialType(long layerPos, long innerLayerObjPos, long * retType)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_PI4 ;
		InvokeHelper(0x139, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, layerPos, innerLayerObjPos, retType);
		return result;
	}
	BOOL tmSetObjectDynamicObjectOrNot(long layerPos, long innerLayerObjPos, BOOL bDynamicObjectOrNot)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_BOOL ;
		InvokeHelper(0x13a, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, layerPos, innerLayerObjPos, bDynamicObjectOrNot);
		return result;
	}
	void tmAppendLayer(long layerType)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x13b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, layerType);
	}
	BOOL tmSetLayerName(long layerPos, LPCTSTR strLayerName)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_BSTR ;
		InvokeHelper(0x13c, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, layerPos, strLayerName);
		return result;
	}
	BOOL tmDeleteLayer(long delLayerPos)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x13d, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, delLayerPos);
		return result;
	}
	BOOL SelectObjectByScrnPo(long memMapPos, long layerPos, long innerLayerObjPos, long scrnPoX, long scrnPoY, BOOL * pRetBeSelect)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_PBOOL ;
		InvokeHelper(0x13e, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, memMapPos, layerPos, innerLayerObjPos, scrnPoX, scrnPoY, pRetBeSelect);
		return result;
	}
	float GetAreaOfGeoRegion(long regionPoCount, BSTR * geoRegionPoints)
	{
		float result;
		static BYTE parms[] = VTS_I4 VTS_PBSTR ;
		InvokeHelper(0x13f, DISPATCH_METHOD, VT_R4, (void*)&result, parms, regionPoCount, geoRegionPoints);
		return result;
	}
	BOOL SetOneMapShowMode(BOOL bSetOnOrCancelOneMapMode, long libMapPos)
	{
		BOOL result;
		static BYTE parms[] = VTS_BOOL VTS_I4 ;
		InvokeHelper(0x140, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, bSetOnOrCancelOneMapMode, libMapPos);
		return result;
	}
	BOOL tmGetPointObjectStyle(long layerPos, long innerLayerObjPos, long * pRetReferLibSymbolId, long * pRetTrueTypeSymbolColor, long * pRetTrueTypeSymbolSize, BSTR * pRetStrText, BSTR * pRetStrFontName, long * pRetFontHeight, long * pRetFontColor, BOOL * pRetIsBold, BOOL * pRetIsItalic, long * pRetSymbolOffsetX, long * pRetSymbolOffsetY, long * pRetTextOffsetX, long * pRetTextOffsetY)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_PI4 VTS_PI4 VTS_PI4 VTS_PBSTR VTS_PBSTR VTS_PI4 VTS_PI4 VTS_PBOOL VTS_PBOOL VTS_PI4 VTS_PI4 VTS_PI4 VTS_PI4 ;
		InvokeHelper(0x141, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, layerPos, innerLayerObjPos, pRetReferLibSymbolId, pRetTrueTypeSymbolColor, pRetTrueTypeSymbolSize, pRetStrText, pRetStrFontName, pRetFontHeight, pRetFontColor, pRetIsBold, pRetIsItalic, pRetSymbolOffsetX, pRetSymbolOffsetY, pRetTextOffsetX, pRetTextOffsetY);
		return result;
	}
	BOOL tmGetLineObjectStyle(long layerPos, long innerLayerObjPos, BOOL * pRetIsTakeSolidLnSytle, BOOL * pRetIsTakeDashLnSytle, long * pRetLnWidth, long * pRetLnColor, long * pRetDashCycle, long * pRetDashLen, BSTR * pRetStrText, BSTR * pRetStrFontName, long * pRetFontHeight, long * pRetFontColor, BOOL * pRetIsBold, BOOL * pRetIsItalic, long * pRetTextOffsetX, long * pRetTextOffsetY, BOOL * pRetIsShowTextAlongLine)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_PBOOL VTS_PBOOL VTS_PI4 VTS_PI4 VTS_PI4 VTS_PI4 VTS_PBSTR VTS_PBSTR VTS_PI4 VTS_PI4 VTS_PBOOL VTS_PBOOL VTS_PI4 VTS_PI4 VTS_PBOOL ;
		InvokeHelper(0x142, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, layerPos, innerLayerObjPos, pRetIsTakeSolidLnSytle, pRetIsTakeDashLnSytle, pRetLnWidth, pRetLnColor, pRetDashCycle, pRetDashLen, pRetStrText, pRetStrFontName, pRetFontHeight, pRetFontColor, pRetIsBold, pRetIsItalic, pRetTextOffsetX, pRetTextOffsetY, pRetIsShowTextAlongLine);
		return result;
	}
	BOOL tmGetFaceObjectStyle(long layerPos, long innerLayerObjPos, long * pRetLibFaceStyleID, BOOL * pRetIsFillColor, long * pRetFaceColor, long * pRetTransparency, BSTR * pRetStrText, BSTR * pRetStrFontName, long * pRetFontHeight, long * pRetFontColor, BOOL * pRetIsBold, BOOL * pRetIsItalic, long * pRetTextOffsetX, long * pRetTextOffsetY)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_PI4 VTS_PBOOL VTS_PI4 VTS_PI4 VTS_PBSTR VTS_PBSTR VTS_PI4 VTS_PI4 VTS_PBOOL VTS_PBOOL VTS_PI4 VTS_PI4 ;
		InvokeHelper(0x143, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, layerPos, innerLayerObjPos, pRetLibFaceStyleID, pRetIsFillColor, pRetFaceColor, pRetTransparency, pRetStrText, pRetStrFontName, pRetFontHeight, pRetFontColor, pRetIsBold, pRetIsItalic, pRetTextOffsetX, pRetTextOffsetY);
		return result;
	}
	BOOL GetS63UserPermit(LPCTSTR strDeviceID, LPCTSTR strManufactureID, LPCTSTR strManufacturerKey, BSTR * retStrUserPermit)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_PBSTR ;
		InvokeHelper(0x144, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, strDeviceID, strManufactureID, strManufacturerKey, retStrUserPermit);
		return result;
	}
	BOOL RenameLibMap(short libMapPos, LPCTSTR pStrNewMapName)
	{
		BOOL result;
		static BYTE parms[] = VTS_I2 VTS_BSTR ;
		InvokeHelper(0x145, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, libMapPos, pStrNewMapName);
		return result;
	}
	BOOL DrawDashLine(BSTR * pBstrLnPoints, long lnPoCount, long lnWidth, long lnColor, long dashCycle, long dashLen)
	{
		BOOL result;
		static BYTE parms[] = VTS_PBSTR VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x146, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, pBstrLnPoints, lnPoCount, lnWidth, lnColor, dashCycle, dashLen);
		return result;
	}
	BOOL SetSoundingSetPointDepth(long memMapPos, long lyrPos, long innerLyrObjPos, long pointPosInSoundingSet, float newDepth)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_R4 ;
		InvokeHelper(0x147, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, memMapPos, lyrPos, innerLyrObjPos, pointPosInSoundingSet, newDepth);
		return result;
	}
	void SetSoundingShowColor(BOOL bSetSoundingColor, long soundingColor1, long soundingColor2)
	{
		static BYTE parms[] = VTS_BOOL VTS_I4 VTS_I4 ;
		InvokeHelper(0x148, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bSetSoundingColor, soundingColor1, soundingColor2);
	}
	BOOL SetObjectAttrValueString(long memMapPos, long layerPos, long innerLayerObjPos, long attrPos, LPCTSTR srcAttrValString)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_BSTR ;
		InvokeHelper(0x149, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, memMapPos, layerPos, innerLayerObjPos, attrPos, srcAttrValString);
		return result;
	}
	BOOL IsLibMapSelectedByLineSection(long nLibMapPos, long lnSectionStartGeoPoX, long lnSectionStartGeoPoY, long lnSectionEndGeoPoX, long lnSectionEndGeoPoY)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x14a, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, nLibMapPos, lnSectionStartGeoPoX, lnSectionStartGeoPoY, lnSectionEndGeoPoX, lnSectionEndGeoPoY);
		return result;
	}
	long GetLibMapPosByMapFileName(LPCTSTR strMapFileName)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x14b, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strMapFileName);
		return result;
	}
	void SetIfUseSafeDepthLineDectect(BOOL bSetSafeLineDetectOnOrOff, BOOL bShowDetectSafeLine)
	{
		static BYTE parms[] = VTS_BOOL VTS_BOOL ;
		InvokeHelper(0x14c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bSetSafeLineDetectOnOrOff, bShowDetectSafeLine);
	}
	BOOL EncryptYmcFile(LPCTSTR strSrcFileName, LPCTSTR strDstFileName, long iKeyNumber)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_I4 ;
		InvokeHelper(0x14d, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, strSrcFileName, strDstFileName, iKeyNumber);
		return result;
	}
	BOOL DecryptYmcFile(LPCTSTR strSrcFileName, LPCTSTR strDstFileName, long iKeyNumber)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_I4 ;
		InvokeHelper(0x14e, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, strSrcFileName, strDstFileName, iKeyNumber);
		return result;
	}
	void SetScaleBarUnit(BOOL bUnitNmOrKm)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x14f, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bUnitNmOrKm);
	}
	void SetIfUseTextOutLineEffect(BOOL bUseOrNot)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x150, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bUseOrNot);
	}
	long GetLayerObjectAttrPosByToken(long memMapPos, long layerPos, LPCTSTR strAttrToken)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_BSTR ;
		InvokeHelper(0x151, DISPATCH_METHOD, VT_I4, (void*)&result, parms, memMapPos, layerPos, strAttrToken);
		return result;
	}
	void SetDectectSafeDepthBufferWidth(float bufferWidthByMeter)
	{
		static BYTE parms[] = VTS_R4 ;
		InvokeHelper(0x152, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bufferWidthByMeter);
	}
	BOOL IsShipCrossingSafeCenterLine(long shipGeoX, long shipGeoY, float approchDistThrshldByMeter)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_R4 ;
		InvokeHelper(0x153, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, shipGeoX, shipGeoY, approchDistThrshldByMeter);
		return result;
	}
	float CaculateScale(long centerMapPoGeoX, long centerMapPoGeoY, long distScreenByPixel, float distMapByMeter)
	{
		float result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_R4 ;
		InvokeHelper(0x154, DISPATCH_METHOD, VT_R4, (void*)&result, parms, centerMapPoGeoX, centerMapPoGeoY, distScreenByPixel, distMapByMeter);
		return result;
	}
	void tmSetLayerSaveToFileOrNot(long layerPos, BOOL bSaveOrNot)
	{
		static BYTE parms[] = VTS_I4 VTS_BOOL ;
		InvokeHelper(0x155, DISPATCH_METHOD, VT_EMPTY, NULL, parms, layerPos, bSaveOrNot);
	}
	void SetMapScreenSize(long scrnWidth, long scrnHeight)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x156, DISPATCH_METHOD, VT_EMPTY, NULL, parms, scrnWidth, scrnHeight);
	}
	void GetEncScrnPoFromGeoPo(long geoX, long geoY, long * retScrnPoX, long * retScrnPoY)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_PI4 VTS_PI4 ;
		InvokeHelper(0x157, DISPATCH_METHOD, VT_EMPTY, NULL, parms, geoX, geoY, retScrnPoX, retScrnPoY);
	}
	void GetGeoPoFromEncScrnPo(long scrnPoX, long scrnPoY, long * retGeoPoX, long * retGeoPoY)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_PI4 VTS_PI4 ;
		InvokeHelper(0x158, DISPATCH_METHOD, VT_EMPTY, NULL, parms, scrnPoX, scrnPoY, retGeoPoX, retGeoPoY);
	}
	void SetIfDrawOtherVesselUseGdiPlus(long bUseGDIPlus)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x159, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bUseGDIPlus);
	}
	long GetBackGroundColor()
	{
		long result;
		InvokeHelper(0x15a, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long GetGridLineParams(long * retLineColor, long * retLonTextColor, long * retLatTextColor, long * retFontSize)
	{
		long result;
		static BYTE parms[] = VTS_PI4 VTS_PI4 VTS_PI4 VTS_PI4 ;
		InvokeHelper(0x15b, DISPATCH_METHOD, VT_I4, (void*)&result, parms, retLineColor, retLonTextColor, retLatTextColor, retFontSize);
		return result;
	}
	void SetEncColor(LPCTSTR strColorToken, short r, short g, short b)
	{
		static BYTE parms[] = VTS_BSTR VTS_I2 VTS_I2 VTS_I2 ;
		InvokeHelper(0x15c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, strColorToken, r, g, b);
	}
	void GetScrnPointsFromGeoPoints(long poCount, BSTR * geoPoints, BSTR * retScrnPoints)
	{
		static BYTE parms[] = VTS_I4 VTS_PBSTR VTS_PBSTR ;
		InvokeHelper(0x15d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, poCount, geoPoints, retScrnPoints);
	}
	void GeoCoor2PlaneCoor(long geoCoorX, long geoCoorY, long * pPlaneCoorX, long * pPlaneCoorY)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_PI4 VTS_PI4 ;
		InvokeHelper(0x15e, DISPATCH_METHOD, VT_EMPTY, NULL, parms, geoCoorX, geoCoorY, pPlaneCoorX, pPlaneCoorY);
	}
	void PlaneCoor2GeoCoor(long planeCoorX, long planeCoorY, long * pRetGeoCoorX, long * pRetGeoCoorY)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_PI4 VTS_PI4 ;
		InvokeHelper(0x15f, DISPATCH_METHOD, VT_EMPTY, NULL, parms, planeCoorX, planeCoorY, pRetGeoCoorX, pRetGeoCoorY);
	}
	void SetObjectShowOrNot(long memMapPos, long layerPos, long innerLayerObjPos, BOOL bShowOrNot)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_BOOL ;
		InvokeHelper(0x160, DISPATCH_METHOD, VT_EMPTY, NULL, parms, memMapPos, layerPos, innerLayerObjPos, bShowOrNot);
	}
	void SetLayerSubStyleParams(long memMapPos, long layerPos, long layerSubStylePos, BOOL bShowOrNot, BOOL bSetColor, long newColor)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_BOOL VTS_BOOL VTS_I4 ;
		InvokeHelper(0x161, DISPATCH_METHOD, VT_EMPTY, NULL, parms, memMapPos, layerPos, layerSubStylePos, bShowOrNot, bSetColor, newColor);
	}
	void SetFirstStandardParrel(float stdParrelLatByDeg)
	{
		static BYTE parms[] = VTS_R4 ;
		InvokeHelper(0x162, DISPATCH_METHOD, VT_EMPTY, NULL, parms, stdParrelLatByDeg);
	}
	void SetOwnShipGpsPosition(float offsetXByMeter, float offsetYByMeter)
	{
		static BYTE parms[] = VTS_R4 VTS_R4 ;
		InvokeHelper(0x163, DISPATCH_METHOD, VT_EMPTY, NULL, parms, offsetXByMeter, offsetYByMeter);
	}
	BOOL GetDrawDCBits(BSTR * retColorBits)
	{
		BOOL result;
		static BYTE parms[] = VTS_PBSTR ;
		InvokeHelper(0x164, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, retColorBits);
		return result;
	}
	void GetDeviceIDForLicSvr(BSTR * retStrDevId)
	{
		static BYTE parms[] = VTS_PBSTR ;
		InvokeHelper(0x165, DISPATCH_METHOD, VT_EMPTY, NULL, parms, retStrDevId);
	}
	void SetLicenceKeyFromSvr(LPWSTR strKey)
	{
		static BYTE parms[] = VTS_UNKNOWN ;
		InvokeHelper(0x166, DISPATCH_METHOD, VT_EMPTY, NULL, parms, strKey);
	}
	BOOL SetOtherVesselSelectedOrNot(long otherVesselNum, BOOL bSelectedOrNot)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_BOOL ;
		InvokeHelper(0x167, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, otherVesselNum, bSelectedOrNot);
		return result;
	}
	BOOL GetOtherVesselSelectedOrNot(long otherVesselNum)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x168, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, otherVesselNum);
		return result;
	}
	void SetSelectedShipShowBoxStyle(long iBoxSize, long iBoxlegLen, long iBoxlegWidth, long mBoxColor)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x169, DISPATCH_METHOD, VT_EMPTY, NULL, parms, iBoxSize, iBoxlegLen, iBoxlegWidth, mBoxColor);
	}
	BOOL SetOtherVesselCurrentInfo(long otherVesselPos, long currentGeoPoX, long currentGeoPoY, float heading, float courseOverGround, float courseThrghWater, float speedOverGround, float speedThrghWater, long * pTime, BSTR * pExtAttrs, long extAttrLen)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_R4 VTS_R4 VTS_R4 VTS_R4 VTS_R4 VTS_PI4 VTS_PBSTR VTS_I4 ;
		InvokeHelper(0x16a, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, otherVesselPos, currentGeoPoX, currentGeoPoY, heading, courseOverGround, courseThrghWater, speedOverGround, speedThrghWater, pTime, pExtAttrs, extAttrLen);
		return result;
	}
	BOOL GetOtherVesselCurrentInfo(long otherVesselPos, BOOL * pBeArpaOrAisTarget, long * pCurrentGeoPoX, long * pCurrentGeoPoY, float * pHeading, float * pCourseOverGround, float * pCourseThrghWater, float * pSpeedOverGround, float * pSpeedThrghWater, long * pTime, BSTR * pExtAttrs)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_PBOOL VTS_PI4 VTS_PI4 VTS_PR4 VTS_PR4 VTS_PR4 VTS_PR4 VTS_PR4 VTS_PI4 VTS_PBSTR ;
		InvokeHelper(0x16b, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, otherVesselPos, pBeArpaOrAisTarget, pCurrentGeoPoX, pCurrentGeoPoY, pHeading, pCourseOverGround, pCourseThrghWater, pSpeedOverGround, pSpeedThrghWater, pTime, pExtAttrs);
		return result;
	}
	long AddOtherVessels(BOOL bArpaOrAisTarget, long iShipCount, BSTR * pGeoPoints, BSTR * pHeadings, BSTR * pCourseOverGround, BSTR * pCourseThrghWater, BSTR * pSpeedOverGround, BSTR * pSpeedThrghWater, BSTR * pRetVesselsID, long iShipAisTypeID)
	{
		long result;
		static BYTE parms[] = VTS_BOOL VTS_I4 VTS_PBSTR VTS_PBSTR VTS_PBSTR VTS_PBSTR VTS_PBSTR VTS_PBSTR VTS_PBSTR VTS_I4 ;
		InvokeHelper(0x16c, DISPATCH_METHOD, VT_I4, (void*)&result, parms, bArpaOrAisTarget, iShipCount, pGeoPoints, pHeadings, pCourseOverGround, pCourseThrghWater, pSpeedOverGround, pSpeedThrghWater, pRetVesselsID, iShipAisTypeID);
		return result;
	}
	void AboutBox()
	{
		InvokeHelper(DISPID_ABOUTBOX, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	BOOL tmGetObjectShowOrNot(long layerPos, long innerLayerPos)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x16d, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, layerPos, innerLayerPos);
		return result;
	}
	void tmGetObjectGeoType(long layerPos, long innerLayerObjPos, long * geoType)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_PI4 ;
		InvokeHelper(0x16e, DISPATCH_METHOD, VT_EMPTY, NULL, parms, layerPos, innerLayerObjPos, geoType);
	}
	void GetTwoShipsDcpaAndTcpa(long firstShipGeoPoX, long firstShipGeoPoY, float firstShipSpeed, float firstShipDirection, long secondShipGeoPoX, long secondShipGeoPoY, float secondShipSpeed, float secondShipDirection, float * pDcpa, float * pTcpa)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_R4 VTS_R4 VTS_I4 VTS_I4 VTS_R4 VTS_R4 VTS_PR4 VTS_PR4 ;
		InvokeHelper(0x16f, DISPATCH_METHOD, VT_EMPTY, NULL, parms, firstShipGeoPoX, firstShipGeoPoY, firstShipSpeed, firstShipDirection, secondShipGeoPoX, secondShipGeoPoY, secondShipSpeed, secondShipDirection, pDcpa, pTcpa);
	}
	BOOL SaveHistoryTracksToFile()
	{
		BOOL result;
		InvokeHelper(0x170, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	long GetHistoryTrackPointsByTime(long checkOffsetTime, BSTR * pStartTime, BSTR * pEndTime, BSTR * pHistoryStartTime, BSTR * pRetTrackPointArray, long * pTrackPoCount)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_PBSTR VTS_PBSTR VTS_PBSTR VTS_PBSTR VTS_PI4 ;
		InvokeHelper(0x172, DISPATCH_METHOD, VT_I4, (void*)&result, parms, checkOffsetTime, pStartTime, pEndTime, pHistoryStartTime, pRetTrackPointArray, pTrackPoCount);
		return result;
	}
	void GetNineNineBoxCenterGeoPo(long * pGeoPoX, long * pGeoPoY, BOOL * pDrawOrNot)
	{
		static BYTE parms[] = VTS_PI4 VTS_PI4 VTS_PBOOL ;
		InvokeHelper(0x173, DISPATCH_METHOD, VT_EMPTY, NULL, parms, pGeoPoX, pGeoPoY, pDrawOrNot);
	}
	void SetShowNineNineBoxOrNot(BOOL bShowOrNot)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x174, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bShowOrNot);
	}
	void SetNineNineBoxCenterGeoPo(long geoPoX, long geoPoY)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x175, DISPATCH_METHOD, VT_EMPTY, NULL, parms, geoPoX, geoPoY);
	}
	void SetDrawNineNineBoxStyle(long mMaxBoxColor, long mMidBoxColor, long mMinBoxColor, long mNameColor)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x176, DISPATCH_METHOD, VT_EMPTY, NULL, parms, mMaxBoxColor, mMidBoxColor, mMinBoxColor, mNameColor);
	}
	BOOL GetNineNineNumberByGeoPo(long geoPoX, long geoPoY, BSTR * pStrNumberValue)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_PBSTR ;
		InvokeHelper(0x177, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, geoPoX, geoPoY, pStrNumberValue);
		return result;
	}
	BOOL SaveMemScrnToImageFile(long imageType, long saveImgScrnLeft, long saveImgScrnTop, long saveImgScrnWidth, long saveImgScrnHeight, LPCTSTR pStrFileName)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_BSTR ;
		InvokeHelper(0x178, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, imageType, saveImgScrnLeft, saveImgScrnTop, saveImgScrnWidth, saveImgScrnHeight, pStrFileName);
		return result;
	}
	void GetPlaneCoorFromGeoCoor(long geoCoorX, long geoCoorY, long * pPlaneCoorX, long * pPlaneCoorY)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_PI4 VTS_PI4 ;
		InvokeHelper(0x179, DISPATCH_METHOD, VT_EMPTY, NULL, parms, geoCoorX, geoCoorY, pPlaneCoorX, pPlaneCoorY);
	}
	void GetGeoPoByPlanePo(long planePoX, long planePoY, long * retGeoPoX, long * retGeoPoY)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_PI4 VTS_PI4 ;
		InvokeHelper(0x17a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, planePoX, planePoY, retGeoPoX, retGeoPoY);
	}
	BOOL IsGeoPointNearObjectEdge(long geoPoX, long geoPoY, long layerPos, long inLayerObjPos, long nearJudgeDistByMeter)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x17b, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, geoPoX, geoPoY, layerPos, inLayerObjPos, nearJudgeDistByMeter);
		return result;
	}
	BOOL tmAddLayerAttribute(long layerPos, long nDataType, LPCTSTR attrName)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_BSTR ;
		InvokeHelper(0x17c, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, layerPos, nDataType, attrName);
		return result;
	}
	BOOL tmSetLineLayerStyleReferLib(LPCTSTR strStyleSelectCondition, long layerPos, long simpleLineType, long dashCycle, long dashLen, long libLineStyleID, BOOL bSetColor, long lineColor, long lineWidth, BOOL bSetText, BOOL bTakeText, LPCTSTR strTextFormat, LPCTSTR strFontName, long fontHeight, long fontColor, BOOL bBold, BOOL bItalic, BOOL bShowTextAlongLine, long textOffsetX, long textOffsetY)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_BOOL VTS_I4 VTS_I4 VTS_BOOL VTS_BOOL VTS_BSTR VTS_BSTR VTS_I4 VTS_I4 VTS_BOOL VTS_BOOL VTS_BOOL VTS_I4 VTS_I4 ;
		InvokeHelper(0x17e, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, strStyleSelectCondition, layerPos, simpleLineType, dashCycle, dashLen, libLineStyleID, bSetColor, lineColor, lineWidth, bSetText, bTakeText, strTextFormat, strFontName, fontHeight, fontColor, bBold, bItalic, bShowTextAlongLine, textOffsetX, textOffsetY);
		return result;
	}
	BOOL tmSetFaceLayerStyleReferLib(LPCTSTR strStyleSelectCondition, long layerPos, BOOL bSetFillStyle, long libFaceStyleID, BOOL bSetFillColor, long fillColor, long transparency, BOOL bSetPatternColor, long patternColor, BOOL bSetBorderLineStyle, long simpleLineType, long dashCycle, long dashLen, long libLineStyleID, BOOL bSetColor, long lineColor, long lineWidth, BOOL bSetText, BOOL bTakeText, LPCTSTR pStrTextFormat, LPCTSTR pStrFontName, long fontHeight, long fontColor, BOOL bIsBold, BOOL bIsItalic, BOOL bAtCenterOrBottom, long textOffsetX, long textOffsetY)
	{
		BOOL result;
		static BYTE parms[] = VTS_BSTR VTS_I4 VTS_BOOL VTS_I4 VTS_BOOL VTS_I4 VTS_I4 VTS_BOOL VTS_I4 VTS_BOOL VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_BOOL VTS_I4 VTS_I4 VTS_BOOL VTS_BOOL VTS_BSTR VTS_BSTR VTS_I4 VTS_I4 VTS_BOOL VTS_BOOL VTS_BOOL VTS_I4 VTS_I4 ;
		InvokeHelper(0x17f, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, strStyleSelectCondition, layerPos, bSetFillStyle, libFaceStyleID, bSetFillColor, fillColor, transparency, bSetPatternColor, patternColor, bSetBorderLineStyle, simpleLineType, dashCycle, dashLen, libLineStyleID, bSetColor, lineColor, lineWidth, bSetText, bTakeText, pStrTextFormat, pStrFontName, fontHeight, fontColor, bIsBold, bIsItalic, bAtCenterOrBottom, textOffsetX, textOffsetY);
		return result;
	}
	BOOL tmSetPointLayerStyleReferLib(long layerPos, LPCTSTR strStyleSelectCondition, long libSymbolID, BOOL bSetColor, long newSymbolColor, float zoomSymbolScale, long rotateSymbolByDegree, BOOL bSetText, BOOL bTakeText, LPCTSTR strTextFormat, LPCTSTR strFontName, long fontHeight, long textColor, BOOL bBold, BOOL bItalic, long textHoriJust, long textVertJust, long txtOffsetX, long txtOffsetY)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_BSTR VTS_I4 VTS_BOOL VTS_I4 VTS_R4 VTS_I4 VTS_BOOL VTS_BOOL VTS_BSTR VTS_BSTR VTS_I4 VTS_I4 VTS_BOOL VTS_BOOL VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x180, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, layerPos, strStyleSelectCondition, libSymbolID, bSetColor, newSymbolColor, zoomSymbolScale, rotateSymbolByDegree, bSetText, bTakeText, strTextFormat, strFontName, fontHeight, textColor, bBold, bItalic, textHoriJust, textVertJust, txtOffsetX, txtOffsetY);
		return result;
	}
	void SetOtherVesselShowTextStartScale(long iScale)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x181, DISPATCH_METHOD, VT_EMPTY, NULL, parms, iScale);
	}
	void ForcelyRefreshMap()
	{
		InvokeHelper(0x182, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void SetMapHollowEffect(long centerGeoPoX, long centerGeoPoY, float radiusByMeter)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_R4 ;
		InvokeHelper(0x183, DISPATCH_METHOD, VT_EMPTY, NULL, parms, centerGeoPoX, centerGeoPoY, radiusByMeter);
	}
	void SetMapDelayEffect(long centerGeoPoX, long centerGeoPoY, float radiusByMeter)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_R4 ;
		InvokeHelper(0x184, DISPATCH_METHOD, VT_EMPTY, NULL, parms, centerGeoPoX, centerGeoPoY, radiusByMeter);
	}
	void CancelMapEffect()
	{
		InvokeHelper(0x185, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void GetMapEffectParameter(long * centerGeoPoX, long * centerGeoPoY, float * radiusByMeter)
	{
		static BYTE parms[] = VTS_PI4 VTS_PI4 VTS_PR4 ;
		InvokeHelper(0x186, DISPATCH_METHOD, VT_EMPTY, NULL, parms, centerGeoPoX, centerGeoPoY, radiusByMeter);
	}
	long GetMapEffect()
	{
		long result;
		InvokeHelper(0x187, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void SetMapEffectRadius(float radiusByMeter)
	{
		static BYTE parms[] = VTS_R4 ;
		InvokeHelper(0x188, DISPATCH_METHOD, VT_EMPTY, NULL, parms, radiusByMeter);
	}
	void SetIfShowNineNineBoxText(BOOL bShowOrNot)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x189, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bShowOrNot);
	}
	BOOL GetIfShowNineNineBoxText()
	{
		BOOL result;
		InvokeHelper(0x18a, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	BOOL GetObjectShowOrNot(long memMapPos, long layerPos, long innerLayerObjPos)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x18b, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, memMapPos, layerPos, innerLayerObjPos);
		return result;
	}
	BOOL IsOwnShipOffRoute(float offRouteDistLimitByMeter, float * pRetOffDistByMeter)
	{
		BOOL result;
		static BYTE parms[] = VTS_R4 VTS_PR4 ;
		InvokeHelper(0x18c, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, offRouteDistLimitByMeter, pRetOffDistByMeter);
		return result;
	}
	void SetVcfLayerDrawOrNot(long layerPos, BOOL bDrawOrNot)
	{
		static BYTE parms[] = VTS_I4 VTS_BOOL ;
		InvokeHelper(0x18d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, layerPos, bDrawOrNot);
	}
	BOOL GetVcfLayerDrawOrNot(long layerPos)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x18e, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, layerPos);
		return result;
	}
	BOOL GetMemMapIsArmsMap(long memMapPos)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x18f, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, memMapPos);
		return result;
	}
	void GetCurrentAimPoint(long * AimPointX, long * AimPointY)
	{
		static BYTE parms[] = VTS_PI4 VTS_PI4 ;
		InvokeHelper(0x190, DISPATCH_METHOD, VT_EMPTY, NULL, parms, AimPointX, AimPointY);
	}
	void SetIfOverlayLandMap(BOOL bOverlayLandMap, long curMapName)
	{
		static BYTE parms[] = VTS_BOOL VTS_I4 ;
		InvokeHelper(0x191, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bOverlayLandMap, curMapName);
	}
	void GetIfOverlayLandMap(BOOL * bOverlayLandMap, long * curMapName)
	{
		static BYTE parms[] = VTS_PBOOL VTS_PI4 ;
		InvokeHelper(0x192, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bOverlayLandMap, curMapName);
	}
	void SetIfShipOverlapOffsetShowOrHide(BOOL bOffSetShowOrHide)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x193, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bOffSetShowOrHide);
	}
	void SetDrawExpandPixel(long expandPixelX, long expandPixelY)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x194, DISPATCH_METHOD, VT_EMPTY, NULL, parms, expandPixelX, expandPixelY);
	}
	BOOL tmZoomLineObject(long layerPos, long objPos, long centerGeoPositionX, long centerGeoPositionY, float scaleValue)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_R4 ;
		InvokeHelper(0x195, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, layerPos, objPos, centerGeoPositionX, centerGeoPositionY, scaleValue);
		return result;
	}
	void tmSetObjectTextRotate(long layerPos, long objPos, float rotateAngle)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_R4 ;
		InvokeHelper(0x196, DISPATCH_METHOD, VT_EMPTY, NULL, parms, layerPos, objPos, rotateAngle);
	}
	float tmGetObjectTextRotate(long layerPos, long objPos)
	{
		float result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x197, DISPATCH_METHOD, VT_R4, (void*)&result, parms, layerPos, objPos);
		return result;
	}
	void SetIfHideShipInSimpleLandArea(BOOL bHide)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x198, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bHide);
	}
	void AddASimpleLandArea(BSTR * landAreaGeoPo, long poCount)
	{
		static BYTE parms[] = VTS_PBSTR VTS_I4 ;
		InvokeHelper(0x199, DISPATCH_METHOD, VT_EMPTY, NULL, parms, landAreaGeoPo, poCount);
	}
	void SetShipTrackStyle(BOOL bOwnOrOtherShip, long shipPos, BOOL bUseOwnTrackColor, long trackColor, long trackLineWide, BOOL bShowTrackPoint, long trackPointRadius, long trackPointFillColor)
	{
		static BYTE parms[] = VTS_BOOL VTS_I4 VTS_BOOL VTS_I4 VTS_I4 VTS_BOOL VTS_I4 VTS_I4 ;
		InvokeHelper(0x19a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bOwnOrOtherShip, shipPos, bUseOwnTrackColor, trackColor, trackLineWide, bShowTrackPoint, trackPointRadius, trackPointFillColor);
	}
	void GetYimaSdkVersion(BSTR * VersionNum, BSTR * TimeCreatedAt)
	{
		static BYTE parms[] = VTS_PBSTR VTS_PBSTR ;
		InvokeHelper(0x19b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, VersionNum, TimeCreatedAt);
	}
	float GetSoundingDepthByGeoPo(long geoPoX, long geoPoY, float fJudgeCircleByNm)
	{
		float result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_R4 ;
		InvokeHelper(0x19c, DISPATCH_METHOD, VT_R4, (void*)&result, parms, geoPoX, geoPoY, fJudgeCircleByNm);
		return result;
	}
	void SetIfOverlaySeaMap(BOOL bOverlaySeaMap)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x19d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bOverlaySeaMap);
	}
	long GetShipPosByGeoArea(long iCheckLenByMeter, BOOL bCheckAllShip, BSTR * arrShipId, long iCheckShipCount, BSTR * arrAreaGeoPo, long iAreaGeoPoCount, BSTR * retArrShipPos)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_BOOL VTS_PBSTR VTS_I4 VTS_PBSTR VTS_I4 VTS_PBSTR ;
		InvokeHelper(0x19e, DISPATCH_METHOD, VT_I4, (void*)&result, parms, iCheckLenByMeter, bCheckAllShip, arrShipId, iCheckShipCount, arrAreaGeoPo, iAreaGeoPoCount, retArrShipPos);
		return result;
	}
	long GetShipPosNearObject(long iMemMapPos, long iLayerPos, long iObjPos, long iCheckLenByMeter, BOOL bCheckAllShip, BSTR * arrShipId, long iCheckShipCount, BSTR * retArrShipPos)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_BOOL VTS_PBSTR VTS_I4 VTS_PBSTR ;
		InvokeHelper(0x19f, DISPATCH_METHOD, VT_I4, (void*)&result, parms, iMemMapPos, iLayerPos, iObjPos, iCheckLenByMeter, bCheckAllShip, arrShipId, iCheckShipCount, retArrShipPos);
		return result;
	}
	BOOL GetShipTrackShowOrNot(BOOL bSetOwnshipOrOtherVessel, long iOtherVesselID)
	{
		BOOL result;
		static BYTE parms[] = VTS_BOOL VTS_I4 ;
		InvokeHelper(0x1a0, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, bSetOwnshipOrOtherVessel, iOtherVesselID);
		return result;
	}
	BOOL ToolAddPointObj(long layerPos)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1a1, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, layerPos);
		return result;
	}
	BOOL ToolAddLineObj(long layerPos, long specialLineType)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x1a2, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, layerPos, specialLineType);
		return result;
	}
	BOOL ToolAddFaceObj(long layerPos, long specialFaceType)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x1a3, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, layerPos, specialFaceType);
		return result;
	}
	BOOL ToolMapMeasure(long toolType)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1a4, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, toolType);
		return result;
	}
	BOOL ToolMapEffect(BOOL bHollowOrDelay)
	{
		BOOL result;
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x1a5, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, bHollowOrDelay);
		return result;
	}
	BOOL ToolUserDefinedOperator()
	{
		BOOL result;
		InvokeHelper(0x1a6, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void ToolEndUserDefinedOperator()
	{
		InvokeHelper(0x1a7, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	BOOL ToolEditingUserObject(long layerPos, long objPos)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x1a8, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, layerPos, objPos);
		return result;
	}
	BOOL ToolIsNoOperate()
	{
		BOOL result;
		InvokeHelper(0x1a9, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	BOOL IsPointNearObjectEdge(long memMapPos, long layerPos, long inLayerObjPos, long destGeoPoX, long destGeoPoY, long nearJudgeDistByMeter, long * pCurDisPo2Obj, BOOL * bPoInFaceOrOut, long * retNearestGeoPoX, long * retNearestGeoPoY)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_PI4 VTS_PBOOL VTS_PI4 VTS_PI4 ;
		InvokeHelper(0x1aa, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, memMapPos, layerPos, inLayerObjPos, destGeoPoX, destGeoPoY, nearJudgeDistByMeter, pCurDisPo2Obj, bPoInFaceOrOut, retNearestGeoPoX, retNearestGeoPoY);
		return result;
	}
	void SetOwnShipShowSymbol(BOOL bUseStandS52Symbol, long symbolID, BOOL bRotateWithCourse, long tinySymbolID, float showTinySymbolScale)
	{
		static BYTE parms[] = VTS_BOOL VTS_I4 VTS_BOOL VTS_I4 VTS_R4 ;
		InvokeHelper(0x1ab, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bUseStandS52Symbol, symbolID, bRotateWithCourse, tinySymbolID, showTinySymbolScale);
	}
	BOOL SetRadarLineDataByPos(long iLinePos, BSTR * pArrLineData, long iCount)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_PBSTR VTS_I4 ;
		InvokeHelper(0x1ac, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, iLinePos, pArrLineData, iCount);
		return result;
	}
	BOOL SetRadarBaseInfo(long iLineCount, long iLineNodeCount, float fPerNodeLenByMeter, long mColor)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_R4 VTS_I4 ;
		InvokeHelper(0x1ad, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, iLineCount, iLineNodeCount, fPerNodeLenByMeter, mColor);
		return result;
	}
	void SetRadarCenterGeoPo(long centerGeoPoX, long centerGeoPoY)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x1ae, DISPATCH_METHOD, VT_EMPTY, NULL, parms, centerGeoPoX, centerGeoPoY);
	}
	void SetRadarShowState(BOOL bShowOrNot, BOOL bShowAllInfoOrFadingColor)
	{
		static BYTE parms[] = VTS_BOOL VTS_BOOL ;
		InvokeHelper(0x1af, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bShowOrNot, bShowAllInfoOrFadingColor);
	}
	void AdjustSoundingDepthByMeter(float fIncreaseDepthByMeter)
	{
		static BYTE parms[] = VTS_R4 ;
		InvokeHelper(0x1b0, DISPATCH_METHOD, VT_EMPTY, NULL, parms, fIncreaseDepthByMeter);
	}
	void DrawScaledMap(long destHDc, long destScrnPoX, long destScrnPoY, long destWidth, long destHeight)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x1b1, DISPATCH_METHOD, VT_EMPTY, NULL, parms, destHDc, destScrnPoX, destScrnPoY, destWidth, destHeight);
	}
	void ToolSetMapDragMode(BOOL bRealtimeDrag)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x1b2, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bRealtimeDrag);
	}
	void ToolSetMapScaledMode(BOOL bAnimationScaled, BOOL bCenterScaled)
	{
		static BYTE parms[] = VTS_BOOL VTS_BOOL ;
		InvokeHelper(0x1b3, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bAnimationScaled, bCenterScaled);
	}
	BOOL ToolClearCache()
	{
		BOOL result;
		InvokeHelper(0x1b4, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void ToolCancelAllOperation()
	{
		InvokeHelper(0x1b5, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void SetCurrentBrushTransparency(long transparency)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1b6, DISPATCH_METHOD, VT_EMPTY, NULL, parms, transparency);
	}


};
