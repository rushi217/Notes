// Segments in proc->gdt.
#define NSEGS     7

// Per-CPU state
struct cpu {
  uchar id;                    // Local APIC ID; Advanced Programmable Interrupt Controller; IDs each core
  struct context *scheduler;   // swtch() here to enter scheduler
  struct taskstate ts;         // Used by x86 to find stack for interrupt
  struct segdesc gdt[NSEGS];   // x86 global descriptor table containing segment descriptors
  volatile uint started;        // Has the CPU started?
  int ncli;                    // Depth of pushcli nesting.CLI/STI used to disable interrupts
  int intena;                  // Were interrupts enabled before pushcli?
  
  // Cpu-local storage variables; see below
  struct cpu *cpu;
  struct proc *proc;           // The currently-running process.
};

extern struct cpu cpus[NCPU];  //number of cpus
extern int ncpu;

// Per-CPU variables, holding pointers to the
// current cpu and to the current process.
// The asm suffix tells gcc to use "%gs:0" to refer to cpu
// and "%gs:4" to refer to proc.  seginit sets up the
// %gs segment register so that %gs refers to the memory
// holding those two variables in the local cpu's struct cpu.
// This is similar to how thread-local variables are implemented
// in thread libraries such as Linux pthreads.
extern struct cpu *cpu asm("%gs:0");       // &cpus[cpunum()]
extern struct proc *proc asm("%gs:4");     // cpus[cpunum()].proc

//PAGEBREAK: 17
// Saved registers for kernel context switches.
// Don't need to save all the segment registers (%cs, etc),
// because they are constant across kernel contexts.
// Don't need to save %eax, %ecx, %edx, because the
// x86 convention is that the caller has saved them.
// Contexts are stored at the bottom of the stack they
// describe; the stack pointer is the address of the context.
// The layout of the context matches the layout of the stack in swtch.S
// at the "Switch stacks" comment. Switch doesn't save eip explicitly,
// but it is on the stack and allocproc() manipulates it.
struct context {
  uint edi;		//Destination index for string operations
  uint esi;		//Source index for string operations	
  uint ebx;		//Base Register; Indexed Addressing; constant value added to this to get address of the operand
  uint ebp;		//Base Pointer; Used to obtain location of the pointer
  uint eip;		//Instruction Pointer; address of the next instruction to be executed
};

enum procstate { UNUSED,	//In wait state
 EMBRYO,					//newly created
  SLEEPING,					//sleep call
   RUNNABLE,				//scheduled
    RUNNING,				//executing
     ZOMBIE };				//dead

// The virtual address where shared memory appears, if requested
#define SHARED_V 0x70000000

// the maximum number of shared pages in the system
#define NSHARED 10

struct shared {
  int refcount;
  void *page; 
};

// Per-process state
struct proc {
  uint sz;                     // Size of process memory (bytes)
  pde_t* pgdir;                // Page table; Page Directory Pointer
  char *kstack;                // Bottom of kernel stack for this process
  enum procstate state;        // Process state
  volatile int pid;            // Process ID
  struct proc *parent;         // Parent process; ppid
  struct trapframe *tf;        // Trap frame for current syscall
  struct context *context;     // swtch() here to run process; the variables to be stored or loaded during switch
  void *chan;                  // If non-zero, sleeping on chan
  int killed;                  // If non-zero, have been killed
  struct file *ofile[NOFILE];  // Open files
  struct inode *cwd;           // Current directory
  struct shared *shared;       // Shared memory record (0 -> none)
  char name[16];               // Process name (debugging)
};

// Process memory is laid out contiguously, low addresses first:
//   text
//   original data and bss
//   fixed-size stack
//   expandable heap
//   (optionally) fixed-sized shared mem segment, 1 page @ 0x7000000

struct file {
  enum { FD_NONE, FD_PIPE, FD_INODE } type;
  int ref; // reference count
  char readable;
  char writable;
  struct pipe *pipe;
  struct inode *ip;
  uint off;
};


// in-core file system types

struct inode {
  uint dev;           // Device number
  uint inum;          // Inode number
  int ref;            // Reference count
  int flags;          // I_BUSY, I_VALID

  short type;         // copy of disk inode
  short major;
  short minor;
  short nlink;
  uint size;
  uint addrs[NDIRECT+1];
};


