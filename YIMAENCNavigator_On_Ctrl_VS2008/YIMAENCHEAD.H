///////////////////////////// YIMAENCHEAD.H ////////////////////////////////////
/***************** Release Version 3.0.2 ***********************/
/***************** Release Data 2006-07-04 *********************/ 

#if _MSC_VER > 1000
#pragma once
#endif
////////////////////////// BASIC DATA TYPES ////////////////////////////////
#ifndef CHAR
typedef char CHAR;
#endif

#ifndef WCHAR
typedef wchar_t WCHAR;
#endif

#ifndef BSTR_CHAR
#define BSTR_CHAR WCHAR
#endif

#ifndef UCHAR
typedef unsigned char UCHAR ;
#endif

#ifndef UINT1
typedef UCHAR UINT1 ;
#endif

#ifndef INT1
typedef CHAR INT1;
#endif

#ifndef UINT2
typedef unsigned short UINT2;
#endif

#ifndef INT2
typedef short INT2;
#endif

#ifndef UINT4
typedef unsigned int UINT4;
#endif

#ifndef INT4
typedef int INT4;
#endif 

#ifndef UINT
typedef UINT4 UINT ;
#endif

#ifndef INT
typedef INT4 INT ;
#endif

#ifndef FLOAT
typedef float FLOAT;
#endif

#ifndef DOUBLE
typedef double DOUBLE;
#endif

#define UNI_GEO_COOR_MULTI_FACTOR 10000000

////////////////////////// MEM_GEO_OBJ_POS ////////////////////////////////
typedef struct MEM_GEO_OBJ_POS //geo object position in memory-maps
{
	int memMapPos;
	int layerPos;
	int innerLayerPos;

	MEM_GEO_OBJ_POS()
	{
		memMapPos = layerPos = innerLayerPos = -1; 
	};

	MEM_GEO_OBJ_POS(int mapPos, int lyrPos, int objPos)
	{
		memMapPos = mapPos;
		layerPos = lyrPos;
		innerLayerPos = objPos;
	};
}MAP_GEO_OBJ_POS;

////////////////////////// M_GEO_OBJ_POS ////////////////////////////////
typedef struct M_GEO_OBJ_POS //geo object position in a specific map
{
	int layerPos;
	int innerLayerObjectPos;

	M_GEO_OBJ_POS()
	{
		layerPos = -1;
		innerLayerObjectPos = -1;
	};

	M_GEO_OBJ_POS(int lyrPos, int inLyrPos)
	{
		layerPos = lyrPos;
		innerLayerObjectPos = inLyrPos;
	};
}M_GEO_OBJ_POS;

inline bool operator==(const M_GEO_OBJ_POS left, const M_GEO_OBJ_POS right)
{		
	return (left.layerPos==right.layerPos
		&& left.innerLayerObjectPos==right.innerLayerObjectPos );		
};

inline bool operator!=(const M_GEO_OBJ_POS left, const M_GEO_OBJ_POS right)
{		
	return (left.layerPos != right.layerPos
		|| left.innerLayerObjectPos != right.innerLayerObjectPos );		
};

////////////////////////// M_POINT //////////////////////////////////////
typedef struct M_POINT
{
	int x;
	int y;	

	M_POINT()
	{
		x = y = 0;
	};

	M_POINT(int poX, int poY)
	{
		x = poX;
		y = poY;
	};

	M_POINT& operator+=(const M_POINT& right)
	{
		x = x + right.x;
		y = y + right.y;

		return *this;
	};

	M_POINT& operator-=(const M_POINT& right)
	{
		x = x - right.x;
		y = y - right.y;

		return *this;
	};

	M_POINT& operator=(const M_POINT& right)
	{
		x = right.x;
		y = right.y;
		
		return *this;
	};
	
	M_POINT(const M_POINT& right)
	{ 
		x = right.x;
		y = right.y;
	};
}M_POINT;

inline bool operator==(const M_POINT left, const M_POINT right)
{	
	return (left.x==right.x && left.y==right.y);		
};

inline M_POINT operator-(const M_POINT left, const M_POINT right)
{	
	M_POINT po;
	po.x = left.x - right.x;
	po.y = left.y - right.y;
	return po;		
};

inline M_POINT operator+(const M_POINT left, const M_POINT right)
{	
	M_POINT po;
	po.x = left.x + right.x;
	po.y = left.y + right.y;
	return po;		
};


///////////////////////////M_TIME////////////////////////////////
typedef struct M_TIME
{
	int Year;
	int Month;
	int Day;
	int Hour;
	int Minute;
	int Second;

	M_TIME()
	{
		Year = 1900;
		Month = 1;
		Day = 1;
		Hour = 0;
		Minute = 0;
		Second = 0;
	}

	M_TIME(int year,int month,int day,int hour,int minute,int second)
	{
		Year = year;
		Month = month;
		Day = day;
		Hour = hour;
		Minute = minute;
		Second = second;
	}

	M_TIME& operator=(const M_TIME& right)
	{
		Year = right.Year;
		Month = right.Month;
		Day = right.Day;
		Hour = right.Hour;
		Minute = right.Minute;
		Second = right.Second;

		return *this;
	};
}M_TIME;


inline M_TIME time_t_2_M_TIME(time_t time)
{
	struct tm *newtime; 
	newtime = localtime(&time);
	M_TIME mtime;
	mtime.Year = 1900 + newtime->tm_year;
	mtime.Month = 1 + newtime->tm_mon;
	mtime.Day = newtime->tm_mday;
	mtime.Hour = newtime->tm_hour;
	mtime.Minute = newtime->tm_min;
	mtime.Second = newtime->tm_sec;
	return mtime;
}

inline time_t M_TIME_2_time_t(M_TIME mtime)
{
	struct tm newtime;  
	newtime.tm_year = mtime.Year - 1900;
	newtime.tm_mon = mtime.Month - 1;
	newtime.tm_mday = mtime.Day;
	newtime.tm_hour = mtime.Hour;
	newtime.tm_min = mtime.Minute;
	newtime.tm_sec = mtime.Second;
	return mktime(&newtime); 
}

//获取当前时间
inline M_TIME GetNowTime()
{ 
	SYSTEMTIME sysTime; 

	GetLocalTime(&sysTime);
	
	M_TIME mtime;
	mtime.Year = sysTime.wYear;
	mtime.Month = sysTime.wMonth;
	mtime.Day = sysTime.wDay;
	mtime.Hour = sysTime.wHour;
	mtime.Minute = sysTime.wMinute;
	mtime.Second = sysTime.wSecond; 

	return mtime;
}

//根据时间差获取时间
inline M_TIME GetTimeAfterSeconds(M_TIME startTime, int passedSeconds)
{
	time_t startTimet = M_TIME_2_time_t(startTime);
	startTimet = startTimet + passedSeconds;
	return time_t_2_M_TIME(startTimet);
}

/* 返回单位秒 */
inline int GetTimePassed(M_TIME startTime, M_TIME endTime)
{
	time_t startTimet = M_TIME_2_time_t(startTime);
	time_t endTimet = M_TIME_2_time_t(endTime);
	return difftime(endTimet, startTimet);
}

//////////////////////// TrackPoint ////////////////////////2015-07-01 added by zcz
typedef struct tag_TrackPoint
{
	M_POINT ptPoint;
	int iOffsetTime;
	float fSpeedOverGround;
	float fSpeedThrghWater;
	float fHeading;
	float fCourseOverGround;
	float fCourseThrghWater;
}TrackPoint;

////////////////////////// M_COLOR //////////////////////////////////////
typedef struct M_COLOR
{
	unsigned char r;
	unsigned char g;
	unsigned char b;	
	unsigned char reserve;  

	M_COLOR()
	{
		r = g = b = reserve = 0;
	};

	M_COLOR(unsigned char R, unsigned char G, unsigned char B)
	{
		r = R;
		g = G;
		b = B;
		reserve = 0;
	};

	M_COLOR(unsigned char R, unsigned char G, unsigned char B, unsigned char rsv)
	{
		r = R;
		g = G;
		b = B;
		reserve = rsv;
	};
}M_COLOR;

typedef int INT_COLOR;

inline bool operator==(const M_COLOR left, const M_COLOR right)
{		
	return( left.r==right.r && left.g==right.g && left.b==right.b);		
};

inline bool operator!=(const M_COLOR left, const M_COLOR right)
{		
	return !( left==right);		
};
 
#define M_RGB(r,g,b) r+(g<<8)+(b<<16)
#define M_COLOR_TO_INT(color) *((int*)&color)
#define M_INT_TO_COLOR(iColor) *((M_COLOR*)&iColor) 
#define M_GET_COLOR(r,g,b) M_INT_TO_COLOR(int(M_RGB(r,g,b)))

inline void M_SET_COLOR_BY_INT(M_COLOR& color, INT_COLOR intColor)
{	
	color = M_INT_TO_COLOR(intColor);  
};

inline void M_SET_COLOR_BY_RGB(M_COLOR& color, int r, int g, int b)
{	
	color.r = r;
	color.g = g;
	color.b = b;
	color.reserve = 0;
};
 
typedef struct MRECT
{
	int leftTopPointX;
	int leftTopPointY;
	int rightDownPointX;
	int rightDownPointY;

	MRECT()
	{
		leftTopPointX = leftTopPointY = 
			rightDownPointX = rightDownPointY = 0 ;
	};

	MRECT(int leftX, int topY, int rightX, int downY)
	{
		leftTopPointX = leftX;
		leftTopPointY = topY;
		rightDownPointX = rightX;
		rightDownPointY = downY;
	};

	MRECT(M_POINT leftTopPo, M_POINT rightBottomPo)
	{
		leftTopPointX = leftTopPo.x;
		leftTopPointY = leftTopPo.y;
		rightDownPointX = rightBottomPo.x;
		rightDownPointY = rightBottomPo.y;
	};

	MRECT& operator=(const MRECT& right)
	{
		leftTopPointX = right.leftTopPointX;
		leftTopPointY = right.leftTopPointY;
		rightDownPointX = right.rightDownPointX;
		rightDownPointY = right.rightDownPointY;

		return *this;
	};
}MRECT;

typedef enum HORI_JUST_OPTION
{
	HORI_JUST_CENTER = 1,
	HORI_JUST_RIGHT = 2,
	HORI_JUST_LEFT = 3
}HORI_JUST_OPTION;

typedef enum VERT_JUST_OPTION
{
	VERT_JUST_BOTTOM = 1,
	VERT_JUST_CENTER = 2,
	VERT_JUST_TOP = 3
}VERT_JUST_OPTION;

typedef enum DISPLAY_CATEGORY_NUM
{
	DISPLAY_BASE = 0,//基本显示
	DISPLAY_STANDARD = 1,//标准显示
	DISPLAY_ALL = 2, //全部显示
}DISPLAY_CATEGORY_NUM;

typedef enum ENC_COLOR_GROUP
{
	DAY_BRIGHT = 1,
	DAY_WHITEBACK = 2,
	DAY_BLACKBACK = 3,
	DUSK = 4,
	NIGHT = 5
}ENC_COLOR_GROUP;

typedef enum LAYER_GEO_TYPE
{ 
	LAYER_GEO_TYPE_NULL = 0,
	ALL_POINT = 1,
	ALL_LINE = 2,
	ALL_FACE = 3,
	MULTIPLE_GEO_TYPE = 5
}LAYER_GEO_TYPE;

typedef enum M_GEO_TYPE //物标的几何属性
{	
	TYPE_NULL = -1,
	TYPE_POINT = 0,
	TYPE_LINE = 2,          
	TYPE_FACE = 3,          
	TYPE_COMBINED_OBJECT = 10
}M_GEO_TYPE; 

typedef enum SPECIAL_LINE_TYPE
{
	NO_SPECIAL_TYPE = 0,
	RECTANGLE_LN_TYPE = 10, 
	CIRCLE_LN_TYPE = 20,
	ELLIPSE_LN_TYPE = 30,
	ARC_LN_TYPE = 40,
	PIE_LN_TYPE = 41,
	BOW_LN_TYPE = 42,	
	SECTOR_LN_TYPE = 50,
	CURVE_LN_TYPE = 60, 
	CURVE_LN_TYPE_WITH_HEAD_ARROW = 61, 
	CURVE_LN_TYPE_WITH_HAED_TAIL_ARROW = 62, 
	CLOSED_CURVE_LN_TYPE = 70,
	SINGLE_ARROW_LN_TYPE = 80,
	DOUBLE_ARROW_LN_TYPE = 90,
	THREE_ARROW_LN_TYPE = 100
}SPECIAL_LINE_TYPE;

typedef enum M_DATA_TYPE_ID //物标属性的基本数据类型
{
	M_NULL = 0,
	M_INT = 1,
	M_BOOL = 2,
	M_FLOAT = 3, 
	M_STRING = 4,  //with a maxinum length of 65536 byte, and a Chinese character is counted as 2 bytes 
	M_ENUM = 5,
	M_LIST = 6
}M_DATA_TYPE_ID; 

#define BOOL_BE_TRUE_STRING "y"
#define BOOL_BE_FALSE_STRING "n"

#define MAX_ATTR_VAL_STRING_LEN 65536
#define MAX_NAMES_LEN 255 

typedef enum MAP_FILE_TYPE
{
	S57BASE_FILE = 0,
	S57UPDATE_FILE = 1,
	YIMAP_FILE = 2
}MAP_FILE_TYPE; 

typedef UINT SHIP_ID;
#define INVALID_SHIP_ID -1

typedef UINT AIS_TYPE_ID;

#define MAX_WAY_POINT_COUNT_OF_ROUTE 100000

#define NAUTICAL_MILE_TO_METER_FACTOR 1852

#define MAP_TYPE_ENC "S57 ENC map"
#define MAP_TYPE_VCF "VCF map"

typedef enum UNDO_OPERATION_TYPE
{ 
	ADD_GEO_OBJ = 3,
	DEL_GEO_OBJ = 4,
	MOD_GEO_OBJ = 5
}UNDO_OPERATION_TYPE;

typedef enum MAP_NATIONAL_LANGUAGE
{
	LANG_ENG = 1,
	LANG_CHN = 2,
	LANG_JPN = 3,
	LANG_KOR = 4
}MAP_NATIONAL_LANGUAGE;

typedef enum DRAW_MAP_WITH_RADAR_MODEL
{
	DRAW_OBJ_OVER_RADAR = 1,
	DRAW_OBJ_UNDER_RADAR = 2,
	DRAW_ALL_OBJ = 3
}DRAW_MAP_WITH_RADAR_MODEL;

typedef enum FIELD_COMPARE_OPTION
{
	EQUAL = 0,
	UNEQUAL = 1, 
	GREATER = 2,//记录数据 大于 SEL_FIELD_CON 的 fieldVal
	GREATER_OR_EQUAL=3,
	SMALLER = 4,
	SMALLER_OR_EQUAL=5,
    CONTAIN = 6  //这两种用于字符串类型, CONTAIN表示记录字段包含条件制定的子字符串 
}FIELD_COMPARE_OPTION;

typedef enum MAP_EFFECT
{
	EFFECT_NONE = 1,	 //无效果  
	EFFECT_HOLLOW = 2,	 //空心效果
	EFFECT_DELAY = 3	 //延迟效果 
}MAP_EFFECT;

typedef struct M_COLOR_ATTENUATION
{
	int layerId;
	int objId;
	int decreaseValuePreSec;//每秒衰减的值
	bool bInAttenuation;//是否在衰减中
	M_COLOR_ATTENUATION()
	{
		layerId = -1;
		objId = -1;
		decreaseValuePreSec = 0;
		bInAttenuation = false;
	}
	M_COLOR_ATTENUATION(int iLayerId,int iObjId)
	{
		layerId = iLayerId;
		objId = iObjId;
		decreaseValuePreSec = 0;
		bInAttenuation = false;
	}
	M_COLOR_ATTENUATION(int iLayerId,int iObjId, int iDecreaseValuePreSec, bool bCurInAttenuation)
	{
		layerId = iLayerId;
		objId = iObjId;
		decreaseValuePreSec = iDecreaseValuePreSec;
		bInAttenuation = bCurInAttenuation;
	} 

}M_COLOR_ATTENUATION;
//////////////////////// UNICODE String <--> Multi-byte String /////////////////
bool ConvertBstrToString(CHAR* pSrcStr, const BSTR_CHAR* pBstr, int size = 0);
bool ConvertStringToBstr(const CHAR* pSrcStr, BSTR_CHAR* pBstr, int size = 0);

bool GetDegreeStringFromGeoCoor(TCHAR* retDegreeString, bool bLongOrLatiCoor, 
								INT coorVal, INT coorMultiFactor);