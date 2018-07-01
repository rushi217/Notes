
 // Routines to let C code use special x86 instructions.
00002 
00003 static inline uchar
00004 inb(ushort port)
00005 {
00006   uchar data;
00007 
00008   asm volatile("in %1,%0" : "=a" (data) : "d" (port));
00009   return data;
00010 }
00011 
00012 static inline void
00013 insl(int port, void *addr, int cnt)
00014 {
00015   asm volatile("cld; rep insl" :
00016                "=D" (addr), "=c" (cnt) :
00017                "d" (port), "0" (addr), "1" (cnt) :
00018                "memory", "cc");
00019 }
00020 
00021 static inline void
00022 outb(ushort port, uchar data)
00023 {
00024   asm volatile("out %0,%1" : : "a" (data), "d" (port));
00025 }
00026 
00027 static inline void
00028 outw(ushort port, ushort data)
00029 {
00030   asm volatile("out %0,%1" : : "a" (data), "d" (port));
00031 }
00032 
00033 static inline void
00034 outsl(int port, const void *addr, int cnt)
00035 {
00036   asm volatile("cld; rep outsl" :
00037                "=S" (addr), "=c" (cnt) :
00038                "d" (port), "0" (addr), "1" (cnt) :
00039                "cc");
00040 }
00041 
00042 static inline void
00043 stosb(void *addr, int data, int cnt)
00044 {
00045   asm volatile("cld; rep stosb" :
00046                "=D" (addr), "=c" (cnt) :
00047                "0" (addr), "1" (cnt), "a" (data) :
00048                "memory", "cc");
00049 }
00050 
00051 struct segdesc;
00052 
00053 static inline void
00054 lgdt(struct segdesc *p, int size)
00055 {
00056   volatile ushort pd[3];
00057 
00058   pd[0] = size-1;
00059   pd[1] = (uint)p;
00060   pd[2] = (uint)p >> 16;
00061 
00062   asm volatile("lgdt (%0)" : : "r" (pd));
00063 }
00064 
00065 struct gatedesc;
00066 
00067 static inline void
00068 lidt(struct gatedesc *p, int size)
00069 {
00070   volatile ushort pd[3];
00071 
00072   pd[0] = size-1;
00073   pd[1] = (uint)p;
00074   pd[2] = (uint)p >> 16;
00075 
00076   asm volatile("lidt (%0)" : : "r" (pd));
00077 }
00078 
00079 static inline void
00080 ltr(ushort sel)
00081 {
00082   asm volatile("ltr %0" : : "r" (sel));
00083 }
00084 
00085 static inline uint
00086 readeflags(void)
00087 {
00088   uint eflags;
00089   asm volatile("pushfl; popl %0" : "=r" (eflags));
00090   return eflags;
00091 }
00092 
00093 static inline uint
00094 xchg(volatile uint *addr, uint newval)
00095 {
00096   uint result;
00097   
00098   // The + in "+m" denotes a read-modify-write operand.
00099   asm volatile("lock; xchgl %0, %1" :
00100                "+m" (*addr), "=a" (result) :
00101                "1" (newval) :
00102                "cc");
00103   return result;
00104 }
00105 
00106 static inline void
00107 loadgs(ushort v)
00108 {
00109   asm volatile("movw %0, %%gs" : : "r" (v));
00110 }
00111 
00112 static inline void
00113 cli(void)
00114 {
00115   asm volatile("cli");
00116 }
00117 
00118 static inline void
00119 sti(void)
00120 {
00121   asm volatile("sti");
00122 }
00123 
00124 // Layout of the trap frame built on the stack by the
00125 // hardware and by trapasm.S, and passed to trap().
00126 struct trapframe {
00127   // registers as pushed by pusha
00128   uint edi;
00129   uint esi;
00130   uint ebp;
00131   uint oesp;      // useless & ignored
00132   uint ebx;
00133   uint edx;
00134   uint ecx;
00135   uint eax;
00136 
00137   // rest of trap frame
00138   ushort gs;
00139   ushort padding1;
00140   ushort fs;
00141   ushort padding2;
00142   ushort es;
00143   ushort padding3;
00144   ushort ds;
00145   ushort padding4;
00146   uint trapno;
00147 
00148   // below here defined by x86 hardware
00149   uint err;
00150   uint eip;
00151   ushort cs;
00152   ushort padding5;
00153   uint eflags;
00154 
00155   // below here only when crossing rings, such as from user to kernel
00156   uint esp;
00157   ushort ss;
00158   ushort padding6;
00159 };
