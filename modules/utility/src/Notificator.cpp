#include "Notificator.hpp"

#include "Constants.hpp"
#include "SingletonGetter.hpp"

Notificator::Notificator(QObject *parent)
    : QObject(parent)
{
}

Notificator *Notificator::instance()
{
    return Singleton::instance().get<Notificator>(constants::MODULE_NAME, "Notificator");
}
