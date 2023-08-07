#pragma once
#include <QGridLayout>
#include <QDockWidget>
#include <QString>
#include <QList>
#include <QLineEdit>
#include <QPushButton>

// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
struct Server
{
  Server(QString _ip="",QString _n="")
    : ip(_ip),
      name(_n)
  {
  }

  QString ip{""};
  QString name{""};
  QString load{""};
  QString memory{""};
};
// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
struct LsfQueue
{
  LsfQueue(QString _n,Server &_s,uint32_t _max)
    : name(_n),
      server(_s),
      maxSlots(_max)
  {
  }

  QString  name;
  Server   server;
  uint32_t maxSlots{0};
  uint32_t pending{0};
  uint32_t running{0};
  QLineEdit *values;
};

// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
class LoadMonitor : public QWidget
{
  Q_OBJECT

public:
  LoadMonitor(QList<Server> &_s,QString t="",QWidget *parent=0);
  LoadMonitor(QString t="",QWidget *parent=0);

  QString getServerStatus(Server&);
  void populateGrid();
  void update();
  void setServerLoadFromTop(Server&,QString,bool=false);
  void setServerMemoryFromFree(Server&,QString,bool=false);

  QList<Server> servers;
  QString title;

  QGridLayout *grid;
};
// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
class QueueMonitor : public QWidget
{
  Q_OBJECT

public:
  QueueMonitor(QList<LsfQueue> &_q,QString t="",QWidget *parent=0);
  QueueMonitor(QString t="",QWidget *parent=0);

  void setQueueStateFromBqueues(QString,bool=false);
  void populateGrid();
  void update();

  QList<LsfQueue> queues;
  QString title;

  bool first;

  QGridLayout *grid;
};
// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
class StatusMonitor : public QDockWidget
{
  Q_OBJECT

public:
  StatusMonitor(QList<Server> &_s,QList<LsfQueue> &_q,
                QString t="",QWidget *parent=0);
  StatusMonitor(QString t="",QWidget *parent=0);

  ~StatusMonitor() {
    killTimer(timerId);
  }

public slots:
  void scanPressed();
  void refreshPressed();

public:
  void clearGrid(QGridLayout*);
  void populatePanels(QList<Server>&,QList<LsfQueue>&);

  //FIXME: code was changed, these are no longer used, kept for now
  void removeRow(QGridLayout *g,int row);
  void removeColumn(QGridLayout *g, int col);
  void remove(QGridLayout *g, int row, int col, bool deleteWidgets);
  void deleteChildWidgets(QLayoutItem *item);

  LoadMonitor  *loadMonitor;
  QueueMonitor *queueMonitor;
  QString title;

  int timerId;
  int index = 0;

  QPushButton *scan;
  QPushButton *refresh;

protected:
  void timerEvent(QTimerEvent *);
};
