#ifndef common_Application
#define common_Application

#include <memory>
#include <common/IObject.h>
#include <util/BaseLogger.h>

namespace elfbox
{
namespace common
{
class IElfBoxEngine;

class IApplicationCore;

class Context;

class Application : public IObject
{
ELF_OBJECT(Application, IObject);

public:
    Application(std::shared_ptr<IApplicationCore> applicationCore,
                std::shared_ptr<Context> context);

    virtual ~Application();
    virtual void run();

private:
    virtual bool setup();
    virtual bool start();
    virtual bool terminat();

    std::shared_ptr<Context> context_;
    std::shared_ptr<IElfBoxEngine> elfBoxEngine_;
    std::shared_ptr<IApplicationCore> applicationCore_;

    LoggerPtr log_;
};
}
}

extern void appMain();
#endif