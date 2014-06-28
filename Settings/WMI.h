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
#include "Structures.h"
#include <qstring.h>
#include <qstringlist.h>

using namespace std;


//-----------------------------------------------------------------
// Defines
//-----------------------------------------------------------------
#define _WIN32_DCOM
# pragma comment(lib, "wbemuuid.lib")
using namespace std;

//-----------------------------------------------------------------
// WMI Class
//-----------------------------------------------------------------
class WMI
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
	vector<Sensor> getSensors(vector<string> hardwareCode, vector<string> sensorType);
	vector<Hardware> getHardware();
	vector<string> getHardwareIdentifier(QString name);

	void refresh();

	string convertCodeToLine(string);
	string queryCode(QueryCode);
	string getSensorIdentifier(QString id);

	QString generateCode(QString, QString, QString, int);
	
private:
	//---------------------------
	// Private Methods
	//---------------------------
	void connectToWMI();
	void queryHardware();
	vector<Sensor> querySensors(string query);

	//--------------------------
	// Datamembers
	//--------------------------
	IWbemLocator *pLoc;
	IWbemServices *pSvc;
	IEnumWbemClassObject* pEnumerator;
	IWbemClassObject *pclsObj;
	HRESULT hres;

	vector<QueryCode> codes;
	vector<Hardware> hardwareList;

	// -------------------------
	// Disabling default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, these declarations are deliberately made without implementation because they should never be used.
	// -------------------------
	WMI(const WMI& t);
	WMI& operator=(const WMI& t);
};