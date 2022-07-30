# yyf: close without confirm
set confirm off

# yyf: logging
set logging on
set logging file gdb.txt
set logging overwrite off
set logging redirect off
set trace-commands on

# yyf: info display pagination
set pagination off

# yyf: startup quickly, only 11.x branch of GDB
# set startup-quietly on

# yyf: step in func without debug info
set step-mode on
# yyf: show tail call info
set debug entry-values 1

set disassembly-flavor intel
set width unlimited
set height unlimited

#source ~/gdbinit/binbase.py
#source ~/gdbinit/heap.py

#define peda
#  source ~/gdbinit/load_peda.py
#end

#define gef
#  source ~/gdbinit/gef/gef.py
#end

define tcp
  file socat
  catch exec
  set follow-fork-mode child
  r tcp4-l:$arg0,bind=127.0.0.1,reuseaddr exec:$arg1,sigint,stderr
end

set history filename ~/.gdb_history
set history save on
set history size 100000
set history remove-duplicates 10

define multicont
set $total = $arg0
  set $i = 0
   while($i<$total)
     set $i = $i + 1
     continue
   end
end



