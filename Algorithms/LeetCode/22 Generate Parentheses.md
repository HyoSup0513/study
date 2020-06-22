```
class Solution:

    def generateParenthesis(self, n: int) -> List[str]:

        str = []
        def generate(left, right, comb):
            if left == 0 and right == 0:
                str.append(comb)
                return
            if left > 0:
                generate(left-1, right, comb+"(")
            if right > 0 and left < right:
                generate(left, right-1, comb+")")
        generate(n,n, "")
        return str
```
