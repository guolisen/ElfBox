#ifndef common_Application
#define common_Application

#include <memory>
#include <common/IObject.h>
#include <util/BaseLogger.h>

namespace elfbox
{
    class IElfBoxEngine;
    class IApplicationCore;

    class Application :public IObject
    {
        ELF_OBJECT(Application, IObject);

    public:
        Application(std::shared_ptr<IApplicationCore> applicationCore);
        virtual ~Application();
        virtual void run();
        virtual bool setup();
        virtual bool start();
        virtual bool terminat();

    private:
        std::shared_ptr<IElfBoxEngine> elfBoxEngine_;
        std::shared_ptr<IApplicationCore> applicationCore_;

        LoggerPtr log_;
    };
}

extern int appMain();
#endif