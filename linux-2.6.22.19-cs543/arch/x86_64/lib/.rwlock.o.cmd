cmd_arch/x86_64/lib/rwlock.o := gcc -Wp,-MD,arch/x86_64/lib/.rwlock.o.d  -nostdinc -isystem /usr/lib/gcc/x86_64-linux-gnu/4.6/include -D__KERNEL__ -Iinclude  -include include/linux/autoconf.h -D__ASSEMBLY__   -m64    -c -o arch/x86_64/lib/rwlock.o arch/x86_64/lib/rwlock.S

deps_arch/x86_64/lib/rwlock.o := \
  arch/x86_64/lib/rwlock.S \
  include/linux/linkage.h \
  include/asm/linkage.h \
  include/asm/rwlock.h \
  include/asm/alternative-asm.i \
    $(wildcard include/config/smp.h) \
  include/asm/dwarf2.h \
    $(wildcard include/config/as/cfi.h) \
    $(wildcard include/config/as/cfi/signal/frame.h) \

arch/x86_64/lib/rwlock.o: $(deps_arch/x86_64/lib/rwlock.o)

$(deps_arch/x86_64/lib/rwlock.o):
