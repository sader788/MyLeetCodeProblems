#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <string>
#include <unordered_set>
#include <array>

// 1.two sum
#ifdef TWO_SUM
class Solution {
public:
    std::vector<int> twoSum(std::vector<int>& nums, int target) {

        std::unordered_map<int32_t, int32_t> hash;

        std::vector<int> res;

        int32_t size = nums.size();

        for (int32_t i = 0; i < size; ++i) {
            auto it = hash.find(target - nums[i]);

            if (it != hash.end()) {
                res.push_back(it->second);
                res.push_back(i);
                break;
            }

            hash.emplace(nums[i], i);
        }
        return res;
    }
};
#endif

// 2. ADD TWO NUMS
#ifdef ADD_TWO_NUMS
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {

        ListNode* res = new ListNode((l1->val + l2->val) % 10);

        ListNode* ptrRes = res;

        uint8_t mod = (l1->val + l2->val) / 10;
        uint8_t sum = 0;

        l1 = l1->next;
        l2 = l2 ->next;

        while(l1 != nullptr || l2 != nullptr) {

            if(l1 != nullptr) {
                sum += l1->val;
                l1 = l1->next;
            }
            if(l2 != nullptr) {
                sum += l2->val;
                l2 = l2->next;
            }

            sum += mod;

            ptrRes->next = new ListNode(sum % 10);
            ptrRes = ptrRes->next;

            mod = sum / 10;
            sum = 0;
        }

        if (mod != 0){
            ptrRes->next = new ListNode(mod);
        }


        return res;
    }
};
#endif

// 3. Longest Substring Without Repeating Characters
#ifdef LONGEST_SUBStR
class Solution {
public:
    int lengthOfLongestSubstring(std::string s) {

        std::unordered_map<char, uint32_t> existedCh;

        uint32_t size = s.size();

        uint32_t maxLen = 0;

        uint32_t start = 0;
        uint32_t end = 0;

        for (; end < size; ++end) {
            auto ch = existedCh.find(s[end]);

            if (ch != existedCh.end()) {
                if(ch->second >= start ) {
                    maxLen = std::max(maxLen, end - start);
                    start = ch->second + 1;
                    ch->second = end;
                }
                else {
                    ch->second = end;
                }
            }
            existedCh.emplace(s[end] , end);
        }

        return std::max(maxLen, end - start);
    }
};
#endif

// 4. Median of two arrays
#ifdef MEDIAN_TWO_ARR
class Solution {
public:
    double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2) {
        const size_t size = nums1.size() + nums2.size();
        uint32_t idx = size / 2;

        std::vector<int32_t> genNums(idx + 1);

        auto it = genNums.begin();

        uint32_t size1 = nums1.size();
        uint32_t size2 = nums2.size();

        int i = 0, j = 0;
        while (i != size1 && j != size2 && (i + j) <= idx) {
            if (nums1[i] < nums2[j])
                *it = nums1[i++];
            else
                *it = nums2[j++];

            ++it;
        }


        for (; j < size2 && (i + j) <= idx; ++it)
            *it = nums2[j++];

        for (; i < size1 && (i + j) <= idx; ++it)
            *it = nums1[i++];


        double median;


        if (size % 2 == 0)
            median = static_cast<double> (genNums[idx] + genNums[idx - 1]) / 2;
        else
            median = genNums[idx];


        return median;
    }
};
#endif


// 5. Longest Palindromic Substring
#ifdef LONGEST_PALINDROMIC
class Solution {
private:
    uint16_t max = 0;
    uint16_t idx = 0;
public:

    inline void checkPalindrome(uint16_t start, uint16_t end, std::string& str) {

        uint16_t size = str.size() - 1;

        while (true) {

            if (str[start] != str[end]){
                ++start;
                --end;
                break;
            }
            if (start == 0) {
                break;
            }
            if (end == size) {
                break;
            }
            --start;
            ++end;
        }

        if(end - start + 1 > max) {
            max = end - start + 1;
            idx = start;
        }
    }

    std::string longestPalindrome(std::string str) {

        uint16_t size = str.size() - 1;

        uint16_t start = 0, end = 0;

        for (uint16_t i = 1; i <= size; ++i) {
            if (str[i - 1] == str [i + 1])
                checkPalindrome(i - 1, i + 1, str);
            if (str[i] == str[i - 1])
                checkPalindrome(i - 1, i, str);
        }

        return std::string(str.substr(idx,max));
    }
};
#endif

int main() {

    return 0;
}

