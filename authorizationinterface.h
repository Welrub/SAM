#ifndef AUTHORIZATIONINTERFACE_H
#define AUTHORIZATIONINTERFACE_H

#include <QString>

class AuthorizationInterface
{
public:
    virtual ~AuthorizationInterface() = 0;
    virtual bool authorization(const QString& login, const QString& pass) = 0;
};

#define AuthorizationInterface_id "SAM.AuthorizationInterface/1.0"

Q_DECLARE_INTERFACE(AuthorizationInterface, AuthorizationInterface_id)

#endif // AUTHORIZATIONINTERFACE_H
