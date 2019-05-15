#include "stdafx.h"
#include "YIMAENCHEAD.H" 
  
bool ConvertBstrToString(CHAR* pSrcStr, const BSTR_CHAR* pBstr, int size)//return the possible max size by BYTE of converted string
{	
	if (pSrcStr == NULL || pBstr == NULL)
		return false;

	int strSize = size;
	if (size == 0)
		strSize = wcslen(pBstr);

	WideCharToMultiByte(CP_ACP, 0, (WCHAR*)pBstr,
				strSize + 1, pSrcStr, 2 * strSize + 2, NULL, NULL); 

	return true;
}

bool ConvertStringToBstr(const CHAR* pSrcStr, BSTR_CHAR* pBstr, int size)//return the possible max size by BYTE of converted string
{	
	if (pSrcStr == NULL || pBstr == NULL)
		return false;

	int strSize = size;
	if (size == 0)
		strSize = strlen(pSrcStr);

	MultiByteToWideChar(CP_ACP, 0, pSrcStr,	strSize + 1, pBstr, strSize + 1);  
	pBstr[strSize] = 0;

	return true;
}

bool GetDegreeStringFromGeoCoor(TCHAR* retDegreeString, bool bLongOrLatiCoor, 
								INT coorVal, INT coorMultiFactor)
{ 
	if (retDegreeString == NULL || coorMultiFactor == 0)
		return false;

	double fArcByDegree = coorVal / (float)coorMultiFactor;  

#ifndef _UNICODE

	if (bLongOrLatiCoor)
	{ 
		if (fArcByDegree >= 0)
		{ 
			sprintf(retDegreeString, "%03d度%6.3f分E", (int)fArcByDegree, 
				60 * (fArcByDegree - (int)fArcByDegree)); 
		}
		else
		{
			fArcByDegree = -fArcByDegree;
			sprintf(retDegreeString, "%03d度%6.3f分W", (int)fArcByDegree, 
				60 * (fArcByDegree - (int)fArcByDegree)); 
		} 
	}
	else
	{
		if (fArcByDegree >= 0)
		{ 
			sprintf(retDegreeString, "%03d度%6.3f分N", (int)fArcByDegree, 
				60 * (fArcByDegree - (int)fArcByDegree)); 
		}
		else
		{
			fArcByDegree = -fArcByDegree;
			sprintf(retDegreeString, "%03d度%6.3f分S", (int)fArcByDegree, 
				60 * (fArcByDegree - (int)fArcByDegree)); 
		}
	}

#else

	if (bLongOrLatiCoor)
	{ 
		if (fArcByDegree >= 0)
		{ 
			wsprintf(retDegreeString, "%03d度%6.3f分E", (int)fArcByDegree, 
				60 * (fArcByDegree - (int)fArcByDegree)); 
		}
		else
		{
			fArcByDegree = -fArcByDegree;
			wsprintf("%03d度%6.3f分W", (int)fArcByDegree, 
				60 * (fArcByDegree - (int)fArcByDegree)); 
		} 
	}
	else
	{
		if (fArcByDegree >= 0)
		{ 
			wsprintf(retDegreeString, "%03d度%6.3f分N", (int)fArcByDegree, 
				60 * (fArcByDegree - (int)fArcByDegree)); 
		}
		else
		{
			fArcByDegree = -fArcByDegree;
			wsprintf(retDegreeString, "%03d度%6.3f分S", (int)fArcByDegree, 
				60 * (fArcByDegree - (int)fArcByDegree)); 
		}
	}

#endif 

	return true;
}




 