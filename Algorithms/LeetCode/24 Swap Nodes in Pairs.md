```
class Solution:
    def swapPairs(self, head: ListNode) -> ListNode:

        cur = head
        while cur and cur.next:
            temp = cur.val
            cur.val = cur.next.val
            cur.next.val = temp
            cur = cur.next.next
        return head
```
