1、https://leetcode.cn/problems/longest-common-prefix/description/?company_slug=baidu

最长前缀和，直接双指针 On

2、https://leetcode.cn/problems/find-peak-element/solutions/998152/xun-zhao-feng-zhi-by-leetcode-solution-96sj/?company_slug=baidu

找峰值 方法1：直接三指针遍历  On + O1

最优：二分模拟爬坡 OLogn + O1

3、https://leetcode.cn/problems/longest-substring-without-repeating-characters/?company_slug=baidu

无重复最长子串 滑动窗口 On + O1 哈希记录值和下标

4、https://leetcode.cn/problems/valid-parentheses/description/?company_slug=baidu

有效括号 栈 On + On

5、https://leetcode.cn/problems/container-with-most-water/description/?company_slug=baidu

盛水最多 双指针，优先移动小的一边，因为移动小的边才有可能变大

6、https://leetcode.cn/problems/merge-intervals/?company_slug=baidu

合并区间 排序 + 双指针 从左往右，注意边界处理，第一个右大于后面的右，只有最大小区下一个区间的左的时候可以合并

7、https://leetcode.cn/problems/two-sum/description/?company_slug=baidu7

两数合，直接哈希做 On + On

8、https://leetcode.cn/problems/3sum/?company_slug=baidu

三数之和，排序 + 双指针,注意去重

9、https://leetcode.cn/problems/generate-parentheses/?company_slug=baidu

括号生成：回溯法或者dp都可以

10、https://leetcode.cn/problems/permutations/description/?company_slug=baidu

全排列，经典回溯

11、https://leetcode.cn/problems/maximum-subarray/submissions/546327893/?company_slug=baidu

最大子数组和，动态规划 dp[i]定义为以nums[i]结尾的最大子数组和

if (dp[i - 1] > 0) {

dp[i] = dp[i - 1] + nums[i];

    } else {

dp[i] = nums[i];

    }

12、https://leetcode.cn/problems/edit-distance/description/?company_slug=baidu

编译距离，这题原来是hard的X_X

13、https://leetcode.cn/problems/compress-string-lcci/submissions/546398036/?company_slug=baidu

双指针

14、https://leetcode.cn/problems/sort-characters-by-frequency/description/?company_slug=baidu

优先队列

15、https://leetcode.cn/problems/find-all-duplicates-in-an-array/?envType=company&envId=tencent&favoriteSlug=tencent-three-months

把相同数换到不同位置

16、

https://leetcode.cn/problems/longest-valid-parentheses/solutions/314683/zui-chang-you-xiao-gua-hao-by-leetcode-solution/?envType=company&envId=tencent&favoriteSlug=tencent-three-months

栈用来做匹配，栈顶记录最后未匹配的下标

17、https://leetcode.cn/problems/shortest-path-in-a-grid-with-obstacles-elimination/description/?envType=company&envId=didi&favoriteSlug=didi-three-months

带状态bfs

18、分割等和子集
