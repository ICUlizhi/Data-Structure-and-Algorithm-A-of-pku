#import "style.typ": *
#show: setup.with(2024, "试卷")
#note[依据目录内 1—16.png 整理。移除原图答案与批注，保留题干。并查集题原称“15 个等价对”，实际只列 9 对，此处按已列 9 对操作。]
姓名：#h(36mm) 学号：
= 一、选择填空
#q("1")[（2 分）抽象数据类型的组成部分不包括（　）。

A. 一组操作　 B. 数据的对象　 C. 数据的存储　 D. 数据的关系]
#q("2")[（2 分）代码找出正整数对 (i,j)，使 $i j <= N$，时间复杂度是（　）。
```cpp
for (int i = 1; i <= N; i++) {
    int max_j = N / i;
    int j = 1;
    while (j <= max_j) {
        printf("%d, %d", i, j);
        j += 1;
    }
}
```
A. $Theta(N log N)$　 B. $Theta(N sqrt(N))$　 C. $Theta(N^2)$　 D. $Theta(sqrt(N) log N)$]
#q("3")[（2 分）双向链表中交换 p 和其后继。已知 p 的前驱、后继均存在，且后继不是尾元素。以下正确的是（　）。
```cpp
// A
p->prev->next=p->next; p->next->prev=p->prev;
p->next->next->prev=p; p->next->next=p;
p->next=p->next->next; p->prev=p->next;
// B
p->next->next->prev=p; p->prev->next=p->next;
p->next->next=p; p->next->prev=p->prev;
p->next=p->next->next; p->prev=p->next;
// C
p->next->next->prev=p; p->next->prev=p->prev;
p->prev=p->next; p->prev->prev->next=p->prev;
p->next=p->prev->next; p->prev->next=p;
```]
#q("4")[（2 分）关于顺序表和链表，下列正确的是（　）。

A. 长度已知且无增删，从内存占用考虑，链表比顺序表更好

B. 长度 n 的有序顺序表，插入一个元素使其仍有序，时间为 $O(log n)$

C. 已定位到待删除元素，顺序表删除操作为 $O(1)$

D. 读操作密集且很少增删的场景应选择顺序表]
#q("5")[（3 分）值为 1 至 5 的五个结点组成二叉搜索树，要求每个结点左子树结点数不少于右子树结点数。共有#h(16mm)种。]
#q("6")[（6 分）自底向上 SiftDown，将 {23,12,17,5,28,30,15,8} 建为最小堆，写出序列。再插入元素 4，SiftUp 后的新序列是什么？]
#q("7")[（3 分）树的嵌套表示为 `(A(B(D)(E(I)(J))(F))(C(G)(H)))`，该树没有（　）度结点。（可多选）

A. 1　 B. 2　 C. 3　 D. 4]
#pagebreak()
= 二、辨析与简答
#q("1")[S、X 分别表示入栈与出栈，初态和终态均为空栈。可执行的操作串称合法序列，如 SXSX 合法，SXXS 非法。

（1）（2 分）给出合法序列的充要条件，无需证明。

（2）（4 分）对无重复元素的固定输入序列，两个不同合法操作序列能否得到相同输出？简述理由。]
#space(h: 12mm)
#q("2")[（1）（2 分）实现 `strcpy(char* destination, char* source)`，若 `source < destination < source + strlen(source)`，如何处理？为什么？

（2）（4 分）计算 `abababa` 优化前与优化后的 next 数组。]
#space(h: 16mm)
#q("3")[（1）（3 分）写出下图二叉树前序、中序、后序遍历结果。
#fig("2024-q3.svg", width: 48%)
（2）（4 分）已知前序 {A,B,D,E,G,H,C,F}，中序 {D,B,G,E,H,A,C,F}。画出二叉树，给出后序序列。]
#space(h: 10mm)
#q("4")[字符 {a,b,c,d,e,f,g} 的频率为 {6%,8%,9%,10%,12%,25%,30%}。

（1）（3 分）画 Huffman 树，要求左孩子权重不大于右孩子。

（2）（2 分）求平均编码长度。

（3）（3 分）g 的频率下降，其他字符的相对比例不变，且 Huffman 编码方案保持不变。g 的频率降至多少时，定长编码比 Huffman 编码更省空间？]
#space(h: 10mm)
#q("5")[（3 分）初始元素各为独立集合。依次处理以下等价对，按小树并入大树、同规模时大根并入小根，并采用路径压缩。画出所得等价类树。

(0,2)、(1,2)、(3,4)、(4,5)、(2,5)、(6,7)、(8,7)、(2,8)、(9,7)。]
#pagebreak()
= 三、算法填空（每空 2 分，共 10 分）
用两个队列实现栈，元素为 int。队列允许 push(x)、pop()、front()、empty()。假设 pop、top 在非空栈上调用。
```cpp
class MyStack {
    queue<int> queue1, queue2;
public:
    void push(int x) {
        /* (1) */;
        while (/* (2) */) {
            /* (3) */;
            queue1.pop();
        }
        swap(queue1, queue2);
    }
    int pop() {
        int r = queue1.front();
        queue1.pop();
        return r;
    }
    int top() {
        return /* (4) */;
    }
    bool empty() {
        return /* (5) */;
    }
};
```
#space(h: 20mm)
= 四、算法设计与实现
#q("1")[（10 分）给定非空字符串，判断是否可由某个非空真子串重复至少 2 次构成。

样例：`abab` → True；`aba` → False；`abcabcabcabc` → True。

给出算法与复杂度分析。]
#space(h: 27mm)
#pagebreak()
#q("2")[（10 分）用数组 L、R 存储 N 个结点的二叉树，结点编号 1—N，L[i]、R[i] 为左右孩子编号，0 表示空；L[0]=R[0]=0。

（1）（6 分）由 L、R 建立父结点数组 T，使 T[i] 存 i 的父结点，T[0]=0。

（2）（4 分）根据 L、R、T 判别结点 U 是否为 V 的后代。分析复杂度。]
#space(h: 25mm)
#q("3")[（10 分）树的镜面映射：将每个结点的孩子次序反转。下图左为原树、右为镜像。
#fig("2024-mirror.svg", width: 78%)
输入时先按“左孩子—右兄弟”转换为二叉树，对只有一个孩子的分支结点补虚孩子 `$`，形成“伪满二叉树”。按前序输出结点：内部结点标记 0，叶结点标记 1，虚结点也输出。

给定这种前序序列，设计算法输出原树镜像后的宽度优先遍历序列。

例：输入 `a0 b0 $1 c0 d0 $1 e1 f1 $1`，输出 `afcbed`。给出算法与复杂度分析。]
#space(h: 28mm)
= 五、证明题
请证明：非空满 k 叉树中（每个内部结点恰有 k 个孩子），若内部结点数为 n，则叶结点数为 $n(k-1)+1$。
#space(h: 25mm)
