#include "../ui/localizeduistrings.h"
#include "routedata.h"
#include <QJsonArray>

using namespace Via::Interfaces;
using namespace Via::Model;
using namespace Via::Structures;
using namespace Via::UI;

/*
void RouteData::refreshNames(RouteDataIterator&& it, size_t index) {
    if (it == nodes.end()) {
        return;
    }

    for (; it != nodes.end(); ++it, ++index) {
        auto &node = *it;
        QString newNumber = QString::number(index + 1);
        if (!node.isNameChangedByUser() && node.getName() != newNumber) {
            node.setName(LocalizedUIStrings::getUIString("NODE_DEFAULT_NAME").arg(newNumber));
        }
    }
} */
