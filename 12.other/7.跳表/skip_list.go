package main

import (
	"math/rand"
	"time"
)

/*
	单链表的查找时间复杂度为 O(n)，跳表就是在单链表上构建索引层，采用二分查找的思想来快速检索数据。
	跳表查找的时间复杂度：O(logn)，和二分查找相同。
	跳表的空间消耗：O(n)
*/
/*
	题目：leetcode 1206
		不使用任何库函数，设计一个跳表。
		跳表是在 O(log(n)) 时间内完成增加、删除、搜索操作的数据结构。
		跳表相比于树堆与红黑树，其功能与性能相当，并且跳表的代码长度相较下更短，其设计思想与链表相似。

		跳表中有很多层，每一层是一个短的链表。
		在第一层的作用下，增加、删除和搜索操作的时间复杂度不超过 O(n)。
		跳表的每一个操作的平均时间复杂度是 O(log(n))，空间复杂度是 O(n)。

		在本题中，你的设计应该要包含这些函数：
			bool search(int target) : 返回target是否存在于跳表中。
			void add(int num): 插入一个元素到跳表。
			bool erase(int num): 在跳表中删除一个值，如果 num 不存在，直接返回false.
								如果存在多个 num ，删除其中任意一个即可。

		注意，跳表中可能存在多个相同的值，你的代码需要处理这种情况。
*/

const (
	maxLevel   = 16 // 最大层级
	p          = 0.25
	ERROR_CODE = -43962200
)

type Skiplist struct {
	head  *node // 头节点，每一层都有头节点，即 head 节点中的 len(next) 等于 level
	level int   // 当前跳表中有多少层
}

type node struct {
	key   int     // 每层的单链表是按照 key 来排序的
	value int     // key 对应的 value 值，在 zset 中，分数就是 key。
	next  []*node // 指向下一个节点的指针，这是一个数组，因为一个节点可能出现在多个层级上
}

func newNode(key, value int, level int) *node {
	return &node{
		key:   key,
		value: value,
		next:  make([]*node, level),
	}
}

// 获取随机level
func randomLevel() int {
	level := 1
	for level < maxLevel && rands() < p {
		level++
	}
	return level
}

func rands() float32 {
	rand.Seed(time.Now().UnixNano())
	return rand.Float32()
}

func Constructor() Skiplist {
	return Skiplist{
		head: &node{
			// 直接让 head 有最高等级，就算上面的层级没有数据，那么 head 指向 nil 即可
			next: make([]*node, maxLevel),
		},
	}
}

func (this *Skiplist) Search(target int) bool {
	_, succ := this.search(target)
	return succ
}

func (this *Skiplist) search(target int) (*node, bool) {
	// 从最高层开始从左向右找，从上往下，直到来到最底层
	c := this.head
	for level := this.level - 1; level >= 0; level-- {
		// 在每一层中持续向右遍历，直到下一个节点不存在或者节点的 key 值大于等于 target
		for c.next[level] != nil && c.next[level].key < target {
			// 当前节点在这一层直接向前
			c = c.next[level]
		}
		// 如果当前节点的下一个节点不为空，并且 key 值等于 target，就找到了
		// 否则进入下一层找
		if c.next[level] != nil && c.next[level].key == target {
			return c.next[level], true
		}
	}
	// 找到最下面一层还没有找到则说明元素不存在。
	return nil, false
}

func (this *Skiplist) Add(key int) {
	// 正常来说value应该是传进来的, 即Add(key, value int)
	// 不过 leetcode 中没有用到 value 字段，这里就默认 value 为 1
	value := 1
	/*
		// 先 search 一下这个key存不存在，如果存在，直接更新 value 即可
		// 不过如果允许有重复的key, 下面代码就注释掉

		if node, succ := this.search(key); succ {
			node.value = value
			return
		}
	*/

	c := this.head
	// update用来记录每一层最后一个小于 key 的节点，最后统一处理链接关系
	update := make([]*node, maxLevel)
	for level := this.level - 1; level >= 0; level-- {
		// 从最高层开始，每一层都向右遍历，找到每一层最后一个小于 key 的节点
		for c.next[level] != nil && c.next[level].key < key {
			c = c.next[level]
		}
		// 记录下
		update[level] = c
	}

	// 随机一个层级
	rdmlevel := randomLevel()
	// 如果随机到的level比当前的level要高, 当前最高层级要更新，
	// 并且头节点的 next 指针也要更新
	if rdmlevel > this.level {
		for level := this.level; level < rdmlevel; level++ {
			update[level] = this.head
		}
		this.level = rdmlevel
	}
	e := newNode(key, value, rdmlevel)
	// 处理每一层的情况
	// o->last => o->update->last
	for level := 0; level < rdmlevel; level++ {
		e.next[level] = update[level].next[level]
		update[level].next[level] = e
	}
}

func (this *Skiplist) Erase(target int) bool {
	// 先 search 一下key等于target的节点存不存在，不存在，直接返回
	if _, succ := this.search(target); !succ {
		return false
	}

	c := this.head
	update := make([]*node, maxLevel)
	for level := this.level - 1; level >= 0; level-- {
		// 从最高层开始，每一层都向右遍历，找到每一层等于 target 的节点的前一个节点
		for c.next[level] != nil && c.next[level].key < target {
			c = c.next[level]
		}
		update[level] = c
	}
	// 此时 c.next[0] 指向的是最下面一层，key等于 target 的节点，即要被删除的元素
	c = c.next[0]
	if c == nil || c.key != target {
		return false
	}

	// 处理每一层的情况
	for level := 0; level < this.level; level++ {
		// o->update->last => o->last
		if update[level].next[level] != c {
			break
		}
		update[level].next[level] = c.next[level]
	}

	// 更新层级 level
	for this.level > 1 && this.head.next[this.level-1] == nil {
		this.level--
	}
	return true

}

func main() {

}
