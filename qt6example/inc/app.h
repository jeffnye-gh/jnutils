#pragma once
#include <QColor>
#include <cstdint>
namespace app
{
  enum FileType { FT_C_SRC, FT_ASM, FT_DUMP, FT_TR, FT_GENERIC };

  enum class ControlSet{ DNN, SAIN, CUST };

  enum PrefType {
    PT_NONE,
    PT_ColorPref
  };

  enum ItemTypes {
    IT_LineNums,

    IT_XRegBackground,
    IT_CRegBackground,
    IT_BkptBackground,

    IT_RegSelectionStyle,
    IT_BkptSelectionStyle,

    IT_Project_Panel,
    IT_System_Tab,
    IT_Break_Tab,
    IT_TCP_Tab,
    IT_State_Tab,
    IT_Tile_Panel,
    IT_Project_Header,
    IT_State_Header,
    IT_State_Horizontal_Header,
    IT_Break_Horizontal_Header,

    IT_Table_Entry,
    IT_Break_Entries
  };


  static const QColor   QC_LINE_NUM  = QColor(0x16,0x97,0xa4);
  static const QColor   QC_XREG_BACK = QColor(0x16,0x97,0xa4);
  static const QColor   QC_CREG_BACK = QColor(0x16,0x97,0xa4);
  static const QColor   QC_BKPT_BACK = QColor(0x16,0x97,0xa4);

  static const QString  REG_SELECT_STYLE =
    "selection-background-color: #19ed0b;"
    "selection-color: #000000;"
  ;

  static const QString  BKPT_SELECT_STYLE =
    "selection-background-color: #19ed0b;"
    "selection-color: #000000;"
  ;

  static const uint32_t tableEntryFontSize    = 8;
  static const uint32_t panelTabFontSize      = 8;
  static const uint32_t dockWidgetFontSize    = 8;
  static const uint32_t brkNumEntriesDflt     = 10;

  static const bool     prjPanelVisibleDflt   = true;
  static const bool     sysPanelVisibleDflt   = true;
  static const bool     brkPanelVisibleDflt   = true;
  static const bool     tcpPanelVisibleDflt   = false;
  static const bool     statePanelVisibleDflt = true;
  static const bool     tilePanelVisibleDflt  = true;

  static const bool     prjPanelHeaderVisible = true;
  static const bool     statePanelHeaderVisible = false;
  static const bool     stateHorzHeaderVisible = true;

  static const bool     brkHorzHeaderVisible = true;
};
