/*
 * @lc app=leetcode.cn id=1352 lang=cpp
 * @lcpr version=30307
 *
 * [1352] 最后 K 个数的乘积
 */

// @lc code=start
class ProductOfNumbers {
public:
    vector<int> preProduct; // 前缀积
    ProductOfNumbers() {
        preProduct.push_back(1); // 初始化放个1，方便计算
    }
    
    void add(int num) {
        if(num == 0) {
            // 遇到0，清空重新开始
            preProduct.clear();
            preProduct.push_back(1);
        } else {
            // 前缀积：当前值 = 上一个前缀积 * num
            int n = preProduct.size();
            preProduct.push_back(preProduct[n-1] * num);
        }
    }
    
    int getProduct(int k) {
        int n = preProduct.size();
        // 如果k >= n，说明最后k个数中包含0，返回0
        if(k >= n) {
            return 0;
        }
        // 最后k个数的乘积 = preProduct[n-1] / preProduct[n-1-k]
        return preProduct[n-1] / preProduct[n-1-k];
    }
};

/**
 * Your ProductOfNumbers object will be instantiated and called as such:
 * ProductOfNumbers* obj = new ProductOfNumbers();
 * obj->add(num);
 * int param_2 = obj->getProduct(k);
 */
// @lc code=end



/*
// @lcpr case=start
// ["ProductOfNumbers","add","add","add","add","add","getProduct","getProduct","getProduct","add","getProduct"]\n[[],[3],[0],[2],[5],[4],[2],[3],[4],[8],[2]]\n
// @lcpr case=end

 */

