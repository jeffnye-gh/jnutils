#pragma once
#include "msg.h"
#include "aspenapi.h"
#include "system.h"
#include "machine.h"
#include "builder.h"
#include "spreadsheet.h"
#include <QtCore>
#include <QtGui>
#if QT_VERSION >= 0x050000
#include <QtWidgets>
#endif
#include <string>
#include <map>
#include <vector>

#define EN_TR 1

#if EN_TR == 1
#define ATR(s) std::cout<<s<<std::endl;
#else
#define ATR(s)
#endif

class IsaEditor;
// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
struct SpaceShipSort
{
  SpaceShipSort(std::string s, int i) : m_s(s),m_i(i) {}
  std::string m_s; int m_i;
};
// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
namespace std
{
  template<> struct greater<SpaceShipSort*>
  {
    bool operator()(SpaceShipSort const* p1, SpaceShipSort const* p2)
    {
      if(!p1) return false;
      if(!p2) return true;
      return p1->m_s > p2->m_s;
    }
  };

  template<> struct less<SpaceShipSort*>
  {
    bool operator()(SpaceShipSort const* p1, SpaceShipSort const* p2)
    {
      if(!p1) return true;
      if(!p2) return false;
      return p1->m_s < p2->m_s;
    }
  };
};
// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
class AspenGui : public QMainWindow
{
    Q_OBJECT

public:
  AspenGui(int,char**,IsaEditor*);

  enum SysSheetNums {
    SysInfoTab,
    SysMachTab,
    SysDefinesTab,
    SysFilesTab,
    SysStructureTab,
    LAST_SYS_TAB
  };

  enum MachSheetNums {
    MachInfoTab,
    MachISATab,
    MachEncodeTableTab,
    MachEncodeFormatsTab,
    MachPipelinesTab,
    MachRegFilesTab,
    MachDefinesTab,
    MachStructureTab,
    MachSupportTab,
    MachOpcodesTab,
    MachEncodeRulesTab,
    MachFuncUnitsTab,
    LAST_MACH_TAB
  };

  bool docsAreClean() { return clean; }
  void setClean(bool b) { clean = b; }
  void setCurrentMdlFile(QString f) { fileName = f; }
  void disableOnClose();
  void enableOnOpen();
  void disableElements(void);

  QString getCurrentMdlFile() { return fileName; }
  std::map<std::string,aspen::Machine>::iterator 
                                          getCurrentMachine(aspen::System&);

  bool maybeSave();
  bool readFile(QString);  
  bool writeFile(QString);  

  QString cleanUpHtml(QString);
  void clearStructures();
  void clearInterface();
  bool populate();
  void clear(bool);

  bool updateAndWriteMDL(QString);
  bool updateBuilderState();
  bool savePcodeFile(QString&);

  void createActions(void);
  void createFileActions(void);
  void createEditActions(void);
  void createFormatActions(void);
  void createSortActions(void);
  void createToolsActions(void);
  void createHelpActions(void);

  void createCntxActions(void);
  void connectCntxActions(void);

  void connectTableSignals(Spreadsheet*);

  void createMenuBarMenus();
  void createDefaultTabs(void);

  void createToolBars(void);
  void createStatusBar(void);

  void createTabCntxMenus();
  void createSheetCntxMenu(Spreadsheet*);

  void createComboBox(void);

  void initIsaEditor(void);

  QTabWidget* createMachTabSet();

  bool criticalDialog(const QString&,const QString&);
  void overWriteButtonBox();

  Spreadsheet *newSheet(int,int,const QStringList&);

  bool addSystemMdlInfo();
  bool addMachineMdlInfo(int,aspen::Machine&);


  //Mach&Sys 
  void addInfoTab(Spreadsheet *s,
                  QStringList&,
                  aspen::ChangeLog&,
                  std::vector<aspen::Nvt>&,
                  std::map<std::string,std::string>&,
                  QString);
  void addDefinesTab(Spreadsheet*,std::map<std::string,aspen::Nvt>&);

  //Sys 
  void addFilesTab(Spreadsheet*,std::map<std::string,std::string>&);
  void addStructureTab(Spreadsheet*,aspen::System&);

  //Mach 
  void addStructureTab(Spreadsheet*,aspen::Machine&);
  void addSupportTab(Spreadsheet*,aspen::Machine&);
  void addOpcodesTab(Spreadsheet*,aspen::Machine&);
  void addEncodeRulesTab(Spreadsheet*,aspen::Machine&);
  void addPipelinesTab(Spreadsheet*,aspen::Machine&);
  void addRegFilesTab(Spreadsheet*,aspen::Machine&);
  void addFuncUnitsTab(Spreadsheet*,aspen::Machine&);
  void addEncodeTableTab(Spreadsheet*,aspen::Machine&);
  void addEncodeFormatsTab(Spreadsheet*,aspen::Machine&);
  bool addMachineInstructions(int,aspen::Machine&);
  bool addMachineInstructions(Spreadsheet*,aspen::Machine&);
  void insHeaderLabels(Spreadsheet*,int,int);
  void addInsOperandsToRow(Spreadsheet*,aspen::Instruction&,int);
  void setAlignmentByRole(Spreadsheet*,int,int,int);
  void addOpcBitsToRow(Spreadsheet*,aspen::Machine&,
                       aspen::Instruction&,int,uint32_t&);
  QString getUseDefQString(aspen::Instruction&);
  QString getOpcBitPositions(aspen::Instruction&);

  int  addTable(Spreadsheet*,int,int,std::map<std::string,aspen::Nvp>&);
  int  addTable(Spreadsheet*,int,int,std::map<std::string,aspen::Nvt>&);
  int  addTable(Spreadsheet*,int,int,std::map<std::string,std::string>&);
  int  addTable(Spreadsheet*,int,int,std::vector<aspen::Nvt>&);
  int  addTable(Spreadsheet*,int,int,std::vector<aspen::Nvp>&);
  int  addNvxHeaders(Spreadsheet*,int,int,bool);
  void padTableRow(Spreadsheet*,int,int,int);

  void addTblItem(QString,Spreadsheet*,int,int,int,int);
  void addTblItem(QString,Spreadsheet*,int,int,int);
  void addTblItem(QString,Spreadsheet*,int,int);

  void setHeadingProperties(QTableWidgetItem*);
  void setLabelProperties(QTableWidgetItem*);
  void setFontProperties(QTableWidgetItem*);

  void copyColWidth(Spreadsheet*,uint32_t,uint32_t);

protected:
  void closeEvent(QCloseEvent *e);

signals:
  void clearAllSheets(void);
  void disableSheetSigs(void);
  void enableSheetSigs(void);

  void disableRecalc(void);
  void restoreRecalc(void);
  void modified(void);
  void updateStatus(void);

private slots:
  void sFileNew(void);
  void sFileClose(void);
  void sFileOpen(void);
  void sFileReload(void);
  bool sFileSave(void);
  bool sFileSaveAs(void);
  bool sFileExportHtmlDocs(void);
  bool sFileExportDescTxt(void);
  bool sFileExportPcodeTxt(void);
  void sFileExit() { if (maybeSave()) close(); }

  void sEditUndo(){}
  void sEditRedo(){}

  void sEditCut() {}
  void sEditCopy() {}
  void sEditPaste() {}

  void sEditClear() {}
  void sEditDelete() {}

  void sEditFind() {}
  void sEditReplace() {}

  void sEditGoTo() {}

  void sEditSelectAll() {}
  void sEditSelectNone() {}

  void sFormatCells() {}
  void sFormatRowHeight() {}
  void sFormatRowAutoFit() {}
  void sFormatRowHide() {}
  void sFormatRowUnhide() {}
  void sFormatColWidth() {}
  void sFormatColAutoFit() {}
  void sFormatColHide() {}
  void sFormatColUnhide() {}

  void sFormatSheetRename() {}
  void sFormatSheetHide() {}
  void sFormatSheetUnhide() {}

  void sSortByMnemonicAsc() {}
  void sSortByMnemonicDes() {}
  void sSortByOpcodeNameAsc() {}
  void sSortByOpcodeNameDes() {}
  void sSortByOpcodeAsc() {}
  void sSortByOpcodeDes() {}
  void sSortByIWordFormat() {}
  void sSortByOperands() {}

  void sToolsBinFill() {}
  void sToolsGenEncoding();
  void sToolsCheckEnc() {}

  void sToolsAddUnit() {}
  void sToolsDelUnit() {}
  void sToolsDupUnit() {}

  void sToolsIsaEditor();
  void sToolsAsipBuilder() {}
  void sToolsGenModel();
  void sToolsGenRtl();
  void sToolsNewSys();
  void sToolsNewMachine();

  void sToolsInsInstruction() {}
  void sToolsInsIWordBit() {}
  void sToolsInsOperand() {}
  void sToolsInsComment() {}

  void sHelpHelp()  {};
  void sHelpAbout() {};
  void sHelpDebug();
  void sDebugSlot() {};

  void sTabCntxRename() {}
  void sTabCntxMove() {}
  void sTabCntxCopy() {}
  void sTabCntxPaste() {}
  void sTabCntxClear() {}
  void sTabCntxDelete() {}

  void sSpreadCntxSetBitType() {}

  void sColHdrCntxCut() {}
  void sColHdrCntxCopy() {}
  void sColHdrCntxPaste() {}
  void sColHdrCntxInsert() {}
  void sColHdrCntxDelete() {}
  void sColHdrCntxClear() {}
  void sColHdrCntxFormatCells() {}
  void sColHdrCntxWidth() {}
  void sColHdrCntxHide() {}
  void sColHdrCntxUnhide() {}

  void sRowHdrCntxCut() {}
  void sRowHdrCntxCopy() {}
  void sRowHdrCntxPaste() {}
  void sRowHdrCntxInsert() {}
  void sRowHdrCntxDelete() {}
  void sRowHdrCntxClear() {}
  void sRowHdrCntxFormatCells() {}
  void sRowHdrCntxWidth() {}
  void sRowHdrCntxHide() {}
  void sRowHdrCntxUnhide() {}

  void sClearContents(void) {}
  void sDisableRecalc(void) {}
  void sRestoreRecalc(void) {}
  void sSpreadsheetModified(void) {}
  void sUpdateStatusBar(void) {}
  void sDisableSigs(void) {}
  void sEnableSigs(void) {}

  void sIsaTabCurrentChanged(int) {}
  void sMdlTabCurrentChanged(int) {}
  void sComboBoxIndexChanged(int);

  //isaeditor
  void sIeCloseEventReq(void);
  void sIeSaveChanges(void);
  void sIeClearStructuresReq(void);
  void sIeResetApiReq(void);

public: //not a slot, but execution is indirectly related to
        //the sIe... slots above, so this is in slots.cpp.
  bool sIeMaybeSaveReq(void);
  // ----------------------------------------------------------------
  std::map<std::string,aspen::Machine>::iterator confirmMachine(QString&);
  // ----------------------------------------------------------------
private:

  QAction *aKeyPressEsc,*aFileNew,*aFileOpen,*aFileClose,*aFileSave,
          *aFileSaveAs,*aFileExportDocs,*aFileExportPcode,*aEditUndo,
          *aEditRedo,*aEditCut,*aEditCopy,*aEditPaste,*aEditClear,
          *aEditDelete,*aEditFind,*aEditReplace,*aEditGoTo,*aEditSelectAll,
          *aEditSelectNone,*aFileExit,*aFileReload,*aFilePreview,
          *aFilePrint,*aFileExportPdf,*aToolsInsInstruction,*aToolsInsIWordBit,
          *aToolsInsOperand,*aToolsInsComment,
          *aToolsIsaEditor,*aToolsGenModel,*aToolsGenRtl,*aToolsNewSys,
          *aToolsNewMachine;

  QAction *aFormatCells,*aFormatRowHeight,*aFormatRowAutoFit,
          *aFormatRowHide,*aFormatRowUnhide,*aFormatColWidth,
          *aFormatColAutoFit,*aFormatColHide,*aFormatColUnhide,
          *aFormatSheetRename,*aFormatSheetHide,*aFormatSheetUnhide;

  QAction *aSortByMnemonicAsc,*aSortByMnemonicDes,*aSortByOpcodeNameAsc,
          *aSortByOpcodeNameDes,*aSortByOpcodeAsc,*aSortByOpcodeDes,
          *aSortByIWordFormat,*aSortByOperands,*aToolsBinFill,
          *aToolsGenEncoding,*aToolsAddUnit,*aToolsDelUnit,*aToolsDupUnit,
          *aToolsCheckEnc;

  QAction *aHelpHelp,*aHelpAbout,*aHelpDebug,*aDebug;

  QMenu *mFile,*mEdit,*mHelp,*mInsert,*mFormat,*mTools,*mSort,*mMnemonic,
        *mOpcode,*mOpcodeName;

  QAction *aSpreadCntxCut,*aSpreadCntxCopy,*aSpreadCntxPaste,
          *aSpreadCntxClear,*aSpreadCntxSetBitType,*aTabCntxRename,
          *aTabCntxMove,*aTabCntxCopy,*aTabCntxPaste,*aTabCntxClear,
          *aTabCntxDelete,*aColHdrCntxCut,*aColHdrCntxCopy,*aColHdrCntxPaste,
          *aColHdrCntxInsert,*aColHdrCntxDelete,*aColHdrCntxClear,
          *aColHdrCntxFormatCells,*aColHdrCntxWidth,*aColHdrCntxHide,
          *aColHdrCntxUnhide,*aRowHdrCntxCut,*aRowHdrCntxCopy,
          *aRowHdrCntxPaste,*aRowHdrCntxInsert,*aRowHdrCntxDelete,
          *aRowHdrCntxClear,*aRowHdrCntxFormatCells,*aRowHdrCntxWidth,
          *aRowHdrCntxHide,*aRowHdrCntxUnhide;

  QToolBar *tbFile,*tbEdit,*tbCellInfo;

  QLabel *lCell,*lLocation,*lFormula;
  QLineEdit *leFormula;

  QStatusBar *statusBar;
  QComboBox *machCombo;
  QLabel    *lIsa;
  QWidget *centralWidget;
  QGridLayout *centralLayout;

private: //initialized in C'tor

  int ac;
  char **av;

  IsaEditor *iedit;
  aspen::Builder *bldr;
  aspen::AspenApi api;

  QString fileName;

  bool clean;
  bool ieditIsOpen;

  QTabWidget *sysTabs;
  QMap<uint32_t,QTabWidget*> machsTabs;

  QList<QStringList> machSheetHeaders;

  int machTabIndex, mdlTabIndex;

  QStringList hdrLabels;
  QStringList oprTypes;
  QStringList units;
  QStringList eRules;

  std::map<std::string,std::string> instrDesc;
  std::map<std::string,std::string> instrPcode;

  bool isaEditorIsOpen;
  std::map<std::string,aspen::Machine> machines;
  bool fileOverwrite;

private:

  static const QString rpath;
  static const bool DEFAULT_TABS;
  static const bool NO_DEFAULT_TABS;

  static const QTabWidget::TabPosition defaultTabPos;

  static const QStringList sysTabNames;
  static const QStringList machTabNames;
  static const QStringList leftCols;
  static const QStringList rightCols;

  static const std::vector<QColor> operandBitColors;

  static const QColor opcodeBitBgClr;
  static const QColor opcodeBitFgClr;

  static const QColor operandBitFgClr;

  static const QColor constBitBgClr;
  static const QColor constBitFgClr;

  static const QColor opcNameBgClr;

  static const QColor headingBgClr;
  static const QColor headingFgClr;

  static const QString unitComboStyle;
  static const QString machComboDefaultText;
};
