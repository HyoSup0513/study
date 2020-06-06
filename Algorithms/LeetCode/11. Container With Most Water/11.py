class Solution:
    def maxArea(self, height: List[int]) -> int:
        vol = 0
        largestvol = 0
        end = len(height)-1
        start = 0
        while start < end:
            if height[start] < height[end]:
                vol = height[start] * (end-start)
                start += 1
            else:
                vol = height[end] * (end-start)
                end -= 1
            if vol > largestvol:
                largestvol = vol
        return largestvol