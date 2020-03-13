## 1. c)

### Recursive Factorial

**Time Complexity:** Linear - O(n)
**Space Complexity:** Linear -  O(n)

### Dynamic Factorial

**Time Complexity:** Linear - O(n)
**Space Complexity:** Constant -  O(1)

## 2. a)
**Input Data**
amount: change to give
coinValues: value of the coins available

**Decision Variables**
change: number of coins of each value

**Goal function**
min(sum(change))

**Restrictions**
sum(change\[i\] \* coinValues\[i\]) = amount

## 2. b)
minCoins(i, k)