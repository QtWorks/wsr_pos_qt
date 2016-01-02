//////////////////////////////////////////////////////////////////////////////////////////
// Code to create a QComboBox where multiple items can be selected and the items
// are shown in a tree.
// Written by Corwin Joy
// This code is hereby placed in the Public Domain.
// This code comes with no warranty of any kind, use at your own risk.qwe c

#include "TreeComboBox.h"
#include <QLineEdit>
#include <QAbstractItemView>
#include <QStandardItemModel>
#include <QtCore/QModelIndex>
#include <QtCore/QTimer>
#include <QKeyEvent>
#include <QHeaderView>
#include <QtCore/QEvent>
#include <QMouseEvent>
#include <QtCore/QModelIndex>
#include <cassert>
//#include "TreeComboBox_moc.cpp"

static const char g_ItemSep[] = "|";

//////////////////////////////////////////////////////////////////////////////////////////

/// TreeComboBox

TreeComboBox::TreeComboBox(QModelIndex const defaultRootIdx, QWidget* parent) : 
QComboBox(parent), skipNextHide(false), defaultRootIndex(defaultRootIdx) //Widget creation
{
  QTreeView* treeView = new QTreeView(this);
  treeView->header()->hide();
  treeView->setMaximumHeight(500); // by default tree will show as 1 line high, need to reserve room
  treeView->setMinimumHeight(500);
  setView(treeView);
  view()->viewport()->installEventFilter(this);
  view()->setSelectionMode(QAbstractItemView::SingleSelection); // click to toggle items

  QComboBox::resize(200,200);
  setEditable(true);
  lineEdit()->setReadOnly(false);
  setInsertPolicy(QComboBox::NoInsert);
  connect(lineEdit(), SIGNAL(editingFinished()), this, SLOT(applyLineEditChanged()));
  sep = QLatin1String(g_ItemSep);
}

void TreeComboBox::showPopup()
{
  setRootModelIndex(defaultRootIndex);
  QComboBox::showPopup();
  applyLineEditChanged();  

  connect(lineEdit(), SIGNAL(textChanged(const QString &)), this, SLOT(blockLineEditChanged(const QString &)));
}

void TreeComboBox::hidePopup()
{
  if (skipNextHide)
    skipNextHide = false;
  else
  {
    UpdateSelectionString(); 
    disconnect(lineEdit(), SIGNAL(textChanged(const QString &)), this, SLOT(blockLineEditChanged(const QString &)));
    QComboBox::hidePopup();
    currentIndexChanged(currentIndexes());
  }
}


void TreeComboBox::blockLineEditChanged(const QString &)
{
  // override any lineEdit text set by base ComboBox methods such as setCurrentIndex
  if (lineEdit()->text() != strSelected)
    lineEdit()->setText(strSelected);
}

void TreeComboBox::applyLineEditChanged()
{
  if(strSelected != lineEdit()->text())
  {
    QString strNew = lineEdit()->text();
    QModelIndex current = model()->index(0, 0, defaultRootIndex);
    if(!current.isValid())
    {
      // empty set of rows, just return
      strSelected = strNew;
      return;
    }

    // clear current selection
    QModelIndexList old = currentIndexes();
    Q_FOREACH(QModelIndex idx, old)
      model()->setData(idx, Qt::Unchecked, Qt::CheckStateRole);
    strSelected = strNew;
    SetCheckStateFromSelectionString();
    UpdateSelectionString(); // selection string may have changed after it was validated
    currentIndexChanged(currentIndexes());
  }
}

QString TreeComboBox::currentText() const
{
  // we must return the most up to date value in line edit, strSelected may take time to catch up
  return lineEdit()->text(); 
}

void TreeComboBox::setEditText(const QString & text)
{
  QComboBox::setEditText(text);
  applyLineEditChanged();
}

void TreeComboBox::ToggleItem(QModelIndex const &index)
{
  // if this item can be checked, as per Qt::ItemIsUserCheckable
  // check the box if this item is selected
  // (typically, checkboxes are enabled via item->setCheckable(true))
  if(model()->data(index, Qt::CheckStateRole).toInt() == Qt::Checked)
  {
    // uncheck
    QModelIndexList indexes = getChildren(index);
    Q_FOREACH(QModelIndex idx, indexes)
    {
      if(model()->flags(idx) & Qt::ItemIsUserCheckable)
        model()->setData(idx, Qt::Unchecked, Qt::CheckStateRole);
    }
  }
  else
  {
    // check
    QModelIndexList indexes = getChildren(index);
    Q_FOREACH(QModelIndex idx, indexes)
    {
      if(model()->flags(idx) & Qt::ItemIsUserCheckable)
        model()->setData(idx, Qt::Checked, Qt::CheckStateRole);
    }
  }

  // update the check flags for the parents
  bool ch, uc;
  setCheckState(defaultRootIndex, false, true, ch, uc);
}

// this routine updates the check flags for the tree starting from the current node
// unchecked = all children are unchecked
// checked = all children are checked
// partial = some children are checked
void TreeComboBox::setCheckState(QModelIndex current, bool bForceChildrenChecked,
                                 bool bNeverForceChildren,
                                 bool &bChildrenChecked, bool &bChildrenUnChecked)
{
  if(current != QModelIndex())
  {
    if(bForceChildrenChecked)
    {
      // force children to be checked
      model()->setData(current, Qt::Checked, Qt::CheckStateRole);
      bChildrenUnChecked = false;
    }

    // leaf node, just return the state
    if(!model()->hasChildren(current))
    {
      if(model()->data(current, Qt::CheckStateRole).toInt() == Qt::Checked)
      {
        bChildrenChecked = true;
        bChildrenUnChecked = false;
      }
      else
      {
        bChildrenChecked = false;
        bChildrenUnChecked = true;
      }
      return;
    }

    // interior node with children. set checkbox based on children
    bChildrenChecked = false;
    bChildrenUnChecked = false;

    if(!bNeverForceChildren && model()->data(current, Qt::CheckStateRole).toInt() == Qt::Checked)
    {
      // force children to be checked
      bForceChildrenChecked = true;
    }

    int rows = model()->rowCount(current);
    int cols = model()->columnCount(current);
    for(int row = 0; row < rows; ++row)
    {
      for(int col = 0; col < cols; ++col)
      {
        bool ch, un;
        ch = false;
        un = false;
        setCheckState(current.child(row, col), bForceChildrenChecked, bNeverForceChildren, ch, un);
        bChildrenChecked |= ch;
        bChildrenUnChecked |= un;
      }
    }

    if(bChildrenUnChecked && !bChildrenChecked)
    {
      model()->setData(current, Qt::Unchecked, Qt::CheckStateRole);
    }
    else if(!bChildrenUnChecked && bChildrenChecked)
    {
      model()->setData(current, Qt::Checked, Qt::CheckStateRole);
    }
    else if(bChildrenUnChecked && bChildrenChecked)
    {
      model()->setData(current, Qt::PartiallyChecked, Qt::CheckStateRole);
    }
    else // (!bChildrenUnChecked && !bChildrenChecked)
    {
      // can only get here if loop above failed to execute.
      assert(!"Invalid check state encountered for child checkboxes.\n"
        "Can't have no checked and no unchecked children.");
    }
  }
  else
  {
    // Treat this as a search from the (hidden) root.
    // Fortunately, we don't need to worry about the hidden root having a checkbox
    current = model()->index(0, 0, defaultRootIndex);
    int topRow = 0;
    while(current.isValid())
    {
      bForceChildrenChecked = false;
      if(!bNeverForceChildren && model()->data(current, Qt::CheckStateRole).toInt() == Qt::Checked)
      {
        // force children to be checked
        bForceChildrenChecked = true;
      }
      bool ch, un;
      ch = false;
      un = false;
      setCheckState(current, bForceChildrenChecked, bNeverForceChildren, ch, un);
      ++topRow;
      current = model()->index(topRow, 0, defaultRootIndex);
    }
  }

}

// Return a list containing the current item + all its children
QModelIndexList TreeComboBox::getChildren(QModelIndex current) const
{
  QModelIndexList indexes;

  if(current != QModelIndex())
  {
    indexes.push_back(current);
    int rows = model()->rowCount(current);
    int cols = model()->columnCount(current);
    for(int row = 0; row < rows; ++row)
    {
      for(int col = 0; col < cols; ++col)
      {
        indexes += getChildren(current.child(row, col));
      }
    }
  }
  else
  {
    // Treat this as a search from the root.
    // We need special handling here because the defaultRootIndex may be
    // the invalid index QModelIndex(), if the defaultRootIndex comes from 
    // QStandardItemModel::invisibleRootItem().
    //
    current = model()->index(0, 0, defaultRootIndex);
    int topRow = 0;
    while(current.isValid())
    {
      indexes += getChildren(current);
      ++topRow;
      current = model()->index(topRow, 0, defaultRootIndex);
    }
  }

  return indexes;
}

// Return a list containing minimal checked representation of the tree
QModelIndexList TreeComboBox::getCheckedChildren(QModelIndex current) const
{
  QModelIndexList indexes;

  if(current != QModelIndex())
  {
    if(model()->data(current, Qt::CheckStateRole).toInt() == Qt::Checked)
    {
      indexes.push_back(current);
    }
    
    if(model()->data(current, Qt::CheckStateRole).toInt() != Qt::Checked &&
      model()->data(current, Qt::CheckStateRole).toInt() != Qt::Unchecked)
    {
      // only expand children if this node is not checked or purely unchecked
      int rows = model()->rowCount(current);
      int cols = model()->columnCount(current);
      for(int row = 0; row < rows; ++row)
      {
        for(int col = 0; col < cols; ++col)
        {
          indexes += getCheckedChildren(current.child(row, col));
        }
      }
    }
  }
  else
  {
    // Treat this as a search from the root.
    // We need special handling here because the defaultRootIndex may be
    // the invalid index QModelIndex(), if the defaultRootIndex comes from 
    // QStandardItemModel::invisibleRootItem().
    //
    current = model()->index(0, 0, defaultRootIndex);
    int topRow = 0;
    while(current.isValid())
    {
      indexes += getCheckedChildren(current);
      ++topRow;
      current = model()->index(topRow, 0, defaultRootIndex);
    }
  }

  return indexes;
}

bool TreeComboBox::eventFilter(QObject* object, QEvent* event)
{
  if (event->type() == QEvent::MouseButtonPress || event->type() == QEvent::MouseButtonRelease)
  {
    QMouseEvent* m = static_cast<QMouseEvent*>(event); 
    QModelIndex index = view()->indexAt(m->pos());
    QRect vrect = view()->visualRect(index);

    if(event->type() == QEvent::MouseButtonPress  && 
      (model()->flags(index) & Qt::ItemIsUserCheckable) &&
      vrect.contains(m->pos()))
    {
      ToggleItem(index);
      UpdateSelectionString(); 
    }
    if (view()->rect().contains(m->pos()))
      skipNextHide = true;
  }
  return QComboBox::eventFilter(object, event);
}



// check items in tree based on strSelected
void TreeComboBox::SetCheckStateFromSelectionString()
{
  QModelIndexList idxes = selectedIndexes(); 
  Q_FOREACH(QModelIndex idx, idxes)
  {
    model()->setData(idx, Qt::Checked, Qt::CheckStateRole);
  }
  bool ch, un;
  setCheckState(defaultRootIndex, false, false, ch, un);
}

// get the currently selected indexes based on strSelected
QModelIndexList TreeComboBox::selectedIndexes() const
{
  QModelIndexList selected;
  QStringList strs = strSelected.split(sep);
  QAbstractItemModel *model = view()->model();
  for (int i=0;i<strs.size();++i) 
  {
    QString str = strs.at(i);
    str = str.trimmed();
    QModelIndexList idxes = model->match(model->index(0, 0), Qt::DisplayRole, str, 1, 
      Qt::MatchExactly | Qt::MatchRecursive);
    selected += idxes;    
  }
  return selected;
}

void TreeComboBox::UpdateSelectionString()
{
  QModelIndex topidx = model()->index(0, 0, defaultRootIndex);
  if(!topidx.isValid())
  {
    return;
  }

  QModelIndexList idxes = getCheckedChildren(defaultRootIndex);
  QString strSep = tr(" ") + sep + tr(" ");
  QString newStr;
  Q_FOREACH(QModelIndex idx, idxes)
    newStr += idx.data().toString() + strSep;
  if(newStr.size() > 0)
  {
    newStr.truncate(newStr.size() + 1 - strSep.size()); // kill trailing sep
  }

  if(newStr != strSelected)
  {
    strSelected = newStr;
    QTimer::singleShot(0, this, SLOT(updateText()));
  }
}

void TreeComboBox::updateText()
{
  lineEdit()->setText(strSelected);
}

// get the currently checked indexes
QModelIndexList TreeComboBox::currentIndexes() const
{
  QModelIndexList indexes = getChildren(defaultRootIndex);
  QModelIndexList matches;
  Q_FOREACH(QModelIndex index, indexes)
  {
    if(model()->data(index, Qt::CheckStateRole).toInt() == Qt::Checked)
      matches.push_back(index);
  }

  return matches;
}

// set the currently checked indexes
void TreeComboBox::setCurrentIndexes(QModelIndexList indexes)
{
  QModelIndexList old = currentIndexes();
  Q_FOREACH(QModelIndex idx, old)
    model()->setData(idx, Qt::Unchecked, Qt::CheckStateRole);
  Q_FOREACH(QModelIndex idx, indexes)
    model()->setData(idx, Qt::Checked, Qt::CheckStateRole);

  // update the check flags for the parents
  bool ch, uc;
  setCheckState(defaultRootIndex, false, false, ch, uc);

  UpdateSelectionString();
  currentIndexChanged(currentIndexes());
}


QVariant TreeComboBox::itemData(QModelIndex index, int role /*= Qt::UserRole */) const
{
  return model()->data(index, role);
}

QModelIndexList TreeComboBox::findData (const QVariant & data, int role, Qt::MatchFlags flags) const 
{
  QModelIndex start = model()->index(0, 0, defaultRootIndex);
  return model()->match(start, role, data, -1, flags | Qt::MatchRecursive);
}

QModelIndexList TreeComboBox::findText (const QString & text, Qt::MatchFlags flags) const 
{
  return findData(text, Qt::DisplayRole , flags);
}


////////////////////////////////////////////////////////////////////
// SplitCompleter forms completion with split character
// This allows you to form a completion on a list with multiple selection items
// as separated by e.g. |
SplitCompleter::SplitCompleter(QObject *parent)
: QCompleter(parent)
{
  sep = QLatin1String(g_ItemSep);
}

SplitCompleter::SplitCompleter(QAbstractItemModel *model, QObject *parent)
: QCompleter(model, parent)
{
  sep = QLatin1String(g_ItemSep);
}

SplitCompleter::SplitCompleter(const QStringList & list, QObject * parent)
: QCompleter(list, parent)
{
  sep = QLatin1String(g_ItemSep);
}

QStringList SplitCompleter::splitPath(const QString &path) const
{
  if (sep.isNull() || path.size() < 1) {
    return QCompleter::splitPath(path);
  }

  QStringList parts = path.split(sep);
  QString current = parts.back();
  prefix = path.left(path.size() - current.size());

  return QStringList(current.trimmed());
}

QString SplitCompleter::pathFromIndex(const QModelIndex &index) const
{
  if (sep.isNull()) {
    return QCompleter::pathFromIndex(index);
  }

  if (!index.isValid())
    return QString();

  QString suffix = QCompleter::pathFromIndex(index);
  
  return  prefix + QLatin1String(" ") + suffix;
}

///////////////////////////////////////////////////////////////////////////
// StandardTreeComboBox

StandardTreeComboBox::StandardTreeComboBox(QWidget* parent /* = 0 */) : TreeComboBox(QModelIndex(), parent)
{
  QStandardItemModel *model  = new QStandardItemModel;
  setModel(model);
  setRoot(model->indexFromItem(model->invisibleRootItem()));
}

static void sortNonCaseSensitive( QStringList &sList ) {
  ///  Sorts the passed sList non-case-sensitively.
  ///  (Preserves the cases! Just doesn't use them
  ///  while sorting.)
  QMap<QString, QString> strMap;
  Q_FOREACH(QString str, sList) 
  {
    strMap.insert(str.toLower(), str);
  }
  sList = strMap.values();
}

// Initialize the list of search items to use for auto-completion
// Call this after the data in the model has been setup
// Here, we want to search over all the items of the tree, regardless of what level they are at.
void StandardTreeComboBox::SetupCompleter(QCompleter::CompletionMode mode)
{
  QStringList searchItems;
  QModelIndexList indexes = getChildren(defaultRootIndex);
  Q_FOREACH(QModelIndex index, indexes)
  {
    searchItems.push_back(model()->data(index, Qt::DisplayRole).toString());
  }
  sortNonCaseSensitive(searchItems);

  SplitCompleter *comp = new SplitCompleter(searchItems, this);
  comp->setCaseSensitivity(Qt::CaseInsensitive);
  comp->setModelSorting(QCompleter::CaseInsensitivelySortedModel);
  comp->setCompletionMode(mode);
  setCompleter(comp);
}

QStandardItemModel *StandardTreeComboBox::model() const
{
  return static_cast<QStandardItemModel *>(TreeComboBox::model());
}

void StandardTreeComboBox::addItem(const QString &text, const QVariant &userData)
{
  QStandardItem *item = new QStandardItem(text);
  item->setCheckable(true);
  item->setData(userData);
  model()->invisibleRootItem()->appendRow(item);
}
