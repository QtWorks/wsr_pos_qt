// Code to create a QComboBox where multiple items can be selected and the items
// are shown in a tree.
// Written by Corwin Joy
// This code is hereby placed in the Public Domain.
// This code comes with no warranty of any kind, use at your own risk.

#pragma once
#include <QComboBox>
#include <QtCore/QList>
#include <QTreeView>
#include <QtCore/QStringList>
#include <QCompleter>

class QStandardItemModel;

class TreeComboBox : public QComboBox
{
Q_OBJECT
Q_PROPERTY(QString separator READ separator WRITE setSeparator)

public:
  TreeComboBox(QModelIndex defaultRootIdx = QModelIndex(), QWidget* parent = 0);
  void setRoot(QModelIndex defaultRootIdx)
  {
    defaultRootIndex = defaultRootIdx;
  }

  bool eventFilter(QObject* object, QEvent* event);
  virtual void showPopup();
  virtual void hidePopup();
  QModelIndexList currentIndexes() const;
  QModelIndexList getChildren(QModelIndex current) const;
  QString separator() const {return sep;};
  QVariant itemData (QModelIndex index, int role = Qt::UserRole + 1 ) const; 
  QModelIndexList findData (const QVariant & data, int role = Qt::UserRole + 1, Qt::MatchFlags flags = Qt::MatchExactly | Qt::MatchCaseSensitive ) const; 
  QModelIndexList findText (const QString & text, Qt::MatchFlags flags = Qt::MatchExactly | Qt::MatchCaseSensitive ) const; 
  QString currentText() const;
  
public Q_SLOTS:
  void setSeparator(const QString &separator) {sep = separator;};
  void setEditText (const QString & text); 
  void updateText();
  void setCurrentIndexes(QModelIndexList indexes); 
  void blockLineEditChanged(const QString &);
  void applyLineEditChanged();

Q_SIGNALS:
  void currentIndexChanged(QModelIndexList indexes);

protected:
  QModelIndexList selectedIndexes() const;
  // private functions
  void UpdateSelectionString();
  void ToggleItem(QModelIndex const &index);
  void SetCheckStateFromSelectionString();
  void setCheckState(QModelIndex current, bool bForceChildrenChecked, 
    bool bNeverForceChildren, bool &bChildrenChecked, bool &bChildrenUnChecked);
  QModelIndexList getCheckedChildren(QModelIndex current) const;

private:
  // functions forbidden from base.  these don't make sense in our derived class
  // jenire 삭제
  //int currentIndex () const {}; // forbidden from base
  void currentIndexChanged(int index); 
  void currentIndexChanged ( const QString & text );
  void activated ( int index ) ; 
  void activated ( const QString & text );  
  QVariant itemData ( int index, int role = Qt::UserRole ) const; 
  QIcon itemIcon ( int index ) const ;
  QString itemText ( int index ) const;


  // member variables
  bool skipNextHide;

protected:
  QModelIndex defaultRootIndex;
  QString strSelected;
  QString sep;
};

class SplitCompleter : public QCompleter
{
  Q_OBJECT
    Q_PROPERTY(QString separator READ separator WRITE setSeparator)

public:
  SplitCompleter(QObject *parent = 0);
  SplitCompleter(QAbstractItemModel *model, QObject *parent = 0);
  SplitCompleter ( const QStringList & list, QObject * parent = 0 );

  QString separator() const {return sep;};
public Q_SLOTS:
  void setSeparator(const QString &separator) {sep = separator;};

protected:
  QStringList splitPath(const QString &path) const;
  QString pathFromIndex(const QModelIndex &index) const;

private:
  QString sep;
  mutable QString prefix;
};


class StandardTreeComboBox : public TreeComboBox
{
  Q_OBJECT

public:
  StandardTreeComboBox(QWidget* parent = 0);
  void SetupCompleter(QCompleter::CompletionMode mode = QCompleter::PopupCompletion);
  QStandardItemModel *model() const;
  
  // convenience method to add item at the top of the tree
  void addItem(const QString &text, const QVariant &userData = QVariant());
};
