# README
## My Additions
### Unix Utilities
I learnt about various system calls used in Unix and applied them in the following practicals

**Sixfive**
- Files: sixfive.c
- Used read and open system calls
- When doing this I learnt about the importance of fds and how they can be useful in redirection of input and output files

**Memdump**
- Files: memdump.c
- Printed contents in memory according to format string given

**find**
- Files: find.c
- Learned about how directory structures work and how they can be accessed to 
- Learned to use fstat system call
- Hit a bug of recursing into the . directory itself

**exec option on find**
- Files: find.c
- Learned to use fork, wait and exec system calls
- Made the error of not wrapping some exec calls with if statements checking if they produced errors or not and sufferred a lot of bugs due to this

**pingpong**
- Files: pingpong.c
- Learnt to use pipe system call
- I ran into some bugs when I used fstat on a fd associated with pipes and you should not do this

### System Calls
I learnt about how to make my own system calls and used gdb when analysing code running on the kernel

**Using gdb**
- Created breakpoints, watchpoints and used other gdb functions to figure out the cause of behaviours of various parts of code

**Sandbox**
- Files: sysfile.c(sys_interpose function), sandbox.c
- Created a system call interpose
- I now understand why you pass an flag1|flag2|flag3... into OPEN because a bit is associated with each flag and that's how you decide whether to include flag in code for open
- Understood how system calls are run or called in xv6 so that I could actually stop the calls being run when mask was called
- Hit a problem when I didn't copy masks from parent to child 
- Learnt how to access arguments from registers

**Memory Available System Call**
- Files: sysfile.c(sys_memAvailable function), kalloc.c(count_free_bytes)
- Learnt about how xv6 stores all the free physical pages in a freelist which is basically a stack
- Iterate through list to calculate free memory

**Attack xv6**
- Files: attack.c, secret.c
- Created a bug in xv6 system(not wiping out the data from freed page)
- Used sbrk() system call to grow memory and match some text in the memory
- Dealt with a bug where first 8 bytes would be overwritten by free to store next pointer so matching for whole string would result in problems




## xv6 README
xv6 is a re-implementation of Dennis Ritchie's and Ken Thompson's Unix
Version 6 (v6).  xv6 loosely follows the structure and style of v6,
but is implemented for a modern RISC-V multiprocessor using ANSI C.

ACKNOWLEDGMENTS

xv6 is inspired by John Lions's Commentary on UNIX 6th Edition (Peer
to Peer Communications; ISBN: 1-57398-013-7; 1st edition (June 14,
2000)).  See also https://pdos.csail.mit.edu/6.1810/, which provides
pointers to on-line resources for v6.

The following people have made contributions: Russ Cox (context switching,
locking), Cliff Frey (MP), Xiao Yu (MP), Nickolai Zeldovich, and Austin
Clements.

We are also grateful for the bug reports and patches contributed by
Abhinavpatel00, Takahiro Aoyagi, Marcelo Arroyo, Hirbod Behnam, Silas
Boyd-Wickizer, Anton Burtsev, carlclone, Ian Chen, clivezeng, Dan
Cross, Cody Cutler, Mike CAT, Tej Chajed, Asami Doi,Wenyang Duan,
echtwerner, eyalz800, Nelson Elhage, Saar Ettinger, Alice Ferrazzi,
Nathaniel Filardo, flespark, Peter Froehlich, Yakir Goaron, Shivam
Handa, Matt Harvey, Bryan Henry, jaichenhengjie, Jim Huang, Matúš
Jókay, John Jolly, Alexander Kapshuk, Anders Kaseorg, kehao95,
Wolfgang Keller, Jungwoo Kim, Jonathan Kimmitt, Eddie Kohler, Vadim
Kolontsov, Austin Liew, Bruce Lowekamp, l0stman, Pavan Maddamsetti,
Imbar Marinescu, Yandong Mao, Matan Shabtay, Hitoshi Mitake, Carmi
Merimovich, mes900903, Mark Morrissey, mtasm, Joel Nider, Hayato Ohhashi,
OptimisticSide, papparapa, phosphagos, Harry Porter, Greg Price, Zheng
qhuo, Quancheng, RayAndrew, Jude Rich, segfault, Ayan Shafqat, Eldar
Sehayek, Yongming Shen, Fumiya Shigemitsu, snoire, Taojie, Cam Tenny,
tyfkda, Warren Toomey, Stephen Tu, Alissa Tung, Rafael Ubal, unicornx,
Amane Uehara, Pablo Ventura, Luc Videau, Xi Wang, WaheedHafez, Keiichi
Watanabe, Lucas Wolf, Nicolas Wolovick, wxdao, Grant Wu, x653, Andy
Zhang, Jindong Zhang, Icenowy Zheng, ZhUyU1997, and Zou Chang Wei.

ERROR REPORTS

Please send errors and suggestions to Frans Kaashoek and Robert Morris
(kaashoek,rtm@mit.edu).  The main purpose of xv6 is as a teaching
operating system for MIT's 6.1810, so we are more interested in
simplifications and clarifications than new features.

BUILDING AND RUNNING XV6

You will need a RISC-V "newlib" tool chain from
https://github.com/riscv/riscv-gnu-toolchain, and qemu compiled for
riscv64-softmmu.  Once they are installed, and in your shell
search path, you can run "make qemu".
