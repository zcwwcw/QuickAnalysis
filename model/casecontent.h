#ifndef CASECONTENT_H
#define CASECONTENT_H

#include <QHash>
#include <QVariant>

struct CaseContent
{
    QHash<QString, CaseContent> childContent;
    QVariant value;
};

#endif // CASECONTENT_H
