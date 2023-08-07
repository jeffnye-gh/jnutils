#include "xmw.h"
#include "controls.h"
#include "json/json.h"
#include "json/writer.h"
#include <iostream>
#include <fstream>
using namespace std;

#define JSON_FILE_FILTER "JSON(*.json);; All files (*.*)"
// -----------------------------------------------------------------------
// FILE SLOTS
// -----------------------------------------------------------------------
void Xmw::fileNew()
{
  if (maybeSave()) {
//    textEdit->clear();
    setCurrentFile("");
  }
}
// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
void Xmw::fileOpen()
{
  if (maybeSave()) {
    QFileDialog fd(this,"Open file");
    fd.setOption(QFileDialog::DontUseNativeDialog);
    fd.setNameFilter(JSON_FILE_FILTER);

    QString fileName="";
    if(fd.exec()) fileName = fd.selectedFiles()[0];

    if (!fileName.isEmpty()) loadFile(fileName);
  }
}
// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
bool Xmw::fileSave()
{
  if (curFile.isEmpty()) {
    return fileSaveAs();
  } else {
    return saveFile(curFile);
  }
}
// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
bool Xmw::fileSaveAs()
{
  QFileDialog fd(this,"Save file as");
  fd.setOption(QFileDialog::DontUseNativeDialog);
  fd.setNameFilter(JSON_FILE_FILTER);
  fd.setAcceptMode(QFileDialog::AcceptSave);
  fd.setLabelText(QFileDialog::Accept,"Save");

  QString fileName="";
  if(fd.exec()) fileName = fd.selectedFiles()[0];

  if (fileName.isEmpty()) return false;
  return saveFile(fileName);
}
// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
bool Xmw::saveFile(const QString &fileName)
{
  QFile file(fileName);
  if (!file.open(QFile::WriteOnly | QFile::Text)) {
      QMessageBox::warning(this, "CAMDASH",
                   QString("Cannot write file %1:\n%2.")
                   .arg(fileName).arg(file.errorString()));
      return false;
  }

  Json::Value env;

  env["architecture"]   = prefs.architecture.toStdString();
  env["uarchversion"]   = prefs.uarchversion.toStdString();
                       
  env["benchmarks"]     = prefs.benchmarks.toStdString();
  env["buildroot"]      = prefs.buildroot.toStdString();
  env["cam"]            = prefs.cam.toStdString();
  env["condortop"]      = prefs.condortop .toStdString();
  env["cpmdromajo"]     = prefs.cpmdromajo.toStdString();
  env["cpmtools"]       = prefs.cpmtools.toStdString();
  env["crosscompile"]   = prefs.crosscompile.toStdString();
  env["dromajo"]        = prefs.dromajo.toStdString();
  env["kernel"]         = prefs.kernel.toStdString();
  env["map"]            = prefs.map .toStdString();
  env["olympia"]        = prefs.olympia.toStdString();
  env["opensbi"]        = prefs.opensbi.toStdString();
  env["patches"]        = prefs.patches.toStdString();
  env["riscvprefix"]    = prefs.riscvprefix.toStdString();
  env["baremetaltools"] = prefs.baremetaltools.toStdString();
  env["linuxtools"]     = prefs.linuxtools.toStdString();
  env["sparta"]         = prefs.sparta.toStdString();
  env["spike"]          = prefs.spike.toStdString();
  env["veer"]           = prefs.veer.toStdString();
  env["whisper"]        = prefs.whisper.toStdString();

  Json::Value root;
  root["environment"] = env;

  Json::StreamWriterBuilder writer; 
  writer["indentation"] = "  ";

  ofstream out(fileName.toStdString());

  if(!out.is_open()) {
    QMessageBox::critical(this, "CAMDASH",
                 QString("Could not write to file %1.").arg(fileName));
  
    return false;
  }

  root["servers"] = servers;
  root["lsfqueues"] = lsfqueues;
  root["testcontrols"] = testcontrols;

  std::string jsonString = Json::writeString(writer,root);

  out << jsonString;
  out << endl;
  out.close(); 

  setCurrentFile(fileName);
  statusBar()->showMessage(tr("File saved"), 2000);
  return true;
}
// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
bool Xmw::loadFile(const QString &fileName)
{
  QFile file(fileName);
  QFileInfo info(file);

  if(info.suffix() == "json") {

    if(loadJsonFile(fileName)) {
      setCurrentFile(fileName);
      statusBar()->showMessage(tr("File loaded"), 2000);
      return true;
    }

  } else {
    //For now only json is comprehended
    QMessageBox::critical(this, "CamDash",
       QString("Unknown file type\n\nname: %1:\ntype: %2")
         .arg(info.completeBaseName()).arg(info.suffix()));

    return false;
  }

  return false;
}
// -----------------------------------------------------------------------
#define qfs(s) QString::fromStdString(s)
// -----------------------------------------------------------------------
bool Xmw::loadJsonFile(QString fileName)
{
  msg.dmsg("+loadJsonFile");

  QFile file(fileName);
  QFileInfo info(file);

  if (!file.open(QFile::ReadOnly | QFile::Text)) {
      QMessageBox::warning(this, "CamDash",
         QString("Cannot read file %1:\n%2.")
           .arg(info.baseName()).arg(file.errorString()));
      return false;
  }

  string fName = fileName.toStdString();

  ifstream in(fName);
  if(!in.is_open()) {
    QMessageBox::critical(this, "CamDash",
       QString("Can not open json file\n\nname: %1")
         .arg(info.completeBaseName()));
    return false;
  }

  Json::Value root;
  in >> root;
  in.close();

  Json::Value env; env = root["environment"];

  prefs.architecture   = qfs(env["architecture"].asString());
  prefs.uarchversion   = qfs(env["uarchversion"].asString());
  prefs.condortop      = qfs(env["condortop"].asString());
  prefs.baremetaltools = qfs(env["baremetaltools"].asString());
  prefs.benchmarks     = qfs(env["benchmarks"].asString());
  prefs.buildroot      = qfs(env["buildroot"].asString());
  prefs.cam            = qfs(env["cam"].asString());
  prefs.cpmdromajo     = qfs(env["cpmdromajo"].asString());
  prefs.crosscompile   = qfs(env["crosscompile"].asString());
  prefs.dromajo        = qfs(env["dromajo"].asString());
  prefs.kernel         = qfs(env["kernel"].asString());
  prefs.linuxtools     = qfs(env["linuxtools"].asString());
  prefs.map            = qfs(env["map"].asString());
  prefs.sparta         = qfs(env["sparta"].asString());
  prefs.olympia        = qfs(env["olympia"].asString());
  prefs.opensbi        = qfs(env["opensbi"].asString());
  prefs.patches        = qfs(env["patches"].asString());
  prefs.riscvprefix    = qfs(env["riscvprefix"].asString());
  prefs.spike          = qfs(env["spike"].asString());
  prefs.cpmtools       = qfs(env["cpmtools"].asString());
  prefs.veer           = qfs(env["veer"].asString());
  prefs.whisper        = qfs(env["whisper"].asString());

  servers      = root["servers"];
  lsfqueues    = root["lsfqueues"];
  testcontrols = root["testcontrols"];

  controls->buildControlDialog(testcontrols);

  populateStatusDock();

  return true;
}
// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
void Xmw::populateStatusDock()
{
  map<QString,Server> serverMap;

  QList<Server> serverList;
  for (Json::Value::ArrayIndex i = 0; i != servers.size(); i++) {
    QString name;
    QString ip;

    if (servers[i].isMember("name")) {
      name = QString::fromStdString(servers[i]["name"].asString());
    }

    if (servers[i].isMember("ip")) {
      ip = QString::fromStdString(servers[i]["ip"].asString());
    }

    Server s(ip,name);
    serverList << s;

    serverMap.insert(make_pair(name,s)); 
  }

  QList<LsfQueue> queueList;
  for (Json::Value::ArrayIndex i = 0; i != lsfqueues.size(); i++) {
    QString queueName="";
    QString serverName="";
    uint32_t maxSlots=0;

    if (lsfqueues[i].isMember("name")) {
      queueName = QString::fromStdString(lsfqueues[i]["name"].asString());
    }

    if (lsfqueues[i].isMember("server")) {
      serverName = QString::fromStdString(lsfqueues[i]["server"].asString());
    }

    if (lsfqueues[i].isMember("maxslots")) {
      maxSlots = lsfqueues[i]["maxslots"].asUInt();
    }

    if(serverMap.find(serverName) != serverMap.end()) {
      LsfQueue q(queueName,serverMap[serverName],maxSlots);
      queueList << q;
    }
  }

  statusDock->populatePanels(serverList,queueList);
}
// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
void Xmw::documentWasModified()
{
//  setWindowModified(textEdit->document()->isModified());
}
// -----------------------------------------------------------------------
// EDIT SLOTS
// -----------------------------------------------------------------------
void Xmw::editAddTestCase()
{
  cout<<"HERE edit add test case"<<endl;
  TestCase tc;
  TestPushButton *button = new TestPushButton(tc,"",this);
  button->hide();
  TestCaseEditDialog *d = new TestCaseEditDialog(button,"");
  if(d->exec() == QDialog::Accepted) {
    int index = controls->tabs->currentIndex();
    QString tabName = controls->tabs->tabText(index);
    QString testName = d->nameLE->displayText();
    QString compPlainText = d->compTE->toPlainText();
    QString simPlainText  = d->simTE->toPlainText();
    cout<<"HERE '"<<compPlainText.toStdString()<<"'"<<endl;
  }
}
// -----------------------------------------------------------------------
void Xmw::editDelTestCase()
{
  cout<<"HERE edit del test case"<<endl;
  
}
// -----------------------------------------------------------------------
// VIEW SLOTS
// -----------------------------------------------------------------------
void Xmw::viewShowStatus()
{
  if(viewShowStatusAct->isChecked()) statusDock->show();
  else                               statusDock->hide();
}
// -----------------------------------------------------------------------
// HELP SLOTS
// -----------------------------------------------------------------------
void Xmw::helpAbout()
{
  QMessageBox::about(this, "Performance dashboard","version: 1.0");
}
// -----------------------------------------------------------------------
void Xmw::helpIssues()
{
  std::cout<<std::endl<<"Known issues in this version"<<std::endl;
  for(auto s : issuesVec) {
    std::cout<<"  -"<<s.toStdString()<<std::endl;
  }
}
