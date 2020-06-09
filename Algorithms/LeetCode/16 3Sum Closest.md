```
class Solution:
    def threeSumClosest(self, nums: List[int], target: int) -> int:

        length = len(nums)
        nums.sort()
        closest = sys.maxsize

        for i in range(length) :
            if i > 0 and nums[i] == nums[i-1] :
                continue

            left, right = i+1, length-1

            while left < right :
                s = nums[i] + nums[left] + nums[right]

                if abs(target-s) < abs(target-closest):
                    closest = s

                if s > target:
                    right -= 1
                else:
                    left += 1
        return closest
```
