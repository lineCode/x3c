//! \file DocEventObserver.h
//! \brief 定义文档事件观察者类 DocEventObserver

#ifndef EXAMPLE_DOCEVENT_OBSERVER_H_
#define EXAMPLE_DOCEVENT_OBSERVER_H_

#include <ChangeObserver/Cx_ChangeObserver.h>

//! 文档事件类型
enum kDocEventType
{
    kDocEvent_BeforeOpen,       //!< 文档打开之前
    kDocEvent_AfterOpen,        //!< 文档打开之后
    kDocEvent_OpenFail,         //!< 文档打开失败
};

//! 作为例子的文档事件观察者类
/*! 本例子用于让派生类都能响应多个事件通知
    \note 建议派生类从本类私有继承
    \ingroup _GROUP_CHANGE_OBSERVER_
*/
class DocEventObserver : public Cx_ChangeObserver
{
    NOCOPY_CONSTRUCTOR(DocEventObserver);
public:
    //! DocEventObserver 观察者的通知数据类
    class Data : public ChangeNotifyData
    {
        NOCOPY_CONSTRUCTOR(Data);
    public:
        Data(kDocEventType _event)
            : ChangeNotifyData("DocEventObserver")
            , event(_event), count(0)
        {
        }

        kDocEventType   event;
        long            count;
    };

protected:
    DocEventObserver() : Cx_ChangeObserver("DocEventObserver")
    {
    }

    //! 响应文档打开之前的通知
    virtual bool OnDocEventBeforeOpen() { return false; }

    //! 响应文档打开之后的通知
    virtual bool OnDocEventAfterOpen() { return false; }

    //! 响应文档打开失败的通知
    virtual bool OnDocEventOpenFail() { return false; }

private:
    void DoUpdate(ChangeNotifyData* data)
    {
        Data* mydata = static_cast<Data*>(data);

        switch (mydata->event)
        {
        case kDocEvent_BeforeOpen:
            if (OnDocEventBeforeOpen())
                mydata->count++;
            break;

        case kDocEvent_AfterOpen:
            if (OnDocEventAfterOpen())
                mydata->count++;
            break;

        case kDocEvent_OpenFail:
            if (OnDocEventOpenFail())
                mydata->count++;
            break;

        default:
            ASSERT(0);
        }
    }
};

#endif // EXAMPLE_DOCEVENT_OBSERVER_H_
