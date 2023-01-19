#ifndef DSDEVENUM
#define DSDEVENUM
#include <dsound.h>

struct DSEnumeratedDevice
{
    LPGUID lpGUID; 
    LPCTSTR lpszDesc;
    LPCTSTR lpszDrvName;
    DSEnumeratedDevice(){}
    int FillDeviceData(LPGUID lpguide, LPCTSTR lpszdesc, LPCTSTR lpszdrvname)
    {
        lpGUID = lpguide;
        lpszDesc = lpszdesc;
        lpszDrvName = lpszdrvname;
        return 1;
    }
    ~DSEnumeratedDevice(){}
};

struct DSEnumeratedDeviceNode
{
    DSEnumeratedDevice DeviceInfo;
    DSEnumeratedDeviceNode* next;
    DSEnumeratedDeviceNode* prev;
    DSEnumeratedDeviceNode(){}
    DSEnumeratedDeviceNode(LPGUID lpguide, LPCTSTR lpszdesc, LPCTSTR lpszdrvname)
    {
        DeviceInfo.FillDeviceData(lpguide, lpszdesc, lpszdrvname);
    }
    ~DSEnumeratedDeviceNode(){}
};

struct DSEnumeratedDeviceList
{
    DSEnumeratedDeviceNode* root;
    bool Chronologic;
    unsigned int nodesInList;
    DSEnumeratedDeviceList()
    {
        root = new DSEnumeratedDeviceNode();
        nodesInList = 0;
        Chronologic = false;
    }

    int AddDeviceNode(LPGUID lpguide, LPCTSTR lpszdesc, LPCTSTR lpszdrvname)
    {
        root->next = new DSEnumeratedDeviceNode(lpguide, lpszdesc, lpszdrvname);
        root->next->prev = root;
        root = root->next;
        nodesInList++;
        return 1;
    }

    int PrintDeviceInfo()
    {
        if(!Chronologic)
        {
            ResetRoot();
        }
        while(root->next)
        {
            LPGUID lpguide = root->DeviceInfo.lpGUID;
            LPCTSTR lpszdesc = root->DeviceInfo.lpszDesc;
            LPCTSTR lpszdrvname = root->DeviceInfo.lpszDrvName;
            if((void*)lpguide == (void*)0xbaadf00dbaadf00d || !lpguide)
            {
                std::cout << "Mega Void" << std::endl;
            }
            if((void*)lpszdesc == (void*)0xbaadf00dbaadf00d || !lpszdesc || lpszdesc < 0)
            {
                std::cout << "Mega Void" << std::endl;
            }
            if((void*)lpszdrvname == (void*)0xbaadf00dbaadf00d || !lpszdrvname)
            {
                std::cout << "Mega Void" << std::endl;
            }

            root = root->next;
            
        }
        return 1;
    }

    int ResetRoot()
    {
        for(int i = 0; i < nodesInList; i++)
        {
            root = root->prev;
        }   
        Chronologic = true;
        return 1;
    }
    ~DSEnumeratedDeviceList()
    {
        if(root)
        {
            free(root);
        }
    }
};

BOOL CALLBACK DSEnumProcLinked( LPGUID lpGUID, LPCTSTR lpszDesc,LPCTSTR lpszDrvName, LPVOID lpContext )
{
    DSEnumeratedDeviceList* DeviceList = (DSEnumeratedDeviceList*)lpContext;
    LPGUID lpTemp = NULL;
    if((void*)lpGUID == (void*)0xbaadf00dbaadf00d || !lpGUID)
    {
        return(TRUE);
    }
    DeviceList->AddDeviceNode(lpGUID, lpszDesc, lpszDrvName);
    return(TRUE);
}

struct DSEnumeratedDeviceArray
{
private:
    DSEnumeratedDevice* m_deviceList;
    unsigned int m_deviceCount;
    unsigned int m_pushIndex;
public:
    DSEnumeratedDeviceArray(){ m_deviceCount = 0; m_deviceList = nullptr; m_pushIndex = 0; m_extracting = false;}
    int AllocateDeviceList()
    {
        if(m_deviceList != nullptr)
        {
            FreeDeviceList();
        }
        m_deviceList = (DSEnumeratedDevice*)malloc(m_deviceCount * sizeof(DSEnumeratedDevice));
        if(m_deviceList != nullptr){ m_extracting = true;  return 1; }
        return 0;
    }
    int FreeDeviceList()
    {
        if(m_deviceList != nullptr)
        {
            free(m_deviceList);
            m_deviceList = nullptr;
            m_extracting = false;
            return 1;
        }
        return 0;
        m_pushIndex = 0;
    }

    int PushDevice(DSEnumeratedDevice Device)
    {
        if(m_deviceList == nullptr)
        {
            int deviceAllocationStatus = AllocateDeviceList();
            if(!deviceAllocationStatus){ return 0; }
        }
        if(m_pushIndex < m_deviceCount)
        {
            m_deviceList[m_pushIndex] = Device;
            m_pushIndex++;
            return 1;
        }
        return 0;
    }

    int IncrementDeviceCount()
    {
        m_deviceCount++;
        return 1;
    }
    unsigned int DeviceCount() {return m_deviceCount;}
    void DisplayDevices(){ for(int i = 0; i < m_deviceCount; i++){  std::cout << m_deviceList[i].lpGUID << " , " << m_deviceList[i].lpszDesc << " , " << m_deviceList[i].lpszDrvName << std::endl; } }
    ~DSEnumeratedDeviceArray()
    {
        FreeDeviceList();
    }
    DSEnumeratedDevice* ReturnDeviceList(){ return m_deviceList; }
    DSEnumeratedDevice operator[](int index){ if(index <= 0 || index > m_deviceCount-1){ return DSEnumeratedDevice(); } return m_deviceList[index]; }
    bool m_extracting;
};

BOOL CALLBACK DSEnumProcArray(LPGUID lpGUID,  LPCTSTR lpszDesc, LPCTSTR lpszDrvName,  LPVOID lpContext)
{
   DSEnumeratedDeviceArray* DeviceArray = (DSEnumeratedDeviceArray*)lpContext;
   if(DeviceArray->m_extracting)
   {
        DSEnumeratedDevice Push; Push.FillDeviceData(lpGUID, lpszDesc, lpszDrvName);
        DeviceArray->PushDevice(Push);
   }else
   {
        DeviceArray->IncrementDeviceCount();
   }

   
   return(TRUE);
}



#endif