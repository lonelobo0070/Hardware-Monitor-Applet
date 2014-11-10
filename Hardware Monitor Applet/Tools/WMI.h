//-----------------------------------------------------------------
// WMI Object
// C++ Header - WMI.h - version v1.0 (2012-08-01)
//-----------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
#include <ctime>
#include <comdef.h>
#include <Wbemidl.h>
#include "../Defines.h"
#include <iomanip>
#include "Tool.h"

//-----------------------------------------------------------------
// Defines
//-----------------------------------------------------------------
#define _WIN32_DCOM
# pragma comment(lib, "wbemuuid.lib")
using namespace std;

//-----------------------------------------------------------------
// WMI Class
//-----------------------------------------------------------------
class WMI : public Tool
{
public:
	//---------------------------
	// Constructor(s)
	//---------------------------
	WMI();

	//---------------------------
	// Destructor
	//---------------------------
	virtual ~WMI(void);

	//---------------------------
	// General Methods
	//---------------------------
	QVector<HardwareSensor> getAllSensors();
	MonitorSystem getMonitorSystem();

private:
	//---------------------------
	// Private Methods
	//---------------------------
	void connect();

	//--------------------------
	// Datamembers
	//--------------------------
	IWbemLocator *pLoc_;
	IWbemServices *pSvc_;
	IEnumWbemClassObject* pEnumerator_;
	IWbemClassObject *pclsObj_;
	HRESULT hres_;

	// -------------------------
	// Disabling default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, these declarations are deliberately made without implementation because they should never be used.
	// -------------------------
	WMI(const WMI& t);
	WMI& operator=(const WMI& t);
};