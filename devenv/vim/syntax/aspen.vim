" Vim syntax file
" Language:     Aspen
" Maintainer:   Jeff Nye
" Last Update:  20019

" For version 5.x: Clear all syntax items
" For version 6.x: Quit when a syntax file was already loaded
if version < 600
   syntax clear
elseif exists("b:current_syntax")
   finish
endif

" Set the local value of the 'iskeyword' option.
" NOTE: '?' was added so that verilogNumber would be processed correctly when
"       '?' is the last character of the number.
if version >= 600
   setlocal iskeyword=@,48-57,63,_,192-255
else
   set iskeyword=@,48-57,63,_,192-255
endif

" A bunch of useful Verilog keywords

syn keyword aspenStmt   isa isaext setisa opr opcregfile
syn keyword aspenStmt   iword ienc field erule enc

"syn keyword aspenStmt   always and assign automatic buf
"syn keyword aspenStmt   bufif0 bufif1 cell cmos
"syn keyword aspenStmt   config deassign defparam design
"syn keyword aspenStmt   disable edge endconfig
"syn keyword aspenStmt   endfunction endgenerate endmodule
"syn keyword aspenStmt   endprimitive endspecify endtable endtask
"syn keyword aspenStmt   event force function
"syn keyword aspenStmt   generate genvar highz0 highz1 ifnone
"syn keyword aspenStmt   incdir initial inout input
"syn keyword aspenStmt   instance integer large liblist
"syn keyword aspenStmt   library localparam macromodule medium
"syn keyword aspenStmt   module nand negedge nmos nor
"syn keyword aspenStmt   noshowcancelled not notif0 notif1 or
"syn keyword aspenStmt   output parameter pmos posedge primitive
"syn keyword aspenStmt   pull0 pull1 pulldown pullup
"syn keyword aspenStmt   pulsestyle_onevent pulsestyle_ondetect
"syn keyword aspenStmt   rcmos real realtime reg release
"syn keyword aspenStmt   rnmos rpmos rtran rtranif0 rtranif1
"syn keyword aspenStmt   scalared showcancelled signed small
"syn keyword aspenStmt   specify specparam strong0 strong1
"syn keyword aspenStmt   supply0 supply1 table task time tran
"syn keyword aspenStmt   tranif0 tranif1 tri tri0 tri1 triand
"syn keyword aspenStmt   trior trireg unsigned use vectored wait
"syn keyword aspenStmt   wand weak0 weak1 wire wor xnor xor
"syn keyword verilogLabel       begin end fork join
"syn keyword verilogConditional if else case casex casez default endcase
"syn keyword verilogRepeat      forever repeat while for

syn keyword aspenProcess bind reap nvp list

syn keyword aspenTODO contained TODO FIXME

syn match   aspenOperator "[:><]"
syn match   aspenOperator ":"
syn match   aspenAttr "\.iword"

"syn match   verilogOperator "[&|~><!)(*%@+/=?:;}{,.\^\-\[\]]"

"syn region  aspenComment   start="/\*" end="\*/" contains=verilogTodo,@Spell
"syn region  aspenComment   start="##" end="##" contains=verilogTodo,@Spell
syn match   aspenComment   "# .*" contains=aspenTODO,@Spell

syn match   aspenFileName "[a-zA-Z_]+[a-zA-Z0-9_]*\.(?:asp|ah)"
syn match   aspenInline "include .*" contains=aspenFileName
"syn match   verilogGlobal "`[a-zA-Z0-9_]\+\>"
"syn match verilogGlobal "`celldefine"
"syn match verilogGlobal "`default_nettype"
"syn match verilogGlobal "`define"
"syn match verilogGlobal "`else"
"syn match verilogGlobal "`elsif"
"syn match verilogGlobal "`endcelldefine"
"syn match verilogGlobal "`endif"
"syn match verilogGlobal "`ifdef"
"syn match verilogGlobal "`ifndef"
"syn match verilogGlobal "`include"
"syn match verilogGlobal "`line"
"syn match verilogGlobal "`nounconnected_drive"
"syn match verilogGlobal "`resetall"
"syn match verilogGlobal "`timescale"
"syn match verilogGlobal "`unconnected_drive"
"syn match verilogGlobal "`undef"
"syn match   verilogGlobal "$[a-zA-Z0-9_]\+\>"

"syn match   verilogConstant "\<[A-Z][A-Z0-9_]\+\>"

syn match   aspenNumber "\(\<\d\+\|\)'[sS]\?[bB]\s*[0-1_xXzZ?]\+\>"
syn match   aspenNumber "\(\<\d\+\|\)'[sS]\?[oO]\s*[0-7_xXzZ?]\+\>"
syn match   aspenNumber "\(\<\d\+\|\)'[sS]\?[dD]\s*[0-9_xXzZ?]\+\>"
syn match   aspenNumber "\(\<\d\+\|\)'[sS]\?[hH]\s*[0-9a-fA-F_xXzZ?]\+\>"
syn match   aspenNumber "\<[+-]\=[0-9_]\+\(\.[0-9_]*\|\)\(e[0-9_]*\|\)\>"

"syn region  verilogString start=+"+ skip=+\\"+ end=+"+ contains=verilogEscape,@Spell
"syn match   verilogEscape +\\[nt"\\]+ contained
"syn match   verilogEscape "\\\o\o\=\o\=" contained

" Directives
"syn match   verilogDirective   "//\s*synopsys\>.*$"
"syn region  verilogDirective   start="/\*\s*synopsys\>" end="\*/"
"syn region  verilogDirective   start="//\s*synopsys dc_script_begin\>" end="//\s*synopsys dc_script_end\>"

"syn match   verilogDirective   "//\s*\$s\>.*$"
"syn region  verilogDirective   start="/\*\s*\$s\>" end="\*/"
"syn region  verilogDirective   start="//\s*\$s dc_script_begin\>" end="//\s*\$s dc_script_end\>"

"Modify the following as needed.  The trade-off is performance versus
"functionality.
syn sync minlines=50

" Define the default highlighting.
" For version 5.7 and earlier: only when not done already
" For version 5.8 and later: only when an item doesn't have highlighting yet
if version >= 508 || !exists("did_verilog_syn_inits")
   if version < 508
      let did_verilog_syn_inits = 1
      command -nargs=+ HiLink hi link <args>
   else
      command -nargs=+ HiLink hi def link <args>
   endif

   " The default highlighting.
"   HiLink verilogCharacter       Character
"   HiLink verilogConditional     Conditional
"   HiLink verilogRepeat          Repeat
"   HiLink verilogString          String
   HiLink aspenTODO            Todo
   HiLink aspenComment         Comment
"   HiLink verilogConstant        Constant
"   HiLink verilogLabel           Label
   HiLink aspenNumber          Number

   HiLink aspenOperator        Special
   HiLink aspenStmt            Statement
   HiLink aspenProcess         Define
   HiLink aspenAttr              Constant

"   HiLink verilogGlobal          Define
   HiLink aspenInline          SpecialComment
"   HiLink verilogDirective       SpecialComment
"   HiLink verilogEscape          Special

   delcommand HiLink
endif

let b:current_syntax = "aspen"

" vim: ts=8
