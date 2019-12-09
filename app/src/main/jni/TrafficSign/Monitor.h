#ifndef DRIVER_ASSISTENCE_MONITORBASE_H
#define DRIVER_ASSISTENCE_MONITORBASE_H

#include "IListeners.h"
#include <deque>

class MonitorBase: public NotifierImage
{
    public:
        virtual ~MonitorBase();

        static MonitorBase * GetInstance(){
            if(!m_monitorInstance){
                m_monitorInstance = new MonitorBase();
            }
            return m_monitorInstance;
        }

    private:
        MonitorBase();
        static MonitorBase* m_monitorInstance;


};


#endif //DRIVER_ASSISTENCE_MONITORBASE_H
