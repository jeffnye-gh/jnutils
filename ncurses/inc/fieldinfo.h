#pragma once
#include <cstdint>
#include <string>

struct FieldInfo {
  FieldInfo(size_t s) 
    : size(s),
      is_uninit(true),
      is_active(false),
      label("???"),
      data(size == 32 ? uninit32 : uninit64),
      active("-")
  {}
  FieldInfo(size_t _s,
            bool _uni,
            bool _act,
            std::string _l,
            std::string _d,
            std::string _a,
            uint32_t _l_x,
            uint32_t _l_y,
            uint32_t _d_x,
            uint32_t _d_y,
            uint32_t _a_x,
            uint32_t _a_y)
    : size(_s),
      is_uninit(_uni),
      is_active(_act),
      label(_l),
      data(_d),
      active(_a),
      label_x (_l_x),
      label_y (_l_y),
      data_x  (_d_x),
      data_y  (_d_y),
      active_x(_a_x),
      active_y(_a_y)
  {
  }

  void set_uninit()
  {
    is_uninit = true;
    is_active = false;
    data = size == 64 ? uninit64 : uninit32;
  }

  void set_modified(bool b)
  {
    if(b == true) {
      active = "*";
      is_active = true;
    } else {
      active = "-";
      is_active = false;
    }
  }

  size_t size;

  bool is_uninit;
  bool is_active;

  std::string label;
  std::string data;
  std::string active;

  uint32_t label_x{0};
  uint32_t label_y{0};

  uint32_t data_x{0};
  uint32_t data_y{0};

  uint32_t active_x{0};
  uint32_t active_y{0};

  static constexpr std::string_view uninit64 = "0x----------------";
  static constexpr std::string_view uninit32 = "0x--------";
  static constexpr std::string_view inactive = "-";

};

struct XregFieldInfo : public FieldInfo
{
  XregFieldInfo(size_t s=64) : FieldInfo(s) {}

  static constexpr uint32_t XREG_y = 1;

  static constexpr uint32_t XREG_0_Lbl_x = 2;
  static constexpr uint32_t XREG_0_Dat_x = 6;
  static constexpr uint32_t XREG_0_Act_x = 25;

  static constexpr uint32_t XREG_1_Lbl_x = 28;
  static constexpr uint32_t XREG_1_Dat_x = 32;
  static constexpr uint32_t XREG_1_Act_x = 51;

};

struct CsrFieldInfo : public FieldInfo
{
  CsrFieldInfo(size_t _size,
               bool _is_uninit,
               bool _is_active,
               std::string _label,
               std::string _data,
               std::string _active,
               uint32_t _label_x,
               uint32_t _label_y,
               uint32_t _data_x,
               uint32_t _data_y,
               uint32_t _active_x,
               uint32_t _active_y)
    : FieldInfo(_size,
                _is_uninit,
                _is_active,
                _label,
                _data,
                _active,
                _label_x,
                _label_y,
                _data_x,
                _data_y,
                _active_x,
                _active_y)
  { }

  static constexpr uint32_t CSR_y = 1;

  static constexpr uint32_t CSR_0_Lbl_x = 2;
  static constexpr uint32_t CSR_0_Dat_x = 14;
  static constexpr uint32_t CSR_0_Act_x = 33;

  static constexpr uint32_t CSR_1_Lbl_x = 37;
  static constexpr uint32_t CSR_1_Dat_x = 49;
  static constexpr uint32_t CSR_1_Act_x = 69;

};

struct BreakPointFieldInfo : public FieldInfo
{
  BreakPointFieldInfo(size_t _size,
                      bool _is_uninit,
                      bool _is_active,
                      std::string _label,
                      std::string _data,
                      std::string _active,
                      uint32_t _label_x,
                      uint32_t _label_y,
                      uint32_t _enb_x,
                      uint32_t _enb_y,
                      uint32_t _data_x,
                      uint32_t _data_y,
                      uint32_t _active_x,
                      uint32_t _active_y,
                      bool _enabled)
    : FieldInfo(_size,
                _is_uninit,
                _is_active,
                _label,
                _data,
                _active,
                _label_x,
                _label_y,
                _data_x,
                _data_y,
                _active_x,
                _active_y),
      enabled(_enabled),
      enable(enabled ? "E" : "D"),
      enable_x(_enb_x),
      enable_y(_enb_y)
  { }
 
  bool enabled;
  std::string enable; 
  uint32_t enable_x;
  uint32_t enable_y;

  static constexpr uint32_t BP_y = 1;
  
  static constexpr uint32_t BP_0_Lbl_x = 2;
  static constexpr uint32_t BP_0_Enb_x = 5;
  static constexpr uint32_t BP_0_Dat_x = 7;
  static constexpr uint32_t BP_0_Act_x = 26;

};

