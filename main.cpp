#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <string>
#include <unordered_set>
#include <array>
#include <cstdlib>
#include <cmath>

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

// 6.Zigzag Conversion
#ifdef ZIG_ZAG
class Solution {
public:
    std::string convert(std::string s, int numRows) {

        if(numRows == 1) return s;

        std::vector<std::string> rows(numRows);

        bool isDown = true;
        uint16_t i = 0;

        uint8_t pick = numRows - 1;

        for (auto ch : s) {
            if(isDown)
                rows[i++].push_back(ch);
            else
                rows[i--].push_back(ch);

            if (i == 0 || i == pick)
                isDown = !isDown;

        }

        std::string res;

        for (auto& str : rows) {
            res += str;
        }

        return res;
    }
};
#endif

// 7. Reverse Integer
#ifdef REVERSE_INTEGER
class Solution {
public:
    int reverse(int x) {
        int res = 0;

        int maxIntDivTen = INT_MAX / 10;
        int minIntDivTen = INT_MIN / 10;

        int8_t mod = 0;

        while (x != 0) {
            mod = x % 10;

            x /= 10;

            if (res > maxIntDivTen || (res == maxIntDivTen && mod > 7)) return 0;
            if (res < minIntDivTen || (res == minIntDivTen && mod < -8)) return 0;

            res = res * 10 + mod;
        }

        return res;
    }
};
#endif

// 8. String to Integer (atoi)
#ifdef STR_TO_INT_ATOI
class Solution {
public:
    int myAtoi(std::string s) {

        int32_t maxIntDivTen = INT_MAX / 10;
        int32_t minIntDivTen = INT_MIN / 10;

        int32_t res = 0;
        uint8_t idx = 0;

        uint8_t size = s.size();

        while (s[idx] == ' ' && idx != size) ++idx;

        int8_t negativeCoef = 1;

        if(idx == size) return 0;
        else if (s[idx] == '-') {negativeCoef = -1; ++idx;}
        else if (s[idx] == '+') {++idx;}

        if (s[idx] < '0' || s[idx] > '9') return 0;

        uint8_t mod = 0;

        while (s[idx] >= '0' && s[idx] <= '9') {

            mod = s[idx] - '0';

            if (res > maxIntDivTen || (res == maxIntDivTen && mod > 7)) return INT_MAX;
            if (res < minIntDivTen || (res == minIntDivTen && mod > 8)) return INT_MIN;

            res = res * 10 + mod * negativeCoef;

            ++idx;
        }

        return res;
    }
};
#endif

//9. Palindrome Number
#ifdef PALINDROME_NUMBER
class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0) return false;

        std::string strX (std::to_string(x));

        uint32_t start = 0, end = 0;

        uint32_t size = (strX.size() - 1);

        uint32_t mid =  size / 2;

        if (strX.size() % 2 == 0) {start = mid; end = mid + 1;}
        else {start = mid; end = mid;}

        while (start >= 0 && end <= size) {
            if (strX[start] != strX[end]) break;
            --start;
            ++end;
        }

        if (start < 0 || end > size) return true;
        else return false;
    }
};
#endif

// 10. Regular Expression Matching
#ifdef REGULAR_EXPRESSION
class Solution {
public:
    bool isMatch(std::string s, std::string p) {
        bool matched = true;

        uint32_t sizeP = p.size();
        uint32_t sizeS = s.size();


        uint32_t idxP = 0, idxS = 0;
        for (; idxP < sizeP && idxS < sizeS; ++idxP, ++idxS) {

            if (p[idxP] >= 'a' && p[idxP] <= 'z' && p[idxP + 1] == '*') {
                while (s[idxS] == p[idxP] && s[idxS] != '\0')
                    ++idxS;
                ++idxP;
                --idxS;
                continue;
            }

            if (p[idxP] == '.')
                if (s[idxS] < 'a' || s[idxS] > 'z') {
                    matched = false;
                    break;
                }
            else if (p[idxP] >= 'a' && p[idxP] <= 'z') {
                if (s[idxS] != p[idxP]) {
                    matched = false;
                    break;
                }
            }
        }

        if (idxS < sizeS || idxP < sizeP) matched = false;

        return matched;
    }
};
#endif

// 11. Container With Most Water
#ifdef MOST_WATER
class Solution {
public:
    int maxArea(std::vector<int>& height) {

        uint32_t size = height.size();

        uint32_t start = 0, end = size - 1;

        uint32_t maxSquare = 0;

        for (uint32_t i = 0; i < size; ++i) {
            uint32_t curHeight = std::min(height[start], height[end]);

            if (curHeight * (end - start) > maxSquare)
                maxSquare = curHeight * (end - start);

            if (height[start] <= height[end]) ++start;
            else --end;

        }

        return maxSquare;
    }
};
#endif

//12. Integer to Roman
#ifdef INT_TO_ROMAN
class Solution {
public:
    std::string intToRoman(int num) {

        std::string res;

        std::vector<std::pair<int, std::string>> romanianNums {{1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"}, {100, "C"}, {90, "XC"}, {50, "L"},
                                                               {40, "XL"}, {10, "X"}, {9, "IX"}, {5, "V"}, {4, "IV"}, {1, "I"}};


        for (auto& el : romanianNums) {
            while (num - el.first >= 0) {
                num -= el.first;
                res += el.second;
            }
        }

        return res;
    }
};
#endif


//13. Roman to Integer
#ifdef ROMAN_TO_INT
class Solution {
public:
    int romanToInt(std::string s) {
        std::unordered_map<char, uint16_t> romanianNums {{'M', 1000}, {'D', 500}, {'C', 100,},
                                                         {'L', 50}, {'X', 10}, {'V', 5}, {'I', 1}};

        uint8_t size = s.size();
        uint32_t res = 0;

        for (uint8_t i = 0; i < size; ++i) {
            if (romanianNums[s[i]] < romanianNums[s[i + 1]]) {
                res += romanianNums[s[i + 1]] - romanianNums[s[i]];
                ++i;
            }
            else {
                res += romanianNums[s[i]];
            }
        }
        return res;
    }
};
#endif

// 14. Longest Common Prefix
#ifdef LONGEST_PREFIX
class Solution {
public:
    std::string longestCommonPrefix(std::vector<std::string>& strs) {
        size_t strsSize = strs.size() - 1;

        std::string prefix = strs[0];

        for (uint8_t i = 1; i < strsSize; ++i) {
            uint8_t j = 0;

            uint8_t prefixSize = prefix.size();

            while (prefix[j] == strs[i][j] && j != prefixSize) ++j;
            prefix = prefix.substr(0, j);
        }
        return prefix;
    }
};
#endif

// 15. 3Sum
#ifdef THREE_SUM
class Solution {
public:
    std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {
        std::sort(nums.begin(), nums.end());

        std::vector<std::vector<int>> res;

        uint16_t size = nums.size() - 1;

        for (uint16_t i = 0; i < size; ++i) {
            uint16_t start = i + 1;
            uint16_t end = size;

            while (start < end) {
                if (end == i) break;

                int32_t sum = nums[start] + nums[i] + nums[end];

                if (sum == 0 && start != i && end != i) {
                    res.push_back({{nums[i], nums[start], nums[end]}});
                    int32_t prev = nums[start];
                    while(nums[start] == prev && start < end) ++start;
                }
                else if (sum < 0)
                    ++start;
                else if (sum > 0)
                    --end;
            }
            int32_t prev = nums[i];

            while(nums[i + 1] == prev && (i + 1) != size) ++i;
        }
        return res;
    }
};
#endif

class Solution {
public:
    int threeSumClosest(std::vector<int>& nums, int target) {

        std::sort(nums.begin(), nums.end());

        int32_t closetSum = 20000;


        uint16_t size = nums.size() - 1;

        for (uint16_t i = 0; i < size; ++i) {
            uint16_t start = i + 1;
            uint16_t end = size;

            while (start < end) {
                int32_t sum = nums[start] + nums[i] + nums[end];

                if (sum == target)
                    return closetSum;
                if (abs(target - sum) < abs(target - closetSum)) {
                    closetSum = sum; ++start;
                }
                else if (sum < target)
                    ++start;
                else
                    --end;
            }
        }
        return closetSum;
    }
};

int main() {

std::vector<int> d = {833,736,953,-584,-448,207,128,-445,126,248,871,860,333,-899,463,488,-50,-331,903,575,265,162,-733,648,678,549,579,-172,-897,562,-503,-508,858,259,-347,-162,-505,-694,300,-40,-147,383,-221,-28,-699,36,-229,960,317,-585,879,406,2,409,-393,-934,67,71,-312,787,161,514,865,60,555,843,-725,-966,-352,862,821,803,-835,-635,476,-704,-78,393,212,767,-833,543,923,-993,274,-839,389,447,741,999,-87,599,-349,-515,-553,-14,-421,-294,-204,-713,497,168,337,-345,-948,145,625,901,34,-306,-546,-536,332,-467,-729,229,-170,-915,407,450,159,-385,163,-420,58,869,308,-494,367,-33,205,-823,-869,478,-238,-375,352,113,-741,-970,-990,802,-173,-977,464,-801,-408,-77,694,-58,-796,-599,-918,643,-651,-555,864,-274,534,211,-910,815,-102,24,-461,-146};

    int res;


    std::string test ("DXI");
    int num = 583;
    Solution sol;
    res = sol.threeSumClosest(d, -2960);
    //std::cout << res;

    return 0;
}

