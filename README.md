# Problem 095 - SubSir 的对换轮换置换

**ACMOJ Problem ID**: 2424

## Table of Contents

- [Problem 095 - SubSir 的对换轮换置换](#problem-095-subsir-的对换轮换置换)
  - [Table of Contents](#table-of-contents)
  - [Introduction](#introduction)
    - [Background](#background)
  - [Assignment Description](#assignment-description)
    - [Grade Composition](#grade-composition)
  - [Assignment Requirements](#assignment-requirements)
    - [Input Format](#input-format)
    - [Output Format](#output-format)
    - [Samples](#samples)
    - [Data Constraints](#data-constraints)
  - [Per-Testcase Resource Limits](#per-testcase-resource-limits)
  - [Test Data](#test-data)
  - [Submission Requirements](#submission-requirements)
    - [Submission Format](#submission-format)
    - [Submission Guidelines](#submission-guidelines)
    - [Evaluation Notes](#evaluation-notes)
    - [Academic Integrity](#academic-integrity)

## Introduction

### Background

This problem tests algorithmic problem-solving skills.

## Assignment Description

### Grade Composition

| Grading Component | Percentage |
| :--: | :--: |
| Pass **2424. SubSir 的对换轮换置换** | 80% |
| Code Review | 20% |

Here are several points that need clarification:

- In the Code Review, we will **strictly examine your code style and repository organization structure, etc.**

- This assignment provides some sample data for testing, stored in the `/workspace/data/095/data_test/` directory. Note that these are not the test cases on the Online Judge. Passing all local test cases does not guarantee that you will pass the OJ tests.

- Besides the provided sample data, we also encourage you to design your own test data based on your program logic to assist debugging.

## Assignment Requirements

### Problem Description

**这是一道头文件题目。你要填充给定的模板，并把头文件提交到OJ上。**

SubSir最近迷上了小猿搜题的PK竞技场，正当某天他打算大干一场的时候，他惊奇地发现他最喜欢的10以内加减法被换成了对换轮换置换题目。由于SubSir完全不会，他希望你能帮他完成计算。

SubSir简要的给你介绍一下对换轮换置换。**大段的数学完全可以不看，直接看例子就能明白**。

>对于一个$0$到$n-1$的排列$(0, 1, ..., n-1)$，若进行某种变换后这个排列变成$(a(0), a(1), ..., a(n-1))$，其中$a(0), a(1), ..., a(n-1)$是$0$到$n-1$的重排列，则称这个变换为置换，记为$[a(0), a(1), ..., a(n-1)]$，本质上就是将下标为$i$的元素替换为原来数组中下标为$a(i)$的元素。

<img src="https://acm.sjtu.edu.cn/OnlineJudge/oj-images/f21a6248-37b5-45d8-9755-c5b4dfd4c4b9" alt="置换例子" title="置换例子">

例如，对于数组$(3, 1, 2, 0)$，进行置换$[2, 3, 1, 0]$后变为$(2, 0, 1, 3)$。

>轮换是一种更加特殊的置换。轮换的写法是$\{b_0, b_1, ..., b_{k-1}\}$，代表一个$k$-轮换。它等于这样的一个置换：$[a(0), a(1), ..., a(n-1)]$，其中第$i$个元素定义如下：若$\exists j, b_j = i$则$a(i) = b_{(j+1)\mod k}$，若$\forall j, b_j \neq i$则$a(i) = i$。其实就是轮换中的元素"轮"换一下位置。

<img src="https://acm.sjtu.edu.cn/OnlineJudge/oj-images/af00d2e7-c821-421b-a6b0-79d8fe7c112d" alt="轮换例子" title="轮换例子" style="width:1000px;">

例如，对于数组$(3, 1, 2, 0)$，进行轮换$\{2,3,1\}$后变为$(3,2,0,1)$。

>对换比轮换更特殊，是$2$-轮换。记为$\{a, b\}$，意思是原数组中下标为$a$的元素和下标为$b$的元素互换位置。

<img src="https://acm.sjtu.edu.cn/OnlineJudge/oj-images/a68725c4-dc95-4438-b74d-7cee89140f5e" alt="对换例子" title="对换例子">

可以发现，其实对换和轮换都是置换的一种。注意到两个置换的叠加的作用效果也是一次置换，所以置换是可以作乘法的。SubSir不打算告诉你这个怎么实现，相信你可以通过简单的推导实现。

有了置换的乘法，我们也就有置换的逆元了，意思是某个置换乘以其逆元得到的置换，应该就是$[0, 1, ..., n-1]$。SubSir不想太难为你，所以告诉你某个置换$[a(0), a(1), ..., a(n-1)]$的逆元是$[{a(0)}^{-1}, a(1)^{-1}, ..., a(n-1)^{-1}]$，其中$a(i)^{-1} = j \iff a(j) = i$。

对于置换前后数组不变的置换，称为恒等置换。

SubSir 觉得这题有点长了，所以给了你下发文件 [attachment]2424.zip[/attachment]。你需要实现：置换轮换对换的初始化和析构、置换的乘积、置换的逆元、对换轮换转换为置换、对换置换轮换作用于数组。

请你在src.hpp中需要填写代码的地方填写并上传，评测机会调用你修改过的头文件。

测试点后$5$个测试内存管理，如果不通过，检查你的内存。

### Input Format



### Output Format



### Samples

#### Sample 1

**Input:**
```
4
2 3 1 0
```

**Output:**
```
0 1 2 3
2 3 1 0
[1 0 3 2]
[3 2 0 1]
{0 1}
3 2 1 0
[1 0 2 3]
3 2 1 0
3 1 2 0
[0 2 1 3]
```

### Data Constraints



## Per-Testcase Resource Limits

- **Time Limit (per test case)**: 1000 ms
- **Memory Limit (per test case)**: 244 MiB
- **Disk Usage**: No disk usage is permitted.

## Test Data

The test data for this problem is located at `/workspace/data/095/data_test/`.

Attachments and starter files for this problem are located at `/workspace/data/095/`.

## Submission Requirements

### Submission Format

Submit a single C++ source file to the Online Judge. The OJ provides its own `main.cpp` which `#include "src.hpp"`. Your submission will be written to `src.hpp` and compiled together with the OJ's driver code.

### Submission Guidelines

- The submitted code must be able to compile successfully through the above compilation process
- The program needs to be able to read data from standard input and write results to standard output
- Please ensure the code runs correctly within the given time and space limits
- **You must use C++ or C language** to implement this assignment

### Evaluation Notes

- The evaluation system will test your program using the provided test data
- The program output must exactly match the expected output (including format)
- Exceeding time or memory limits will be judged as the corresponding error type
- Please pay attention to the overall time performance of your code and the time complexity of each part of your algorithm.

### Academic Integrity

If any violations are found during evaluation or code review (including but not limited to using unconventional methods to pass test cases), your final score may be significantly reduced or become **0 points**.
