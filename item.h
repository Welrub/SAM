#ifndef ITEM_H
#define ITEM_H
#include <QString>

class item
{
public:
    item(QString name, int32_t amount = 0, int32_t cost = 0, int32_t notification_if = 0, bool is_notific = true)
        :   _name(name), _amount(amount), _cost(cost), _notification_if(notification_if), _is_notific(is_notific)
    {   }
    item(const item& it) = default;
    item(item&& it) = default;
private:
    QString _name = "";
    int32_t _amount = 0;
    int32_t _cost = 0;
    int32_t _notification_if = 0;
    bool _is_notific = true;
};

#endif // ITEM_H
