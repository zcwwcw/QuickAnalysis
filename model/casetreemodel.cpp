#include "casetreemodel.h"

CaseTreeModel::CaseTreeModel(QObject *parent) :
    QAbstractItemModel(parent), m_itemMapper1(NULL),
    m_itemMapper2(NULL)
{
    QList<QVariant> itemData;
    itemData << "CaseList";
    m_rootItem = new TreeItem(itemData);
    m_itemMapper1 = new QSignalMapper(this);
    connect(m_itemMapper1, SIGNAL(mapped(QObject*)),
            this, SIGNAL(itemPropertiesUpdate(QObject*)));
    m_itemMapper2 = new QSignalMapper(this);
    connect(m_itemMapper2, SIGNAL(mapped(QObject*)),
            this, SIGNAL(itemPropertiesRebuild(QObject*)));
}

CaseTreeModel::~CaseTreeModel()
{
    delete m_rootItem;
}

TreeItem *CaseTreeModel::addCase(const QString &filePath)
{
    QFileInfo fileInfo(filePath);
    if(fileInfo.exists())
    {
        return setupModelData(filePath, m_rootItem);
    }
    return NULL;
}

TreeItem *CaseTreeModel::getItem(const QModelIndex &index) const
{
    if (index.isValid())
    {
        TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
        if (item)
            return item;
    }
    return NULL;
}

QVariant CaseTreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());

    return item->data(index.column());
}

Qt::ItemFlags CaseTreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;
    return QAbstractItemModel::flags(index);
}

QModelIndex CaseTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    TreeItem *parentItem;

    if (!parent.isValid())
        parentItem = m_rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    TreeItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex CaseTreeModel::indexFromItem(TreeItem *item, int column) const
{
    if (!item || (item == m_rootItem))
        return QModelIndex();
    const TreeItem *par = item->parent();
    TreeItem *itm = const_cast<TreeItem*>(item);
    if(!par)
        par = m_rootItem;
    int row = par->indexOfItem(itm);
    return createIndex(row, column, itm);
}

QModelIndex CaseTreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    TreeItem *childItem = static_cast<TreeItem*>(index.internalPointer());
    TreeItem *parentItem = childItem->parent();

    if (parentItem == m_rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int CaseTreeModel::rowCount(const QModelIndex &parent) const
{
    TreeItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = m_rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    return parentItem->childCount();
}

int CaseTreeModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<TreeItem*>(parent.internalPointer())->columnCount();
    else
        return m_rootItem->columnCount();
}

TreeItem *CaseTreeModel::setupModelData(const QString &filePath, TreeItem *parent)
{
    QFile caseFile(filePath);
    if(!caseFile.open(QIODevice::ReadOnly))
    {
        return NULL;
    }
    QTextStream stream(&caseFile);
    QString tmpData = stream.readAll();
    CaseContent caseContent = getContent(tmpData);

    QFileInfo caseInfo(filePath);
    QList<QVariant> caseItmeData;
    caseItmeData << caseInfo.baseName();
    TreeItem *caseItem = new TreeItem(caseItmeData, parent);
    parent->appendChild(caseItem);

    QList<QVariant> modelItemData;
    modelItemData << tr("Model");
    TreeItem *modelItem = new ModelTreeItem(modelItemData, caseItem);
    connect(modelItem, SIGNAL(propertiesUpdate()), m_itemMapper1, SLOT(map()));
    connect(modelItem, SIGNAL(propertiesRebuild()), m_itemMapper2, SLOT(map()));
    m_itemMapper1->setMapping(modelItem, modelItem);
    m_itemMapper2->setMapping(modelItem, modelItem);
    caseItem->appendChild(modelItem);

    QList<QVariant> fltconItemData;
    fltconItemData << tr("FLTCON");
    FltconTreeItem *fltconItem = new FltconTreeItem(fltconItemData, modelItem);
    connect(fltconItem, SIGNAL(propertiesUpdate()), m_itemMapper1, SLOT(map()));
    connect(fltconItem, SIGNAL(propertiesRebuild()), m_itemMapper2, SLOT(map()));
    m_itemMapper1->setMapping(fltconItem, fltconItem);
    m_itemMapper2->setMapping(fltconItem, fltconItem);
    fltconItem->setContent(caseContent);
    modelItem->appendChild(fltconItem);

    QList<QVariant> refqItemData;
    refqItemData << tr("REFQ");
    RefqTreeItem *refqItem = new RefqTreeItem(refqItemData, modelItem);
    connect(refqItem, SIGNAL(propertiesUpdate()), m_itemMapper1, SLOT(map()));
    connect(refqItem, SIGNAL(propertiesRebuild()), m_itemMapper2, SLOT(map()));
    m_itemMapper1->setMapping(refqItem, refqItem);
    m_itemMapper2->setMapping(refqItem, refqItem);
    refqItem->setContent(caseContent);
    modelItem->appendChild(refqItem);

    QList<QVariant> geometryItemData;
    geometryItemData << tr("GEOMETRY");
    GeometryTreeItem *geometryItem = new GeometryTreeItem(geometryItemData, modelItem);
    connect(fltconItem, SIGNAL(nvinfChanged()), geometryItem, SLOT(nmachOrnvinfChanged()));
    connect(fltconItem, SIGNAL(nmachChanged()), geometryItem, SLOT(nmachOrnvinfChanged()));
    connect(geometryItem, SIGNAL(propertiesUpdate()), m_itemMapper1, SLOT(map()));
    connect(geometryItem, SIGNAL(propertiesRebuild()), m_itemMapper2, SLOT(map()));
    m_itemMapper1->setMapping(geometryItem, geometryItem);
    m_itemMapper2->setMapping(geometryItem, geometryItem);
    geometryItem->setContent(caseContent);
    modelItem->appendChild(geometryItem);

    QList<QVariant> protubItemData;
    protubItemData << tr("PROTUB");
    ProtubTreeItem *protubItem = new ProtubTreeItem(protubItemData, modelItem);
    connect(protubItem, SIGNAL(propertiesUpdate()), m_itemMapper1, SLOT(map()));
    connect(protubItem, SIGNAL(propertiesRebuild()), m_itemMapper2, SLOT(map()));
    m_itemMapper1->setMapping(protubItem, protubItem);
    m_itemMapper2->setMapping(protubItem, protubItem);
    protubItem->setContent(caseContent);
    modelItem->appendChild(protubItem);

    QList<QVariant> finsetItemData;
    finsetItemData << tr("FINSET");
    FinsetTreeItem *finsetItem = new FinsetTreeItem(finsetItemData, modelItem);
    connect(finsetItem, SIGNAL(propertiesUpdate()), m_itemMapper1, SLOT(map()));
    connect(finsetItem, SIGNAL(propertiesRebuild()), m_itemMapper2, SLOT(map()));
    m_itemMapper1->setMapping(finsetItem, finsetItem);
    m_itemMapper2->setMapping(finsetItem, finsetItem);
    finsetItem->setContent(caseContent);
    modelItem->appendChild(finsetItem);

    QList<QVariant> deflctItemData;
    deflctItemData << tr("DEFLCT");
    DeflctTreeItem *deflctItem = new DeflctTreeItem(deflctItemData, modelItem);
    connect(deflctItem, SIGNAL(propertiesUpdate()), m_itemMapper1, SLOT(map()));
    connect(deflctItem, SIGNAL(propertiesRebuild()), m_itemMapper2, SLOT(map()));
    m_itemMapper1->setMapping(deflctItem, deflctItem);
    m_itemMapper2->setMapping(deflctItem, deflctItem);
    deflctItem->setContent(caseContent);
    modelItem->appendChild(deflctItem);

    QList<QVariant> trimItemData;
    trimItemData << tr("TRIM");
    TrimTreeItem *trimItem = new TrimTreeItem(trimItemData, modelItem);
    connect(trimItem, SIGNAL(propertiesUpdate()), m_itemMapper1, SLOT(map()));
    connect(trimItem, SIGNAL(propertiesRebuild()), m_itemMapper2, SLOT(map()));
    m_itemMapper1->setMapping(trimItem, trimItem);
    m_itemMapper2->setMapping(trimItem, trimItem);
    trimItem->setContent(caseContent);
    modelItem->appendChild(trimItem);

    QList<QVariant> inletItemData;
    inletItemData << tr("INLET");
    InletTreeItem *inletItem = new InletTreeItem(inletItemData, modelItem);
    connect(inletItem, SIGNAL(propertiesUpdate()), m_itemMapper1, SLOT(map()));
    connect(inletItem, SIGNAL(propertiesRebuild()), m_itemMapper2, SLOT(map()));
    m_itemMapper1->setMapping(inletItem, inletItem);
    m_itemMapper2->setMapping(inletItem, inletItem);
    inletItem->setContent(caseContent);
    modelItem->appendChild(inletItem);

    QList<QVariant> solutionItemData;
    solutionItemData << tr("Solution");
    SolutionTreeItem *solutionItem = new SolutionTreeItem(solutionItemData, caseItem);
    connect(solutionItem, SIGNAL(propertiesUpdate()), m_itemMapper1, SLOT(map()));
    connect(solutionItem, SIGNAL(propertiesRebuild()), m_itemMapper2, SLOT(map()));
    m_itemMapper1->setMapping(solutionItem, solutionItem);
    m_itemMapper2->setMapping(solutionItem, solutionItem);
    caseItem->appendChild(solutionItem);
    return caseItem;
}

CaseContent CaseTreeModel::getContent(const QString &tmpData)
{
    CaseContent content;
    QRegExp itemRx("\\$[^/}]+\\$");
    itemRx.setMinimal(true);
    QStringList datas;
    int itemPos = 0;
    while ((itemPos = itemRx.indexIn(tmpData, itemPos)) != -1)
    {
        datas << itemRx.cap(0);
        itemPos += itemRx.matchedLength();
    }
    for(int i = 0, iend = datas.count(); i < iend; i++)
    {
        QRegExp itemKeyRx("\\$\\w+");
        if(itemKeyRx.indexIn(datas[i]) == -1)
        {
            continue;
        }
        CaseContent itemContent;
        QRegExp valueItemRx("([A-Z]+)=([A-Z0-9.,-]+),");
        QStringList valueItems;
        int valuePos = 0;
        while ((valuePos = valueItemRx.indexIn(datas[i], valuePos)) != -1)
        {
            valueItems << valueItemRx.cap(0);
            valuePos += valueItemRx.matchedLength();
        }
        for(int j = 0, jend = valueItems.count(); j < jend; j++)
        {
            QStringList valueList = valueItems[j].split('=', QString::SkipEmptyParts);
            if(valueList.count() != 2)
            {
                continue;
            }
            QString key = valueList[0];
            QString value = valueList[1];
            if(value[value.count() - 1] == ',')
            {
                value.remove(value.count() - 1, 1);
            }
            CaseContent valueContent;
            valueContent.value = value;
            itemContent.childContent.insert(key, valueContent);
        }

        content.childContent.insert(itemKeyRx.cap().remove("$"), itemContent);
    }
    return content;
}
