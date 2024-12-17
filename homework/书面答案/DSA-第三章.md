1.
- 使用一个辅助队列 \( Q \) 将栈 \( S \) 的前 \( k \) 个元素取出，依次放入队列中。
- 由于队列是先进先出（FIFO），当我们将这些元素重新放回栈 \( S \) 时，它们的顺序将自动逆序。
```
reverse_top_k(S,k):
    1. 初始化辅助队列Q
    2. 循环k次执行:
        1. enQueue(Q,pop(S)) \\将S的前k个元素取出并依次放入Q
    3. 循环k次执行:
        1. push(S,deQueue(Q)) \\将Q的k个元素依次取出并放入S
    4. 返回S
```


- 首先，使用一个辅助队列 Q ，将栈 S 中所有元素依次出栈并放入队列 Q，此时队列中的元素顺序与栈中原始顺序相反。
- 再次使用栈 S 和队列 Q 比较两者的元素顺序，如果从栈顶到栈底的元素与从栈底到栈顶的元素相同，则栈是回文结构。
- 最后将队列中的元素重新放回栈 S，以恢复栈的原始顺序。
```
function is_palindrome(S):
    Q = empty queue
    
    # Step 1: 将栈 S 中的元素逐个弹出并放入队列 Q
    n = 0
    while S is not empty:
        element = S.pop()
        Q.enqueue(element)
        n += 1  # 记录栈的大小
    
    # Step 2: 将队列中的元素重新放回栈中并检查是否回文
    is_palindrome = True
    for i from 1 to n:
        element = Q.dequeue()
        S.push(element)
        Q.enqueue(element)  # 同时放回队列以恢复栈顺序
        
    # Step 3: 再次从栈中弹出元素，与队列的头部比较
    for i from 1 to n:
        top_element = S.pop()
        queue_element = Q.dequeue()
        if top_element != queue_element:
            is_palindrome = False
        Q.enqueue(top_element)  # 同时将元素放回队列以保持顺序
    
    # Step 4: 将队列中的元素重新放回栈，恢复栈的原始顺序
    while Q is not empty:
        S.push(Q.dequeue())
    
    return is_palindrome

```

2. 
设可能性数量为 $f(n)$, 规定 $f(0)=1$, 默认第一辆车进栈,如果进队可以视为进栈后立即出栈,卸货顺序不变

$n=n_0$ 时第一辆车可以在栈内只剩第一辆车的任意时刻出栈, 对第一辆车出栈的时刻 $i$, (假设每时刻卸货一辆), 此时已卸货的一定为第 $1,...,i$ 辆车.因此卸货顺序可视为 $n=i-1,n=n_0-i$ 两种情况下各一种卸货顺序的拼接

令 $i$ 遍历 $[n]$, 有:
$$f(n)=\sum_{i\in [n]}f(i-1)f(n-i)=\frac{1}{n+1}\binom{2n}{n} \quad(\text{Catalan数})$$

3.
**必要性:**
- 反证法, 若存在 $i<j<k\;s.t.\; p_i>p_k>p_j$,
- 对 $i<j $, 为使 $p_i>p_j$, 一定有: $p_i,p_j$ 都入栈了 
- 对 $i<k $, 为使 $p_i>p_k$, 一定有: $p_k$ 入栈了 
- 入栈顺序为 $p_j,p_k,p_i$ 此时当 $i$ 第一个出栈时, $j,k$ 一定都已经在栈内且还没有出栈, 根据入栈顺序知 $j>k$, 矛盾
- 必要性证毕
**充分性:**
- 归纳证明, 对 $n=3$ 充分性显然
- 一般情况下, $n$ 最后一个输入, 假设 $p_l=n$ 
- 根据归纳假设, $p_1,\dots,p_{l-1} ,p_{l+1},p_n$ 符合性质且是合法序列, 下考虑加入 $p_l=n$ 后序列的合法性
  - 由于 $n$ 最后一个输入, 在 $n$ 输入后, 如果入栈 $n$ 也是第一个输出, 可以视为直接输出. 因此加入 $p_l=n$ 后序列的合法性 $\Leftrightarrow $ 在 $n$ 后输出的元素是逐一从栈中泵出.
  - 假设序列满足性质, 则对 $i=l<j<k$ , 由于 $p_l=n=\max p_i$ , 一定有 $p_k<p_j$ , 这说明 $n$ 后的输出符合先进后出, 由于 $n$ 输入后所有元素只能在栈中逗留, 所以加入 $p_l=n$ 后序列合法
- 充分性证毕