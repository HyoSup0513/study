```
class Solution:
    def letterCombinations(self, digits: str) -> List[str]:
        if len(digits) == 0:
            return []
        table = {2:"abc", 3:"def", 4:"ghi", 5:"jkl",6:"mno",7:"pqrs",8:"tuv",9:"wxyz"}
        result = []
        self.findcomb(digits, table, result, cur_str='', cur_length=0)
        return result

    def findcomb(self, digits, table, result, cur_str, cur_length,coun):

        if cur_length == len(digits):
            result.append(cur_str)

            return
        for i in table[int(digits[cur_length])]:
            self.findcomb(digits, table, result, cur_str+i, cur_length+1, coun)
```
