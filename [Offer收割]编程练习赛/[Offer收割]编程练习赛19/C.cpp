// 𝑓[0][0][0][0]=0 // 左边没有更多位置了自然𝑗_1,𝑗_2均为0
// 𝑓𝑜𝑟 𝑖=0~(𝑛−1), 𝑗_1=0~2,𝑗_2=0~1,𝑘=0~2
//         𝑖𝑓 (𝑓[𝑖][𝑗_1 ][𝑗_2 ][𝑘]≠−1)
//                 𝑖𝑓 (𝑘≠2) // 𝑟[𝑖+1]可以大于𝑟[𝑖+2]
//                         𝑢𝑝𝑑𝑎𝑡𝑒(𝑓[𝑖+1][𝑗_2+1][1][0], 𝑓[𝑖][𝑗_1 ][𝑗_2 ][𝑘]+𝑎[𝑖][𝑗_1 ])
//                         𝑢𝑝𝑑𝑎𝑡𝑒(𝑓[𝑖+1][𝑗_2+1][0][2], 𝑓[𝑖][𝑗_1 ][𝑗_2 ][𝑘]+𝑎[𝑖][𝑗_1+1])
//                 𝑖𝑓 (𝑘 ≠1) // 𝑟[𝑖+1]可以小于𝑟[𝑖+2]
//                         𝑢𝑝𝑑𝑎𝑡𝑒(𝑓[𝑖+1][𝑗_2 ][1][1], 𝑓[𝑖][𝑗_1 ][𝑗_2 ][𝑘]+𝑎[𝑖][𝑗_1+1])
//                         𝑢𝑝𝑑𝑎𝑡𝑒(𝑓[𝑖+1][𝑗_2 ][0][0], 𝑓[𝑖][𝑗_1 ][𝑗_2 ][𝑘]+𝑎[𝑖][𝑗_1+2])