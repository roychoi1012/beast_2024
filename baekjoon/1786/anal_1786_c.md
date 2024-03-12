#### `search_ptn(...)` 함수의 main code fraction

```c
for (int32_t i = 0; i <= (len_T - len_P); i++) {
    // adjust range to search
    strncpy(str, T + i, len_P);

    for (int32_t j = len_P-1; j >= 0; j--) {
        // if there is a new string (character) in text which is not in pattern
        if (strchr(P, str[j]) == NULL) {
            i += j;
        }

        if (P[j] == str[j]) {
            next++;
            // success to search pattern in  text
            if (next == len_P) {
                idx[cnt++] = i + 1;
                next = 0;
            }
        }
    }
}
```



##### key ideas of improvement

- Line 1:  `for`-loop의 the number of iterations $\leq $  `len_T`: text `T`의 tail 끝까지 수행할 필요없음
- Line 9: Line 1에서 `for`-loop의 loop variant `i`가 $i\gets i+1$로 증가함과 동시에 Line 8의 조건을 만족하면 Line 9에서 loop variant `i`의 jump가 가능. Best case의 경우 $i\gets i+|P|-1$. 



##### Evaluation

1. Correctness: 옳게 동작하는 것인가**??**
2. Complexity
- Notation: $n=|T|,m=|P|$ where $T$ is a text  and $P$ is a pattern
- Assumptions
  - A#1: A best case: Line 1의 `for`-loop이 $n/m$ 번 수행
  - A#2: Lines 11-18가 1번 실행
- Line 5: `for`-loop의 loop variant `j`가 항상 $m$번 수행. Line 1의 `for`-loop과 달리 jump 없음
  - Line 8: `strchr(...)` function의 time complexity = $O(m)$. 함수로 분리되어 있으나 `for`-loop과 `if`-statement의 결합으로 $m$번 비교 필요
  - A#2 가정하에 Line 5의 `for`-loop에 의하여 induce되는 the number of steps
    - Line 7: $m$
    - Line 8: 1
    - Lines 11-17: 1 by A#2
  - The total number of steps during Lines 5-18 = $m\cdot(m+2)=O(m^2)$
- The total time complexity in best case:
  - Line 1의 `for`-loop: $n/m$ 수행
  - Line 5의 nested `for`-loop: $O(m^2)$ 수행 
  - Thus, the total complexity is $n/m\cdot O(m^2)=O(nm)$ even in best case



#### How to improve?

- Line 8과 9사이에 `break` 추가하여 Line 5의 `for`-loop의 jump 허용 **??**; __즉, 검증된 idea가 아니고 확인해봐야 함__
- 또는 다른 방법을 사용하여 loop variant `j`를 jump하게 해야하는데, 이걸 찾으면 결국 BM algorithm이나 KMP로 수렴 **??** 
