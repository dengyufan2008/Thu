``struct`` 内存分布: 每个变量需要地址开头为自身大小的倍数. 结构体整体的大小会是最大变量的倍数. 最优化: 变量从大到小排序.

RISC-V 架构: 32 reg, reg0 always 0. 指令后加 i 表示 rhs 为常数.
``add x y z``: ``x = y + z;``, ``sub``, ``xor``, ``sll``: shift left logically, ``sra`` shift right arithmetically.
``lw x offset(y)``: ``x = *(y+offset);``.
``sw x offset(y)``: ``*(y+offset) = x;``.
``beq x y L``: jump tp ``L`` if ``x == y``. ``j L``: jump to ``L``.

内存分配: Code: 存程序; Static Data: 存全局变量; Heap: 存局部用指针分配的数组; Stack: 存函数内的变量; OS: 留给 OS.

Cache 结构: 将地址分为 Tag, Index, Offset. 将 Block 划分进不同的 Set.

Process: 资源分配单位; Thread: 执行单位.

``int fork()``: 将当前 process 复制一份. 返回 ``0`` 表示是子进程, 父进程返回子进程的 pid.
``int wait(int* status)``: 等待直到子进程之一执行完. 返回执行完的进程的 pid, ``int waitpid(int pid, int* status, int options)``.

child 在停止后仍然占用资源, 以让 parent 在之后知道运行结果. parent 停止后会杀死 child, 所有返回值由 pid=1 的进程接收.

RE: ``[]`` 表示其中之一, 内部不需要转义. ``^`` 表示排除.
``?`` 表示出现 0/1 次, ``+`` 表示出现至少 1 次.
``|`` 表示或.
``()`` 为捕获组, 也表示优先级. ``(?!)`` 断言之后的不是内部的字符串, 且不消耗字符.

``tr '[:upper:]' '[:lower:]' < departments.txt | sort -u | awk '{print} END{print NR}'``: 将 txt 里的大写转小写; 排序并去重; 逐行输出并输出行数.

``lock``: ``Acquire()`` and ``Release()``. ``semaphore``: ``P()`` and ``V()``. ``condition``: ``wait(&lock)``, ``signal()``, ``broadcast()``.
